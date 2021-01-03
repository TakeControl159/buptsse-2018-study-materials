#include "test.h"
#include "Work.h"
#include <iostream>
using namespace std;

test::test()
{

}

test::~test()
{

}
int main()
{
	Work work;
	work.find(0);
	work.output();
	system("pause");
	return 0;
}