#include <stdio.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
int nuu = 0;
int num = 0;

//将捕捉到的对象标号记录在栈中的函数
void WriteClass(int* N, int n)
{
	cout << n << " ";
	N[n] = 1;	
}

//获取行数的函数
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
					//cout << "执行遍历：" << *c << endl;
					if (*c == '=')
					{
						//cout << "执行跳出" << endl;
						break;
					}
					if (*c != ' ')
					{
						//cout << "执行写入：" << *c << endl;
						sn.append(1, *c);
					}
				}
				//cout << "正在将 " << sn << " 写入n" << endl;
				n = atoi(sn.c_str());
			}
		}
	}
	if (n == 0)
		cout << endl << "没有检测到需要拆分的IFC文件。";
	else
		cout << endl << "这个文档一共有 " << n << "  个实例对象" << endl;
	return n;
}

//获取当前实例标号的函数
int ClassNum(const char* c)
{
	string sn;
	if (*c == '#' || *c == '#')
	{
		for (; *c != '=';)
		{
			c++;
			//cout << "执行遍历：" << *c << endl;
			if (*c == '=' || *c == ',' || *c == ')')
			{
				//cout << "执行跳出" << endl;
				break;
			}
			if (*c != ' ')
			{
				//cout << "执行写入：" << *c << endl;
				sn.append(1, *c);
			}
		}
		//cout << "正在将 " << sn << " 写入n" << endl;
		return atoi(sn.c_str());
	}
}

//对比实例类型是否为查找的目标实例类型
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
		cout << endl << "找到基础实例对象：" << s;
		return true;
	}
	if (s == "IFCSITE")
	{
		cout << endl << "找到基础实例对象：" << s;
		return true;
	}
	if (s == "IFCBUILDING")
	{
		cout << endl << "找到基础实例对象：" << s;
		return true;
	}
	if (s == "IFCBUILDINGSTOREY")
	{
		cout << endl << "找到基础实例对象：" << s;
		return true;
	}
	if (s == "IFCSPACE")
	{
		cout << endl << "找到基础实例对象：" << s;
		return true;
	}
	if (s == FC)
	{
		cout << endl << "找到目标实例对象：" << s;
		nuu++;
		return true;
	}
	return false;
}

//扫描实例中调用的实例
void CatchClass(int* N,string* fill, int n)
{
	const char* c = fill[n].c_str();
	int w;
	for (int i = 0; i < size(fill[n]); i++)
	{
		//跳过字符串第一个井字符
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
	cout << "请输入你想要查找的模块：" << endl;
	cin >> FC;
	//ifstream in("需要转换的文档.ifc");
	ifstream in("123.ifc");
	ofstream out("分离成品.ifc");
	int n = Com();
	int* N = new int[n + 1];
	string* fill = new string[n + 1];
	//开始查找所有被调用的实例对象编号
	if (n != 0)
	{
		

		cout << endl << "头文件的内容：ISO-10303-21;" << endl;
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
							cout << "头文件的内容：" << str << endl;
							out << str << endl;
							getline(in, str);
						}
					}
				}
			}
		}
		cout << "头文件的内容：ENDSEC;" << endl;
		out << "ENDSEC;" << endl;
		cout << "头文件内容结束。" << endl;
		int w;
		for (int i = 0; i < n;)
		{
			i++;
			const char* a = fill[i].c_str();
			if (FindClass(a, FC))
			{
				cout << "   第 ";
				w = ClassNum(a);
				WriteClass(N,w);
				cout << "行：" << endl << fill[i] << endl;
				cout << "。。。。。。" << endl << "开始查找目标实例中调用的其他实例：";
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
			cout << " " << num << "：" << u<<endl;
			out << fill[u] << endl;
		}
	}
	cout << endl << "ENDSEC;" << endl << endl << "END-ISO-10303-21; " << endl;
	out << endl << "ENDSEC;" << endl << endl << "END-ISO-10303-21; " << endl;

	cout << endl << "我们一共找到了 " << nuu << " 个实例类型为“"<<FC<<"”实例对象。" << endl;

	cout << endl << "我们一共要分离 " << num << " 实例对象。" << endl;
}

int main()
{
	cout << "=====开始=====" << endl;
	//=====开始=====

	//Fill();
	string m;
	m = "123.txt";
	ofstream oo(m);
	oo<<"111222333" << endl;
	//=====结束=====
	cout << endl << "=====结束=====";

	for (string str;str != "END";) 
	{
		cout << endl << "请输入终止指令“END”结束本程序：" << endl;
		cin >> str;
		if (str != "END")
			cout << endl << "请输入正确的终止指令" << endl;
	}
	
	return 1;
}