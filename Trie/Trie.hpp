#ifndef TRIE_HPP
#define TRIE_HPP
#include <map>
#include <algorithm>
using namespace std;

template<typename T>
class Trie {
public:
	struct TreeNode
	{
		T* value = nullptr;
		std::map<T, TreeNode*> branches;
	};

	using size_type = size_t;

public:
	Trie();
	~Trie();
	void insert(T* target, size_type length);
	void remove(T* target, size_type length);
	const TreeNode* search(T* target, size_type) const;

	size_type size() const;
	bool empty() const;

	template<typename VisitType>
	void preOrder(const VisitType&) const;

private:
	TreeNode* root;
	size_type _size;

	TreeNode* find(T* target, size_type) const;

	template<typename VisitType>
	static void preOrder(TreeNode*, const VisitType&);

	static void destroy(TreeNode*);
};


template<typename T>
Trie<T>::Trie() {
	_size = 0;
	root = new TreeNode();
}

template<typename T>
Trie<T>::~Trie() {
	destroy(root);
}


template<typename T>
typename Trie<T>::size_type Trie<T>::size() const {
	return _size;
}

template<typename T>
bool Trie<T>::empty() const {
	return size() == 0;
}


template<typename T>
void Trie<T>::insert(T* target, size_type length) {
	TreeNode* cur = root;
	int pos = 0;
	while(pos < length) {
		TreeNode*& node = cur->branches[target[pos]];
	    if (!node)
	    {
	    	node = new TreeNode;
	    }
	    cur = node;
	    pos++;
	    if (pos == length)
	    {
	    	if (!node->value)
	    	{
	    		node->value = new T[length]{T()};
		    	copy(target, target + length, node->value);
		    	_size++;
	    	}
	    	break;
	    }
	}		
}

template<>
void Trie<char>::insert(char *target, size_type length) {
	TreeNode* cur = root;
	int pos = 0;
	while(pos < length) {
		TreeNode*& node = cur->branches[target[pos]];
	    if (!node)
	    {
	    	node = new TreeNode;
	    }
	    cur = node;
	    pos++;
	    if (pos == length)
	    {
	    	if (!node->value)
	    	{
	    		node->value = new char[length + 1]{0};
		    	copy(target, target + length, node->value);
		    	_size++;
		    	break;
	    	}
	    }
	}		
}

template<typename T>
void Trie<T>::remove(T* target, size_type length) {
	TreeNode* node = find(target, length);
	if (node)
	{
		delete[] node->value;
		node->value = nullptr;
		_size--;
	}
}

template<typename T>
typename Trie<T>::TreeNode* Trie<T>::find(T* target, size_type length) const {
	TreeNode* cur = root;
	int pos = 0;
	while(pos < length && cur) {
	    cur = (cur->branches)[target[pos++]];
	}
	if (cur && cur->value) {
		return cur;
	}
	else {
		return nullptr;
	}
}

template<typename T>
const typename Trie<T>::TreeNode* Trie<T>::search(T* target, size_type length) const {
	return find(target, length);
}

template<typename T>
template<typename VisitType>
void Trie<T>::preOrder(const VisitType& visit) const {
	preOrder(root, visit);
}

template<typename T>
template<typename VisitType>
void Trie<T>::preOrder(TreeNode* treeRoot, const VisitType& visit) {
	if (treeRoot)
	{
		visit(treeRoot->value);
		for(auto& i : treeRoot->branches) {
			preOrder(i.second, visit);
		}
	}
}

template<typename T>
void Trie<T>::destroy(TreeNode* treeRoot) {
	if (treeRoot)
	{
		for(auto& i : treeRoot->branches) {
			destroy(i.second);
		}
		if (treeRoot->value)
		{
			delete[] treeRoot->value;
		}
		delete treeRoot;
	}
}
#endif // TRIE_HPP
