#ifndef BS_TREE_H
#define BS_TREE_H

#include <queue>

template<typename T>
struct BSTreeNode
{
	T value;
	BSTreeNode* left;
	BSTreeNode* right;
	BSTreeNode(const T& v, BSTreeNode* l = nullptr, BSTreeNode* r = nullptr)
		: value(v), left(l), right(r) { }
};

template<typename T>
class BSTree
{
	typedef BSTreeNode<T>* NodeType;
	NodeType root;

	NodeType minimal(NodeType);
	NodeType maximal(NodeType);

	NodeType recursive_insert(NodeType, const T&);
	NodeType recursive_remove(NodeType, const T&);

	template<typename Visit>
	void recursive_inOrder(NodeType, Visit);
public:
	BSTree();

	void insert(const T&);
	void remove(const T&);

	template<typename Visit>
	void inOrder(Visit);

	template<typename Visit>
	void levelOrder(Visit);
};

template<typename T>
BSTree<T>::BSTree() : root(nullptr) { }

template<typename T>
typename BSTree<T>::NodeType BSTree<T>::minimal(NodeType treeRoot) {
	if(treeRoot) {
		while(treeRoot->left) {
		    treeRoot = treeRoot->left;
		}
	}
	return treeRoot;
}

template<typename T>
typename BSTree<T>::NodeType BSTree<T>::maximal(NodeType treeRoot) {
	if(treeRoot) {
		while(treeRoot->right) {
		    treeRoot = treeRoot->right;
		}
	}
	return treeRoot;
}

template<typename T>
template<typename Visit>
void BSTree<T>::inOrder(Visit visit) {
	recursive_inOrder(root, visit);
}

template<typename T>
template<typename Visit>
void BSTree<T>::recursive_inOrder(NodeType treeRoot, Visit visit) {
	if(treeRoot) {
		recursive_inOrder(treeRoot->left, visit);
		visit(treeRoot->value);
		recursive_inOrder(treeRoot->right, visit);
	}
}

template<typename T>
template<typename Visit>
void BSTree<T>::levelOrder(Visit visit) {
	using std::queue;

	queue<NodeType> node_queue;
	node_queue.push(root);
	while(!node_queue.empty()) {
	    NodeType cur = node_queue.front();
	    node_queue.pop();
	    if(cur) {
	    	visit(cur->value);	
	    	node_queue.push(cur->left);
	    	node_queue.push(cur->right);
	    }
	}
}

template<typename T>
void BSTree<T>::insert(const T& x) {
	root = recursive_insert(root, x);
}

template<typename T>
void BSTree<T>::remove(const T& x) {
	root = recursive_remove(root, x);
}

template<typename T>
typename BSTree<T>::NodeType BSTree<T>::recursive_insert(NodeType treeRoot, const T& x) {
	if(treeRoot) {
		if(x < treeRoot->value) {
			treeRoot->left = recursive_insert(treeRoot->left, x);
		}
		else if(x > treeRoot->value) {
			treeRoot->right = recursive_insert(treeRoot->right, x);
		}
	}
	else {
		treeRoot = new BSTreeNode<T>(x);
	}
	return treeRoot;
}
template<typename T>
typename BSTree<T>::NodeType BSTree<T>::recursive_remove(NodeType treeRoot, const T& x) {
	if(treeRoot) {
		if(treeRoot->value == x) {
			if(treeRoot->left) {
				NodeType precursor = maximal(treeRoot->left);
				T tmp = precursor->value;
				treeRoot->left = recursive_remove(treeRoot->left, tmp);
				treeRoot->value = tmp;
			}
			else if(treeRoot->right) {
				NodeType successor = minimal(treeRoot->right);
				T tmp = successor->value;
				treeRoot->right = recursive_remove(treeRoot->right, tmp);
				treeRoot->value = tmp;
			}
			else {
				delete treeRoot;
				treeRoot = nullptr;
			}
		}
		else {
			if(x < treeRoot->value) {
				treeRoot->left = recursive_remove(treeRoot->left, x);
			}
			else {
				treeRoot->right = recursive_remove(treeRoot->right, x);
			}
		}
	}
	return treeRoot;
}
#endif // BS_TREE_H
