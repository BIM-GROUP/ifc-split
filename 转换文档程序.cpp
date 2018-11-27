#include <stdio.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int nuu = 0;
int num = 0;

//����׽���Ķ����ż�¼��ջ�еĺ���
void WriteClass(int* N, int n)
{
	cout << n << " ";
	N[n] = 1;	
}

//��ȡ�����ĺ���
int Com()
{
	string sn;
	ifstream in("123.ifc");
	int n = 0;
	const char* c;
	for (string str; getline(in, str);)
	{
		if (str != "")
		{
			c = str.c_str();
			//cout << c << endl;
			sn = "";
			if (*c == '#' || *c == '#')
			{
				for (; *c != '=';)
				{
					c++;
					//cout << "ִ�б�����" << *c << endl;
					if (*c == '=')
					{
						//cout << "ִ������" << endl;
						break;
					}
					if (*c != ' ')
					{
						//cout << "ִ��д�룺" << *c << endl;
						sn.append(1, *c);
					}
				}
				//cout << "���ڽ� " << sn << " д��n" << endl;
				n = atoi(sn.c_str());
			}
		}
	}
	if (n == 0)
		cout << endl << "û�м�⵽��Ҫ��ֵ�IFC�ļ���";
	else
		cout << endl << "����ĵ�һ���� " << n << "  ��ʵ������" << endl;
	return n;
}

//��ȡ��ǰʵ����ŵĺ���
int ClassNum(const char* c)
{
	string sn;
	if (*c == '#' || *c == '#')
	{
		for (; *c != '=';)
		{
			c++;
			//cout << "ִ�б�����" << *c << endl;
			if (*c == '=' || *c == ',' || *c == ')')
			{
				//cout << "ִ������" << endl;
				break;
			}
			if (*c != ' ')
			{
				//cout << "ִ��д�룺" << *c << endl;
				sn.append(1, *c);
			}
		}
		//cout << "���ڽ� " << sn << " д��n" << endl;
		return atoi(sn.c_str());
	}
}

//�Ա�ʵ�������Ƿ�Ϊ���ҵ�Ŀ��ʵ������
bool FindClass(const char* c, string FC)
{
	string str = c;
	string s;
	for (int i = 1; i < size(str); i++)
	{
		c++;
		if (*c == '=')
		{
			for (; i < size(str); i++)
			{
				c++;
				if (*c != ' ')
				{
					if (*c == '(')
						break;
					s.append(1, *c);
				}

			}
			break;
		}
	}
	if (s == "IFCPROJECT")
	{
		cout << endl << "�ҵ�����ʵ������" << s;
		return true;
	}
	if (s == "IFCSITE")
	{
		cout << endl << "�ҵ�����ʵ������" << s;
		return true;
	}
	if (s == "IFCBUILDING")
	{
		cout << endl << "�ҵ�����ʵ������" << s;
		return true;
	}
	if (s == "IFCBUILDINGSTOREY")
	{
		cout << endl << "�ҵ�����ʵ������" << s;
		return true;
	}
	if (s == "IFCSPACE")
	{
		cout << endl << "�ҵ�����ʵ������" << s;
		return true;
	}
	if (s == FC)
	{
		cout << endl << "�ҵ�Ŀ��ʵ������" << s;
		nuu++;
		return true;
	}
	return false;
}

//ɨ��ʵ���е��õ�ʵ��
void CatchClass(int* N,string* fill, int n)
{
	const char* c = fill[n].c_str();
	int w;
	for (int i = 0; i < size(fill[n]); i++)
	{
		//�����ַ�����һ�����ַ�
		c++;
		if (*c == '#' || *c == '#')
		{
			w = ClassNum(c);
			WriteClass(N,w);
			CatchClass(N,fill, w);
		}
	}
}

void Fill()
{
	string FC;
	cout << "����������Ҫ���ҵ�ģ�飺" << endl;
	cin >> FC;
	//ifstream in("��Ҫת�����ĵ�.ifc");
	ifstream in("123.ifc");
	ofstream out("�����Ʒ.ifc");
	int n = Com();
	int* N = new int[n + 1];
	string* fill = new string[n + 1];
	//��ʼ�������б����õ�ʵ��������
	if (n != 0)
	{
		

		cout << endl << "ͷ�ļ������ݣ�ISO-10303-21;" << endl;
		out<<"ISO-10303-21;"<<endl;
		for (string str; getline(in, str);)
		{

			if (str != "")
			{
				const char* c = str.c_str();
				if (*c == '#' || *c == '#')
				{
					n = ClassNum(c);
					fill[n] = str;
				}
				else
				{
					if (str == "HEADER;")
					{
						for (;str != "ENDSEC;";)
						{ 
							cout << "ͷ�ļ������ݣ�" << str << endl;
							out << str << endl;
							getline(in, str);
						}
					}
				}
			}
		}
		cout << "ͷ�ļ������ݣ�ENDSEC;" << endl;
		out << "ENDSEC;" << endl;
		cout << "ͷ�ļ����ݽ�����" << endl;
		int w;
		for (int i = 0; i < n;)
		{
			i++;
			const char* a = fill[i].c_str();
			if (FindClass(a, FC))
			{
				cout << "   �� ";
				w = ClassNum(a);
				WriteClass(N,w);
				cout << "�У�" << endl << fill[i] << endl;
				cout << "������������" << endl << "��ʼ����Ŀ��ʵ���е��õ�����ʵ����";
				CatchClass(N,fill, w);
				cout << endl << endl;
			}
		}
		
	}

	
	
	getchar();
	cout << endl << endl << "DATA;" << endl << endl;
	out << endl << endl << "DATA;" << endl << endl;
	for (int u = 0; u<n+1; u++)
	{
		if (N[u] == 1)
		{
			num++;
			cout << " " << num << "��" << u<<endl;
			out << fill[u] << endl;
		}
	}
	cout << endl << "ENDSEC;" << endl << endl << "END-ISO-10303-21; " << endl;
	out << endl << "ENDSEC;" << endl << endl << "END-ISO-10303-21; " << endl;

	cout << endl << "����һ���ҵ��� " << nuu << " ��ʵ������Ϊ��"<<FC<<"��ʵ������" << endl;

	cout << endl << "����һ��Ҫ���� " << num << " ʵ������" << endl;
}

int main()
{
	cout << "=====��ʼ=====" << endl;
	//=====��ʼ=====

	//Fill();
	string m;
	m = "123.txt";
	ofstream oo(m);
	oo<<"111222333" << endl;
	//=====����=====
	cout << endl << "=====����=====";

	for (string str;str != "END";) 
	{
		cout << endl << "��������ָֹ�END������������" << endl;
		cin >> str;
		if (str != "END")
			cout << endl << "��������ȷ����ָֹ��" << endl;
	}
	
	return 1;
}