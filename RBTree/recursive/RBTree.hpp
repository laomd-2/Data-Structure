#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "RBTreeNode.hpp"
#include <queue>

template<typename T>
class RBTree
{
public:
	RBTree();
	~RBTree();

	template<typename VisitType>
	void inOrder(const VisitType&) const;
	template<typename VisitType>
	void levelOrder(const VisitType&) const;

	void insert(const T&);
	void erase(const T&);

private:
	static RBNode<T>* rotate_right(RBNode<T>*);
	static RBNode<T>* rotate_left(RBNode<T>*);

	template<typename VisitType>
	void inOrder(RBNode<T>*, const VisitType&) const;

	RBNode<T>* recursive_insert(RBNode<T>*, const T&);
	RBNode<T>* erase(RBNode<T>*, const T&);

	void destory(RBNode<T>*);
	
	RBNode<T>* const nil;
	RBNode<T>* root;
};

template<typename T>
RBTree<T>::RBTree() : nil(new RBNode<T>(T())), root(nil) {
	nil->color = BLACK;
}
template<typename T>
RBTree<T>::~RBTree() {
	destory(root);
	delete nil;
}

template<typename T>
void RBTree<T>::destory(RBNode<T>* treeRoot) {
	if(treeRoot != nil) {
		destory(treeRoot->left);
		destory(treeRoot->right);
		delete treeRoot;
	}
}

template<typename T>
void RBTree<T>::insert(const T& target) {
	root = recursive_insert(root, target);
	if(root->color == RED) {
		root->color = BLACK;
	}
}
template<typename T>
void RBTree<T>::erase(const T& target) {
	root = erase(root, target);
	if(root->color == RED) {
		root->color = BLACK;
	}
}


template<typename T>
RBNode<T>* RBTree<T>::recursive_insert(RBNode<T>* treeRoot, const T& target) {
	if(treeRoot != nil) {
		if(target < treeRoot->value) {
			treeRoot->left = recursive_insert(treeRoot->left, target);
			if(treeRoot->left->color == RED) {
				if(treeRoot->left->left->color == RED) {
					treeRoot->color = RED;
					if(treeRoot->right->color == BLACK) {
						treeRoot = rotate_right(treeRoot);
						treeRoot->color = BLACK;
					}
					else {
						treeRoot->left->color = treeRoot->right->color = BLACK;
					}
				}
				else if(treeRoot->left->right->color == RED) {
					treeRoot->color = RED;
					if(treeRoot->right->color == BLACK) {
						treeRoot->left = rotate_left(treeRoot->left);
						treeRoot = rotate_right(treeRoot);
						treeRoot->color = BLACK;
					}
					else {
						treeRoot->left->color = treeRoot->right->color = BLACK;
					}
				}
			}
		}
		else if(target > treeRoot->value) {
			treeRoot->right = recursive_insert(treeRoot->right, target);
			if(treeRoot->right->color == RED) {
				if(treeRoot->right->right->color == RED) {
					treeRoot->color = RED;
					if(treeRoot->left->color == BLACK) {
						treeRoot = rotate_left(treeRoot);
						treeRoot->color = BLACK;
					}
					else {
						treeRoot->right->color = treeRoot->left->color = BLACK;
					}
				}
				else if(treeRoot->right->left->color == RED) {
					treeRoot->color = RED;
					if(treeRoot->left->color == BLACK) {
						treeRoot->right = rotate_right(treeRoot->right);
						treeRoot = rotate_left(treeRoot);
						treeRoot->color = BLACK;
					}
					else {
						treeRoot->right->color = treeRoot->left->color = BLACK;
					}
				}
			}
		}
	}
	else {
		treeRoot = new RBNode<T>(target);
		treeRoot->color = RED;
		treeRoot->left = treeRoot->right = nil;
	}
	return treeRoot;
}
template<typename T>
RBNode<T>* RBTree<T>::erase(RBNode<T>* treeRoot, const T& target) {

}

template<typename T>
RBNode<T>* RBTree<T>::rotate_right(RBNode<T>* treeRoot) {
	auto rootB = treeRoot->left;
	treeRoot->left = rootB->right;
	rootB->right = treeRoot;
	return rootB;
}
template<typename T>
RBNode<T>* RBTree<T>::rotate_left(RBNode<T>* treeRoot) {
	auto rootB = treeRoot->right;
	treeRoot->right = rootB->left;
	rootB->left = treeRoot;
	return rootB;
}

template<typename T>
template<typename VisitType>
void RBTree<T>::inOrder(const VisitType& visit) const {
	inOrder(root, visit);
}
template<typename T>
template<typename VisitType>
void RBTree<T>::inOrder(RBNode<T>* treeRoot, const VisitType& visit) const
{
	if (treeRoot != nil)
	{
		inOrder(treeRoot->left, visit);
		visit(treeRoot->value);
		inOrder(treeRoot->right, visit);
	}
}

template<typename T>
template<typename VisitType>
void RBTree<T>::levelOrder(const VisitType& visit) const {
	std::queue<RBNode<T>*> allNodes;
	allNodes.push(root);
	while(!allNodes.empty()) {
	    auto cur = allNodes.front();
	    allNodes.pop();
	    if (cur != nil)
	    {
	    	visit(cur->value);
	    	allNodes.push(cur->left);
	    	allNodes.push(cur->right);
	    }
	}
}

#endif // RB_TREE_HPP
