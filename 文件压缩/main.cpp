#define _CRT_SECURE_NO_WARNINGS
#include"FileCompress.h"
#include"HuffmanTree.h"


int main()
{
	FileCompress fc;
	int beg1 = ::GetTickCount();
	fc.Compress("Test.txt");
	int end1 = ::GetTickCount();
	fc.UnCompress("Test.txt");
	int end2 = ::GetTickCount();
	cout << "ѹ��" << end1 - beg1 << endl;
	cout << "��ѹ" << end2 - end1 << endl;
	system("pause");
}
