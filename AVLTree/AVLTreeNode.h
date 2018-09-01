#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

template<typename T>
struct AVLTreeNode
{
	T value;
	AVLTreeNode* left = nullptr;
	AVLTreeNode* right = nullptr;

	unsigned height = 1;

	AVLTreeNode(const T& v) : value(v) {

	}
};

#endif // AVL_TREE_NODE_H
