#include <iostream>
#include "BigNumb.h"
#include <string.h>
using std::cout;

using namespace std;
void printGuide() //����������� �� �����
{
	cout << "GUIDE: " << endl;
	cout << "BI_2 <A filelame> <operation> <B filelame> <Resultult filename> [-b] [<Modul filename>]" << endl << endl;
	cout << "Use the following parameters:" << endl;
	cout << "  operations:" << endl;
	cout << "    \"+\" - addition" << endl;
	cout << "    \"-\" - subtraction" << endl;
	cout << "    \"*\" - Multipl" << endl;
	cout << "    \"/\" - Divid" << endl;
	cout << "    \"%\" - taking the remainder" << endl;
	cout << "    \"^\" - involution (pow)" << endl;
	cout << "  -b for operations with binary files" << endl;
}

bool OBRAB(BigNumb A, BigNumb B, BigNumb Modul, char operation, BigNumb& Result)
{
	if (Modul < (int)0)     //�������� ��������� ������, �� ���������������
	{
		cout << "Negative Modul!" << endl;
		return false;
	}

	if (operation == '^')    //� ���������� ������� ���������� � �������
	{
		Result = Pow(A, B, Modul);
		return true;
	}

	if (Modul > (int)0)
	{
		A = A % Modul;
		B = B % Modul;
	}

	switch (operation)
	{
	case '+':
		Result = A + B;
		break;

	case '-':
		Result = A - B;
		break;

	case '*':
		Result = A * B;
		break;

	case '/':
		try
		{
			Result = A / B;
		}
		catch (int err)  //������������ ����������, � ������ ������� �� 0
		{
			cout << "Dividing by zero" << endl;
			return false;
		}
		break;

	case '%':
		try
		{
			Result = A % B;
		}
		catch (int err)   //������������ ����������, � ������ ������� �� 0
		{
			cout << "Dividing by zero" << endl;
			return false;
		}
		break;

	default:
		cout << "Wrong operation." << endl;     //������ ������. � ������, ���� ������� �������������� ��������
		printGuide();
		return false;
	}

	if (Modul > (int)0)     //���� � ���������� ��� ������ ������, �������� ��������� ��� ���������� ������
	{
		Result = Result % Modul;
		while (Result < (int)0)
			Result = Result + Modul;
	}

	return true;
}

int main(int argc, char* argv[])
{
	if (argc < 5)
	{
		cout << "Too few arguments passed." << endl;  //������ ������������� ���������� ����������
		printGuide();								  //������� �����������
		return -1;
	}

	if (argc > 7)
	{
		cout << "Too many arguments passed." << endl; //������ ������� ����� ����������
		printGuide();								  //������� �����������
		return -1;
	}

	if (strlen(argv[2]) > 1)
	{
		cout << "Wrong operation." << endl;    //�������� ��������  ??
		printGuide();
		return -1;
	}

	char* fileA = argv[1];    //������ ������� ����
	char operation = argv[2][0]; //��������
	char* fileB = argv[3];  //������ ������� ����
	char* fileResult = argv[4]; //���� ��� ���������
	bool binary = false;   //��������/����������
	char* moduleFile = NULL;  //���������� �� ������

	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))  //��������� ��� �� ������ �������� ����������
			binary = true;
		else
			moduleFile = argv[5]; // ���� �������� ���������� ����� �� ���, 6-� �������� ��������� �� ��������� �� ���� ������
	}

	if (argc == 7)  //���� ������� ��� 6 ����������, �������� � ��������� ������� � ��� ����������, ������������ �� ������ �� �����
	{
		binary = true;
		moduleFile = argv[6];
	}

	BigNumb A, B, Modul = (int)0;

	if (binary)   //���� ����� ��������
	{
		A.FromBinaryFile(fileA); //�������� ������ ����� �� ��������� �����
		B.FromBinaryFile(fileB); //�������� ������ ����� �� ��������� �����
		if (moduleFile)  //���� ���� ���� � �������
			Modul.FromBinaryFile(moduleFile); //�������� ������
	}
	else   //���� ����� �� ��������
	{
		A.FromFile(fileA); //�������� ������ �����
		B.FromFile(fileB); //�������� ������ �����
		if (moduleFile)  //���� ���� ���� � �������
			Modul.FromFile(moduleFile); //�������� ������
	}

	BigNumb Result;

	if (!OBRAB(A, B, Modul, operation, Result))  //���������� � ����������. ���� ���������� ����������� �������
		return -1;

	if (binary)   //���� ���������� ������ ������� � 
		Result.InBinaryFile(fileResult);  //���� ��������
	else
		Result.InFile(fileResult);  //���� �� ��������

	return 0;
}