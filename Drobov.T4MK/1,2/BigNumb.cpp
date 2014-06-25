#include "BigNumb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;

#define DIV_BY_ZERO 1

BigNumb::BigNumb()							//����������� �� ���������. �������� �����.
{
	this->size = 1;
	this->sign = 0;
	this->discharges = new unsigned char[1];
	this->discharges[0] = 0;
}

BigNumb::BigNumb(const char* string)		//�������������� �������� ������ String � �����
{
//�������, ��� ������ - ������ � ���������� ���� ������-���� �����,
//������� ��������� �� ��������� 10 � ��������� 256.
//��� ����� ���������� ������ ����� � ����� ������� �� 10 ^ i,
//��� i - ����� ������� ���� �����
	
	int strLen = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strSign = 1;
		strLen--;
	}

	BigNumb Result;		//������������, ������������� ��������� �������� ������ � �����.

	BigNumb pow10 = 1; // 10 ^ i
	for (int i = strLen + strSign - 1; i >= strSign; i--)		//���� �������� �� ������ �������� ������� �� ������ ��������.
	{
		int rI = string[i] - '0'; 
		Result = Result + pow10 * rI;
		pow10 = pow10 * 10;
	}
	Result.sign = strSign;		//���������� ���� �����.

	this->size = 0;
	*this = Result;		//*This ��������� �� ���������� � �������� ����� �����.
}

BigNumb::BigNumb(const BigNumb &right)		//����������� �����������. 
{
	this->size = right.size;
	this->discharges = new unsigned char[this->size];
	this->sign = right.sign;
	memcpy(discharges, right.discharges, this->size * sizeof(unsigned char));
	return;
}

