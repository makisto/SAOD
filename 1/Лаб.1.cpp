#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

void FillInc(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = i;
}

void FillDec(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = size - i;
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand() % size;
}

int CheckSum(int *Mas, int size)
{
	int sum = 0;
	for(int i = 0; i < size; i++)
	sum += Mas[i];
	cout << "Контрольная сумма - " << sum << '\n';
}

int RunNumber(int *Mas, int size)
{
	int flag = 1;
	for (int i = 0; i < size; i++)
	{
		if(Mas[i] > Mas[i + 1])
		flag++;
	}
	cout << "Количество серий - " << flag << '\n';
}

void PrintMas(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	cout << Mas[i] << " ";
	cout << '\n';
}

int main()
{                           
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	
	int size;
	
	cout << "Количество элементов - ";
	cin >> size;
	int Mas[size];
	
	cout << endl << "Массив возрастающих чисел: " << endl;
	FillInc(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << '\n';
	
	cout << "Массив убывающих чисел: " << endl;
	FillDec(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << '\n';
	
	cout << "Массив случайных чисел: " << endl;
	FillRand(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	
	return 0;
}         
