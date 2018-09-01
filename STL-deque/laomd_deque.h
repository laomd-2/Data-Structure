#ifndef __LAOMD_DEQUE_H_
#define __LAOMD_DEQUE_H_
#include <memory>
#include <initializer_list>
#include <algorithm>
 
template <typename T, const size_t buffer_size>
class DequeIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T*; 
	using reference = T&;
	using const_reference = const T&;
	using map_type = T**;
	using self = DequeIterator;
	
	DequeIterator(map_type buffer = nullptr, size_type cur = 0) 
        : _buffer(buffer), _cur(cur)  {
	    _buffer += _cur / buffer_size;	
	    _cur %= buffer_size;
	}
	bool operator==(const self& other) const {
		return _buffer == other._buffer && _cur == other._cur;
	}
	bool operator!=(const self& other) const {
	    return !(*this == other);
	}
	self operator++() {
		if (_buffer) {
			++_cur;
			if (_cur >= buffer_size) {
				++_buffer;
				_cur = 0;
			}
		}
		return *this;
	}
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}
	self operator--() {
		if (_buffer) {
			if (_cur == 0u) {
				--_buffer;
				_cur = buffer_size; 
			}
			--_cur;
		}
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
	reference operator*() {
		return *(*_buffer + _cur);
	}
	const_reference operator*() const {
		return *(*_buffer + _cur);
	}
	pointer operator->() const {
        return *_buffer + _cur;
	}
private:
	size_type _cur;
	map_type _buffer;
};
template <typename T, size_t buffer_size = 20u>
class Deque {
public:
	using size_type = size_t; 
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = DequeIterator<T, buffer_size>;
	using map_type = T**;
	using self = Deque;
	
//	constructors
	Deque() {
	    init();
	}
	explicit Deque(size_type n, const value_type& val = value_type()) : Deque() {
        while(n--) push_back(val);
	}
	template <typename InputIterator>
	Deque(InputIterator first, InputIterator last) : Deque() {
		std::for_each(first, last, [&](const value_type& val) {
			push_back(val);
		});
	}
	Deque(std::initializer_list<value_type> _l) : Deque(_l.begin(), _l.end()) {}
	Deque(const self& other) : Deque() {
        *this = other;
	}
	Deque(self&& other) : Deque() {
		*this = std::move(other);
	}
//	destructor
	~Deque() {
		clear();
	}
//	operator=
	self& operator=(const self& other) {
		if (this != &other) {
			iterator first1 = begin(), last1 = end();
			iterator first2 = other.begin(), last2 = other.end();
			while(first1 != last1 && first2 != last2) {
				*first1 = *first2;
				++first1;
				++first2;
			}
			if (first1 != last1) {
			    size_type dis = std::distance(first1, last1);
				while (dis--) pop_back(); 
			}
			else {
				while(first2 != last2) {
				push_back(*first2);
				++first2;
			}
			}
		}
		return *this; 
	}
	self& operator=(self&& other) {
		if (this != &other) {
			clear();
			swap(other);
		}
		return *this;
	}
	self& operator=(std::initializer_list<value_type> _l) {
		*this = std::move(Deque(_l));
	}
//	iterators
	iterator begin() const {
		return start;
	}
	iterator end() const {
	    return finish;
	}
//	capacity
	size_type size() const {
	    return std::distance(start, finish);
	}
	bool empty() const {
	    return start == finish;
	}
	void resize(size_type new_size, const value_type& val = value_type()) {
		size_type current_size = size();
		while (new_size > current_size) {
			push_back(val);
			++current_size;
		}
		while (new_size < current_size) {
			pop_back();
			--current_size;
		}
	}
//	member access
	const_reference front() const {
		return *begin();
	}
	reference front() {
		return *begin();
	}
	const_reference back() const {
	    iterator tmp = end();
	    --tmp;
	    return *tmp;
	}
	reference back() {
		iterator tmp = end();
	    --tmp;
	    return *tmp;
	}
//	modifiers
	void push_back(const value_type& val) {
		if (finish == iterator(_buffer_map + number_of_buffers, 0)) {
			right_extend();
			if (empty()) start = finish = iterator(_buffer_map, 0); 
		}
		*(finish) = val;
		++finish;
	} 
	void push_front(const value_type& val) {
		if (start == iterator(_buffer_map, 0)) {
			left_extend(); 
			if (empty()) start = finish = iterator(_buffer_map, 0);
		}
		*(--start) = val;
	}
	void pop_back() {
		--finish; 
		if (finish == iterator(_buffer_map + number_of_buffers - 1, 0)) {
			right_shrinft();
		}
	}
	void pop_front() {
		++start;
		if (start == iterator(_buffer_map + 1, 0)) {
			left_shrinft();
		}
	}
	void swap(self& other) {
		std::swap(start, other.start);
		std::swap(finish, other.finish);
		std::swap(number_of_buffers, other.number_of_buffers);
		std::swap(_buffer_map, other._buffer_map);
	} 
	void clear() {
		if (_buffer_map) {
			std::for_each(_buffer_map, _buffer_map + number_of_buffers, [](pointer buffer) {
				delete[] buffer;
			});
			delete[] _buffer_map;
			init();
		}
	}
protected:
	void init() {
		_buffer_map = nullptr; 
		number_of_buffers = 0;
		start = finish = iterator();
	}
	void right_extend() {
		map_type tmp = _buffer_map;
		_buffer_map = new pointer[number_of_buffers + 1];
		std::copy_n(tmp, number_of_buffers, _buffer_map);
		_buffer_map[number_of_buffers++] = new value_type[buffer_size]; 
		delete[] tmp;
	}
	void left_extend() {
        map_type tmp = _buffer_map;
		_buffer_map = new pointer[number_of_buffers + 1];
		std::copy_n(tmp, number_of_buffers, _buffer_map + 1);
		_buffer_map[0] = new value_type[buffer_size];
		number_of_buffers++;
		delete[] tmp;
	}
	void right_shrinft() {
		delete[] _buffer_map[--number_of_buffers];
		map_type tmp = _buffer_map;
		if (number_of_buffers == 0) init();
		else {
			_buffer_map = new pointer[number_of_buffers];
			std::copy_n(tmp, number_of_buffers, _buffer_map);
		}
		delete[] tmp;
	}
	void left_shrinft() {
		delete[] _buffer_map[0];
		--number_of_buffers;
		map_type tmp = _buffer_map;
		if (number_of_buffers == 0) init();
		else {
			_buffer_map = new pointer[number_of_buffers];
			std::copy_n(tmp + 1, number_of_buffers, _buffer_map);
		}
		delete[] tmp;
	}
private:
	iterator start;
	iterator finish;
	map_type _buffer_map;
	size_type number_of_buffers;
};
#endif 
