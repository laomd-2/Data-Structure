#include <iostream>
#include "laomd_stack.h"
#include "test.h"
#include <stack>
using namespace std;

int main() {
	try {
//		testConstructors();
//		testPush();
//		testPop();
//		testSwap();
	}
	catch(std::exception& e) {
		cout << e.what() << endl;
	}
	stack<int> s;
	s.push(10);
	s.pop();
	s.pop();
	return 0;
} 
