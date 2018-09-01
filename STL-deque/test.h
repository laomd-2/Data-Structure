#ifndef __TEST_H_
#define __TEST_H_
#include "laomd_deque.h"
#include <iostream>
using namespace std;
 
void testTraverse(Deque<int>& deq) {
	for (auto it = deq.begin(); it != deq.end(); ++it) 
	    cout << *it << ' ';
	cout << endl;
}
void testConstructor() {
    Deque<int> deq;
   	testTraverse(deq);
   	Deque<int> deq2(3u, 10);
   	testTraverse(deq2);
   	int arr[] = {1,2,4,5};
   	Deque<int> deq3(arr, arr + 4);
   	testTraverse(deq3);
   	Deque<int> deq4({1,2,3,4});
   	testTraverse(deq4);
   	Deque<int> deq5(std::move(deq4));
   	testTraverse(deq4);
   	testTraverse(deq5);
   	Deque<int> deq6(deq5);
   	deq6.push_back(10);
   	testTraverse(deq6);
   	testTraverse(deq5);
   	deq6 = deq2;
   	testTraverse(deq6);
}
	
void testPop() {
	int arr[] = {1,2,4,5};
   	Deque<int> deq3(arr, arr + 4);
   	testTraverse(deq3);	
   	while(!deq3.empty()) {
   	    deq3.pop_front();
//   	    deq3.pop_back();
		testTraverse(deq3);	
    }
}
void testAccess() {
	int arr[] = {1,2,4,5};
   	Deque<int> deq3(arr, arr + 4);
   	cout << deq3.front() << endl;
   	cout << deq3.back() << endl;
}
void testResize() {
	int arr[] = {1,2,4,5};
   	Deque<int> deq(arr, arr + 4);
    deq.resize(10);
    testTraverse(deq);
    deq.resize(2);
    testTraverse(deq);
}
#endif
