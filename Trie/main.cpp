#include <cstdlib>
#include <ctime>
#include "test.h"
int main(int argc, char const *argv[])
{
	srand(time(nullptr));

	testChar();	
	return 0;
}