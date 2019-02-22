#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
using namespace std;
//文件夹名
string
    System_Str = "系统文件",
	Configure_Str = "配置文件",
	OutPut_Str = "输出文件";
/* 
    a : 97
	z : 122
	A : 65
	Z : 90
*/

string Convert_String(string str)//将字符串中的小写字母转换为大写的函数
{
	//cout << ">待转换的字符串为：" << str << endl;
	const char* c = str.c_str();
	string Convert_str;//转换后的字符串
	char Convert_c;//转换后的字符
	for (unsigned int i = 0; i < str.size(); i++, c++)
	{
		if (*c > 96 && *c < 123)
		{
			Convert_c = *c - 32;
		}
		else
			Convert_c = *c;
		Convert_str.append(1, Convert_c);
	}
	//cout << "+转换后的字符串为：" << Convert_str << endl;
	return Convert_str;
}

bool Inspect(string Class_Name,int& Class_Number)//检查程序，缺少配置文件时终止程序，缺少系统文件时创建文件。
{
	ifstream Class_In(Configure_Str + "/" + Class_Name + "类型.txt");
	ifstream Class_Out(System_Str + "/" + Class_Name + "类型");
	ifstream ClassNum_In(System_Str + "/" + Class_Name + "数量");
	string u;
	bool n = false;
	cout << "+";
	if (!Class_In)
	{
		cout << Class_Name + Configure_Str << "不存在，将终止程序。" << endl;
		return false;
	}
	else
	{
		cout << Class_Name + Configure_Str << "存在，请问是否更新？" << endl;
		cin >> n;
	}
	if (!Class_Out)
	{
		cout << ">";
		cout << Class_Name + System_Str << "不存在，将强制更新。" << endl;
		CreateDirectory(System_Str.c_str(), NULL);
		n = true;
	}
	
	if (n)
	{
		ofstream ClassOut(System_Str + "/" + Class_Name + "类型");
		ofstream ClassNum_Out(System_Str + "/" + Class_Name + "数量");
		for (string str; getline(Class_In, str);Class_Number++)
		{
			str = Convert_String(str);
			ClassOut << str << endl;
		}
		ClassNum_Out << Class_Number;
	}
	else
	{
		getline(ClassNum_In, u);
		Class_Number = atoi(u.c_str());
	}
	return true;
}

void Inspect(string* Class,int n)//重载检查函数，将转换后的实例类型输入到查询数组里面。
{
	ifstream C_In(System_Str + "/" + Class[0] + "类型");
	for (int i = 0; i < n; i++)
		getline(C_In, Class[i + 1]);
}

string getClass(string str,long& FCN)
{
	//提取实例类型
	const char* c = str.c_str();
	if (*c != '#')
		return "0";
	string n;
	long nn;
	string s;//计类型器
	for (;;)
	{
		if (*c == '#')
		{
			for (;;)
			{
				c++;
				if (*c == '=')
					break;
				if (*c != ' ')
					n.append(1, *c);
			}
		}
		break;
	}
	nn = atoi(n.c_str());
	if (FCN < nn)
		FCN = nn;
	for (;;)
	{
		//获取实例类型
		if (*c == '=')
		{
			for (;;)
			{
				c++;
				if (*c == '(')
					return s;
				if (*c != ' ')
					s.append(1, *c);
			}
		}
		c++;
	}
}

bool Inspect(string str, string Class,string* ClassType, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (Class == ClassType[i + 1])
			return 1;
	}
	return 0;
}

//从字符串中获得实例编号并且记录
long getNum(string str, long* Num)
{
	string n;
	const char *c = str.c_str();
	for (;;)
	{
		if (*c == '#')
		{
			for (;;)
			{
				c++;
				if (*c == '=' || *c == ',' || *c == ')')
					break;
				if (*c != ' ')
					n.append(1, *c);
			}
		}
		break;
	}
	//Num[atoi(n.c_str())] = 1;
	return atoi(n.c_str());
}
long getNum(const char* c, long* Num)
{
	string n;
	for (;;)
	{
		if (*c == '#')
		{
			for (;;)
			{
				c++;
				if (*c == '=' || *c == ',' || *c == ')')
					break;
				if (*c != ' ')
					n.append(1, *c);
			}
		}
		break;
	}
	Num[atoi(n.c_str())] = 1;
	return atoi(n.c_str());
}
void MoPutOut(string str,string* IfcFill, long* Num)
{
	const char* c = str.c_str();
	c++;
	for (;*c != ';';c++)
	{
		if (*c == '#') {
			MoPutOut(IfcFill[getNum(c,Num)],IfcFill,Num);
		}
	}
}

