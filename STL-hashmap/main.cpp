#include "laomd_hash_map.h"
#include "test.h"

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
