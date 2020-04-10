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
	cout << "����������� ����� - " << sum << '\n';
}

int RunNumber(int *Mas, int size)
{
	int flag = 1;
	for (int i = 0; i < size; i++)
	{
		if(Mas[i] > Mas[i + 1])
		flag++;
	}
	cout << "���������� ����� - " << flag << '\n';
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
	
	cout << "���������� ��������� - ";
	cin >> size;
	int Mas[size];
	
	cout << endl << "�������� ������ ������������ �����: " << endl;
	FillInc(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "��������������� ������ ������������ �����: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "������������: " << M << endl;
	cout << "���������: " << C << endl;
	cout << "�����������: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "�������� ������ ��������� �����: " << endl;
	FillDec(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "��������������� ������ ��������� �����: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "������������: " << M << endl;
	cout << "���������: " << C << endl;
	cout << "�����������: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "�������� ������ ��������� �����: " << endl;
	FillRand(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "��������������� ������ ��������� �����: " << endl;
	SelectSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "������������: " << M << endl;
	cout << "���������: " << C << endl;
	cout << "�����������: " << M + C << endl << '\n';
	
	M = 0; C = 0;
	
	cout << "������������� ���������: " << 3 * (size - 1) << endl;
	cout << "������������� ������������: " << (size * (size - 1)) / 2 << endl;
	cout << "������������� �����������: " <<(3 * (size - 1)) + ((size * (size - 1)) / 2);

	return 0;
}
