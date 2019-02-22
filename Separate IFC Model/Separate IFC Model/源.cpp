#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
using namespace std;
//�ļ�����
string
    System_Str = "ϵͳ�ļ�",
	Configure_Str = "�����ļ�",
	OutPut_Str = "����ļ�";
/* 
    a : 97
	z : 122
	A : 65
	Z : 90
*/

string Convert_String(string str)//���ַ����е�Сд��ĸת��Ϊ��д�ĺ���
{
	//cout << ">��ת�����ַ���Ϊ��" << str << endl;
	const char* c = str.c_str();
	string Convert_str;//ת������ַ���
	char Convert_c;//ת������ַ�
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
	//cout << "+ת������ַ���Ϊ��" << Convert_str << endl;
	return Convert_str;
}

bool Inspect(string Class_Name,int& Class_Number)//������ȱ�������ļ�ʱ��ֹ����ȱ��ϵͳ�ļ�ʱ�����ļ���
{
	ifstream Class_In(Configure_Str + "/" + Class_Name + "����.txt");
	ifstream Class_Out(System_Str + "/" + Class_Name + "����");
	ifstream ClassNum_In(System_Str + "/" + Class_Name + "����");
	string u;
	bool n = false;
	cout << "+";
	if (!Class_In)
	{
		cout << Class_Name + Configure_Str << "�����ڣ�����ֹ����" << endl;
		return false;
	}
	else
	{
		cout << Class_Name + Configure_Str << "���ڣ������Ƿ���£�" << endl;
		cin >> n;
	}
	if (!Class_Out)
	{
		cout << ">";
		cout << Class_Name + System_Str << "�����ڣ���ǿ�Ƹ��¡�" << endl;
		CreateDirectory(System_Str.c_str(), NULL);
		n = true;
	}
	
	if (n)
	{
		ofstream ClassOut(System_Str + "/" + Class_Name + "����");
		ofstream ClassNum_Out(System_Str + "/" + Class_Name + "����");
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

void Inspect(string* Class,int n)//���ؼ�麯������ת�����ʵ���������뵽��ѯ�������档
{
	ifstream C_In(System_Str + "/" + Class[0] + "����");
	for (int i = 0; i < n; i++)
		getline(C_In, Class[i + 1]);
}

string getClass(string str,long& FCN)
{
	//��ȡʵ������
	const char* c = str.c_str();
	if (*c != '#')
		return "0";
	string n;
	long nn;
	string s;//��������
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
		//��ȡʵ������
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

//���ַ����л��ʵ����Ų��Ҽ�¼
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
	//�����ļ���
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
	//�ļ������ڴ棺
	int un = 0;
	for (string str; getline(finI, str);)
	{
		IfcFill[getNum(str,IfcFillClass)] = str;
		un++;
	}
	//�ݹ����ģ��
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
	cout << "¼������ " << un << endl;
	cout << "�������" << bn << endl;
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
	//���ֶ�
	string 
		Location_Str = "����ʵ��",
		BuildingElement_Str = "��������",
		Model_Str = "ģ��ʵ��";
	//ʵ�����ͼ�����
	int LocationClass_Number = 0,
		BuildingElementClass_Number = 0,
		ModelClass_Number = 0;
	//������������
	int &LocationCite = LocationClass_Number,
		&BuildingElementCite = BuildingElementClass_Number,
		&ModelCite = ModelClass_Number;
	//����ļ��ṹ������
	if (Inspect(Location_Str, LocationClass_Number) &&
		Inspect(BuildingElement_Str, BuildingElementClass_Number) &&
		Inspect(Model_Str, ModelClass_Number))
		cout
		<< ">" << Location_Str << ": " << LocationClass_Number << endl
		<< ">" << BuildingElement_Str << ": " << BuildingElementClass_Number << endl
		<< ">" << Model_Str << ": " << ModelClass_Number << endl;
	//��������Ҫ��ѯ��ʵ���������뵽�ڴ浱�С�
	string* LocationClass = new string[LocationClass_Number+1],
		  * BuildingElementClass = new string[BuildingElementClass_Number+1],
		  * ModelClass = new string[ModelClass_Number+1];
	LocationClass[0] = Location_Str;
	BuildingElementClass[0] = BuildingElement_Str;
	ModelClass[0] = Model_Str;
	//��ʵ�������������鵱��
	Inspect(LocationClass, LocationClass_Number);
	Inspect(BuildingElementClass, BuildingElementClass_Number);
	Inspect(ModelClass, ModelClass_Number);
	//��ȡ�ļ���
	string FillName;
	cout << "+����������Ҫ������ļ�·�������֣�";
	cin >> FillName;
	ifstream Fill_In(FillName);
	long IfcClassNum = 0;//Ifc�ļ�ʵ������
	long& IFCNum = IfcClassNum;//���ļ�ʵ�����������ã��������ú����޸ġ�
	clock_t Start, Finish;
	double totaltime;
	Start = clock();//��ʱ
	if (Fill_In)
	{
		SeparateClass(FillName,
			LocationClass, LocationClass_Number,
			BuildingElementClass, BuildingElementClass_Number,
			ModelClass, ModelClass_Number,IFCNum);
	}
	else
		cout << ">����·�������ļ������ڣ����򼴽��رա�" << endl;
	cout << "���ļ��� "<<IfcClassNum<<" ��ʵ����" << endl;
	Finish = clock();//��ʱ����
	totaltime = (double)(Finish - Start) / CLOCKS_PER_SEC;
	cout << ">>�˴η�����ʱ " <<totaltime<<" �롣"<< endl;

	//===�رճ���ģ��===
	string End_String;
	while (End_String != "End")
	{
		cout << "�����롰End������ֹ����" << endl;
		cin >> End_String;
	}
	getchar();
	return 1;
}