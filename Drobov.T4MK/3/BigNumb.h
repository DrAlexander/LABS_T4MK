#pragma once

class BigNumb
{
private:
	int size; 					//������ �����.
	unsigned char* discharges; 	//����������� �������� � �����.
	int sign; 					//���� �����. 0 - �������������, 1 - �������������.

public:
	//������������.
	BigNumb();
	BigNumb(const char* String);
	BigNumb(const BigNumb& RightValue);
	BigNumb(int RightValue);

	//����������.
	~BigNumb(); 
	
	char* TakeString(); //������� ���������� ������, �������������� ����� ������ �����.
	
	//����� ����� ��� Python.
	char* __repr__();
	char* __str__();

	//�������� ��� �������.
	bool FromFile(const char* FileName); 		//������� ������ ����� �� �����.
	bool InFile(const char* FileName);  		//������� ������ ����� � ����.
	bool FromBinaryFile(const char* FileName); 	//������� ������ ����� �� ��������� �����.
	bool InBinaryFile(const char* FileName);    //������� ������ ����� � �������� ����.

	//������������� ���������.
	BigNumb& operator=(const BigNumb& right);      // =
	BigNumb operator+(const BigNumb& right) const; // + 
	BigNumb operator-() const;                     // ������� �����.
	BigNumb operator-(const BigNumb& right) const; // -
	BigNumb operator*(const BigNumb& right) const; // * 
	BigNumb operator/(const BigNumb& right) const; // /
	BigNumb operator%(const BigNumb& right) const; // % 
	BigNumb operator^(const BigNumb& right) const; // ^ - ���������� ����� � �������.

	bool operator>(const BigNumb& B);  //�������� ��������� >
	bool operator>=(const BigNumb& B); //�������� ��������� >=
	bool operator<(const BigNumb& B);  //�������� ��������� <
	bool operator<=(const BigNumb& B); //�������� ��������� <=
	bool operator==(const BigNumb& B); //�������� ��������� ==
	bool operator!=(const BigNumb& B); //�������� ��������� !=
	
	//���������� ���������� ��� Python.
	BigNumb operator+(const int& right) const;
	BigNumb operator-(const int& right) const;
	BigNumb operator*(const int& right) const;
	BigNumb operator/(const int& right) const;
	BigNumb operator%(const int& right) const;

	bool operator>(const int& B);
	bool operator>=(const int& B);
	bool operator<(const int& B);
	bool operator<=(const int& B);
	bool operator==(const int& B);
	bool operator!=(const int& B);

private:
	void SetSize(int newSize); 				//��������� ������ ��� newSize ���������.
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void DeleteZeroes(); 					//�������� ������� �����.
	int Compare(const BigNumb& B); 			//���������.
	void Shift(int s);

	BigNumb Add_Sub(const BigNumb& left, const BigNumb& right) const;     			//�������� � ���������.
	BigNumb Multipl(const BigNumb A, const BigNumb B) const;           				//���������.
	BigNumb Divid(const BigNumb& A, const BigNumb& B, BigNumb &remainder) const;  	//�������.

};

	BigNumb Pow(const BigNumb& A, const BigNumb& B, BigNumb& Modul);  				//���������� � �������.