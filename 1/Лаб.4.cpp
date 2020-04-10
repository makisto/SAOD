#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <graphics.h>
#include <conio.h>

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
	ShakerSort(Mas, size);
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
	ShakerSort(Mas, size);
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
	ShakerSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "Перестановки: " << M << endl;
	cout << "Сравнения: " << C << endl;
	cout << "Трудоёмкость: " << M + C << endl << '\n';
	M = 0; C = 0;
	
	cout << "Теоретические сравнения:" << (size * size - size)/2 << endl;
	cout << "Теоретические перестановки:" << (3 * (size * size - size))/4 << endl;
	cout << "Теоретическая трудоёмкость: " << ((size * size - size)/2 + ((3 * (size * size - size))/4)) << endl << endl;
	
	M = 0; C = 0;
	
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "N""\t|\t""Убывающие""\t|\t""Случайные""\t|\t""Возрастающие""\t|\t" << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	
	for (int i = 100; i <= 500; i += 100)
	{
		cout << i << "\t|\t\t";
		FillDec(Mas, i);
		ShakerSort(Mas, i); 
		cout << M + C;
		M = 0; C = 0;
		
		cout << "\t|\t\t";
		FillRand(Mas, i);
		ShakerSort(Mas, i); 
		cout << M + C; 
		M=0; C=0;
		
		cout << "\t|\t\t";
		FillInc(Mas, i);
		ShakerSort(Mas, i); 
		cout << M+C; 
		M=0; C=0;
		cout << "\t|\t" << endl;
	};
	
	cout << "---------------------------------------------------------------------------------" << endl;
	
	initwindow(640, 480);
	moveto(320, 0);
	lineto(320, 480);
	moveto(0, 240);
	lineto(640, 240);
	moveto(320, 240);
	setcolor(GREEN);
	for (int i = 1; i < 100; i += 5)
	{
		lineto(i + 320, M + C + 240);
		M += 3 * (i * i - i)/4;
		C += (i * i - i)/2;
	}
	getch();
	
	return 0;
}
