#include <iostream>
#include "BigNumb.h"
#include <string.h>
using std::cout;

using namespace std;
void printGuide() //Руководство по вводу
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
	if (Modul < (int)0)     //Проверка введеного модуля, на отрицательность
	{
		cout << "Negative Modul!" << endl;
		return false;
	}

	if (operation == '^')    //В параметрах указали возведение в степень
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
		catch (int err)  //Обрабатываем исключение, в случае деления на 0
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
		catch (int err)   //Обрабатываем исключение, в случае деления на 0
		{
			cout << "Dividing by zero" << endl;
			return false;
		}
		break;

	default:
		cout << "Wrong operation." << endl;     //Выдаем ошибку. В случае, если введена несуществующая операция
		printGuide();
		return false;
	}

	if (Modul > (int)0)     //Если в параметрах был указан модуль, приводим результат под необходимы модуль
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
		cout << "Too few arguments passed." << endl;  //Задано недостаточное количество аргументов
		printGuide();								  //Выводим руководство
		return -1;
	}

	if (argc > 7)
	{
		cout << "Too many arguments passed." << endl; //Задано слишком много аргументов
		printGuide();								  //Выводим руководство
		return -1;
	}

	if (strlen(argv[2]) > 1)
	{
		cout << "Wrong operation." << endl;    //неверная операция  ??
		printGuide();
		return -1;
	}

	char* fileA = argv[1];    //первый входной файл
	char operation = argv[2][0]; //операция
	char* fileB = argv[3];  //второй входной файл
	char* fileResult = argv[4]; //файл под результат
	bool binary = false;   //бинарный/небинарный
	char* moduleFile = NULL;  //вычисления по модулю

	if (argc == 6)
	{
		if (!strcmp(argv[5], "-b"))  //Проверяем был ли введен параметр бинарности
			binary = true;
		else
			moduleFile = argv[5]; // Если параметр бинарности задан не был, 6-й аргумент принимаем за указатель на файл модуля
	}

	if (argc == 7)  //Если указали все 6 аргументов, работаем с бинарными файлами и все вычисления, осуществляем по модулю из файла
	{
		binary = true;
		moduleFile = argv[6];
	}

	BigNumb A, B, Modul = (int)0;

	if (binary)   //если файлы бинарные
	{
		A.FromBinaryFile(fileA); //получаем первое число из бинарного файла
		B.FromBinaryFile(fileB); //получаем второе число из бинарного файла
		if (moduleFile)  //если есть файл с модулем
			Modul.FromBinaryFile(moduleFile); //получаем модуль
	}
	else   //если файлы не бинарные
	{
		A.FromFile(fileA); //получаем первое число
		B.FromFile(fileB); //получаем второе число
		if (moduleFile)  //если есть файл с модулем
			Modul.FromFile(moduleFile); //получаем модуль
	}

	BigNumb Result;

	if (!OBRAB(A, B, Modul, operation, Result))  //Приступаем к вычислению. Если вычисления закончились ошибкой
		return -1;

	if (binary)   //Если вычисления прошли успешно и 
		Result.InBinaryFile(fileResult);  //файл бинарный
	else
		Result.InFile(fileResult);  //файл не бинарный

	return 0;
}