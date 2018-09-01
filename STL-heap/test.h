#ifndef __TEST_H_
#define __TEST_H_
#include <functional>
#include <iostream>
#include <vector>
#include "laomd_heap.h"
using namespace std;

template <typename T, typename C>
void testTraverse(const Heap<T, C>& hp) {
	for (auto it = hp.begin(); it != hp.end(); ++it) {
		cout << *it << ' ';
	}
	cout << endl;
}
void testConstructors() {
	Heap<int> hp1;
	testTraverse(hp1);
	Heap<int, std::greater<int>> hp2({1,2,3,0,1,3,6});
	testTraverse(hp2);
	int arr[] = {1,2,6,8,2,4,1};
	Heap<int> hp3(arr, arr + 7);
	testTraverse(hp3);
	Heap<int> hp4({1,2,3,0,1,3,6});
	testTraverse(hp4);
}
void testPush() {
	Heap<int> hp;
	hp.push(10);
	hp.push(1);
	hp.push(12);
	hp.push(11);
	testTraverse(hp);
}
void testPop() {
	Heap<int> hp;
	hp.push(10);
	hp.push(1);
	hp.push(12);
	hp.push(11);
	hp.pop();
	testTraverse(hp); 
} 
void testSwap() {
	Heap<int> hp1, hp2;
	hp1.push(10);
	hp1.push(1);
	hp2.push(100);
	hp1.swap(hp2);
	testTraverse(hp1);
	testTraverse(hp2);
}
#endif
