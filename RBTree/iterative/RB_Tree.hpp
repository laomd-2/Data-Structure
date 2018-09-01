#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "RB_TreeNode.hpp"
#include <queue>

template<typename T>
class RB_Tree
{
public:
	RB_Tree();
	~RB_Tree();

	template<typename VisitType>
	void inOrder(const VisitType&) const;
	template<typename VisitType>
	void levelOrder(const VisitType&) const;

	void insert(const T&);
	void remove(const T&);
private:
	void rotate_right(RB_Node<T>*);
	void rotate_left(RB_Node<T>*);

	RB_Node<T>* find(RB_Node<T>*, const T&);

	template<typename VisitType>
	void inOrder(RB_Node<T>*, const VisitType&) const;

	void insertFixUp(RB_Node<T>*);
	void removeFixUp(RB_Node<T>*);

	RB_Node<T>* maximum(RB_Node<T>*) const;

	void destory(RB_Node<T>*);

private:
	RB_Node<T>* const nil;
	RB_Node<T>* root;
};

template<typename T>
RB_Tree<T>::RB_Tree() : nil(new RB_Node<T>(T())), root(nil) {
	nil->color = BLACK;
	nil->parent = root;
	nil->left = nil->right = root;
}
template<typename T>
RB_Tree<T>::~RB_Tree() {
	destory(root);
	delete nil;
}

template<typename T>
void RB_Tree<T>::destory(RB_Node<T>* treeRoot) {
	if(treeRoot != nil) {
		destory(treeRoot->left);
		destory(treeRoot->right);
		delete treeRoot;
	}
}

template<typename T>
RB_Node<T>* RB_Tree<T>::maximum(RB_Node<T>* node) const {
	if(node != nil) {
		while(node->right != nil) {
		    node = node->right;
		}
	}
	return node;
}

template<typename T>
RB_Node<T>* RB_Tree<T>::find(RB_Node<T>* treeRoot, const T& target) {
	RB_Node<T>* cur = treeRoot;
	RB_Node<T>* parent = nil;
	while(cur != nil) {
		parent = cur;
	    if(target < cur->value) {
	    	cur = cur->left;
	    }
	    else if(target > cur->value) {
	    	cur = cur->right;
	    }
	    else {
	    	return cur;
	    }
	}
	return parent;
}


template<typename T>
void RB_Tree<T>::insert(const T& target) {
	RB_Node<T>* parent = find(root, target);
	if(parent != nil && parent->value == target) {
		return;
	}

	RB_Node<T>* newnode = new RB_Node<T>(target);
	newnode->parent = parent;
	newnode->color = RED;
	newnode->left = newnode->right = nil;

	if(parent == nil) {
		root = newnode;
	}
	else {
		if(target < parent->value) {
			parent->left = newnode;
		}
		else {
			parent->right = newnode;
		}
	}
	insertFixUp(newnode);
}

template<typename T>
void RB_Tree<T>::insertFixUp(RB_Node<T>* child) {
	RB_Node<T>* grand;
	RB_Node<T>* parent;
	RB_Node<T>* uncle;
	while(child->parent->color == RED) {
		parent = child->parent;
	    grand = child->parent->parent;

	    if(parent == grand->left) {
	    	uncle = grand->right;
	    	grand->color = RED;
	    	if(uncle->color == RED) {
	    		parent->color = uncle->color = BLACK;
	    		child = grand;
	    	}
	    	else {
	    		if(child == parent->left) {
	    			parent->color = BLACK;
	    			rotate_right(grand);
	    		}
	    		else {
	    			child = child->parent;
	    			rotate_left(parent);
	    		}
	    	}
	    }
	    else {
	    	uncle = grand->left;
	    	grand->color = RED;
	    	if(uncle->color == RED) {
	    		parent->color = uncle->color = BLACK;
	    		child = grand;
	    	}
	    	else {
	    		if(child == parent->right) {
	    			parent->color = BLACK;
	    			rotate_left(grand);
	    		}
	    		else {
	    			child = child->parent;
	    			rotate_right(parent);
	    		}
	    	}
	    }
	}
	root->color = BLACK;
}


