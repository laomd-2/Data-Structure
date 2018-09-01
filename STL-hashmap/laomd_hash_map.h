#ifndef _UNORDERED_MAP_H
#define _UNORDERED_MAP_H

#include <initializer_list>
#include <memory>
#include <functional>
#include <bits/hashtable.h>

template<typename K, typename V, typename Hash = std::hash<K>, typename Pred = std::equal_to<K>>
class HashMap
{
	typedef K key_type;
	typedef V mapped_type;
	typedef std::pair<const key_type, V> value_type;
	typedef std::_Hashtable<key_type, value_type, std::allocator<value_type>,
				std::__detail::_Select1st, Pred, Hash,
				std::__detail::_Mod_range_hashing,
				std::__detail::_Default_ranged_hash,
				std::__detail::_Prime_rehash_policy, 
				std::__detail::_Hashtable_traits<
				    std::__cache_default<key_type, Hash>::value, 
				    false, true>
				> 
	    HashTable;
    HashTable _htable;
public:
	typedef typename HashTable::hasher          hasher;
	typedef typename HashTable::key_equal		key_equal;
	typedef typename HashTable::allocator_type 	allocator_type;
	typedef typename HashTable::iterator		iterator;
	typedef typename HashTable::const_iterator	const_iterator;
	typedef typename HashTable::size_type		size_type;
	
	explicit HashMap(size_type n = 10) : _htable(n, hasher(), key_equal(), allocator_type()) {}
	
	template<typename _InputIterator>
	HashMap(_InputIterator first, _InputIterator last, size_type n = 0)
	  	: _htable(first, last, n, hasher(), key_equal(), allocator_type()){}
	  
	HashMap(const HashMap&) = default;
	HashMap(HashMap&&) = default;
	
	HashMap(std::initializer_list<value_type> __l, size_type n = 0)
	  	: _htable(__l, n, hasher(), key_equal(), allocator_type()) {}

	// assignment operator.
	HashMap& operator=(const HashMap&) = default;
	HashMap& operator=(HashMap&&) = default;
	HashMap& operator=(std::initializer_list<value_type> __l)
	{
	  	_htable = __l;
	  	return *this;
	}
	
	// operator []
	mapped_type& operator[](const key_type& key) {
		return insert(value_type(key, mapped_type())).first->second;
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
	void insert(_InputIterator first, _InputIterator last) { _htable.insert(first, last); }
	
	void insert(std::initializer_list<value_type> __l) { _htable.insert(__l); }
	
	iterator erase(const_iterator position) { return _htable.erase(position); }
	iterator erase(iterator it) { return _htable.erase(it); }
	iterator erase(const_iterator first, const_iterator last)
	{ return _htable.erase(first, last); }
	
	size_type erase(const key_type& __x) { return _htable.erase(__x); }
	
	void clear() noexcept { _htable.clear(); }
	void swap(HashMap& __x) { _htable.swap(__x._htable); }
	
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
