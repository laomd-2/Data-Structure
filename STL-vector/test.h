#ifndef TEST_H_
#define TEST_H_
#include <cstdlib>
#include <iostream>
#include "laomd_vector.h"
using namespace std;

void testInsert(Vector<string>& v) {
	for (int i = 0; i < 10; i++) {
		auto s = v.size();
		v.insert(v.begin() + rand() % (s ? s : 1), string(3, 'A' + rand() % 52));
	}
}
void testTraverse(Vector<string>& v) {
	v.traverse([](string a) {
		cout << a << ' ';
	});
	cout << endl;
}
void testErase(Vector<string>& v) {
	while(v.size() != 0){
		int pos = rand() % v.size();
		cout << "erase " << pos << endl;
		v.erase(v.begin() + pos);
		testTraverse(v);
	}
	v.push_back("haha");
	testTraverse(v);
	v.pop_back();
	testTraverse(v);
}
void testRemove(Vector<string>& v) {
	for (int i = 0; i < 5; i++) {
		string key = string(3, 'A' + rand() % 52);
		cout << "remove " << key << endl;
		v.remove((key));
		testTraverse(v);
	}
}
void testCopy(Vector<string>& v) {
    Vector<string> vv(v);
	testTraverse(vv);
	testErase(vv);
	testTraverse(v);
	
	Vector<string> vvv(std::move(vv));
	testTraverse(vv);
	testInsert(vvv);
	testTraverse(vv);
	testTraverse(vvv); 
}
void testResize(Vector<string>& v) {
	v.resize(v.size() * 2 + 1);
	testTraverse(v);
	v.resize(3);
	testTraverse(v);
} 
void testSort(Vector<string>& v) {
	v.sort();
	testTraverse(v);
} 
void testUnique(Vector<string>& v) {
	v.unique();
	testTraverse(v);
} 
void testLower_bound(Vector<string>& v) {
	cout << v.lower_bound("aaa") << endl;
} 
void testReserve(Vector<string> v) {
	v.reserve(10);
	try {
		v[9];
	}
	catch (std::exception& e) {
		cout << e.what() << endl;
	}
	cout << v.size() << ' ' << v.capacity() << endl;
}
void testAssign(Vector<string>& v) {
	v.assign(10u, "lalala");
	testTraverse(v);
}
void testSwap(Vector<string>& v) {
    Vector<string> vv;
    vv.insert(vv.begin(), "lalala");
    vv.swap(v);
    testTraverse(v);
    testTraverse(vv);
}
#endif
