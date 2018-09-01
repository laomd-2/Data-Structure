#ifndef __LAOMD__LIST_H_
#define __LAOMD__LIST_H_
#include <initializer_list>
#include <algorithm>
#include <iterator>
template <typename T>
struct ListNode {
	using value_type = T;
	using self = ListNode;
	value_type _val;
	self* prev;
	self* next;
	ListNode(const value_type& val) 
	    : _val(val), prev(nullptr), next(nullptr) {} 
};

template <typename T>
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
public:
	using value_type = T;
	using link_type = ListNode<T>*;
	using self = ListIterator;
	
    explicit ListIterator(link_type ptr = nullptr) : _node(ptr) {}
    explicit operator link_type () const {
	    return _node;
	}
    bool operator==(const self& other) {
    	return _node == other._node;
	}
	bool operator!=(const self& other) {
		return !(*this == other);
	}
	self operator++() {
		_node = _node->next;
    	return *this;
	}
	self operator++(int) {
		self tmp = *this;
		_node = _node->next;
		return tmp;
	}
	self operator--() {
		_node = _node->prev;
		return *this;
	}
	self operator--(int) {
		self tmp = *this;
		_node = _node->prev;
		return tmp;
	}
	value_type& operator*() {
		return _node->_val;
	}
	const value_type& operator*() const {
	    return _node->_val;
	}
	link_type operator->() {
		return _node;
	}
	link_type operator->() const {
	    return _node;
	}
private: 
    link_type _node;
};

