#ifndef __LAOMD_MAP_H_
#define __LAOMD_MAP_H_
#include <algorithm>
#include <bits/stl_tree.h>
#include <functional>
#include <initializer_list>

template <typename K, typename V, typename Compare = std::less<K>>
class Map {
public:
	using value_type = std::pair<const K, V>;
private:
	using RbTree = std::_Rb_tree<K, value_type, std::_Select1st<value_type>, Compare>;
public:
	using key_type = typename RbTree::key_type;
	using mapped_type = V;
	using reference = mapped_type&;
	using const_reference = const mapped_type&;
	using size_type = typename RbTree::size_type;
	using iterator = typename RbTree::iterator;
	using const_iterator = typename RbTree::const_iterator;
	using reverse_iterator = typename RbTree::reverse_iterator; 
	using const_reverse_iterator = typename RbTree::const_reverse_iterator; 
	using self = Map;
	 
//	constructors
	Map() : _tree() {}
	template <typename InputIterator>
	Map(InputIterator first, InputIterator last) : _tree() { insert(first, last); }
	Map(std::initializer_list<key_type> _l) : Map(_l.begin(), _l.end()) {} 
	Map(const self& other) : _tree(other._tree) {}
	Map(self&& other) : _tree(std::move(other._tree)) {}
	
//	operator=
    self& operator=(const self& other) { _tree = other._tree; return *this;}
    self& operator=(self&& other) {	_tree = std::move(other._tree); return *this; }
	self& operator=(std::initializer_list<key_type> _l) { return *this = std::move(self(_l)); }
	
//	capacity
    size_type size() const { return _tree.size(); }
    bool empty() const { return _tree.empty(); }
    size_type max_size() const { return _tree.max_size(); }
    
//  iterators
    iterator begin() { return _tree.begin(); }
    iterator end() { return _tree.end(); }
    reverse_iterator rbegin() { return _tree.rbegin(); }
    reverse_iterator rend() { return _tree.rend(); }
    const_iterator begin() const { return _tree.begin(); }
    const_iterator end() const { return _tree.end(); }
    const_reverse_iterator rbegin() const { return _tree.rbegin(); }
    const_reverse_iterator rend() const { return _tree.rend(); }
    
//  elements access
    reference operator[](const key_type& key) {
        return (insert(value_type(key, mapped_type())).first)->second;
	}
	const_reference operator[](const key_type& key) const {
	    return (insert(value_type(key, mapped_type())).first)->second;
	}
	reference at(const key_type& key) {
    	
	}
	const_reference at(const key_type& key) const {
	    
	}
//  modifiers
    std::pair<iterator, bool> insert(const value_type& item) {
   	    return _tree._M_insert_unique(item);
	}
	void insert(iterator position, const value_type& item) {
		_tree._M_insert_unique(position, item);
	}
	void insert(std::initializer_list<value_type> __list) { 
	    insert(__list.begin(), __list.end()); 
	}
	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last) {
//		_tree._M_insert_unique(first, last);
		std::for_each(first, last, [&](const key_type& key) {
			(*this)[key];
		});
	}
	void erase(iterator position) { _tree.erase(position); }
	size_type erase(const key_type& key) { return _tree.erase(key); }
	void erase(iterator first, iterator last) { _tree.erase(first, last); }
	void swap(self& other) { _tree.swap(other._tree); }
	void clear() { _tree.clear(); }
	
//	observers
    Compare key_comp() const { return _tree.key_comp(); }
	
//	operations
    iterator find(const key_type& key) { return _tree.find(key); }
    const_iterator find(const key_type& __x) const { return _tree.find(__x); }
	size_type count(const key_type& key) const { return find(key) == end() ? 0 : 1; }
	iterator lower_bound(const key_type& key) { return _tree.lower_bound(key); }
	const_iterator
      lower_bound(const key_type& __x) const
      { return _tree.lower_bound(__x); }
	iterator upper_bound(const key_type& key) { return _tree.upper_bound(key); }
	const_iterator
      upper_bound(const key_type& __x) const
      { return _tree.upper_bound(__x); }

	std::pair<iterator, iterator> equal_range(const key_type& key) { return _tree.equal_range(key); } 
	std::pair<const_iterator, const_iterator>
      equal_range(const key_type& __x) const
      { return _tree.equal_range(__x); }
private:
	RbTree _tree;
};
#endif 

