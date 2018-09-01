#ifndef HASH_SET_H
#define HASH_SET_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include "test.h"
using namespace std;

template<typename T, typename HasherType = hash<T>>
class HashSet {
private:
	std::vector<std::list<T>> buckets;
	HasherType hasher;
public:
	using iterator = typename std::list<T>::iterator;
	using const_iterator = typename std::list<T>::const_iterator;
	using size_type = unsigned;
public:
	HashSet(size_type bucketCount = 17, 
			const HasherType& h = HasherType()) 
		: buckets(bucketCount), hasher(h) {

	}

	template<typename InputIterator>
	HashSet(InputIterator begin, 
			InputIterator end,
			size_type bucketCount = 13, 
			const HasherType& h = HasherType()) 
		: buckets(bucketCount), hasher(h) {

	}

	bool empty() const {
		for(const auto& bucket : buckets) {
			if (!bucket.empty())
			{
				return false;
			}
		}
		return true;
	}

	size_type size() const {
		size_type cnt = 0;
		for(const auto& bucket : buckets) {
			cnt += bucket.size();
		}
		return cnt;
	}

	const_iterator find(const T& value) const {
		const auto& bucket = buckets[bucket(value)];
		const_iterator it = bucket.cbegin();
		const_iterator e = bucket.cend();

		while(it != e) {
		    if (*it == value)
		    {
		    	return it;
		    }
		    it++;
		}
		return cend();
	}

	iterator find(const T& value) {
		auto& theBucket = buckets[bucket(value)];
		iterator it = theBucket.begin();
		iterator e = theBucket.end();

		while(it != e) {
		    if (*it == value)
		    {
		    	return it;
		    }
		    it++;
		}
		return end();
	}

	iterator end() {
		return buckets.back().end();
	}

	const_iterator cend() const {
		return buckets.back().cend();
	}

	void insert(const T& value) {
		auto& theBucket = buckets[bucket(value)];
		for(const auto& i : theBucket) {
			if (i == value)
			{
				return;
			}
		}
		theBucket.push_back(value);
	}

	void erase(const T& value) {
		buckets[bucket(value)].remove(value);
	}

	void clear() {
		for(auto& theBucket : buckets) {
			theBucket.clear();
		}
	}

	size_type bucket_count() const {
		return buckets.size();
	}

	size_type bucket_size(size_type n) const {
		return buckets.at(n).size();
	}

	size_type bucket(const T& value) {
		return hasher(value) % bucket_count();
	}

	HasherType hash_function() const {
		return hasher;
	}

	template<typename C>
	friend std::ostream& operator<< (std::ostream& output, const HashSet<C>& set) {
		unsigned num = set.bucket_count();
		for(unsigned i = 0; i < num; ++i) {
			const auto& theBucket = set.buckets[i];
			output << "bucket " << i << ": ";
			for(auto& value : theBucket) {
				output << value << ' ';
			}
			output << std::endl;
		}

		return output;
	}
};


#endif // HASH_SET_H