template <typename T>
class List {
public:
	using value_type = T;
	using size_type = size_t;
	using pointer = T*;
	using reference = T&;
	using const_reference = const T&;
	using iterator = ListIterator<T>;
	using link_type = ListNode<T>*;
	using self = List;
	
//	constructors
	List() {
		init();
	}
	explicit List(size_type n) : List(n, value_type()){}
	List(size_type n, const value_type& val) : List() {
		_fill(n, val);
	}
	template <typename InputIterator>
	List(InputIterator first, InputIterator last) : List() {
		_fill(first, last);
	}
	List(std::initializer_list<value_type> _l) : List(_l.begin(), _l.end()) {} 
	List(const self& other) : List() {
		*this = other;
	}
	List(self&& other) : List() {
		*this = std::move(other);
	}
	
//	destructor
	~List() {
		clear();
		delete _head;
	}
//	operator=
	self& operator=(const self& other) {
		if (this != &other) {
			assign(other.begin(), other.end());
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
	List& operator=(std::initializer_list<value_type> __l)
 	{
		assign(__l.begin(), __l.end());
		return *this;
 	}
//	iterators
	iterator begin() {
		return iterator(_head->next);
	}
	iterator begin() const {
        return iterator(_head->next);
	}
	iterator end() {
		return iterator(_head);
	}
	iterator end() const {
	    return iterator(_head);
	}
//	capacity
	size_type size() const {
        return std::distance(begin(), end());
	}
	bool empty() const {
        return _head->next == _head;
	}
	size_type max_size() const {
	    return size_type(-1);
	}
//	element access
	reference front() {
		return *begin();
	}
	const_reference front() const {
	    return *begin();
	}
	reference back() {
		iterator __tmp = end();
		--__tmp;
		return *__tmp;
	}
	const_reference back() const {
	    iterator __tmp = end();
		--__tmp;
		return *__tmp;
	}
//	modifiers
	void assign(size_type n, const value_type& val) {
		iterator first = begin(), last = end();
		while (n && first != last) {
			*first = val;
			++first;
			--n;
		}
		if (n) {
			insert(end(), n, val);
		}
		else {
			erase(first, last);
		}
	}
	void assign(std::initializer_list<value_type> __l) { 
        this->assign(__l.begin(), __l.end());
	}
	template<typename InputIterator>
	void assign(InputIterator first, InputIterator last) {
		iterator cur = begin(), myend = end();
		while (cur != myend && first != last) {
			*cur = *first;
			++first;
			++cur;
		}
		if (first != last) {
			insert(end(), first, last);
		}
		else {
			erase(cur, myend);
		}		
	}
	void push_front(const value_type& val) {
		insert(begin(), val);
	}
	void push_back(const value_type& val) {
		insert(end(), size_type(1), val);
	}
	void pop_front() {
		erase(begin());
	}
	void pop_back() {
		iterator __tmp = end();
		--__tmp;
		erase(__tmp);
	}
	void insert(iterator position, const value_type& val) {
		insert(position, size_type(1), val);
	}
	void insert(iterator position, size_type n, const value_type& val) {
		self __tmp(n, val);
	  	splice(position, __tmp);
	}
	template <typename InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last) {
		self __tmp(first, last);
	  	splice(position, __tmp);
	}
	iterator erase(iterator position) {
		if (position != end()) {
			link_type tmp(position);
			position->prev->next = position->next;
			position->next->prev = position->prev;
			++position;
			delete tmp;
		}
		return position;
	}
	iterator erase(iterator first, iterator last) {
		while (first != last)
	        first = erase(first);
		return last;
	}
	void swap(self& other) {
		std::swap(_head, other._head);
	}
	void resize(size_type n, const value_type& val = value_type()) {
		size_type length = size();
		if (n > length) {
			insert(end(), n - length, val);
		}
		else {
		    iterator cur;
		    if (n > length / 2) {
		    	cur = end();
		    	std::advance(cur, n - length);
			}
			else {
				cur = begin();
				std::advance(cur, n);
			}
			erase(cur, end());
		}
	}
	void clear() {
		erase(begin(), end());
	}
//	operations
	void splice(iterator position, self& x) {
		splice(position, x, x.begin(), x.end());
	}
	void splice(iterator position, self& x, iterator i) {
		splice(position, x, i, x.end());
	}
	void splice(iterator position, self& x, iterator first, iterator last) {
		if (first != last) {
			link_type prev = position->prev;
			link_type tmp = first->prev;
			prev->next = link_type(first);
			first->prev = prev;
			last->prev->next = link_type(position);
			position->prev = last->prev;
			tmp->next = link_type(last);
			last->prev = tmp;
		}
	}
	void remove(const value_type& val) {
		remove_if([&](const value_type& ele) {
			return ele == val;
		});
	}
	template <typename Predicate>
	void remove_if(Predicate pred) {
		iterator cur = begin();
		while(cur != end()) {
			if (pred(*cur)) {
				cur = erase(cur);
			}
			else {
				++cur;
			}
		}
	}
	template <typename BinaryPredicate = std::equal_to<value_type>>
	void unique(BinaryPredicate binary_pred = BinaryPredicate()) {
		iterator cur = begin();
		iterator first = cur;
		++cur;
		while(cur != end()) {
			if (*cur == *first) {
				cur = erase(cur);
			}
			else {
				first = cur;
				++cur;
			}
		}
	}
	void merge(self& x) {
		merge(x, std::less<value_type>());
	}
	template <typename Compare>
	void merge(self& x, Compare comp) {
		iterator first1 = begin(), last1 = end();
		iterator first2 = x.begin(), last2 = x.end();
		link_type cur = _head, tmp;
		while(first1 != last1 && first2 != last2) {
//			link_type tmp(comp(*first1, *first2) ? first1++ : first2++);
			if (comp(*first1, *first2)) {
				tmp = link_type(first1);
				++first1;
			}
			else {
				tmp = link_type(first2);
				++first2;
			}
			cur->next = tmp;
			tmp->prev = cur;
			cur = cur->next;
		}
		if (first2 != last2) {
			cur->next = link_type(first2);
			first2->prev = cur;
			cur = last2->prev;
		}
		cur->next = _head;
		_head->prev = cur; 
		x._head->next = x._head->prev = x._head;
	}
	void reverse() {
		link_type cur = _head;
		do {
			std::swap(cur->next, cur->prev);
			cur = cur->prev;
		}while(cur != _head);
	}
	template <typename Compare = std::less<value_type>>
	void sort(Compare comp = Compare()) {
		
	}
protected:
	link_type getNode(const value_type& val = value_type()) {
		return new ListNode<value_type>(val);
	}
	void init() {
		_head = getNode();
		_head->next = _head->prev = _head;
	} 
	void _fill(size_type n, const value_type& val) {
		link_type cur = _head;
		while(n--) {
			cur->next = getNode(val);
			cur->next->prev = cur;
			cur = cur->next;
		}
		cur->next = _head;
		_head->prev = cur;
	}
	template <typename InputIterator>
	void _fill(InputIterator first, InputIterator last) {
		link_type cur = _head;
		while(first != last) {
			cur->next = getNode(*first);
			cur->next->prev = cur;
			cur = cur->next;
			++first;
		}
		cur->next = _head;
		_head->prev = cur;
	}
private:
	link_type _head;
}; 
#endif
