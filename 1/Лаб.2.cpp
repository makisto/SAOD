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

int C = 0, M = 0;

void SelectSort(int *Mas, int size)
{
	for (int i = 0; i < size - 1; i++) 
	{
		int min = i; 
		for(int j = i + 1; j < size; j++) 
			{
				C++;
				if(Mas[j] < Mas[min]) 
				min = j;    
			}
		M += 3;
		int temp = Mas[i];      
		Mas[i] = Mas[min];
		Mas[min] = temp;
	}
}

int main() 
{
	setlocale(LC_ALL, "Russian"); 
	srand(time(NULL));
	
	int size;
	
	cout << "Количество элементов - ";
	cin >> size;
	int Mas[size];
	
	cout << endl << "Исходный массив возрастающих чисел: " << endl;
	FillInc(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Отсортированный массив возрастающих чисел: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Перестановки: " << M << endl;
	cout << "Сравнения: " << C << endl;
	cout << "Трудоёмкость: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "Исходный массив убывающих чисел: " << endl;
	FillDec(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Отсортированный массив убывающих чисел: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Перестановки: " << M << endl;
	cout << "Сравнения: " << C << endl;
	cout << "Трудоёмкость: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "Исходный массив случайных чисел: " << endl;
	FillRand(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Отсортированный массив случайных чисел: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Перестановки: " << M << endl;
	cout << "Сравнения: " << C << endl;
	cout << "Трудоёмкость: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "Теоретические сравнения: " << 3 * (size - 1) << endl;
	cout << "Теоретические перестановки: " << (size * (size - 1)) / 2 << endl;
	cout << "Теоретическая трудоёмкость: " <<(3 * (size - 1)) + ((size * (size - 1)) / 2);

	return 0;
}
