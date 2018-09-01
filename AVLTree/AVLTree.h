#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "AVLTreeNode.h"
#include <queue>
#include <algorithm>
using std::max;
using std::queue;

template<typename T>
class AVLTree
{
private:
	AVLTreeNode<T>* LLrotate(AVLTreeNode<T>*);
	AVLTreeNode<T>* RRrotate(AVLTreeNode<T>*);
	AVLTreeNode<T>* LRrotate(AVLTreeNode<T>*);
	AVLTreeNode<T>* RLrotate(AVLTreeNode<T>*);

	unsigned height(AVLTreeNode<T>*) const;
	AVLTreeNode<T>* minimum(AVLTreeNode<T>*) const;
	AVLTreeNode<T>* maximum(AVLTreeNode<T>*) const;

	void BSTInsert(AVLTreeNode<T>*&, const T&);
	AVLTreeNode<T>* insert(AVLTreeNode<T>*&, const T&);
	AVLTreeNode<T>* remove(AVLTreeNode<T>*&, const T&);

	void destroy(AVLTreeNode<T>*); 

	template<typename VisitType>
	void inOrder(AVLTreeNode<T>*, const VisitType&) const;
public:
	AVLTree(const AVLTree&) = delete;
	AVLTree& operator=(const AVLTree&) = delete;

	AVLTree() : root(nullptr) {

	}

	void BSTInsert(const T&);
	void insert(const T&);
	void remove(const T&);

	unsigned height() const {
		return height(root);
	}

	template<typename VisitType>
	void levelOrder(const VisitType&) const;

	template<typename VisitType>
    void inOrder(const VisitType&) const; 

	~AVLTree() {
		destroy(root);
	}

private:
	AVLTreeNode<T>* root;
};

template<typename T>
AVLTreeNode<T>* AVLTree<T>::LLrotate(AVLTreeNode<T>* treeRoot) {
	auto rootB = treeRoot->left;
	treeRoot->left = rootB->right;
	rootB->right = treeRoot;

	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right)) + 1;
	rootB->height = max(height(rootB->left), height(rootB->right)) + 1;

	return rootB;
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::RRrotate(AVLTreeNode<T>* treeRoot) {
	auto rootB = treeRoot->right;
	treeRoot->right = rootB->left;
	rootB->left = treeRoot;

	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right)) + 1;
	rootB->height = max(height(rootB->left), height(rootB->right)) + 1;

	return rootB;
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::LRrotate(AVLTreeNode<T>* treeRoot) {
	treeRoot->left = RRrotate(treeRoot->left);
	return LLrotate(treeRoot);
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::RLrotate(AVLTreeNode<T>* treeRoot) {
	treeRoot->right = LLrotate(treeRoot->right);
	return RRrotate(treeRoot);
}	

template<typename T>
unsigned AVLTree<T>::height(AVLTreeNode<T>* treeRoot) const {
	return treeRoot ? treeRoot->height : 0;
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* treeRoot) const {
	if(treeRoot) {
		while(treeRoot->left) {
		    treeRoot = treeRoot->left;
		}
	}
	return treeRoot;
}
template<typename T>
AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* treeRoot) const {
	if(treeRoot) {
		while(treeRoot->right) {
		    treeRoot = treeRoot->right;
		}
	}
	return treeRoot;
}

template<typename T>
void AVLTree<T>::destroy(AVLTreeNode<T>* treeRoot) {
	if (treeRoot)
	{
		destroy(treeRoot->left);
		destroy(treeRoot->right);
		delete treeRoot;
	}
}

template<typename T>
void AVLTree<T>::BSTInsert(const T& ele) {
	BSTInsert(root, ele);
}
template<typename T>
void AVLTree<T>::BSTInsert(AVLTreeNode<T>*& treeRoot, const T& ele) {
	if(treeRoot) {
		if(ele < treeRoot->value) {
			BSTInsert(treeRoot->left, ele);
		}
		else if(ele > treeRoot->value) {
			BSTInsert(treeRoot->right, ele);
		}
	}
	else {
		treeRoot = new AVLTreeNode<T>(ele);
	}
	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right)) + 1;
}

