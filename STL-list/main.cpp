#include "laomd_list.h" 
#include "test.h"
#include <list>
using namespace std;

int main() {
	try {
		testConstructor();
		List<int> alist;
		testInsert(alist);
		testAssign(alist);
		testSwap(alist);
		testErase(alist);
		testRemove(alist);
		testUnique(alist);
		testSplice(alist);
		testMerge(alist);
		testReverse(alist);
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	return 0;
}
