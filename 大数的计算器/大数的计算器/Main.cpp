#include"BigData.h"

void test()
{
	BigData data1 = "+11111111111111111111111111111";
	BigData data2 = "-222222222222222222222222222222222222";
	cout << data1 + data1 << endl;
	cout << data2 + data2 << endl;
	cout << data1 + data2 << endl;
	cout << data2 + data1 << endl;

	cout << data1 - data1 << endl;
	cout << data2 - data2 << endl;
	cout << data1 - data2 << endl;
	cout << data2 - data1 << endl;
}

int main()
{
	test();
	return 0;
}