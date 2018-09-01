#ifndef __LAOMD_SET_H_
#define __LAOMD_SET_H_
#include <functional>
#include <initializer_list>
#include <bits/stl_tree.h>

template <typename T, typename Compare = std::less<T>>
class Set {
public:
	using RbTree = std::_Rb_tree<T, T, std::_Identity<T>, Compare>;
	using value_type = typename RbTree::value_type;
	using size_type = typename RbTree::size_type;
	using reference = value_type&;
	using const_reference = const value_type&;
	using iterator = typename RbTree::const_iterator; 
	using reverse_iterator = typename RbTree::const_reverse_iterator;
	using self = Set;
	
//	constructors
    Set() : _tree() {}
	template <typename InputIterator>
	Set(InputIterator first, InputIterator last) : _tree() {
	    _tree._M_insert_unique(first, last);
	}
	Set(std::initializer_list<value_type> _l) : Set(_l.begin(), _l.end()) {}
	Set(const self& other) : _tree(other._tree) {}
	Set(self&& other) noexcept : _tree(std::move(other._tree)) {}
	
//	destructor
    ~Set() = default;
    
//  operator=
    Set& operator=(const self& other)
    {
	    _tree = other._tree;
	    return *this;
    }
    Set& operator=(self&& other)
    {
	    clear();
	    swap(other);
	    return *this;
    }
    Set& operator=(std::initializer_list<value_type> __l)
    {
	    clear();
	    insert(__l.begin(), __l.end());
	    return *this;
    }	
//	iterators
    iterator begin() const { return _tree.begin(); }
	iterator end() const { return _tree.end(); }
	reverse_iterator rbegin() const { return _tree.rbegin(); }
	reverse_iterator rend() const { return _tree.rend(); }
	
//	capacity
    size_type size() const { return _tree.size(); }
    bool empty() const { return _tree.empty(); }
    size_type max_size() const { return _tree.max_size(); }
    
//  modifiers
    std::pair<iterator, bool> insert(const value_type& val) { 
	    auto __p = _tree._M_insert_unique(val);
	    return std::pair<iterator, bool>(__p.first, __p.second);
    }
	iterator insert(iterator position, const value_type& val) {	return _tree.insert_unique(position, val); }
	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last) { _tree.insert_unique(first, last); }
	void insert(std::initializer_list<value_type> __l) { insert(__l.begin(), __l.end()); }
	iterator erase(iterator position) {	return _tree.erase(position); }
	iterator erase(iterator first, iterator last) {	return _tree.erase(first, last); }
	size_type erase(const value_type& val) { return _tree.erase(val); }
	void swap(self& other) { _tree.swap(other._tree); }
	void clear() { _tree.clear(); } 
	Compare key_comp() const { return _tree.key_comp(); }
	iterator find(const value_type& val) const { return _tree.find(val); } 
	size_type count(const value_type& val) const { return _tree.find(val) == _tree.end() ? 0 : 1; }
	iterator lower_bound(const value_type& val) const {	return _tree.lower_bound(val); }
	iterator upper_bound(const value_type& val) const { return _tree.upper_bound(val); }
	std::pair<iterator, iterator> equal_range(const value_type& val) const { return _tree.eqaul_range(val); }
private:
	RbTree _tree;
};
#endif

