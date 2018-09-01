#ifndef __TEST_H_
#define __TEST_H_
#include <iostream>
#include <string>
#include "laomd_hash_map.h"
using namespace std;

template <typename T, typename C>
void testTraverse(const HashMap<T, C>& m) {
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << '(' << it->first << ',' << it->second << ") ";
	}

	cout << endl;
}
void testConstructors() {
    HashMap<int, int> m1;
    testTraverse(m1);
    
	pair<int, int> arr[] = {std::make_pair(1, 3)};
	HashMap<int, int> m2(arr, arr + sizeof(arr) / sizeof(*arr));
	testTraverse(m2);
	
	HashMap<int, int> m3({std::make_pair(1, 2)});
	testTraverse(m3);
	
	HashMap<int, int> m4(std::move(m3));
	testTraverse(m3);
	testTraverse(m4);
}
void testInsert() {
	HashMap<string, int> m;
	m.insert(std::make_pair("laomd", 0));
	m.insert(std::make_pair("lalala", 1));
	m.insert(std::make_pair("laomd", 2));
	testTraverse(m);
	
	m["lueluelue"] = 10;
	m["lalala"]++;
	testTraverse(m);
}
void testErase() {
	HashMap<string, int> m;
	m["laomd"] = 10;
	m["lalala"] = 1;
	m.erase(m.begin());
	m.erase("lalala");
	m.erase("hahaha");
	testTraverse(m);
}
#endif
