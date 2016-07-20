#include"bigdata.h"

string BigData::INT64ToString(INT64 lldata)
{
	//1ȷ������λ
	//2��λ�洢

	INT64 tmp = lldata;
	string retData("+");
	if (lldata < 0)
	{
		retData[0] = '-';
		tmp *= -1;
	}
	while (tmp)
	{
		int cTemp = (tmp) % 10+'0';
		retData.append(1,cTemp);
		tmp /= 10;		
	}

//	m_strData = retData;
	long Size = retData.size()-1;
	for (long begin = 1; begin<= Size; ++begin, --Size)
	{
		::swap(retData[begin], retData[Size]);
	}
	
	return retData;
}

ostream& operator<<(ostream& _out,const BigData&data)
{
	if (string("") != data.m_strData)
	{
		_out << data.m_strData;
	}
	else
	{
		_out << data.m_llData;
	}
	return _out;
}

istream& operator>>(istream& _in, BigData&data)
{
	//�����ַ������ж��Ƿ�
	return _in;
}

BigData operator+(const BigData&)
{
	//
	return BigData();
}

//atoi �ص㣺00123abc  --��123
//			 00 123abc --��0
//so��1����ǰ�ÿո�
//2 ����ǰ��0��
//3���������ּ�������
void BigData::TryInitByStr(const char *str)
{

	//�Ϸ�����Ȼ���ж��Ƿ����
	string retData;
	retData.append(1, '+');

	//ȷ������λ�Լ���һ����Чλ
	int index = 0;
	int FlagOfData = 1;

	//ȥ��ǰ�ÿո�
	while (*(str + index) == ' ')
		index++;
	if (str[index] == '-')
	{
		retData[0] = '-';
		index += 1;
		FlagOfData = -1;
	}
	else if (str[index] == '+')
		index += 1;

	//ȥ��ǰ��0
	while (*(str + index) == '0')
	{
		index++;
		continue;
	}

	INT64 m_TempData = 0;
	//�õ���һ����0λ�á�ͬʱֱ��ʵ�ֳ�ʼ��m_llData
	while (*(str + index) >= '0'&&*(str + index) <= '9')
	{
		retData.append(1, *(str + index));
		m_TempData = m_TempData * 10 + (*(str + index) - '0');
		index++;
	}

	//��������浽m_llData;
	m_TempData *= FlagOfData;
	m_llData = m_TempData;

	//�õ��Ϸ�����  �����ַ���ģʽ����
	//�Ƚ��ж��Ƿ����
	if (retData[0] == '-'
		&&
		(retData.size() == 20
		&& (strcmp(retData.c_str(), "-9223372036854775808") > 0)
		|| retData.size() > 20   //�Ϸ�����������ȹ���
		)
		)
	{
		m_strData = retData;
		return;
	}
	if (retData[0] == '+'
		&&
		(retData.size() == 20
		&& (strcmp(retData.c_str(), "+9223372036854775807") > 0)
		||retData.size()>20	
		)
		)
	{
		m_strData = retData;
		return;
	}
	m_strData = "";
}

