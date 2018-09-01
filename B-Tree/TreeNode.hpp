#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP
#include <algorithm>
#include <cmath>

template<typename T, const unsigned ORDER>
class TreeNode
{
	T keys[ORDER] = {T()};
	unsigned _size = 0;
	TreeNode* branches[ORDER + 1] = {nullptr};
public:
	TreeNode* parent = nullptr;

	unsigned size() const;
	bool is_leaf() const;
	bool is_full() const;
	bool is_enough() const;
	bool has_extra() const;

	unsigned indexOf(TreeNode* child) const;
	unsigned indexOf(const T& key) const;

	std::pair<T, TreeNode*> split();
	TreeNode* merge(TreeNode* rightChild);

	TreeNode* getBranch(unsigned position) const;
	void setBranch(unsigned position, TreeNode* branch);
	void addBranch(unsigned position, TreeNode* branch);
	void removeBranch(unsigned position);

	T getKey(unsigned position) const;
	void setKey(unsigned position, const T& newKey);
	void addKey(unsigned position, const T& key);
	void removeKey(unsigned position);
};

template<typename T, const unsigned ORDER>
unsigned TreeNode<T, ORDER>::size() const {
	return _size;
}

template<typename T, const unsigned ORDER>
bool TreeNode<T, ORDER>::is_leaf() const {
	for(unsigned i = 0; i <= _size; ++i) {
		if(branches[i]) {
			return false;
		}
	}
	return true;
}

template<typename T, const unsigned ORDER>
bool TreeNode<T, ORDER>::is_full() const {
	return _size >= ORDER;
}

template<typename T, const unsigned ORDER>
bool TreeNode<T, ORDER>::is_enough() const {
	return _size >= std::ceil(ORDER / 2.0) - 1;
}

template<typename T, const unsigned ORDER>
bool TreeNode<T, ORDER>::has_extra() const {
	return _size > std::ceil(ORDER / 2.0) - 1;
}

template<typename T, const unsigned ORDER>
unsigned TreeNode<T, ORDER>::indexOf(TreeNode* child) const {
	int index = 0;
	for(; index <= _size; index++) {
		if(branches[index] == child) {
			break;
		}
	}
	return index;
}

template<typename T, const unsigned ORDER>
unsigned TreeNode<T, ORDER>::indexOf(const T& key) const {
	int index = 0;
	while(index < _size) {
	    if(key > keys[index]) {
	    	index++;
	    }
	    else {
	    	break;
	    }
	}
	return index;
}

template<typename T, const unsigned ORDER>
std::pair<T, TreeNode<T, ORDER>*> TreeNode<T, ORDER>::split() {
	unsigned mid = size() / 2;
	TreeNode* rightHalf = new TreeNode;
	rightHalf->parent = parent;

	for(unsigned i = mid + 1; i < _size; ++i) {
		rightHalf->addBranch(rightHalf->size(), branches[i]);
		branches[i] = nullptr;
		rightHalf->addKey(rightHalf->size(), keys[i]);
		keys[i] = T();
	}

	rightHalf->addBranch(rightHalf->size(), branches[_size]);
	branches[_size] = nullptr;

	_size = mid;
	if(rightHalf->size() == 0) {
		delete rightHalf;
		rightHalf = nullptr;
	}
	return std::make_pair(keys[mid], rightHalf);
} 

template<typename T, const unsigned ORDER>
TreeNode<T, ORDER>* TreeNode<T, ORDER>::merge(TreeNode* rightChild) {
	if(rightChild) {
		for(unsigned i = 0; i < rightChild->_size; ++i) {
			addBranch(_size + 1, rightChild->branches[i]);
			rightChild->branches[i] = nullptr;
			keys[_size++] = rightChild->keys[i];
			rightChild->keys[i] = T();
		}
		addBranch(_size + 1, rightChild->branches[rightChild->_size]);
		rightChild->_size = 0;
	}
	return this;
}

template<typename T, const unsigned ORDER>
TreeNode<T, ORDER>* TreeNode<T, ORDER>::getBranch(unsigned position) const {
	return branches[position];
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::setBranch(unsigned position, TreeNode* branch) {
	branches[position] = branch;
	if(branches[position]) {
		branches[position]->parent = this;
	}
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::addBranch(unsigned position, TreeNode* branch) {
	for(unsigned i = _size + 1; i > position; --i) {
		branches[i] = branches[i - 1];
	}
	branches[position] = branch;
	if(branches[position]) {
		branches[position]->parent = this;
	}
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::removeBranch(unsigned position) {
	for(unsigned i = position; i < _size; ++i) {
		branches[i] = branches[i + 1];
	}
	branches[_size] = nullptr;
}

template<typename T, const unsigned ORDER>
T TreeNode<T, ORDER>::getKey(unsigned position) const {
	if(position < _size) {
		return keys[position];
	}
	else {
		return T();
	}
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::setKey(unsigned position, const T& newKey) {
	if(position < _size) {
		keys[position] = newKey;
	}
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::addKey(unsigned position, const T& key) {
	if(position <= _size) {
		for(unsigned i = _size; i > position; --i) {
			keys[i] = keys[i - 1];
		}
		keys[position] = key;
		_size++;
	}
}

template<typename T, const unsigned ORDER>
void TreeNode<T, ORDER>::removeKey(unsigned position) {
	if(position < _size) {
		for(unsigned i = position; i < _size - 1; ++i) {
			keys[i] = keys[i + 1];
		}
		--_size;
	}
}	

#endif // TREE_NODE_HPP
