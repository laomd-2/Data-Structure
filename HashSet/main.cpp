#include <iostream>
#include <string>
#include <functional>
#include <cstdlib>
#include <ctime>
#include "HashSet.h"
#include "test.h"
using namespace std;

int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	HashSet<MyClass> myset;

	const unsigned count = 40;

	for(unsigned i = 0; i < count; ++i) {
		auto num = MyClass(to_string(rand() & 31), i);
		cout << num << ' ';
		myset.insert(num);
	}
	cout << endl;

	cout << myset;

	auto it = myset.find(MyClass("24", 1));
	if (it != myset.end())
	{
		cout << *it;
	}
	else {
		cout << "Not exist";
	}
	cout << endl;
	return 0;
}