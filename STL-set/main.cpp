#include "test.h"
#include <iostream>

using namespace std;

int main() {
	try {
        testConstructors();	
		testInsert();
		testErase();	
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
