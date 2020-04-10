#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <math.h>
#include <iomanip>

#define base_fields 4000

using namespace std;

double P[256], Q[256], L[256];
char a[256];
string codewords[256];

void QuickSort(double* a, char* b, int l, int n)
{
	double x = a[(l+n) / 2];
	int i = l;
	int j = n;
	while(i <= j)
	{
		while(a[i] > x)
		{
			i++;
		}
		while(a[j] < x)
		{
			j--;
		}
		if(i <= j)
		{
			double temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			char buf = b[i];
			b[i] = b[j];
			b[j] = buf;
			i++;
			j--;
		} 
	}
	if(l < j)
	{
		QuickSort(a, b, l, j);	
	}
	if(i < n)
	{
		QuickSort(a, b, i, n);	
	}
}

void probabilities()
{
    long count = 0;
    FILE* fin = fopen("testBase4.dat", "r+b");
    while (!feof(fin))
	{
		int j = fgetc(fin);
		P[j]++;
		count++;
    }
    count--;
    fclose(fin);
    cout << count << endl;
    for (int i = 0; i < 256; i++)
	{
		if(P[i] > 0)
		{
			a[i] = i;
			P[i] /= (float)count;	
		}	
    }
    QuickSort(P, a, 0, 255);
}

void shennon()
{
	Q[0] = 0;
	if(P[0] > 0)
	{
		L[0] = (int)(-1 * log2(P[0]) + 1);	
	}
	for(int i = 1; i < 256; i++)
	{
		if(P[i] > 0)
		{
			Q[i] = Q[i - 1] + P[i - 1];
			L[i] = (int)(-1 * log2(P[i]) + 1);	
		}	
	}
	for(int i = 0; i < 256; i++)
	{
		for(int j = 0; j < L[i]; j++)
		{
			Q[i] = Q[i] * 2;
			if((char)(Q[i] + 48) == '2')
			{
				codewords[i] += "0";	
			}
			else
			{
				codewords[i] += (char)(Q[i] + 48);	
			}	
			if(Q[i] > 1) 
			{
				Q[i] -= 1; 	
			} 
		}
	}
}

void parametrs()
{
	double S = 0;
	double M = 0;
	double psum = 0;
	int cou = 1;
	cout << "Кодовая таблица" << endl;
	for (int i = 0; i < 256; i++)
	{
		if(P[i] > 0)
		{
			cout << cou++ << "\t" /*<< a[i]*/ << "\t" << P[i] << "\t           "  << codewords[i].length() << "\t" << codewords[i] << endl;	
			S += P[i] * (float)L[i];
			M += -1 * P[i] * log2(P[i]);
			psum += P[i];
		}
    }
    cout << "Сумма вероятностей: " << psum << endl;
	cout << "Энтропия: " << M << endl;
	cout << "Средняя длина кодового слова: " << S << endl;
}

int main()
{
	char b[256];
	/*probabilities();
	shennon();
	parametrs();*/
	for(int i = 0; i < 256; i++)
	{
		b[i] = i;
		cout << i << "\t" << b[i] << endl;
	}
	return 0;
}
