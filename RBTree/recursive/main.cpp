#include "RBTree.hpp"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	RBTree<int> mytree;

	const int count = 30;
	for(unsigned i = 0; i < count; ++i) {
		mytree.insert(rand() % count);
	}

	auto visit = [](int a) {cout << a << ' ';};
	mytree.levelOrder(visit);
	cout << endl;

	mytree.inOrder(visit);
	cout << endl;
	return 0;
}




// void debug() {
// 	debug(root);
// }
// int debug(RBNode<T>* treeRoot) {
// 	if(treeRoot == nil) {
// 		return 0;
// 	}
// 	else {
// 		int l = debug(treeRoot->left);
// 		int r = debug(treeRoot->right);
// 		if(l != r) {
// 			cout << "Oops" << endl;
// 			throw 1;
// 		}
// 		if(treeRoot->color == BLACK) {
// 			l++;
// 		}
// 		return l;
// 	}
// }