void SeparateClass(string Fill, string* L, int LN, string* B, int BN, string* M, int MN,long& FCN)
{
	CreateDirectory(OutPut_Str.c_str(), NULL);
	ifstream fin(Fill);
	string Class;
	//创建文件流
	ofstream LO(OutPut_Str + "/" + L[0] + ".txt");
	ofstream BO(OutPut_Str + "/" + B[0] + ".txt");
	ofstream MO(OutPut_Str + "/" + M[0] + ".txt");
	
	for (string str; getline(fin, str);)
	{
		Class = getClass(str,FCN);
		if (Class != "0")
		{
			if (Inspect(str, Class, L, LN))
				LO << str << endl;
			if (Inspect(str, Class, B, BN))
				BO << str << endl;
			/*if (Inspect(str, Class, M, MN))
				MO << str << endl;*/
		}
	}
	LO.close();
	BO.close();
	//MO.close();
	fin.close();
	string* IfcFill = new string[FCN+1];
	long* IfcFillClass = new long[FCN+1];
	ifstream finI(Fill);
	ifstream BOI(OutPut_Str + "/" + B[0] + ".txt");
	//文件输入内存：
	int un = 0;
	for (string str; getline(finI, str);)
	{
		IfcFill[getNum(str,IfcFillClass)] = str;
		un++;
	}
	//递归查找模型
	for (string str; getline(BOI, str);)
	{
		MoPutOut(str, IfcFill, IfcFillClass);
		//cout << str << endl;
	}
	int bn = 0;
	for (unsigned int i = 0; i <= FCN + 1; i++)
	{
		if (IfcFillClass[i] == 1) {
			MO << IfcFill[i] << endl;
			bn++;
		}
	}
	cout << "录入行数 " << un << endl;
	cout << "输出行数" << bn << endl;
	MO.close();
}

int main()
{
	/*
		a : 97
		z : 122
		A : 65
		Z : 90
		a = A + 32;
	*/
	//文字段
	string 
		Location_Str = "坐标实例",
		BuildingElement_Str = "建筑构件",
		Model_Str = "模型实例";
	//实例类型计数器
	int LocationClass_Number = 0,
		BuildingElementClass_Number = 0,
		ModelClass_Number = 0;
	//计数器的引用
	int &LocationCite = LocationClass_Number,
		&BuildingElementCite = BuildingElementClass_Number,
		&ModelCite = ModelClass_Number;
	//检查文件结构完整性
	if (Inspect(Location_Str, LocationClass_Number) &&
		Inspect(BuildingElement_Str, BuildingElementClass_Number) &&
		Inspect(Model_Str, ModelClass_Number))
		cout
		<< ">" << Location_Str << ": " << LocationClass_Number << endl
		<< ">" << BuildingElement_Str << ": " << BuildingElementClass_Number << endl
		<< ">" << Model_Str << ": " << ModelClass_Number << endl;
	//将所有需要查询的实例类型输入到内存当中。
	string* LocationClass = new string[LocationClass_Number+1],
		  * BuildingElementClass = new string[BuildingElementClass_Number+1],
		  * ModelClass = new string[ModelClass_Number+1];
	LocationClass[0] = Location_Str;
	BuildingElementClass[0] = BuildingElement_Str;
	ModelClass[0] = Model_Str;
	//将实例类型输入数组当中
	Inspect(LocationClass, LocationClass_Number);
	Inspect(BuildingElementClass, BuildingElementClass_Number);
	Inspect(ModelClass, ModelClass_Number);
	//获取文件名
	string FillName;
	cout << "+请输入您想要处理的文件路径及名字：";
	cin >> FillName;
	ifstream Fill_In(FillName);
	long IfcClassNum = 0;//Ifc文件实例数量
	long& IFCNum = IfcClassNum;//对文件实例数量的引用，方便利用函数修改。
	clock_t Start, Finish;
	double totaltime;
	Start = clock();//计时
	if (Fill_In)
	{
		SeparateClass(FillName,
			LocationClass, LocationClass_Number,
			BuildingElementClass, BuildingElementClass_Number,
			ModelClass, ModelClass_Number,IFCNum);
	}
	else
		cout << ">输入路径或者文件不存在，程序即将关闭。" << endl;
	cout << "本文件有 "<<IfcClassNum<<" 个实例。" << endl;
	Finish = clock();//计时结束
	totaltime = (double)(Finish - Start) / CLOCKS_PER_SEC;
	cout << ">>此次分离用时 " <<totaltime<<" 秒。"<< endl;

	//===关闭程序模块===
	string End_String;
	while (End_String != "End")
	{
		cout << "请输入“End”以终止程序。" << endl;
		cin >> End_String;
	}
	getchar();
	return 1;
}