BigNumb::BigNumb(int value)					//�����������, ������� �� ������ ����� �������� �����, �������������� � ������� "������� �����".
{
	this->discharges = new unsigned char[11]();
	this->size = 0;
	this->sign = 0;
	if (value < 0)
	{
		this->sign = 1;
		value = -value;
	}
	do
	{
		this->size++;
		this->discharges[this->size - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->DeleteZeroes();
}

BigNumb::~BigNumb()							//����������.
{
	delete[] discharges;
}

char* BigNumb::TakeString()					//������� �������� ����� � ��������� ������.
{
	//��� �������� ����� � ������,
	//���������� � ������ ������� �� ������� ����� �� 10,
	//���� ����� �� ������ ������ ����.
	
	BigNumb temp = *this; // �����, ������� ����� ������ �� 10.
	temp.sign = 0;
	
	std::vector<char> tmpStr; // ������, � ������� ����� ����������, ���������� ������.


	while (temp != (int)0)
	{
		BigNumb remainder;
		temp = Divid(temp, 10, remainder); // ����� ����� �� 10 � ���������� �������.
		char ost = remainder[0] + '0'; 	   // ������� �� �������, ��������� � 0-��� ������� remainder.
		tmpStr.push_back(ost);
	}

	if (this->sign)			//���� �����, ���� ��������������, ���������� ����.
		tmpStr.push_back('-');

	//���������� tmpStr ������ ������ ������, �������������� �����.
	//����� � ������ ����� �������� ����� �� �����.

	int strSize = tmpStr.size(); //�������������� ������.
	char* string = new char[strSize + 1]();

	for (int i = 0; i < tmpStr.size(); i++)
	{
		string[strSize - i - 1] = tmpStr[i];
	}

	return string;
}




bool BigNumb::FromFile(const char* filename)			//������� ��������� ������ �� �����.
{
	ifstream Text_file(filename);
	if (Text_file.fail())
		return false;

	//���������� ������ �����.
	Text_file.seekg(0, std::ios::end);
	int SizeOfFile = Text_file.tellg();
	Text_file.seekg(0, std::ios::beg);

	char* string = new char[SizeOfFile + 1]();
	Text_file >> string;
	Text_file.close();

	*this = BigNumb(string);
	delete[] string;
	return true;
}

bool BigNumb::InFile(const char* filename)				//������� ������ ������ � ����.
{
	ofstream Resultult_file(filename);
	if (Resultult_file.fail())
		return false;

	char* string = this->TakeString();
	Resultult_file << string;
	delete[] string;
	Resultult_file.close();

	return true;
}

bool BigNumb::InBinaryFile(const char* filename)		//������� ������ ���������� � �������� ����.
{
	//�.� � ��������� ������������ ��������� 256, ����� �������, ��� �������� ���� ������������ ����� ������ �������������.
	ofstream outBinFile(filename, std::ios::binary);
	if (outBinFile.fail())
		return false;

	//���������� ������������ � ����.
	outBinFile.write((char*) this->discharges, this->size); 
	
	outBinFile.close();
	return true;
}

bool BigNumb::FromBinaryFile(const char* filename)		//������� ��������� ����� �� ��������� �����.
{
	ifstream inBinFile(filename, std::ios::binary);
	if (inBinFile.fail())
		return false;
		
	//���������� ������ �����.
	inBinFile.seekg(0, std::ios::end);
	int SizeOfFile = inBinFile.tellg();
	inBinFile.seekg(0, std::ios::beg);

	delete[] this->discharges;
	this->discharges = new unsigned char[SizeOfFile];
	this->size = SizeOfFile;
	this->sign = 0;

	//��������� ���������� ��������� �����.
	inBinFile.read((char*)this->discharges, SizeOfFile);
	inBinFile.close();

	return true;
}




void BigNumb::SetSize(int newSize)						//������������ ������ ��� �����, ��� ���� ������� ���.
{	
	if (this->size)
		delete[] this->discharges;
	this->size = newSize;
	this->sign = 0;
	this->discharges = new unsigned char[this->size]();
}

void BigNumb::DeleteZeroes()							//������� �������� ����� �� ������� �������� �����.
{
	while ((size - 1) && discharges && discharges[size - 1] == 0)
		this->size--;

	if (this->size == 1 && discharges[0] == 0)
		this->sign = 0;
}

int BigNumb::Compare(const BigNumb& B)					//������� ���������.
{
	//������� ���������� ��������:
	//0 - ���� this � ����� �����,
	//>0 - ���� this ������,
	//<0 - ���� this ������.
	
	int thisSign = 1;
	if (this->sign == 1)
		thisSign = -1;

	if (this->sign != B.sign)
		return thisSign;

	if (this->size > B.size)
		return thisSign;

	if (this->size < B.size)
		return -thisSign;

	int i = this->size - 1;

	while (this->discharges[i] == B[i] && i > 0)
	{
		i--;
	}
	return ( (int) this->discharges[i] - (int) B[i]) * thisSign;
}

void BigNumb::Shift(int s)								//������� ������ ����� �� s, �������� ����� (��������� �� 256^s).
{
	unsigned char* newdischarges = new unsigned char[this->size + s]();
	for (int i = 0; i < this->size; i++)
	{
		newdischarges[i + s] = this->discharges[i];
	}

	delete[] this->discharges;
	this->discharges = newdischarges;
	this->size += s;
	this->DeleteZeroes();
}





BigNumb BigNumb::Add_Sub(const BigNumb& left, const BigNumb& right) const				//������� �������� � ��������� ���������.
{
	BigNumb A = left, B = right;		//� ���������� � ����� ������� �� ������ �����, � B - �������.
	A.sign = 0;
	B.sign = 0;
	if (A > B)
	{
		A.sign = left.sign;
		B.sign = right.sign;
	}
	else
	{
		A = right;
		B = left;
	}

	if (A.sign == B.sign)		//��������� ����� �����.
	{							//���� ����� ����� ���������� �����, ���������� �� � ��������� ������ ����.
		BigNumb Result;
		Result.SetSize(A.size + 1);

		int carry = 0;

		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] + carry;
			if (i < B.size)
				tmp += B[i];

			Result[i] = tmp % 256;
			carry = tmp / 256;
		}

		Result[A.size] = carry;
		Result.sign = A.sign;
		Result.DeleteZeroes();
		return Result;
	}
	else					//���� ����� ����� ������ �����, �������� ���� �� ������� � ��������� ������ ����.
	{						 
		BigNumb Result;
		Result.SetSize(A.size);

		int carry = 0;
		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] - carry;
			if (i < B.size)
				tmp -= B[i];

			carry = 0;
			if (tmp < 0)
			{
				carry = 1;
				tmp += 256;
			}
			Result[i] = tmp;
		}

		Result.sign = A.sign;
		Result.DeleteZeroes();
		return Result;
	}
}

BigNumb BigNumb::Multipl(const BigNumb A, const BigNumb B) const						//������� ���������.
{
	BigNumb Result;
	Result.SetSize(A.size + B.size);
	int carry = 0;
	for (int i = 0; i < B.size; i++)
	{
		carry = 0;
		for (int j = 0; j < A.size; j++)
		{
			int tmp = (int) B[i] * (int) A[j] + (int) carry + (int) Result[i + j];
			carry = tmp / 256;
			Result[i + j] = tmp % 256;
		}
		Result[i + A.size] = carry;
	}

	Result.sign = (A.sign != B.sign);
	Result.DeleteZeroes();
	return Result;
}

