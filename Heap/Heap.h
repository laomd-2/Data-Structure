#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
using namespace std;

static const unsigned maxSize = 100;

template<typename T, typename Compare = less<T> >
class Heap {
private:
	using size_type = unsigned;
public:
	Heap() : _size(0), 
			data(new T[maxSize]{T()}), 
			comp(Compare()) {
		
	}

	template <class InputIterator>
	Heap(InputIterator b, InputIterator e) : Heap() {
		_size = copy(b, e, data + 1) - (data + 1);

		// using stl/algorithm
		// make_heap(data + 1, data + _size + 1, comp);

		size_type begin = _size / 2;
		while(begin > 0) {

			size_type curPos = begin;
			T tmp = data[curPos];

			size_type s = size();

			while (curPos * 2 <= s) {
				size_type left = curPos * 2;

				if (left + 1 <= s)
				{
					if (comp(data[left], data[left + 1]))
					{
						left++;
					}
				}

				if (comp(tmp, data[left]))
				{
					data[curPos] = data[left];
					curPos = left;
				}
				else
				{
					break;
				}
			}
			data[curPos] = tmp;
		    begin--;
		}
	}

	Heap(const Heap& other) : Heap() {
		*this = other;
	}

	Heap& operator= (const Heap& other) {
		if (this != &other)
		{
			_size = other._size;
			copy(other.data + 1, other.data + other._size + 1, data + 1);
		}
		return *this;
	}

	~Heap() {
		delete[] data;
	}

	void push(const T& value) {

		// using stl/algorithm
		// data.push_back(value);
		// push_heap(data.begin() + 1, data.end(), comp);

		data[++_size] = value;
		size_type curPos = size();

		while(curPos > 1 && comp(data[curPos / 2], data[curPos])) {
		    data[curPos] = data[curPos / 2];
		    data[curPos / 2] = value;
		    curPos /= 2;
		}
	}

	void pop() {
		
		if (!empty())
		{
			// using stl/algorithm
			// 	pop_heap(data.begin() + 1, data.end(), comp);
			// 	data.pop_back();

			T tmp = data[1] = data[size()];
			_size--;

			size_type curPos = 1, s = size();

			while (curPos * 2 <= s) {
				size_type left = curPos * 2;

				if (left + 1 <= s)
				{
					if (comp(data[left], data[left + 1]))
					{
						left++;
					}
				}

				if (comp(tmp, data[left]))
				{
					data[curPos] = data[left];
					curPos = left;
				}
				else
				{
					break;
				}
			}
			data[curPos] = tmp;
		}
		else
		{
			throw logic_error("heap is empty");
		}


		
	}

	T top() const {
		if (!empty())
		{
			return data[1];
		}
		else
		{
			throw logic_error("heap is empty");
		}
	}

	bool empty() const {
		return size() == 0;
	}

	size_type size() const {
		return _size;
	} 

private:
	T* data;
	Compare comp;
	size_type _size;
};

template<typename T>
using MaxHeap = Heap<T, less<T> >;

template<typename T>
using MinHeap = Heap<T, greater<T> >;

#endif // HEAP_H
