#include "RB_Tree.hpp"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	auto visit = [](int a) {cout << a << ' ';};

	int times = 100;
	while(times--) {
		RB_Tree<int> mytree;
	    const int count = 1000;
		cout << "insert:" << endl;
		for(unsigned i = 0; i < count; ++i) {
			int tmp = rand() % count;
			cout << tmp << ' ';
			mytree.insert(tmp);
		}
		cout << endl;

		cout << "inOrder:" << endl;
		mytree.inOrder(visit);
		cout << endl;
		for(unsigned i = 0; i < count; ++i) {
			int tmp = rand() % count;
			cout << "remove: " << tmp << endl;
			mytree.remove(tmp);
			cout << "inOrder:" << endl;
			mytree.inOrder(visit);
			cout << endl;
		}
	}
	return 0;
}
