#ifndef SOURCE_H
#define SOURCE_H

#include <map>
#include <vector>
using namespace std;

class unionFindSet
{
	std::map<int, int> child2parent;
	unsigned _size;
	const static int nil = -1;
public:
	unionFindSet(unsigned n) : _size(n) {
		for(unsigned i = 0; i < n; ++i) {
			child2parent[i] = nil;
		}
	}
	unionFindSet(const vector<int>& all) {
		initialize(all);
	}
	unionFindSet(int* arr, int size) : _size(size) {
		for(unsigned i = 0; i < size; i++) {
			child2parent[arr[i]] = nil;
		}
	}
	void initialize(const vector<int>& all) {
		_size = all.size();
		for(int i : all) {
			child2parent[i] = nil;
		}
	}
	void unite(int a, int b) {
		int sa = find(a);
		int sb = find(b);
		if(sa != sb) {
			if(child2parent[sa] < child2parent[sb]) {
				child2parent[sa] += child2parent[sb];	
				child2parent[sb] = sa;
			}
			else {
				child2parent[sb] += child2parent[sa];	
				child2parent[sa] = sb;
			}
			_size--;
		}
	}
	bool is_connected(int a, int b) {
		int sa = find(a);
		int sb = find(b);
		return sa == sb;
	}
	int find(int a) {
		if (child2parent.find(a) == child2parent.end())
		{
			child2parent[a] = nil;
			_size++;
		}

		if(child2parent[a] <= nil) {
			return a;
		}
		else {
			return child2parent[a] = find(child2parent[a]);
		}
	}
	unsigned numOfSets() const {
		return _size;
	}
	unsigned numOfMember(int a) {
		return -child2parent[find(a)];
	}
};

#endif // SOURCE_H
