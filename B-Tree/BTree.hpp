#ifndef B_TREE_HPP
#define B_TREE_HPP
#include <queue>
#include <tuple>
#include <stdexcept>
#include "TreeNode.hpp"

template<typename T, const int ORDER>
class BTree {
private:
	using nodeType = TreeNode<T, ORDER>;
	nodeType* root = nullptr;	
public:
	BTree();
	void insert(const T& target);
	void remove(const T& target);
	std::pair<const nodeType*, int> search(const T& target) const;

	bool empty() const;
	template<typename VisitType>
	void levelOrder(const VisitType&) const;

private:
	static std::pair<nodeType*, int> find(nodeType*, const T& target);
	static nodeType* minimum(nodeType*);
	static nodeType* maximum(nodeType*);

	void insertFixup(nodeType*);
	void removeFixup(nodeType*);

	void remove(nodeType*, T target);
};
template<typename T, const int ORDER>
BTree<T, ORDER>::BTree() {
	if(ORDER < 3) {
		throw std::logic_error("tree order should >= 3");
	}
}

template<typename T, const int ORDER>
bool BTree<T, ORDER>::empty() const {
	return root == nullptr;
}

template<typename T, const int ORDER>
typename BTree<T, ORDER>::nodeType* BTree<T, ORDER>::minimum(nodeType* treeRoot) {
	if(treeRoot) {
		nodeType* cur = nullptr;
		while((cur = treeRoot->getBranch(0))) {
		    treeRoot = cur;
		}
	}
	return treeRoot;
}

template<typename T, const int ORDER>
typename BTree<T, ORDER>::nodeType* BTree<T, ORDER>::maximum(nodeType* treeRoot) {
	if(treeRoot) {
		nodeType* cur = nullptr;
		while((cur = treeRoot->getBranch(treeRoot->size()))) {
		    treeRoot = cur;
		}
	}
	return treeRoot;
}

template<typename T, const int ORDER>
std::pair<typename BTree<T, ORDER>::nodeType*, int> 
		BTree<T, ORDER>::find(nodeType* treeRoot, const T& target) {

	nodeType* parent = nullptr;
	int index = 0;
	while(treeRoot) {
		parent = treeRoot;
		index = treeRoot->indexOf(target);
		if(treeRoot->getKey(index) == target) {
			break;
		}
		else {
			treeRoot = treeRoot->getBranch(index);
		}
	}
	return std::make_pair(parent, index);
}

template<typename T, const int ORDER>
std::pair<const typename BTree<T, ORDER>::nodeType*, int> 
		BTree<T, ORDER>::search(const T& target) const {
	auto position = find(root, target);
	if(position.first->getKey(position.second) != target) {
		position.first = nullptr;
	}
	return position;
}	


template<typename T, const int ORDER>
void BTree<T, ORDER>::insertFixup(nodeType* child) {
	while(child && child->is_full()) {
	    nodeType* parent = child->parent;
		if(parent == nullptr) {
			parent = root = new nodeType;
			root->parent = nullptr;
			child->parent = root;
			root->addBranch(0, child);
		}

		nodeType* nextChild;
		T midKey;
		std::tie(midKey, nextChild) = child->split();

		unsigned branch = parent->indexOf(child);
		parent->addBranch(branch + 1, nextChild);
		parent->addKey(branch, midKey);

		child = parent;
	}
}

template<typename T, const int ORDER>
void BTree<T, ORDER>::removeFixup(nodeType* child) {
	while(child && !child->is_enough()) {
		nodeType* parent = child->parent;
		if(parent) {
			int branch = parent->indexOf(child);
			int left = branch - 1, right = branch + 1;

			// case 1 : left sibling has an extra key
			if(left >= 0) {
				nodeType* leftSibling = parent->getBranch(left);
				if(leftSibling && leftSibling->has_extra()) {
					child->addBranch(0, leftSibling->getBranch(leftSibling->size()));
					leftSibling->removeBranch(leftSibling->size());
					child->addKey(0, parent->getKey(left));
					parent->setKey(left, leftSibling->getKey(leftSibling->size() - 1));
					leftSibling->removeKey(leftSibling->size() - 1);
					break;
				}
			}

			// case 2 : right sibling has an extra key
			if(right <= parent->size()) {
				nodeType* rightSibling = parent->getBranch(right);
				if(rightSibling && rightSibling->has_extra()) {
					child->addBranch(child->size() + 1, rightSibling->getBranch(0));
					rightSibling->removeBranch(0);
					child->addKey(child->size(), parent->getKey(branch));
					parent->setKey(branch, rightSibling->getKey(0));
					rightSibling->removeKey(0);
					break;
				}
			}

			// case 3 : merge left sibling, right sibling and the key in parent
			if(left < 0) {
				left = branch;
				branch++;
			}
			if(left < parent->size()) {
				nodeType* small = parent->getBranch(left);
				nodeType* big = parent->getBranch(branch);
				int position = small->size();
				small->merge(big);
				small->addKey(position, parent->getKey(left));
				delete big;
				parent->removeBranch(branch);
				parent->removeKey(left);
			}
			child = parent;
		}
		else {
			if(root->size() == 0) {
				root = root->getBranch(0);
				if(root) {
					root->parent = nullptr;
				}
			}
			break;
		}
	}
}

template<typename T, const int ORDER>
void BTree<T, ORDER>::insert(const T& target) {
	int index;
	nodeType* node;
	std::tie(node, index) = find(root, target);
	
	if(!node || node->getKey(index) != target) {
		if(!node) {
			root = node = new nodeType;
			root->parent = nullptr;
		}
		node->addKey(index, target);
		insertFixup(node);
	}

}

template<typename T, const int ORDER>
void BTree<T, ORDER>::remove(const T& target) {
	remove(root, target);
}

template<typename T, const int ORDER>
void BTree<T, ORDER>::remove(nodeType* treeRoot, T target) {
	int index;
	std::tie(treeRoot, index) = find(treeRoot, target);
	
	if(treeRoot && treeRoot->getKey(index) == target) {
		if(!treeRoot->is_leaf()) {
			int oldIndex = index;

			nodeType* pre = maximum(treeRoot->getBranch(index));
			if(pre->size() == 0) {
				pre = minimum(treeRoot->getBranch(index + 1));
				index = 0;
			}
			else {
				index = pre->size() - 1;
			}

			target = pre->getKey(index);
			treeRoot->setKey(oldIndex, target);
			treeRoot = pre;
		}

		treeRoot->removeKey(index);
		removeFixup(treeRoot);
	}
}

template<typename T, const int ORDER>
template<typename VisitType>
void BTree<T, ORDER>::levelOrder(const VisitType& visit) const {
	std::queue<nodeType*> allNodes;
	allNodes.push(root);
	while(!allNodes.empty()) {
	    nodeType* cur = allNodes.front();
	    allNodes.pop();
	    if (cur)
	    {
	    	for(unsigned i = 0; i < cur->size(); ++i) {
	    		visit(cur->getKey(i));
	    		allNodes.push(cur->getBranch(i));
	    	}
	    	allNodes.push(cur->getBranch(cur->size()));
	    }
	}
	
}
#endif // B_TREE_HPP
