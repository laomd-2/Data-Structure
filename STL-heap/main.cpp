#include <iostream>
#include "test.h"
using namespace std;

int main() {
	try {
		testConstructors();
		testPush();
		testPop();
		testSwap();
	}
	catch(std::exception& e) {
		cout << e.what() << endl;
	}
	return 0;
} 
