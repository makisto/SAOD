#include <math.h>
#include <iostream>

#define size 256

using namespace std;

void InsertSort(double* p, char* a)
{
	int i, j;
	double t1;
	char t2;
	for (i = 1; i < size; i++) 
	{
		t1 = p[i]; 
		t2 = a[i];
		for (j = i - 1; (j >= 0) && (t1 >= p[j]); j--)
		{
			p[j+1] = p[j];
			a[j+1] = a[j];
		}
		p[j+1] = t1;
		a[j+1] = t2;
	}
}

void probabilities(string mess, int n, double* p)
{
	int j = 0;
	
	for (int i = 0; i < n; i++)
	{
		j = mess[i];
		p[j]++;
	}
	
	for (int i = 0; i < size; i++)
	{
		p[i] /= n;
	}
}

void shennon(double* p, string* codewords, int* l, double* q)
{
	q[0] = 0;
	l[0] = (int)(-1 * log2(p[0]) + 1);	
	for (int i = 1; i < size; i++)
	{
		q[i] = q[i - 1] + p[i - 1];
		if(p[i] > 0)
		{
			l[i] = (int)(-1 * log2(p[i]) + 1);	
		}
	}
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < l[i]; j++)
		{
			q[i] *= 2;
			if((char)(q[i] + 48) == '2')
			{
				codewords[i] += "0";	
			}
			else
			{
				codewords[i] += (char)(q[i] + 48);	
			}
			if(q[i] > 1) 
			{
				q[i]--; 	
			}
		}
	}
}

void gilbmur(string* codewords, int* l, double* q, double* p)
{
	q[0] = 0;
	l[0] = (int)(-1 * log2(p[0]) + 1);
	for (int i = 1; i < size; i++)
	{
		q[i] = q[i - 1] + p[i - 1];
		if(p[i] > 0)
		{
			l[i] = (int)(-1 * log2(p[i]) + 2);	
		}
	}
	for (int i = 0; i < size; i++)
	{
		q[i] += p[i] / 2;
	}
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < l[i]; j++)
		{
			q[i] *= 2;
			if((char)(q[i] + 48) == '2')
			{
				codewords[i] += "0";	
			}
			else
			{
				codewords[i] += (char)(q[i] + 48);	
			}
			if(q[i] > 1) 
			{
				q[i]--; 	
			}
		}
	}
}

int med(int l, int r, double* p)
{
	double sumL, sumR;
	sumL = 0;
	for(int i = l; i < r - 1; i++)
	{
		sumL += p[i];
	}
	sumR = p[r - 1];
	int m = r - 1;
	while(sumL >= sumR)
	{
		m--;
		sumL -= p[m];
		sumR += p[m];
	}
	return m;
}

void fano(int l, int r, string* codewords, double* p)
{
	if (l < r - 1)
	{
		int m = med(l, r, p);
		for (int i = l; i < r; i++)
		{
			if (i <= m)
			{
				codewords[i] += "0";	
			} 
			else 
			{
				codewords[i] += "1";
			}
		}
		fano(l, m + 1, codewords, p);
		fano(m + 1, r, codewords, p);
	}
}

int up(int n, double q, double* p)
{
	int j;
	int i;
	for (i = (n - 2); i > 0; i--)
	{
		if(p[i - 1] <= q)
		{
			p[i] = p[i - 1];	
		}
		else 
		{
			j = i;
			break;
		}
	}
	if (!i)
	j = 0;
	p[j] = q;
	return j;
}

int down(int n, int j, string* codewords)
{
	string s = codewords[j];
	for (int i = j; i < (n - 2); i++)
	{
		codewords[i] = codewords[i + 1];
	}
	codewords[n - 2].clear();
	codewords[n - 1].clear();
	codewords[n - 2] = s + "0";
	codewords[n - 1] = s + "1";
}

void huffman(int n, double* p, string* codewords)
{
	int j;
	double q;
	if (n == 2)
	{
		codewords[n - 2] = "0";
		codewords[n - 1] = "1";
	} 
	else 
	{
		q = p[n - 2] + p[n - 1];
		j = up (n, q, p);
		huffman (n - 1, p, codewords);
		down (n, j, codewords);
	}
}

void fillmas(double* p, char* a, int* l, double* q)
{
	for (int i = 0; i < size; i++)
	{
		p[i] = 0;
		a[i] = i;
		l[i] = 0;
		q[i] = 0;
	}
}

double erge(string* codewords, char* a, double* p)
{
	float psum = 0;
	double entropy = 0;
	double length = 0;
	for (int i = 0; i < size; i++)
	{
		if(p[i] > 0)
		{
			cout << a[i] << "\t" << p[i] << "\t" << codewords[i].length() << "\t" << codewords[i] << endl;
		}
	}
	
	for(int i = 0; i < size; i++)
	{
		if(p[i] > 0)
		{
			entropy += -1 * p[i] * log2(p[i]);
			length += codewords[i].length() * p[i];
			psum += p[i];
		}
	}
	cout << "Сумма вероятностей:" << psum << endl;
	cout << "Энтропия: " << entropy << endl;
	cout << "Средняя длина кодового слова: " << length << endl << endl;
	
	return length;
}

int main()
{
	string mess = "fggfugjkrndfgnbkojdsdx;'clr cjenricrseldgzdnlck'";
	
	double p[size];
	char a[size];
	double q[size];
	int l[size];
	double p1[size];
	double shennon_length = 0;
	double gilmoor_length = 0;
	double fano_length = 0;
	double huffman_length = 0;
	double entropy = 0;
	
	string codewords[size];
	string codewords2[size];
	string codewords3[size];
	string codewords4[size];
	
	cout << "Код Шеннона" << endl;
	fillmas(p, a, l, q);
	probabilities(mess, mess.length(), p);
	InsertSort(p, a);
	shennon(p, codewords, l, q);
	shennon_length = erge(codewords, a, p);
	
	cout << "Код Гилберта-Мура" << endl;
	fillmas(p, a, l, q);
	probabilities(mess, mess.length(), p);
	gilbmur(codewords2, l, q, p);
	gilmoor_length = erge(codewords2, a, p);
	
	cout << "Код Фано" << endl;
	fillmas(p, a, l, q);
	probabilities(mess, mess.length(), p);
	InsertSort(p, a);
	int lk = 0;
	while (p[lk] != 0)
	{
		lk++;
	}
	int kl = lk;
	fano(0, kl, codewords4, p);
	fano_length = erge(codewords4, a, p);
	
	cout << "Код Хаффмана" << endl;
	fillmas(p, a, l, q);
	probabilities(mess, mess.length(), p);
	InsertSort(p, a);
	for (int i = 0; i < size; ++i)
	{
		p1[i] = p[i];
	}
	huffman(kl, p1, codewords3);
	huffman_length = erge(codewords3, a, p);
	
	for(int i = 0; i < size; i++)
	{
		if(p[i] > 0)
		{
			entropy += -1 * p[i] * log2(p[i]);	
		}
	}
	cout << "Энтропия: " << entropy << endl << endl;
	cout << "Средняя длина кодового слова: " << endl;
	cout << "Код Шеннона: " << shennon_length << endl;
	cout << "Код Гилберта-Мура: " << gilmoor_length<< endl;
	cout << "Код Фано: " << fano_length << endl;
	cout << "Код Хаффмана: " << huffman_length << endl;
	
	return 0;
}
