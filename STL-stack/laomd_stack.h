#ifndef __LAOMD_STACK_H_
#define __LAOMD_STACK_H_
#include <bits/concept_check.h>
#include <algorithm>
#include <deque>

template <typename T, typename Sequence = std::deque<T>>
class Stack {
	__glibcxx_class_requires(T, _SGIAssignableConcept)
	__glibcxx_class_requires(Sequence, _BackInsertionSequenceConcept)
	__glibcxx_class_requires2(T, Sequence::value_type, _SameTypeConcept)
public:
	using value_type = typename Sequence::value_type;	
	using size_type = size_t;
	using reference = T&;
	using const_reference = const T&;
    using container_type = Sequence;
    using self = Stack<T>;
    
//    constructors
    explicit Stack(const container_type& ctnr) : _data(ctnr) {}
	explicit Stack(container_type&& ctnr = container_type()) : _data(std::move(ctnr)) {}
	Stack(const self& other) : _data(other._data) {}
	Stack(self&& other) : _data(std::move(other._data)) {}
//	destructor
    bool empty() const { return _data.empty(); }
	size_type size() const { return _data.size(); }
	
//	access
	reference top() { return _data.back(); }
	const_reference top() const { return _data.back(); }
	
//	modifiers
	void push(const value_type& val) { _data.push_back(val); }
	void pop() { _data.pop_back(); }
	void swap(self& other) noexcept { std::swap(_data, other._data); }
private:
	container_type _data;
};
#endif
