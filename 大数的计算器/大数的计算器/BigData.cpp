#include"BigData.h"

///////////////////////////////////////////////////////////////////
//Ĭ�Ϲ��캯��
BigData::BigData()
:m_strData("")
, m_value(0)
{

}
//�������� INT64 ���ڵ����Ĺ��캯��
BigData::BigData(INT64 num)
:m_value(num)
{
	//ִ������ת�����ַ����Ĳ���
	INT64toStr(num);
}
//������һ���ַ������ַ�����ʾ�������� INT64 ���ķ�Χ
BigData::BigData(const char* Data)
{
	INT64 iTemp = 0;
	char symbol;
	assert(Data);
	char *pData = (char *)Data;//��ǿת���޷���ֵ
	if ('+' == pData[0] || '-' == pData[0])
	{
		symbol = pData[0];
		pData++;
	}
	else if (*pData >= '0'&&*pData <= '9')
	{
		symbol = '+';
	}
	else
	{
		m_value = 0;
		m_strData = "0";
		return;
	}
	while (*pData == '0')
	{
		pData++;
	}
	m_strData.resize(strlen(pData) + 1);
	m_strData[0] = symbol;
	for (int i = 1; i < strlen(Data) + 1; i++)
	{
		if (*pData >= '0'&&*pData <= '9')
		{
			iTemp = iTemp * 10 + *pData - '0';
			m_strData[i] = *pData;
			pData++;
		}
		else
		{
			break;
		}
	}
	if ('-' == symbol)
	{
		iTemp = 0 - iTemp;
	}
	m_value = iTemp;        //m_value ���ܻ����~~~~~~



	//if (0 == strcmp(Data, "0"))
	//{
	//	m_strData.append(1, '0');
	//	return;
	//}
}
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
/*�����ļӷ�*/
BigData BigData::operator+(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{//��֤m_value�������Ч��
		if (m_strData[0] != b.m_strData[0])
		{
			return BigData(m_value + b.m_value);
		}
		else
		{//ͬ�ŵļӷ��������
			if ('-' == m_strData[0] && MININT - m_value <= b.m_value)
			{//��������֮�Ͳ���С�� MININT
				return BigData(m_value + b.m_value);
			}
			if ('+' == m_strData[0] && MAXINT - m_value >= b.m_value)
			{//��������֮�Ͳ��ܴ��� MAXINT
				return BigData(m_value + b.m_value);
			}
		}
	}
	//����ʹ��bigData�����㷽����
	string strret;
	if (m_strData[0] == b.m_strData[0])
	{//ͬ�����
		strret = Add(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}
	else
	{//������ == ���
		strret = Sub(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}

}
/*�����ļ���*/
BigData BigData::operator-(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		if (m_strData[0] != b.m_strData[0])
		{
			if (('-' == m_strData[0] && MININT + b.m_value<m_value) ||
				'+' == m_strData[0] && MAXINT + b.m_value>m_value)
			{//��������������ֱ�ӷ���
				return BigData(m_value - b.m_value);
			}
		}
		else
		{//ͬ�����ֱ�ӷ���
			return BigData(m_value - b.m_value);
		}
	}

	//1.������һ�����/��������
	//2.����Ľ�����

	if (m_strData[0] != b.m_strData[0])
	{//��ŵļ��� == �ӷ�
		string strret = Add(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}
	else
	{//ͬ�ż��� == ����
		string strret = Sub(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}
}

string BigData::Add(string left, string right)
{
	int lSize = left.size();
	int rSize = right.size();
	char Symbol = left[0];
	if (lSize < rSize)
	{
		swap(lSize, rSize);
		swap(left, right);
	}

	string strret;
	strret.resize(left.size() + 1);
	strret[0] = Symbol;                ///////////////ע�����λ��д��
	int CS = 0;
	for (int i = 1; i < left.size(); i++)
	{
		int ctmp;
		ctmp = left[lSize - i] - '0' + CS;
		if (i < rSize)
		{
			ctmp += right[rSize - i] - '0';
		}
		//��λ�ͽ�λ�Ĵ���
		strret[lSize - i + 1] = ctmp % 10 + '0';
		CS = ctmp / 10;
	}
	strret[1] = CS + '0';
	return strret;
}

string BigData::Sub(string left, string right)
{
	int leftSize = left.size();
	int rightSize = right.size();
	char Symbol = left[0];
	string leftTmp = left, rightTmp = right;
	leftTmp[0] = '+', rightTmp[0] = '+';
	/*��֤ left �ľ���ֵ���� right*/
	if (leftSize < rightSize || leftSize == rightSize && leftTmp < rightTmp)
	{
		swap(leftSize, rightSize);
		swap(left, right);
		if (Symbol == '+')
		{
			Symbol = '-';
		}
		else
		{
			Symbol = '+';
		}
	}

	string result;
	result.resize(leftSize);
	result[0] = left[0];
	int overBit = 0, tmp;
	for (int i = 1; i < leftSize; ++i)
	{
		tmp = left[leftSize - i] - '0' - overBit;
		if (i < rightSize)
		{
			tmp -= right[rightSize - i] - '0';
		}
		if (tmp < 0)      //��һλ����������Ҫ��λ
		{
			overBit = 1;
			tmp += 10;
		}
		else
		{
			overBit = 0;
		}
		result[leftSize - i] = tmp + '0';
	}
	return result;
}
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
/*�ж��Ƿ����*/
bool BigData::IsINT64OverFlow()
{
	string strtmp;

	//long long ��ȡֵ��ΧΪ -9223372036854775808 ~ +9223372036854775807
	if ('-' == m_strData[0])
	{
		strtmp = "-9223372036854775808";
	}
	else
	{
		strtmp = "+9223372036854775807";
	}
	if (m_strData.size() > strtmp.size())  //���
	{
		return true;
	}
	if (m_strData.size() == strtmp.size() && m_strData>strtmp)
	{
		return true;
	}
	return false;
}
/*������ת��Ϊstring����*/
void BigData::INT64toStr(INT64 num)
{
	INT64 temp = num;
	int count = 0;
	if (temp < 0)
	{
		temp = 0 - temp;
	}
	while (temp)
	{
		temp = temp / 10;
		count++;
	}
	m_strData.resize(count + 1);
	if (num < 0)
	{
		m_strData[0] = '-';
	}
	else
	{
		m_strData[0] = '+';
	}
	for (int i = 1; i < count; i++)
	{
		m_strData[count - i] = '0' + num % 10;
		num = num / 10;
	}
}
/*�����������*/
ostream& operator<<(ostream& ostr, BigData b)
{
	if (!b.IsINT64OverFlow())
	{
		ostr << b.m_value << "    ";
	}
	else if (b.m_strData[0] == '+')
	{
		ostr << (char *)b.m_strData.c_str() + 1;
	}
	else
	{
		ostr << b.m_strData;
	}
	return ostr;
}
istream& operator>>(istream& istr, BigData b)
{
	istr >> b.m_value;
	istr >> b.m_strData;
	return istr;
}
///////////////////////////////////////////////////////////////////