template<typename T>
void RB_Tree<T>::remove(const T& target) {
	RB_Node<T>* node = find(root, target);
	if(node != nil && node->value == target) {
		if(node->left != nil && node->right != nil) {
			RB_Node<T>* pre = maximum(node->left);
			node->value = pre->value;
			node = pre;
		}
		RB_Node<T>* newnode = node->left != nil ? node->left : node->right;
		newnode->parent = node->parent;
		if(node->parent == nil) {
			root = newnode;
			nil->parent = root;
			nil->left = nil->right = root;
		}
		else {
			if(node == node->parent->left) {
				node->parent->left = newnode;
			}
			else {
				node->parent->right = newnode;
			}
		}
		if(node->color == BLACK) {
			removeFixUp(newnode);
		}
		delete node;
	}
}

template<typename T>
void RB_Tree<T>::removeFixUp(RB_Node<T>* node) {
	while(node != root && node->color == BLACK) {
	    RB_Node<T>* parent = node->parent;
	    RB_Node<T>* brother;
	    if(node == parent->left) {
	    	brother = parent->right;
	    	if(brother->color == RED) {
	    		brother->color = BLACK;
	    		parent->color = RED;
	    		rotate_left(parent);
	    	}
	    	else {
	    		if(brother->left->color == BLACK && brother->right->color == BLACK) {
	    			brother->color = RED;
	    			node = parent;
	    		}
	    		else if(brother->right->color == BLACK) {
	    			brother->color = RED;
                    brother->left->color = BLACK;
                    rotate_right(brother);
	    		}
	    		else {
	    			brother->color = parent->color;
                    parent->color = BLACK;
                    brother->right->color = BLACK;
                    rotate_left(node->parent);
                    node = root;
	    		}
	    	}
	    }
	    else {
	    	brother = parent->left;
	    	if(brother->color == RED) {
	    		brother->color = BLACK;
	    		parent->color = RED;
	    		rotate_right(parent);
	    	}
	    	else {
	    		if(brother->right->color == BLACK && brother->left->color == BLACK) {
	    			brother->color = RED;
	    			node = parent;
	    		}
	    		else if(brother->left->color == BLACK) {
	    			brother->color = RED;
                    brother->right->color = BLACK;
                    rotate_left(brother);
	    		}
	    		else {
	    			brother->color = parent->color;
                    parent->color = BLACK;
                    brother->left->color = BLACK;
                    rotate_right(node->parent);
                    node = root;
	    		}
	    	}
	    }
	}
	node->color = BLACK;
	nil->parent = root;
}

	
template<typename T>
void RB_Tree<T>::rotate_right(RB_Node<T>* node) {
	RB_Node<T>* lower_left = node->left;
    lower_left->parent =  node->parent;
    node->left=lower_left->right;
    if(lower_left->right!=nil)
    {
        lower_left->right->parent = node;
    }
    if(node->parent==nil) //rotate node is root
    {
        root = lower_left;
        nil->right = root;
        nil->left= root;
    }
    else
    {
        if(node == node->parent->right)
        {
            node->parent->right = lower_left;
        }
        else
        {
            node->parent->left = lower_left;
        }
    }
    node->parent = lower_left;
    lower_left->right = node;
}
template<typename T>
void RB_Tree<T>::rotate_left(RB_Node<T>* node) {
	RB_Node<T>* lower_right = node->right;
    lower_right->parent =  node->parent;
    node->right=lower_right->left;
    if(lower_right->left!=nil)
    {
        lower_right->left->parent = node;
    }
    if(node->parent==nil) //rotate node is root
    {
        root = lower_right;
        nil->left = root;
        nil->right= root;
    }
    else
    {
        if(node == node->parent->left)
        {
            node->parent->left = lower_right;
        }
        else
        {
            node->parent->right = lower_right;
        }
    }
    node->parent = lower_right;
    lower_right->left = node;
}

template<typename T>
template<typename VisitType>
void RB_Tree<T>::inOrder(const VisitType& visit) const {
	inOrder(root, visit);
}
template<typename T>
template<typename VisitType>
void RB_Tree<T>::inOrder(RB_Node<T>* treeRoot, const VisitType& visit) const
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
void RB_Tree<T>::levelOrder(const VisitType& visit) const {
	std::queue<RB_Node<T>*> allNodes;
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
