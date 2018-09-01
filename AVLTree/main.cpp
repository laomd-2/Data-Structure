#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AVLTree.h"
using namespace std;
void simpleTest() {
	AVLTree<int> myTree;

	int arr[] = {1,2,3,4,5,6,7,8,9,10};

	for(unsigned i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
		myTree.insert(arr[i]);
	}

	cout << myTree.height() << endl;

	myTree.levelOrder([](int a) {
		cout << a << ' ';
	});

	cout << endl;

	for(unsigned i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
		myTree.remove(arr[i]);
	}
	
	cout << myTree.height() << endl;

	myTree.inOrder([](int a) {
		cout << a << ' ';
	});

	cout << endl;
}

void hardTest() {
	srand(time(nullptr));
	AVLTree<int> myTree;

	for(unsigned i = 0; i < 10000; ++i) {
		myTree.insert(rand() % 10000);
	}
	for(unsigned i = 0; i < 10000; ++i) {
		myTree.remove(rand() % 10000);
	}
}
int main(int argc, char const *argv[])
{
	/*simpleTest();
	for(unsigned i = 0; i < 10; ++i) {
		hardTest();	
	}*/
	AVLTree<char> t;
	string s = "hebacdfgljikm";
	
	for(char c : s) {
	    t.BSTInsert(c);
	}
	// t.levelOrder([](char a) {
 //    	cout << a << ' ';
 //    });
    // cout << endl;
    char c;
	while(cin >> c) {
	    t.remove(c);
	    t.levelOrder([](char a) {
	    	cout << a << ' ';
	    });
	    cout << endl;
	}
	return 0;
}