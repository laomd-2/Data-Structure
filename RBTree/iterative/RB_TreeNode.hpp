#ifndef RB_TREE_NODE_HPP
#define RB_TREE_NODE_HPP

enum Color
{
	BLACK, RED
};
template<typename T>
struct RB_Node
{
	T value;
	Color color;
	RB_Node* left;
	RB_Node* right;
	RB_Node* parent;
	RB_Node(const T& v) : value(v) {

	}
};


#endif // RB_TREE_NODE_HPP
