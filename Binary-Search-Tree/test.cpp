#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "BSTree.h"
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));
	BSTree<int> tree;
	std::vector<int> v;
	int n = 20;
	while(n--) {
	    int x = rand() % 20;
	    cout << x << ' ';
	    v.push_back(x);
	    tree.insert(x);
	}
	cout << endl;

	for(auto&& i : v) {
		tree.remove(i);
		tree.levelOrder([](int x) {
			cout << x << ' ';
		});
		cout << endl;		
	}
	return 0;
}		