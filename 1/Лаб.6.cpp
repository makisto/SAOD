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

void ShellSort(int *Mas, int size)
{
	int m = log10(size)/log10(2)-1;
	int H[m];
	H[0] = 1;
	int z = 1;
	for(int i = 1; i < m; i++)
	H[i] = 2 * H[i - 1] + 1;
	int k = H[m - 1];
	while(k>0)
	{
		z++;
		for(int i = 0; i < size; i++)
		{
			int t = Mas[i];
			int j = i;
			C++;
			while(j >= k && Mas[j - k] > t)
			{
				Mas[j] = Mas[j - k];
				j = j - k;
				M += 2;
			}
		Mas[j] = t;
		M++;
		}
	if(z > m)
	break;
	k = H[m - z];
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	
	int size;
	
	cout << "���������� ��������� - ";
	cin >> size;
	int Mas[500];
	
	cout << endl << "�������� ������ ������������ �����: " << endl;
	FillInc(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "��������������� ������ ������������ �����: " << endl;
	ShellSort(Mas, size);
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
	ShellSort(Mas, size);
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
	ShellSort(Mas, size);
	PrintMas(Mas, size);
	CheckSum(Mas, size);
	RunNumber(Mas, size);
	cout << "������������: " << M << endl;
	cout << "���������: " << C << endl;
	cout << "�����������: " << M + C << endl << '\n';
	
	cout << "K-���������� �� ������� �����:";
	int m = log10(size)/log10(2)-1;
	int H[m];
	H[0] = 1;
	int z = 1;
	for(int i = 1; i < m; i++)
	H[i] = 2 * H[i - 1] + 1;
	for(int i = 0; i < m; i++)
	cout << H[i] << " " << endl;
	
	cout << "������������� ���������:" << (size * size - size)/2 << endl;
	cout << "������������� ������������:" << ((size * size - size)/2) + 2 * size - 2 << endl;
	cout << "������������� �����������: " << ((size * size - size)/2 + ((size * size - size)/2) + 2 * size - 2) << endl << endl;
	
	M = 0; C = 0;
	
	cout<<"N ""\t|\t""K-Sort""\t|\t""Insert""\t|\t""Shell"<<endl;
	for (int i = 100; i <= 500; i += 100)
	{
		cout << i << "\t|\t";
		int t = (log10(i)/log10(2) - 1);
		cout << t << "\t|\t";
		
		FillRand(Mas, i);
		InsertSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\t|\t";
		
		FillRand(Mas, i);
		ShellSort(Mas, i);
		cout << M + C;
		M = 0; C = 0;
		cout << "\n";
	}

	return 0;
}