BigNumb BigNumb::Divid(const BigNumb& A, const BigNumb& B, BigNumb &remainder) const	//������� �������.
{																						//���������� ����� ����� �� �������, � ����� ������� � ���������� remainder.
	remainder = A;
	remainder.sign = 0;

	BigNumb divider = B;
	divider.sign = 0;

	if (divider == BigNumb((int)0))
	{
		throw DIV_BY_ZERO;
	}

	if (remainder < divider)
	{
		remainder = A;
		return BigNumb((int)0);
	}

	BigNumb Result;
	Result.SetSize(A.size - B.size + 1);

	for (int i = A.size - B.size + 1; i; i--)
	{
		int qGuessCenterInterMax = 256;
		int qGuessCenterInterMin = 0;
		int qGuessCenter = qGuessCenterInterMax;

		//������������ ������ ����� qGuessCenter �������� �������.
		while (qGuessCenterInterMax - qGuessCenterInterMin > 1)
		{
			qGuessCenter = (qGuessCenterInterMax + qGuessCenterInterMin) / 2;

			//tmp = qGuessCenter * divider * 256^i;
			BigNumb tmp = divider * qGuessCenter;
			tmp.Shift(i - 1);		//������������ ����� ����� �� (i - 1) �������� �����, (��������� ����� �� 256^(i - 1))
			
			if (tmp > remainder)
				qGuessCenterInterMax = qGuessCenter;
			else
				qGuessCenterInterMin = qGuessCenter;
		}
		BigNumb tmp = divider * qGuessCenterInterMin;
		tmp.Shift(i - 1); 			//��������� �� 256 ^ (i - 1).
		remainder = remainder - tmp;
		Result[i - 1] = qGuessCenterInterMin;
	}

	Result.sign = (A.sign != B.sign);
	remainder.sign = (A.sign != B.sign);
	remainder.DeleteZeroes();
	Result.DeleteZeroes();

	return Result;
}

BigNumb Pow(const BigNumb& A, const BigNumb& B, BigNumb& Modul) 						//������� ���������� ����� A � ������� B, �� ������ Modul.
{
	if (Modul <= (int)0)
		return A ^ B;

	BigNumb base = A % Modul;
	BigNumb Result = 1;

	for (BigNumb i = B; i > (int)0; i = i - 1)
		Result = (Result * base) % Modul;

	return Result;
}





//���������� ����������.

unsigned char & BigNumb::operator[](int i)
{
	if (i < 0)
		return this->discharges[this->size + i];
	return this->discharges[i];
}

unsigned char BigNumb::operator[](int i) const
{
	if (i < 0)
		return this->discharges[this->size + i];
	return this->discharges[i];
}

BigNumb& BigNumb::operator=(const BigNumb& rhv)
{
	if (this->size)
		delete[] this->discharges;

	this->size = rhv.size;
	this->discharges = new unsigned char[size];
	this->sign = rhv.sign;
	memcpy(discharges, rhv.discharges, size);
	return *this;
}

BigNumb BigNumb::operator-() const  					//������� �����.
{
	BigNumb Result = *this;
	Result.sign = !Result.sign;
	return Result;
}

BigNumb BigNumb::operator^(const BigNumb& right) const  //���������� ����� *this � ������� right.
{
	BigNumb Result = 1;
	BigNumb base = *this;
	for (BigNumb i = right; i > (int)0; i = i - 1)
		Result = Result * base;
	return Result;
}

BigNumb BigNumb::operator+(const BigNumb& right) const
{
	return Add_Sub(*this, right);
}

BigNumb BigNumb::operator-(const BigNumb& right) const
{
	return *this + (-right);
}

BigNumb BigNumb::operator*(const BigNumb& right) const
{
	return Multipl(*this, right);
}

BigNumb BigNumb::operator/(const BigNumb& right) const
{
	BigNumb rem;
	return Divid(*this, right, rem);
}

BigNumb BigNumb::operator%(const BigNumb& right) const
{
	BigNumb rem;
	Divid(*this, right, rem);
	return rem;
}

//��������� ���������

bool BigNumb::operator>(const BigNumb& B)
{
	return this->Compare(B) > 0;
}

bool BigNumb::operator>=(const BigNumb& B)
{
	return this->Compare(B) >= 0;
}

bool BigNumb::operator<(const BigNumb& B)
{
	return this->Compare(B) < 0;
}

bool BigNumb::operator<=(const BigNumb& B)
{
	return this->Compare(B) <= 0;
}

bool BigNumb::operator==(const BigNumb& B)
{
	return this->Compare(B) == 0;
}

bool BigNumb::operator!=(const BigNumb& B)
{
	return this->Compare(B) != 0;
}