#include <ctime>
#include <cstdlib>
#include <iostream> 
#include <deque> 
#include "test.h" 
#include "laomd_deque.h"
using namespace std;

int main() {
	srand(time(nullptr));
	try {
		testConstructor();
//		testPop();
//		testAccess();
//		testResize(); 
	}	
	catch(std::exception& e) {
		cout << e.what() << endl;
	}
	return 0;
} 
