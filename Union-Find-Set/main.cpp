#include <iostream>
#include <vector>
#include "source.h"
using namespace std;

int main(int argc, char const *argv[])
{
	int cnt;
	cin >> cnt;

	vector<int> computers(cnt);

	for (int i = 0; i < cnt; ++i)
	{
		cin >> computers[i];
	}

	unionFindSet myset(computers);

	int times;
	int a, b;
	cin >> times;
	while(times--) {
	    cin >> a >> b;
	    myset.unite(a, b);
	}
	
	cin >> times;
	while(times--) {
	    cin >> a >> b;
	    cout << boolalpha << myset.is_connected(a, b) << endl;
	}
	cin >> a;
	cout << myset.numOfMember(a) << endl;
	cout << myset.numOfSets() << endl;
	return 0;
}	