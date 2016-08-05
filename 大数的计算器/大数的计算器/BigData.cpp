#include"BigData.h"

///////////////////////////////////////////////////////////////////
//默认构造函数
BigData::BigData()
:m_strData("")
, m_value(0)
{

}
//参数是在 INT64 以内的数的构造函数
BigData::BigData(INT64 num)
:m_value(num)
{
	//执行数字转换成字符串的操作
	INT64toStr(num);
}
//参数是一个字符串，字符串表示的数超出 INT64 表达的范围
BigData::BigData(const char* Data)
{
	INT64 iTemp = 0;
	char symbol;
	assert(Data);
	char *pData = (char *)Data;//不强转就无法赋值
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
	m_value = iTemp;        //m_value 可能会溢出~~~~~~



	//if (0 == strcmp(Data, "0"))
	//{
	//	m_strData.append(1, '0');
	//	return;
	//}
}
///////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////
/*大数的加法*/
BigData BigData::operator+(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{//保证m_value计算的有效性
		if (m_strData[0] != b.m_strData[0])
		{
			return BigData(m_value + b.m_value);
		}
		else
		{//同号的加法可能溢出
			if ('-' == m_strData[0] && MININT - m_value <= b.m_value)
			{//两个负数之和不能小于 MININT
				return BigData(m_value + b.m_value);
			}
			if ('+' == m_strData[0] && MAXINT - m_value >= b.m_value)
			{//两个整数之和不能大于 MAXINT
				return BigData(m_value + b.m_value);
			}
		}
	}
	//必须使用bigData的运算方法了
	string strret;
	if (m_strData[0] == b.m_strData[0])
	{//同号相加
		strret = Add(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}
	else
	{//异号相加 == 相减
		strret = Sub(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}

}
/*大数的减法*/
BigData BigData::operator-(BigData b)
{
	if (!IsINT64OverFlow() && !b.IsINT64OverFlow())
	{
		if (m_strData[0] != b.m_strData[0])
		{
			if (('-' == m_strData[0] && MININT + b.m_value<m_value) ||
				'+' == m_strData[0] && MAXINT + b.m_value>m_value)
			{//异号相减结果不溢出直接返回
				return BigData(m_value - b.m_value);
			}
		}
		else
		{//同号相减直接返回
			return BigData(m_value - b.m_value);
		}
	}

	//1.至少有一个溢出/结果会溢出
	//2.相减的结果溢出

	if (m_strData[0] != b.m_strData[0])
	{//异号的减法 == 加法
		string strret = Add(m_strData, b.m_strData);
		return BigData(strret.c_str());
	}
	else
	{//同号减法 == 减法
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
	strret[0] = Symbol;                ///////////////注意符号位的写法
	int CS = 0;
	for (int i = 1; i < left.size(); i++)
	{
		int ctmp;
		ctmp = left[lSize - i] - '0' + CS;
		if (i < rSize)
		{
			ctmp += right[rSize - i] - '0';
		}
		//本位和进位的处理
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
	/*保证 left 的绝对值大于 right*/
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
		if (tmp < 0)      //这一位不够减，需要借位
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
/*判断是否溢出*/
bool BigData::IsINT64OverFlow()
{
	string strtmp;

	//long long 的取值范围为 -9223372036854775808 ~ +9223372036854775807
	if ('-' == m_strData[0])
	{
		strtmp = "-9223372036854775808";
	}
	else
	{
		strtmp = "+9223372036854775807";
	}
	if (m_strData.size() > strtmp.size())  //溢出
	{
		return true;
	}
	if (m_strData.size() == strtmp.size() && m_strData>strtmp)
	{
		return true;
	}
	return false;
}
/*将整形转化为string类型*/
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
/*重载输入输出*/
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