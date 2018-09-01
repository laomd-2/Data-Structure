#ifndef __TEST_H_
#define __TEST_H_
#include <iostream>
#include <vector>
#include "laomd_stack.h"
using namespace std;

template <typename C>
void testTraverse(Stack<int, C> stk) {
	while(!stk.empty()) {
		cout << stk.top() << ' ';
		stk.pop();
	}
	cout << endl;
	stk.pop();
}
void testConstructors() {
	Stack<int> stk1;
	testTraverse(stk1);
	
	vector<int> v;
	v.push_back(10);
	Stack<int, vector<int>> stk2(v);
	testTraverse(stk2);
	
	Stack<int> stk3(stk1);
	
	Stack<int, vector<int>> stk4(std::move(stk2));
	testTraverse(stk2);
	testTraverse(stk4);
}
void testPush() {
	
}
void testPop() {
	
} 
void testSwap() {
	Stack<int> stk1, stk2;
	stk1.push(10);
	stk2.push(100);
	stk1.swap(stk2);
	testTraverse(stk1);
	testTraverse(stk2);
}
#endif
