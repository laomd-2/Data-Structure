#ifndef __LAOMD_LIST_H_
#define __LAOMD_LIST_H_
#include <iostream>
#include "laomd_list.h"
using namespace std; 

void testTraverse(List<int>& alist) {
	for (auto it = alist.begin(); it != alist.end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}
void testConstructor() {
//	default
	List<int> l1; 
//	fill
	List<int> l2(4u);
	List<int> l3(4u, 2);
	testTraverse(l2);
	testTraverse(l3);
//	range
	int arr[] = {1,2,3,4};
	List<int> l4(arr, arr + 4);
	testTraverse(l4); 
//	copy
	List<int> l5(l4);
	l5.insert(l5.begin(), 5);
	testTraverse(l5);
	testTraverse(l4);
//	move
	List<int> l6(std::move(l4));
	testTraverse(l4);
	testTraverse(l6);
}
void testInsert(List<int>& alist) {
	for (int i = 0; i < 10; i++) {
		alist.push_back(i);
	}
	for (int i = 0; i < 10; i++) {
		alist.push_front(i);
	}	
	alist.insert(++alist.begin(), 100);
	alist.insert(--alist.end(), 1000);
	testTraverse(alist);
}
void testAssign(List<int>& alist) {
	alist.assign(4u, 4);
	testTraverse(alist);
	int arr[] = {1,2,3,4};
	alist.assign(arr, arr + 4);
	testTraverse(alist);
	
	List<int> newlist;
	newlist.assign(10u, 0);
	testTraverse(newlist);
}
void testErase(List<int>& alist) {
	alist.assign(10u, 2);
	testTraverse(alist);
	while (!alist.empty()) {
		alist.erase(alist.begin());
		testTraverse(alist);
	}
	alist.assign(8u, 4);
	alist.erase(++alist.begin(), --alist.end());
	testTraverse(alist);
}
void testRemove(List<int>& alist) {
    int arr[] = {1,3,2,6,3,10,1,4,10,10,2,2};
	alist.assign(arr, arr + 12);
	alist.remove(10);
	testTraverse(alist);
	alist.remove_if([](int a) {
		return a & 1;
	});
	testTraverse(alist);
}
void testSwap(List<int>& alist) {
	alist.assign(3u, 3);
	List<int> newlist;
	newlist.insert(newlist.begin(), 10);
	newlist.swap(alist);
	testTraverse(alist);
	testTraverse(newlist);
}
void testResize(List<int>& alist) {
	
}
void testUnique(List<int>& alist) {
    int arr[] = {1,3,3,2,6,6,3,10,1,4,10,10,2,2};
	alist.assign(arr, arr + 14);
	alist.unique();
	testTraverse(alist);
}
void testSplice(List<int>& alist) {
	alist.assign(4u, 2);
	alist.push_back(10);
	alist.push_front(3);
	
	List<int> newlist = alist;
	alist.splice(alist.begin(), newlist);
	testTraverse(alist);
	testTraverse(newlist); 
	
	newlist.assign(3u, 3);
	alist.splice(alist.begin(), newlist, ++newlist.begin(), --newlist.end());
	testTraverse(alist);
	testTraverse(newlist); 
	
}
void testMerge(List<int>& alist) {
	alist.assign(3u, 4);
	alist.push_back(5);
	List<int> newlist(4u, 2);
	newlist.push_back(6);
	alist.merge(newlist);
	testTraverse(alist);
	testTraverse(newlist);
}
void testSort(List<int>& alist) {
	int arr[] = {1,3,2,6,3,10,1,4,10,10,2,2};
	alist.assign(arr, arr + 12);
	alist.sort();
	testTraverse(alist);
}
void testReverse(List<int>& alist) {
	int arr[] = {1,3,2,6,3,10,1,4,10,10,2,2};
	alist.assign(arr, arr + sizeof(arr) / sizeof(*arr));
	alist.reverse();
	testTraverse(alist);	
}
#endif
