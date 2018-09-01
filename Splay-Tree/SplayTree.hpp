#ifndef SPLAY_TREE_HPP
#define SPLAY_TREE_HPP
#include <queue>

template<typename T>
class SplayTree {
public:
	struct TreeNode
	{
		T value;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
		TreeNode(const T& v) : value(v) {

		}
	};
public:
	SplayTree();
	SplayTree(const SplayTree&) = delete;
	SplayTree& operator= (const SplayTree&) = delete;
	SplayTree(SplayTree&&) = default;
	SplayTree& operator= (SplayTree&&) = default;
	~SplayTree();

	SplayTree& splay(const T&);
	TreeNode* find(const T&);
	SplayTree& remove(const T&);
	SplayTree* split(const T&);
	SplayTree& join(SplayTree& greater);

	bool empty() const;

	template<typename VisitType>
	void levelOrder(const VisitType&) const;

	template<typename VisitType>
    void inOrder(const VisitType&) const; 
    template<typename VisitType>
	void preOrder(const VisitType&) const;

private:
	TreeNode* zig(TreeNode*);
	TreeNode* zag(TreeNode*);
	TreeNode* zig_zig(TreeNode*);
	TreeNode* zag_zag(TreeNode*);
	TreeNode* zig_zag(TreeNode*);
	TreeNode* zag_zig(TreeNode*);

	void destroy(TreeNode*);

	template<typename VisitType>
	void inOrder(TreeNode*, const VisitType&) const;
	template<typename VisitType>
	void preOrder(TreeNode*, const VisitType&) const;

	TreeNode* splay(TreeNode*&, const T&);
	TreeNode* find(TreeNode*, const T&);

private:
	TreeNode* root;
};

template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zig(TreeNode* treeRoot) {
	auto rootB = treeRoot->left;
	treeRoot->left = rootB->right;
	rootB->right = treeRoot;

	return rootB;
}
template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zag(TreeNode* treeRoot) {
	auto rootB = treeRoot->right;
	treeRoot->right = rootB->left;
	rootB->left = treeRoot;

	return rootB;
}
template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zig_zig(TreeNode* treeRoot) {
	return zig(zig(treeRoot));
}
template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zag_zag(TreeNode* treeRoot) {
	return zag(zag(treeRoot));
}
template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zig_zag(TreeNode* treeRoot) {
	treeRoot->left = zag(treeRoot->left);
	return zig(treeRoot);
}
template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::zag_zig(TreeNode* treeRoot) {
	treeRoot->right = zig(treeRoot->right);
	return zag(treeRoot);
}

template<typename T>
SplayTree<T>::~SplayTree() {
	destroy(root);
}
template<typename T>
SplayTree<T>::SplayTree() : root(nullptr) {
	
}

template<typename T>
void SplayTree<T>::destroy(TreeNode* treeRoot) {
	if (treeRoot)
	{
		destroy(treeRoot->left);
		destroy(treeRoot->right);
		delete treeRoot;
	}
}

template<typename T>
bool SplayTree<T>::empty() const {
	return root == nullptr;
}

template<typename T>
SplayTree<T>& SplayTree<T>::splay(const T& target) {
	splay(root, target);
	return *this;
}
template<typename T>
typename SplayTree<T>::TreeNode* 
	SplayTree<T>::splay(TreeNode*& treeRoot, const T& target) {
	if(treeRoot) {
		if(target < treeRoot->value) {
			treeRoot->left = splay(treeRoot->left, target);
			if (treeRoot->left->value == target)
			{
				if (treeRoot == root) {
					treeRoot = zig(treeRoot);
				}
			}
			else {
				if(treeRoot->left->left && treeRoot->left->left->value == target) {
					treeRoot = zig_zig(treeRoot);	
				}
				else {
					treeRoot = zig_zag(treeRoot);
				}	
			}
		}
		else if(target > treeRoot->value) {
			treeRoot->right = splay(treeRoot->right, target);
			if (treeRoot->right->value == target)
			{
				if (treeRoot == root) {
					treeRoot = zag(treeRoot);
				}
			}
			else {
				if(treeRoot->right->right && treeRoot->right->right->value == target) {
					treeRoot = zag_zag(treeRoot);	
				}
				else {
					treeRoot = zag_zig(treeRoot);
				}	
			}
		}
	}
	else {
		treeRoot = new TreeNode(target);
	}
	return treeRoot;
}

template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::find(const T& target) {
	return find(root, target);
}

template<typename T>
typename SplayTree<T>::TreeNode* SplayTree<T>::find(TreeNode* treeRoot, const T& target) {
	if(treeRoot) {
		if(target == treeRoot->value) {
			splay(target);
			return treeRoot;
		}
		else if(target < treeRoot->value) {
			return find(treeRoot->left, target);
		}
		else {
			return find(treeRoot->right, target);
		}
	}
	else {
		return nullptr;
	}
}

template<typename T>
SplayTree<T>& SplayTree<T>::remove(const T& target) {
	if (find(target))
	{
		TreeNode* tmp = root;
		if(root->left == nullptr || root->right == nullptr) {
			root = root->left ? root->left : root->right;					
		}
		else {
			TreeNode* cur = root->left;
			while(cur->right) {
			    cur = cur->right;
			}

			//join root->left and root->right
			root = root->left;
			tmp->left = splay(root, cur->value);
			tmp->left->right = tmp->right;
			root = tmp->left;
		}
		delete tmp;
	}
	return *this;
}

template<typename T>
SplayTree<T>* SplayTree<T>::split(const T& key) {
	splay(key);
	SplayTree* result = new SplayTree[2];
	result[0].root = root->left;
	result[1].root = root->right;
	root = nullptr;
	return result;
}

template<typename T>
SplayTree<T>& SplayTree<T>::join(SplayTree& greater) {
	if (root) {
		TreeNode* cur = root;
		while(cur->right) {
		    cur = cur->right;
		}
		splay(cur->value);
		root->right = greater.root;
	}
	else {
		root = greater.root;
	}
	greater.root = nullptr;
	return *this;
}

template<typename T>
template<typename VisitType>
void SplayTree<T>::levelOrder(const VisitType& visit) const {
	std::queue<TreeNode*> allNodes;
	allNodes.push(root);
	while(!allNodes.empty()) {
	    TreeNode* cur = allNodes.front();
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
void SplayTree<T>::inOrder(const VisitType& visit) const {
	inOrder(root, visit);
}

template<typename T>
template<typename VisitType>
void SplayTree<T>::inOrder(TreeNode* treeRoot, const VisitType& visit) const {
	if (treeRoot)
	{
		inOrder(treeRoot->left, visit);
		visit(treeRoot->value);
		inOrder(treeRoot->right, visit);
	}
}
template<typename T>
template<typename VisitType>
void SplayTree<T>::preOrder(const VisitType& visit) const {
	preOrder(root, visit);
}

template<typename T>
template<typename VisitType>
void SplayTree<T>::preOrder(TreeNode* treeRoot, const VisitType& visit) const {
	if (treeRoot)
	{
		visit(treeRoot->value);
		preOrder(treeRoot->left, visit);
		preOrder(treeRoot->right, visit);
	}
}
#endif // SPLAY_TREE_HPP
