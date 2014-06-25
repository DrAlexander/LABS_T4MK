#pragma once

class BigNumb
{
private:
	int size; 					//Размер числа.
	unsigned char* discharges; 	//Колличество разрядов в числе.
	int sign; 					//Знак числа. 0 - положительное, 1 - отрицательное.

public:
	//Конструкторы.
	BigNumb();
	BigNumb(const char* String);
	BigNumb(const BigNumb& RightValue);
	BigNumb(int RightValue);

	//Деструктор.
	~BigNumb(); 
	
	char* TakeString(); //Функция возвращает строку, представляющую собой запись числа.
	
	//Вывод числа для Python.
	char* __repr__();
	char* __str__();

	//Операции над файлами.
	bool FromFile(const char* FileName); 		//Функция чтения числа из файла.
	bool InFile(const char* FileName);  		//Функция записи числа в файл.
	bool FromBinaryFile(const char* FileName); 	//Функция чтения числа из бинарного файла.
	bool InBinaryFile(const char* FileName);    //Функция записи числа в бинарный файл.

	//Перегружаемые операторы.
	BigNumb& operator=(const BigNumb& right);      // =
	BigNumb operator+(const BigNumb& right) const; // + 
	BigNumb operator-() const;                     // Унарный минус.
	BigNumb operator-(const BigNumb& right) const; // -
	BigNumb operator*(const BigNumb& right) const; // * 
	BigNumb operator/(const BigNumb& right) const; // /
	BigNumb operator%(const BigNumb& right) const; // % 
	BigNumb operator^(const BigNumb& right) const; // ^ - возведение числа в степень.

	bool operator>(const BigNumb& B);  //Оператор сравнения >
	bool operator>=(const BigNumb& B); //Оператор сравнения >=
	bool operator<(const BigNumb& B);  //Оператор сравнения <
	bool operator<=(const BigNumb& B); //Оператор сравнения <=
	bool operator==(const BigNumb& B); //Оператор сравнения ==
	bool operator!=(const BigNumb& B); //Оператор сравнения !=
	
	//Перегрузка операторов для Python.
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
	void SetSize(int newSize); 				//Выделение памяти под newSize элементов.
	unsigned char & operator[](int i);
	unsigned char operator[](int i) const;
	void DeleteZeroes(); 					//Удаление ведущих нулей.
	int Compare(const BigNumb& B); 			//Сравнение.
	void Shift(int s);

	BigNumb Add_Sub(const BigNumb& left, const BigNumb& right) const;     			//Сложение и вычитание.
	BigNumb Multipl(const BigNumb A, const BigNumb B) const;           				//Умножение.
	BigNumb Divid(const BigNumb& A, const BigNumb& B, BigNumb &remainder) const;  	//Деление.

};

	BigNumb Pow(const BigNumb& A, const BigNumb& B, BigNumb& Modul);  				//Возведение в степень.