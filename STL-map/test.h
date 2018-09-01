#ifndef __TEST_H_
#define __TEST_H_
#include <iostream>
#include <string>
#include "laomd_map.h"
using namespace std;

template <typename T, typename C>
void testTraverse(const Map<T, C>& m) {
	for (auto it = m.begin(); it != m.end(); ++it) {
		cout << '(' << it->first << ',' << it->second << ") ";
	}
	cout << endl;
}
void testConstructors() {
    Map<int, int> m1;
    testTraverse(m1);
    
	int arr[] = {1,5,2,8,0};
	Map<int, int> m2(arr, arr + 5);
	testTraverse(m2);
	
	Map<int, int> m3({9,8,7,6,1});
	testTraverse(m3);
	
	Map<int, int> m4(std::move(m3));
	testTraverse(m3);
	testTraverse(m4);
}
void testInsert() {
	Map<string, int> m;
	m.insert(std::make_pair("laomd", 0));
	m.insert(std::make_pair("lalala", 1));
	m.insert(std::make_pair("laomd", 2));
	testTraverse(m);
	
	m["lueluelue"] = 10;
	m["lalala"]++;
	testTraverse(m);
}
void testErase() {
	Map<string, int> m;
	m["laomd"] = 10;
	m["lalala"] = 1;
	m.erase(m.begin());
	m.erase("lalala");
	m.erase("hahaha");
	testTraverse(m);
}
#endif