BigData BigData::operator+(const BigData&data)
{
	//������������û����������Ҳû�����
	if (data.m_strData.size() == 0 && m_strData.size() == 0
		&& m_llData + data.m_llData <= LLONG_MAX
		//fuck~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		&&m_llData - data.m_llData >= LLONG_MIN)
	{
		return BigData(m_llData + data.m_llData);
	}
	//������,����������һ�����ʱ
	return Add(data);
}

//���㼸�������
//1����һ���������
//2������û����������ǽ�������
BigData BigData::Add(const BigData & data)
{
	//��������������ת������Ϊstring ���ͣ�Ȼ�����
	//1�õ������ַ�����
	//2���

	string str1 = m_strData == "" ? (INT64ToString(m_llData)) : m_strData;
	string str2 = data.m_strData == "" ? (INT64ToString(data.m_llData)) : data.m_strData;
	
	if (str1.size() < str2.size())
	{
		str1.swap(str2);
	}
	else if (str1.size() == str2.size())
	{
		//�������������ȣ�ͨ��һ�����Ըı䱣֤--------����ֵ������ҡ�
		char temp = str2[0];
		str2[0] = str1[0];

		//����Ҿ���ֵ��ͬ
		if (str1[0]!=temp&&str1[0] == str2[0] && strcmp(str1.c_str(), str2.c_str()) == 0)
		{
			return BigData(INT64(0));
		}
		if (strcmp(str1.c_str(), str2.c_str())<0)
		{
			str2[0] = temp;
			str1.swap(str2);
		}
		str2[0] = temp;

	}
	size_t sIndex1 = str1.size()-1;
	size_t sIndex2 = str2.size()-1;
	//˳��ӣ�����棬
	//����������

	string retData;
	//ͬ��
	if (str1[0] == str2[0])
	{
		//����λ
		retData.append(1, str1[0]);

		int Step = 0;
		while (sIndex1)
		{
			int ret;
			if (sIndex2 != 0)
			{
				ret = str1[sIndex1] - '0' + str2[sIndex2] - '0' + Step;
				sIndex2--;
			}
			else
			{
				ret = str1[sIndex1] - '0' + Step;
			}
			Step = ret / 10;
			retData.append(1, ret % 10 + '0');
			sIndex1--;
		}

		if (Step != 0)
		{
			retData.append(1, Step + '0');
		}
	}
	//����Ҿ���ֵ�������
	else
	{
		retData.append(1, str1[0]);
		int Step = 0;
		while (sIndex1)
		{
			int ret;
			if (sIndex2 != 0)
			{
				ret = str1[sIndex1] - str2[sIndex2--] + Step;
			}
			else
			{
				ret = str1[sIndex1] - '0' + Step;
			}
			Step = (ret-9) / 10;
			retData.append(1, (ret+10) % 10 + '0');
			sIndex1--;
		}
	}

	
	long Size = retData.size() - 1;
	for (long begin = 1; begin <= Size; ++begin, --Size)
	{
		::swap(retData[begin], retData[Size]);
	}

	return BigData(retData.c_str());
}

BigData BigData::operator-(const BigData&data)
{
	//������������û����������Ҳû�����
	if (data.m_strData.size() == 0 && m_strData.size() == 0
		&& m_llData - data.m_llData <= LLONG_MAX
		//fuck~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		&&m_llData + data.m_llData >= LLONG_MIN)
	{
		return BigData(m_llData - data.m_llData);

	}
	//������,����������һ�����ʱ
	return Sub(data);
}

BigData BigData::Sub(const BigData& data)
{
	BigData retData(data);
	if (retData.m_strData == "")
	{
		retData.m_llData *= -1;
	}
	else if (retData.m_strData[0] == '+')
	{
		retData.m_strData[0] = '-';
	}
	else
	{
		retData.m_strData[0] = '+';
	}
	return *this+retData;
}


BigData BigData::operator*(const BigData&data)
{
	//������������û����������Ҳû�����
	if (data.m_strData.size() == 0 && m_strData.size() == 0
		&& m_llData * data.m_llData <= LLONG_MAX
		//fuck~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		&&m_llData * data.m_llData >= LLONG_MIN)
	{
		return BigData(m_llData * data.m_llData);
	}
	//������,����������һ�����ʱ
	return Mul(data);
}


BigData BigData::Mul(const BigData&data)
{
	//str1����С��str2.
	string str1 = m_strData == "" ? (INT64ToString(m_llData)) : m_strData;
	string str2 = data.m_strData == "" ? (INT64ToString(data.m_llData)) : data.m_strData;

	if (str1.size() > str2.size())
	{
		str1.swap(str2);
	}
	BigData retData(INT64(0));
	char retSys = str1[0] == str2[0] ? '+' : '-';

	size_t sIndex1 = str1.size() - 1;

	int count = 0;//����ƫ��0��λ��
	while (sIndex1)
	{
		string tmp;
		tmp.push_back('+');
		
		tmp.append(count, '0');
		size_t sIndex2 = str2.size() - 1;

		//
		count++;
		int Step = 0;
		while (sIndex2)
		{
			//����0ֱ�Ӳ�λ����
			if (str1[sIndex1] == '0')
				break;

			int ret;
			ret = (str1[sIndex1] - '0') * (str2[sIndex2] - '0') + Step;
			
			Step = ret / 10;
			tmp.append(1, ret % 10 + '0');
			sIndex2--;

		}
		if (Step != 0)
		{
			tmp.append(1, Step + '0');
		}

		long Size = tmp.size() - 1;
		for (long begin = 1; begin <= Size; ++begin, --Size)
		{
			::swap(tmp[begin], tmp[Size]);
		}

		retData = retData + BigData(tmp.c_str());
		sIndex1--;
	}

	retData.m_strData[0]= retSys;
	//����
	return retData;
}

BigData BigData::operator/(const BigData&data)
{
	
	if (data.m_strData.size() == 0 && m_strData.size() == 0
		&& m_llData * data.m_llData <= LLONG_MAX
		//fuck~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		&&m_llData * data.m_llData >= LLONG_MIN)
	{
		return BigData(m_llData * data.m_llData);
	}
	//������,����������һ�����ʱ
	return Div(data);
}

BigData BigData::Div(const BigData&data)
{
//	������
	string retData("+");
	if (data.m_llData ==  0)
	{
		cout << "�Ƿ���" << endl;
		exit(1);
	}
	else if (m_llData == 0)
	{
		return BigData(INT64(0));
	}
	
	string str1 = m_strData == "" ? (INT64ToString(m_llData)) : m_strData;
	string str2 = data.m_strData == "" ? (INT64ToString(data.m_llData)) : data.m_strData;

	//����λȷ����
	int retSys = str1[0] == str2[0] ? 1 : -1;

	//�޸ķ���λΪ����֤���㷽��
	str1[0] = str2[0] = '+';

	size_t sIndex1 = str1.size() - 1;
	size_t sIndex2 = str2.size() - 1;
	//���2�ĳ���С��1 ��ô����0
	if (str1.size() < str2.size())
	{
		return BigData(INT64(0));
	}
	//����������.ֱ�ӽ�������õ������λ����
	//������ƫ�ơ�����ʽ����
	else
	{
		BigData result(INT64(0));
		///1022 2222/9911
		//����5�Σ���0  3��
		
		//����
		string res(str1);
		//������
		string divNum(str2);

		while (BigData(res.c_str())>=BigData(divNum.c_str()))
		{
			//��Ϊ111/99����99/11���ֲ��벻��������ͳһ��һλ��

			int loopTime = res.size() - divNum.size() - 1;
			string ret("+");
			//������0;
			if (loopTime>0)
				divNum.append(loopTime, '0');
		
			///����1.�����ֲ��ĳ������
			int retNum = 1;
			while (BigData(res.c_str()) >= BigData(retNum)*BigData(divNum.c_str()))
			{
				retNum = retNum+1;
			}
			//����֮��Ӧ���ǱȽ����1��
			//һ�γ����/[0,99)��
			retNum = retNum-1;
			//if (retNum < 0)
			//	continue;
			if (retNum/10)
			{
				ret.append(1, retNum / 10 + '0');
				ret.append(1, retNum % 10 + '0');
			}
			else
			{
				ret.append(1, retNum + '0');
			}
			//��ͬλ��ʱû�в�0����ʱloopTimeΪ-1������Ҫ����0��
			if (loopTime>0)
				ret.append(loopTime, '0');

			//����������㡣��
			result = result + BigData(ret.c_str());


			BigData tmp = BigData(res.c_str()) - BigData(divNum.c_str())*BigData(INT64(retNum));
			//���³���
			res = tmp.m_strData==""?INT64ToString(tmp.m_llData):tmp.m_strData.c_str();

			//��������ԭ
			divNum = str2;
		}

		//����λ����
		result = result*retSys;
		return result;
	}
}

bool BigData::operator>(const BigData&data)
{
	if (data.m_strData.size() == 0 && m_strData.size() == 0)
	{
		return (m_llData > data.m_llData);
	}
	//������,����������һ�����ʱ
	BigData tmp = (*this) - data;
	if (tmp.m_strData == "")
	{
		if (tmp.m_llData >0)
			return true;
		else
			return false;
	}
	else
	{
		if (tmp.m_strData[0] == '+')
			return true;
		else
			return false;
	}
}
bool BigData::operator==(const BigData&data)
{
	if (data.m_strData.size() == 0 && m_strData.size() == 0)
	{
		return (m_llData == data.m_llData);
	}
	//������,����������һ�����ʱ
	BigData tmp = (*this) - data;

	if (tmp.m_llData == 0)
		return true;
	else
		return false;
}


bool BigData::operator>=(const BigData&data)
{
	return (*this >data || *this == data);

}
bool BigData::operator<(const BigData&data)
{
	return !(*this >data || *this == data);
}
