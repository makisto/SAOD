#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

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
	Mas[i] = rand()%size;
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

void BubbleSort(int *Mas, int size)
{
	for(int i = 0; i < size - 1; i++) 
	{
		for(int j = 0; j < size - i - 1; j++) 
		{		
			C++;
			if(Mas[j] > Mas[j + 1]) 
			{
				M += 3;
				int temp = Mas[j];
				Mas[j] = Mas[j + 1];
				Mas[j + 1] = temp;
			}
		}
	}
}

void ShakerSort(int *Mas, int size)
{
	int Left = 0;
	int Right = size - 1;
	int change = size;
	do
	{
	for (int j = Right; j >= Left + 1; j--)
	{
		C++;
		if (Mas[j] < Mas[j - 1]) 
		{
			M += 3;
			int temp = Mas[j];
			Mas[j] = Mas[j - 1];
			Mas[j - 1] = temp;
			change = j;
		}
	}	
	Left = change;
	for (int j = Left; j <= Right - 1; j++)
	{
		C++;
		if (Mas[j] > Mas[j + 1]) 
		{
			M += 3;
			int temp = Mas[j];
			Mas[j] = Mas[j + 1];
			Mas[j + 1] = temp;
			change = j;
		}
	}
	Right = change;
	} while(Left < Right);
}

void InsertSort(int *Mas, int size)
{
	for(int i = 1; i < size; i++)
	{
		int t = Mas[i];
		int j = i;
		C++;
		while((j > 0) && (Mas[j - 1] > t))
		{
			Mas[j] = Mas[j - 1];
			j--;
			M += 2;
		}
		Mas[j] = t;	
		M++;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	
	int size;
	
	cout << "Количество элементов - ";
	cin >> size;
	int Mas[500];
	
	cout << endl << "Исходный массив возрастающих чисел: " << endl;
	FillInc(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Отсортированный массив возрастающих чисел: " << endl;
	InsertSort(Mas, size);
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
	InsertSort(Mas, size);
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
	InsertSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Перестановки: " << M << endl;
	cout << "Сравнения: " << C << endl;
	cout << "Трудоёмкость: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "Теоретические сравнения:" << (size * size - size)/2 << endl;
	cout << "Теоретические перестановки:" << ((size * size - size)/2) + 2 * size - 2 << endl;
	cout << "Теоретическая трудоёмкость: " << ((size * size - size)/2 + (((size * size - size)/2) + 2 * size - 2)) << endl << endl;
	
	M = 0; C = 0;

	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "N""\t|\t""Select""\t\t|\t""Bubble""\t\t|\t""Shaker""\t\t|\t""Insert""\t\t|\t" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	
	for (int i = 100; i <= 500; i += 100)
	{
		cout << i << "\t|\t\t";
		FillRand(Mas, i);
		SelectSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\t|\t\t";
		
		FillRand(Mas, i);
		BubbleSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\t|\t\t";
		
		FillRand(Mas, i);
		ShakerSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\t|\t\t";
		
		FillRand(Mas, i);
		InsertSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\t|\t\t";
	}
	
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	
	return 0;
}