template<typename T>
AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& treeRoot, const T& ele) {
	if(treeRoot) {
		if(ele < treeRoot->value) {
			treeRoot->left = insert(treeRoot->left, ele);
			int bf = height(treeRoot->left) - height(treeRoot->right);
			if (bf == 2)
			{
				if(ele < treeRoot->left->value) {
					treeRoot = LLrotate(treeRoot);
				}
				else if(ele > treeRoot->left->value) {
					treeRoot = LRrotate(treeRoot);
				}
			}
		}
		else if (ele > treeRoot->value) {
			treeRoot->right = insert(treeRoot->right, ele);
			int bf = height(treeRoot->left) - height(treeRoot->right);
			if (bf == -2)
			{
				if(ele > treeRoot->right->value) {
					treeRoot = RRrotate(treeRoot);
				}
				else if(ele < treeRoot->right->value) {
					treeRoot = RLrotate(treeRoot);
				}
			}
		}
	}
	else {
		treeRoot = new AVLTreeNode<T>(ele);		
	}
	treeRoot->height = max(height(treeRoot->left), height(treeRoot->right)) + 1;
	return treeRoot;
}

#include <iostream>
using namespace std;
template<typename T>
AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& treeRoot, const T& ele) {
	if(treeRoot) {
		if(ele == treeRoot->value) {
			if(treeRoot->left && treeRoot->right) {
				if(height(treeRoot->left) > height(treeRoot->right)) {
					auto maxNode = maximum(treeRoot->left);
					T tmp = maxNode->value;
					auto t = treeRoot;
					treeRoot = remove(treeRoot, tmp);
					t->value = tmp;
				}
				else {
					auto minNode = minimum(treeRoot->right);
					T tmp = minNode->value;
					auto t = treeRoot;
					treeRoot = remove(treeRoot, tmp);
					t->value = tmp;
				}
			}
			else {
				auto tmp = treeRoot;
				treeRoot = treeRoot->left ? treeRoot->left : treeRoot->right;
				delete tmp;
				return nullptr;
			}
		}
		else if(ele < treeRoot->value) {
			treeRoot->left = remove(treeRoot->left, ele);
			int bf = height(treeRoot->left) - height(treeRoot->right);
			if(bf == -2) {
				if(height(treeRoot->right->right) >= height(treeRoot->right->left)) {
					treeRoot = RRrotate(treeRoot);
				}
				else {
					treeRoot = RLrotate(treeRoot);	
				}
			}
		}
		else {
			treeRoot->right = remove(treeRoot->right, ele);
			int bf = height(treeRoot->left) - height(treeRoot->right);
			if(bf == 2) {
				if(height(treeRoot->left->left) >= height(treeRoot->left->right)) {
					treeRoot = LLrotate(treeRoot);
				}
				else {
					treeRoot = LRrotate(treeRoot);	
				}
			}
		}
	}
	return treeRoot;
}
template<typename T>
void AVLTree<T>::insert(const T& ele) {
	insert(root, ele);
}
template<typename T>
void AVLTree<T>::remove(const T& ele) {
	remove(root, ele);
}

template<typename T>
template<typename VisitType>
void AVLTree<T>::levelOrder(const VisitType& visit) const {
	std::queue<AVLTreeNode<T>*> allNodes;
	allNodes.push(root);
	while(!allNodes.empty()) {
	    AVLTreeNode<T>* cur = allNodes.front();
	    allNodes.pop();
	    if (cur)
	    {
	    	visit(cur->value);
	    	allNodes.push(cur->left);
	    	allNodes.push(cur->right);
	    }
	}
}
template<typename T>
template<typename VisitType>
void AVLTree<T>::inOrder(const VisitType& visit) const {
	inOrder(root, visit);
}

template<typename T>
template<typename VisitType>
void AVLTree<T>::inOrder(AVLTreeNode<T>* treeRoot, const VisitType& visit) const {
	if (treeRoot)
	{
		inOrder(treeRoot->left, visit);
		visit(treeRoot->value);
		inOrder(treeRoot->right, visit);
	}
}


#endif // AVL_TREE_H
