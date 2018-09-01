#ifndef __LAOMD_HEAP_H_
#define __LAOMD_HEAP_H_
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <vector>

template <typename T>
class HeapIterator {
public:
	using value_type = T;
	using const_reference = const T&;
	using pointer = typename std::vector<value_type>::const_iterator;
	using self = HeapIterator;
	 
	explicit HeapIterator(pointer cur = pointer()) : _cur(cur) {}
	bool operator==(const self& other) const {
	    return _cur == other._cur;
	} 
	bool operator!=(const self& other) const {
	    return _cur != other._cur;
	}
	self operator++() {
		++_cur;
		return *this;
	} 
	self operator++(int) {
		self tmp = *this;
		++(*this);
		return tmp;
	}
	self operator--() {
		--_cur;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
	    --(*this);
		return tmp; 
	}
	const_reference operator*() const {
	    return *_cur;
	}
	pointer operator->() const {
	    return _cur;
	}
private:
	pointer _cur;
};

template <typename T>
class HeapReverseIterator : public HeapIterator<T> {
public:
	using Base = HeapIterator<T>;
	using value_type = typename Base::value_type;
	using const_reference = typename Base::const_reference;
	using pointer = typename std::vector<value_type>::const_reverse_iterator;
	using self = HeapReverseIterator;
	
	HeapReverseIterator(pointer cur = pointer()) : Base(Base::pointer(cur)) {}
    self operator++() {
		return Base::operator--();
	} 
	self operator++(int) {
		self tmp = *this;
		++(*this);
		return tmp;
	}
	self operator--() {
		return Base::operator++();
	}
	self operator--(int) {
		self tmp = *this;
	    --(*this);
		return tmp; 
	}
}; 

template <typename T, typename Compare = std::less<T>>
class Heap {
public:
	using container_type = std::vector<T>;
	using value_type = typename container_type::value_type;
	using size_type = typename container_type::size_type;
	using reference = typename container_type::reference;
	using const_reference = typename container_type::const_reference;
	using iterator = HeapIterator<value_type>;
	using reverse_iterator = HeapReverseIterator<value_type>;
	using self = Heap;
	
//	constructors
    Heap() :_data(), comp() {}
    template <typename InputIterator>
	Heap(InputIterator first, InputIterator last) : _data(first, last), comp() {
		std::make_heap(_data.begin(), _data.end(), comp);
	} 
	Heap(std::initializer_list<value_type> _list) : Heap(_list.begin(), _list.end()) {}
	
//	operator=
    self& operator=(const self& other) { _data = other._data; }
	self& operator=(self&& other) { clear(); swap(other); }
	self& operator=(std::initializer_list<value_type> _list) {
	    _data.assign(_list);
	    std::make_heap(_data.begin(), _data.end(), comp);
	}
	
//	iterators
    iterator begin() const { return iterator(_data.begin()); }
    iterator end() const { return iterator(_data.end()); }
    reverse_iterator rbegin() const { return reverse_iterator(_data.rbegin()); }
    reverse_iterator rend() const { return reverse_iterator(_data.rend()); }
	
//	capacity
    size_type size() const { return _data.size(); }
    bool empty() const { return _data.empty(); }
    size_type max_size() const { return _data.max_size(); }
    
//  modifiers
    void push(const value_type& val) {
    	_data.push_back(val);
    	std::push_heap(_data.begin(), _data.end(), comp);
	}
	value_type pop() {
		value_type result = _data.at(0);
		std::pop_heap(_data.begin(), _data.end(), comp);
		_data.pop_back();
		return result;
	}
	void swap(self& other) {
		std::swap(_data, other._data);
	} 
	void clear() { _data.clear(); }
//	element access 
	const_reference top() const {
	    return _data.at(0);
	}
private:
	container_type _data; 
	Compare comp;
}; 
#endif 
