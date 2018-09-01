#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Heap.h"

using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	const unsigned count = 10;

	vector<int> tmp(count);

	for(unsigned i = 0; i < count; ++i) {
		int num = rand() % 100;
		tmp[i] = num;
		cout << num << ' ';
	}
	cout << endl;

	MinHeap<int> myHeap(tmp.begin(), tmp.end());

	// MinHeap<int> other(myHeap);

	while(!myHeap.empty()) {
	    cout << myHeap.top() << ' ';
	    myHeap.pop();
	}
	cout << endl;

	// while(!other.empty()) {
	//     cout << other.top() << ' ';
	//     other.pop();
	// }
	// cout << endl;
	return 0;
}