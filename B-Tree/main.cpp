#include <iostream>
#include <cstdlib>
#include <ctime>
// #include "BTree.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	BTree<int, 3> mytree;

	auto visit = [&](int value) {
		cout << value << ' ';
	};

	// test insert
	const int count = 100;

	for(unsigned i = 0; i < count; ++i) {
		int tmp = rand() % count;
		mytree.insert(tmp);
	}

	mytree.levelOrder(visit);
	cout << endl;

	// test remove
	for(unsigned i = 0; i < count; ++i) {
		int tmp = rand() % count;
		mytree.remove(tmp);
	}

	mytree.levelOrder(visit);
	cout << endl;
	return 0;
}		