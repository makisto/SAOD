#include <iostream>
#include <math.h>

#define size 256
	
using namespace std;

void probabilities(string mess, int n, double* p, double* q, char* a)
{
	for(int i = 0; i < size; i++)
	{
		a[i] = i;
		p[i] = 0;
		q[i] = 0;
	}
	
	for (int i = 0; i < n; i++)
	{
		int j = mess[i];
		p[j]++;
	}
	
	for (int i = 0; i < size; i++)
	{
		p[i] /= n;	
	}

	q[0] = p[0];
	for(int i = 1; i < size; i++)
	{
		q[i] = q[i - 1] + p[i];
	}
}

void erge(char* a, double* p, double* q)
{
	float psum = 0;
	double entropy = 0;
	for (int i = 0; i < size; i++)
	{
		if(p[i] > 0)
		{
			cout << a[i] << "\t" << p[i] << "\t" << q[i] << endl;
		}
	}
	
	for(int i = 0; i < size; ++i)
	{
		if(p[i] > 0)
		{
			entropy += -1 * p[i] * log2(p[i]);
			psum += p[i];
		}
	}
	cout << "Сумма вероятностей:" << psum << endl;
	cout << "Энтропия: " << entropy << endl;
}

void ariphcode(string mess, char* a, double* q, double* p)
{
	double h = 1;
	double hpr = 1;
	double r = 1;
	double l = 0;
	double lpr = 0;
	int length = 0;
	int m = 0;
	int lsr = 0;
	
	for(int i = 0; i < mess.length(); i++)
	{
		char j = mess[i];
		for(int i = 0; i < size; i++)
		{
			if(j == a[i])
			{
				m = i;				
				//cout << (int)a[i] << "\t" << q[m] << "\t" << q[m - 1] << endl << endl;
				break;	
			}	
		}
		l = lpr + (r * q[m - 1]);
		h = lpr + (r * q[m]);
		r = h - l;
		lpr = l;
		hpr = h;
		cout << lpr << "\t" << hpr << "\t" << r << endl << endl;
		cout << endl << endl;
		length = -1 * log2(r);
		cout << "Длина закодированного файла в битах:" << length << endl;
		lsr = length / 8;
		if(lsr % 2 == 0 || lsr < 1)
		{
			lsr++;	
		}
		cout << "Коэффициент сжатия(%):" << (double)lsr/mess.length() * 100<< endl;	
	}
}

int main()
{
	string mess = "Hello";
	
	double p[size];
	double q[size];
	char a[size];	
	
	probabilities(mess, mess.length(), p, q, a);
	ariphcode(mess, a, q, p);	
	erge(a, p, q);
	
	return 0;
}
