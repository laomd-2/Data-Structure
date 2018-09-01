#ifndef __TEST_H_
#define __TEST_H_
#include <iostream>
#include <string>
#include "laomd_set.h"
using namespace std;

template <typename T>
void testTraverse(const Set<T>& s) {
	for (auto it = s.begin(); it != s.end(); ++it) {
		cout << *it << ' ';
	}
	cout << endl;
}
void testConstructors() {
    Set<int> s1;
    testTraverse(s1);
    
	int arr[] = {1,5,2,8,0};
	Set<int> s2(arr, arr + 5);
	testTraverse(s2);
	
	Set<int> s3({9,8,7,6,1});
	testTraverse(s3);
	
	Set<int> s4(std::move(s3));
	testTraverse(s3);
	testTraverse(s4);
}
void testInsert() {
	Set<string> s;
	s.insert("laomd");
	s.insert("lalala");
	s.insert("laomd");
	testTraverse(s);
}
void testErase() {
	Set<string> s;
	s.insert("laomd");
	s.insert("lalala");
	s.erase(s.begin());
	s.erase("hahaha");
	testTraverse(s);
}
#endif
