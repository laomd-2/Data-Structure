#ifndef TEST_H
#define TEST_H
#include "Trie.hpp"
#include <iostream>
using namespace std;

template<typename T>
int generate(T* str, T begin, int maxLength) {
	int tmp;
	int length = 0;
	for (; length < maxLength; ++length)
	{
		tmp = rand() % (maxLength + 1);
		if(tmp == maxLength && length) {
			break;
		}
		else {
			str[length] = begin + tmp;
		}
	}
	return length;
}

void testChar() {
	Trie<char> mytree;

	char str[27]= {0};

	int count = 10;
	int length;
	const int maxLength = 3;

	cout << "insert:" << endl;
	for (int i = 0; i < count; ++i)
	{
		length = generate(str, 'a', maxLength);
		cout << str << ' ';
		mytree.insert(str, length);
	}
	cout << endl << "size is " << mytree.size() << endl;

	cout << endl << "search:" << endl;
	cout << str << ' ';
	cout << (mytree.search(str, length) != nullptr) << ' ';
	
	for (int i = 0; i < count; ++i)
	{
		length = generate(str, 'a', maxLength);
		cout << str << ' ';
		cout << (mytree.search(str, length) != nullptr) << ' ';
	}

	cout << endl << "remove:" << endl;
	for (int i = 0; i < 3; ++i)
	{
		length = generate(str, 'a', maxLength);
		cout << str << ' ';
		mytree.remove(str, length);
	}
	cout << endl << "size is " << mytree.size() << endl;

	auto visit = [](char *s) {
		if (s)
		{
			cout << s << ' ';
		}
	};
	mytree.preOrder(visit);
	cout << endl;
}


#endif // TEST_H
