#include "SplayTree.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	SplayTree<int> mytree;

	int count = 10;
	auto visit = [](int a) {
		cout << a << ' ';
	};

	for(unsigned i = 0; i < count; ++i) {
		int tmp = rand() % (count * 2);
		mytree.splay(tmp);
	}

	cout << "find elements:" << endl;
	for(unsigned i = 0; i < count / 2; ++i) {
		int tmp = rand() % (count * 2);
		cout << tmp << ' ';
		cout << (mytree.find(tmp) != nullptr) << endl;
	}
	
	cout << "remove elements:" << endl;
	for(unsigned i = 0; i < count; ++i) {
		int tmp = rand() % (count * 2);
		cout << tmp << ' ';
		mytree.remove(tmp);
	}
	cout << endl;

	cout << "levelOrder:" << endl;
	mytree.levelOrder(visit);
	cout << endl;
	cout << "inOrder:" << endl;
	mytree.inOrder(visit);
	cout << endl;

	SplayTree<int> otherTree;
	for(unsigned i = 0; i < count; ++i) {
		int tmp = rand() % (count * 2) + (count * 2);
		otherTree.splay(tmp);
	}

	mytree.join(otherTree);
	mytree.inOrder(visit);
	cout << endl;
	otherTree.inOrder(visit);
	cout << endl;

	SplayTree<int>* result = mytree.split(count);
	mytree.inOrder(visit);
	cout << endl;
	result[0].inOrder(visit);
	cout << endl;
	result[1].inOrder(visit);
	cout << endl;

	delete [] result;

	return 0;
}	