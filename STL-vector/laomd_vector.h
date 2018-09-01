#ifndef __LAOMD_VECTOR_H_
#define __LAOMD_VECTOR_H_
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <memory>

template <typename T>
class Vector {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
	using value_type = T;
	using pointer = value_type*;
	using iterator = value_type*;
	using const_iterator = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	
//  constructors    
	Vector() : _size(0) {
 	   init(0);
	}
	explicit Vector(size_type n) : _size(n) {
        init(n);
	}
	Vector(size_type n, const value_type& val) : Vector(n) {
		assign(n, val);
	}
	template <typename InputIterator>
	Vector(InputIterator first, InputIterator last) : Vector() {
		assign(first, last);
	} 
	Vector(const Vector& other) : Vector() {
		*this = other;
	}
	Vector(Vector&& other) : Vector() {
		*this = std::move(other);
	}
	
//	destructor
	~Vector() {
		clear();
	}
	
//	assign operators
	Vector& operator=(const Vector& other) {
		if (this != &other) {
			clear(); 
			init(other._capacity); 
			_size = other._size;
			std::uninitialized_copy_n(other.begin(), other._size, begin());
		}
		return *this;
	}
	Vector& operator=(Vector&& other) {
		if (this != &other) {
			clear();
			_size = other._size;
			_capacity = other._capacity;
			_data = other._data;
			other.init(0); 
		}
		return *this;
	}
	
//	capacity
	size_type size() const { return _size; }
	bool empty() const { return size() == 0; }
	void resize(size_type new_size, const value_type& val = value_type()) {
		if (new_size > _size) {
			if (new_size > _capacity) {
				reserve(new_size);
			} 
			std::uninitialized_fill_n(end(), new_size - _size, val);
		}
		_size = new_size;
	}
	size_type max_size() const { return size_type(-1); }
	void reserve(size_type new_capacity) {
		if (new_capacity > _capacity) {
			pointer tmp = _data;
			init(new_capacity);
			std::move(tmp, tmp + _size, begin());
			delete[] tmp;
		}
	}
	size_type capacity() const { return _capacity; }
	void shrink_to_fit() {
		if (_capacity > _size) {
			_capacity = 0;
			reserve(_size);
		}
	}
	
//	iterators
	iterator begin() {
		return _data;
	}
	const_iterator begin() const {
	    return _data;
	}
	iterator end() {
		return _data + _size;
	}
	const_iterator end() const {
	    return _data + _size;
	}
//	element access
	reference at(size_type n) {
		if (n < 0 || n >= _size) 
		    throw std::range_error("index out of range");
	    return _data[n];
	}
	const_reference at(size_type n) const {
		if (n < 0 || n >= _size) 
		    throw std::range_error("index out of range");
	    return _data[n];
	}
	reference operator[](size_type n) {
		return at(n);
	}
	const_reference operator[](size_type n) const {
	    return at(n);
	}
	reference front() {
		return at(0);
	}
	const_reference front() const {
	    return at(0);
	}
	reference back() {
		return at(_size - 1);
	}
	const_reference back() const {
	    return at(_size - 1);
	}
	value_type* data() {
		return _data;
	}
	const value_type* data() const {
	    return _data;
	}
	
//	modifiers
    void assign(size_type n, const value_type& val) {
    	if (n > _capacity) {
    		reserve(n);
        }
		std::fill_n(begin(), n, val);
		_size = n;
	}
	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last) {
		difference_type dis = std::distance(first, last);
		if (dis > _capacity) {
			reserve(dis);
		}
		std::copy(first, last, begin());
		_size = dis;
	}
	void push_back(const value_type& val) {
		insert(end(), val);
	}
	void pop_back() {
		erase(end() - 1);
	}
	void insert(iterator position, const value_type& val) {
		insert(position, 1, val);
	}
	void insert(iterator position, size_type n, const value_type& val) {
		if (position - begin() > _size) 
		    throw std::range_error("index out of range");
		if (_size == _capacity){
			reserve(_capacity * 2 + n);
		}
		std::move_backward(position, end(), end() + n);
		std::fill_n(position, n, val);
		_size += n;
	}
	template <typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		if (position - begin() > _size) 
		    throw std::range_error("index out of range");
		    
        difference_type dis = std::distance(first, last);
		if (_size == _capacity){
			reserve(_capacity * 2 + dis);
		}
		std::move_backward(position, end(), end() + dis);
		std::copy(first, last, position);
		_size += dis;
	}
	void erase(iterator position) {
		erase(position, position + 1); 
	}
	void erase(iterator first, iterator last) {
		_size = std::move(last, end(), first) - begin();
	}
	void remove(const value_type& key) {
		_size = std::remove(begin(), end(), key) - begin(); 
	}
	void swap(Vector& other) {
		std::swap(_data, other._data);
		std::swap(_size, other._size);
		std::swap(_capacity, other._capacity);
	}
	template <typename Comp = std::less<T>>
	void sort(const Comp& key_comp = Comp()) {
		std::sort(begin(), end(), key_comp); 
	}
	const_reference lower_bound(const_reference key) const {
	    return *std::lower_bound(begin(), end(), key);
	}
	void unique() {
		_size = std::unique(begin(), end()) - begin();
	}
	template <typename Action>
	void traverse(const Action& action) {
		std::for_each(begin(), end(), action);
	}
	void clear() {
		if (_data) {
			delete[] _data;
		}
		init(0);
	}
	
private:
	void init(size_type n) {
		if (n == 0) {
			_data = nullptr;
			_size = 0;
		}
		else {
			_data = new value_type[n];
		}
		_capacity = n;
	}
	
	pointer _data;
	size_type _size, _capacity;
};
#endif
