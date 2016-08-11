#pragma once
#include"stdafx.h"
class HuffmanTree;

class HuffmanTreeNode
{
	friend class FileCompress;
	friend class HuffmanTree;
public:
	HuffmanTreeNode( const int time,const unsigned char&data = 0)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _data(data)
		, _times(time)
	{}
public:
	~HuffmanTreeNode()
	{}

	const unsigned char _data;
private:
	HuffmanTreeNode * _left;
	HuffmanTreeNode * _right;
	HuffmanTreeNode * _parent;
	int _times;
};



class HuffmanTree
{
public:
	HuffmanTree()
		:_root(NULL)
	{}
	~HuffmanTree()
	{
		clear();
	}
	void clear()
	{
		_clear(_root);
		_root = NULL;

	}
	void _clear(HuffmanTreeNode *root)
	{
		if (root)
		{
			if (root->_left == NULL &&root->_right == NULL)
			{
				delete root;
				root = NULL;
			}

			else
			{
				_clear(root->_left);
				_clear(root->_right);
			}
		}
	}
	HuffmanTreeNode* getRoot()const 
	{
		return _root;
	}
	//��ȡ�ļ�������huffmanTree����  ����EOF����
	HuffmanTreeNode* SetHuffmanTree(const int* countTimes)
	{
		_leafVec.clear();
		vector<HuffmanTreeNode*> nodeVec;

		for (int i = 0; i < 256; ++i)
		{
			if (countTimes[i] != 0)
			{
				HuffmanTreeNode* newNode = new HuffmanTreeNode(countTimes[i], i);
				nodeVec.push_back(newNode);		//���ڽ����ã���̬�䶯
			}
		}
		while (nodeVec.size()>1)
		{
			//�ҵ���С������������������
			HuffmanTreeNode* cur1 = FindMin(nodeVec);
			HuffmanTreeNode* cur2 = FindMin(nodeVec);
			HuffmanTreeNode* insertNode = new HuffmanTreeNode(cur1->_times + cur2->_times);

			insertNode->_left = cur1;
			insertNode->_right = cur2;
			cur1->_parent = cur2->_parent = insertNode;

			nodeVec.push_back(insertNode);
		}
		_root = nodeVec[0];
	}
	
	void Show()
	{
		_Show(_root);
	}
	void _Show(HuffmanTreeNode* root)
	{
		if (root == NULL)
			return;
		else if (root->_left == NULL&root->_right == NULL)
		{
			cout << root->_data;
		}
		_Show(root->_left);
		_Show(root->_right);
	}
protected:
	//��������huffmanTree
	HuffmanTreeNode* FindMin(vector<HuffmanTreeNode*>&ve)
	{
		HuffmanTreeNode* ret = ve[0];
		int reti = 0;
		for (int i = 1; i < ve.size(); ++i)
		{
			if (ve[i]->_times < ret->_times)
			{
				ret = ve[i];
				reti = i;
			}
		}
		ve.erase(ve.begin() + reti);
		return ret;
	}
protected:
	HuffmanTreeNode* _root;
public:
	vector<HuffmanTreeNode*> _leafVec;	//Ҷ�ӽڵ㱣��
};