#include <ctime>
#include <cstdlib> 
#include <iostream>
#include <string>
#include "laomd_vector.h"
#include "test.h"
using namespace std;

int main() {
	
//	test1 
	srand(time(NULL));
	try {
		Vector<string> v;
		testAssign(v);
		testErase(v);
		testReserve(v);
		testInsert(v);
		testTraverse(v);
		testCopy(v);
		testRemove(v);
		testSort(v);
		testUnique(v);
		testLower_bound(v);
		testResize(v);
		testSwap(v);
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	} 
	return 0;
}


