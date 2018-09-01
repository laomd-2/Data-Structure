#ifndef _UNORDERED_SET_H
#define _UNORDERED_SET_H

#include <initializer_list>
#include <memory>
#include <functional> // equal_to, _Identity
#include <bits/hashtable.h>

template<typename _Value, typename _Hash = std::hash<_Value>, typename _Pred = std::equal_to<_Value>>
class HashSet
{
	typedef std::_Hashtable<_Value, _Value, std::allocator<_Value>,
				std::__detail::_Identity, _Pred, _Hash,
				std::__detail::_Mod_range_hashing,
				std::__detail::_Default_ranged_hash,
				std::__detail::_Prime_rehash_policy, 
				std::__detail::_Hashtable_traits<
				    std::__cache_default<_Value, _Hash>::value, true, true>
				> 
	    HashTable;
    HashTable _htable;
public:
	typedef typename HashTable::key_type	key_type;
	typedef typename HashTable::value_type	value_type;
	typedef typename HashTable::hasher	hasher;
	typedef typename HashTable::key_equal	key_equal;
	typedef typename HashTable::allocator_type allocator_type;
	typedef typename HashTable::iterator		iterator;
	typedef typename HashTable::const_iterator	const_iterator;
	typedef typename HashTable::size_type		size_type;
	
	explicit HashSet(size_type __n = 10) : _htable(__n, hasher(), key_equal(), allocator_type()) {}
	
	template<typename _InputIterator>
	HashSet(_InputIterator __f, _InputIterator __l, size_type __n = 0)
	  : _htable(__f, __l, __n, hasher(), key_equal(), allocator_type()){}
	  
	HashSet(const HashSet&) = default;
	HashSet(HashSet&&) = default;
	
	HashSet(std::initializer_list<value_type> __l, size_type __n = 0)
	  : _htable(__l, __n, hasher(), key_equal(), allocator_type()) {}

//	assignment operator.
	HashSet& operator=(const HashSet&) = default;
	HashSet& operator=(HashSet&&) = default;
	HashSet& operator=(std::initializer_list<value_type> __l)
	{
	  _htable = __l;
	  return *this;
	}
	
	// size and capacity:
	bool empty() const noexcept { return _htable.empty(); }
	size_type size() const noexcept { return _htable.size(); }
	size_type max_size() const noexcept { return _htable.max_size(); }
	
	// iterators.
	iterator begin() noexcept { return _htable.begin(); }
	iterator end() noexcept { return _htable.end(); }
	const_iterator begin() const noexcept { return _htable.begin(); }
	const_iterator end() const noexcept { return _htable.end(); }
	
	std::pair<iterator, bool> insert(const value_type& __x)
	{ return _htable.insert(__x); }

	template<typename _InputIterator>
	void insert(_InputIterator __first, _InputIterator __last) { _htable.insert(__first, __last); }
	
	void insert(std::initializer_list<value_type> __l) { _htable.insert(__l); }
	
	iterator erase(const_iterator __position) { return _htable.erase(__position); }
	iterator erase(iterator __it) { return _htable.erase(__it); }
	iterator erase(const_iterator __first, const_iterator __last)
	{ return _htable.erase(__first, __last); }
	
	size_type erase(const key_type& __x) { return _htable.erase(__x); }
	
	void clear() noexcept { _htable.clear(); }
	void swap(HashSet& __x) { _htable.swap(__x._htable); }
	
	// lookup.
	iterator find(const key_type& __x) { return _htable.find(__x); }
	const_iterator find(const key_type& __x) const { return _htable.find(__x); }
	
	size_type count(const key_type& __x) const { return _htable.count(__x); }
	
	std::pair<iterator, iterator> equal_range(const key_type& __x) 
	{ return _htable.equal_range(__x); }
	
	std::pair<const_iterator, const_iterator> equal_range(const key_type& __x) const 
	{ return _htable.equal_range(__x); }
};
#endif
