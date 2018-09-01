#ifndef RB_TREE_NODE_HPP
#define RB_TREE_NODE_HPP

enum Color
{
	BLACK, RED
};

template<typename T>
struct RBNode
{
	T value;
	Color color;
	RBNode* left;
	RBNode* right;
	RBNode(const T& v) : value(v) {

	}
};


#endif // RB_TREE_NODE_HPP
