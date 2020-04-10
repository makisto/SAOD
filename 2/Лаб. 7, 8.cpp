#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <math.h>

using namespace std;

const int size = 100;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

struct vertex
{
	int data;
	int ves;
	vertex *left;
	vertex *right;
};

vertex* root = NULL;
int SSum = 0;
int aa = 0;

int RootObhod(vertex *p)
{
	if(p != NULL)
	{
		cout << p -> data << " ";
		RootObhod(p -> left);
		RootObhod(p -> right);
	}
	else
	{
		return 0;
	}
}

int LeftObhod(vertex *p)
{
	if(p != NULL) 
	{
		LeftObhod(p -> left);
		cout << p -> data << " ";
		LeftObhod(p -> right);
	}
	else
	{
		return 0;
	}
}

int UndRootObhod(vertex *p)
{
	if(p != NULL)
	{
		UndRootObhod(p -> left);
		UndRootObhod(p -> right);
		cout << p -> data << " ";
	}
	else
	{
		return 0;
	}
}

int TreeSize(vertex *p)
{
	int hsize;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		hsize = 1 + TreeSize(p -> left) + TreeSize(p -> right);
		return hsize;
	}
}

int TreeVes(vertex *p)
{
	int hves;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		hves = p -> ves + TreeVes(p -> left) + TreeVes(p -> right);
		return hves;
	}
}

int TreeSum(vertex *p)
{
	int sum;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		sum = p -> data + TreeSum(p -> left) + TreeSum(p -> right);
		return sum;
	}
}

int TreeHeight(vertex *p)
{
	int height;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		height = 1 + max(TreeHeight(p -> left), TreeHeight(p -> right));
		return height;
	}
}

int TreeSizeSum(vertex *p, int l)
{
	int sum;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		sum = l + TreeSizeSum(p -> left, l + 1) + TreeSizeSum(p -> right, l + 1);
		return sum;
	}
}

void TreeSearch(vertex *p, int x)
{
	while(p != NULL)
	{
		if(p -> data < x)
		{
			p = p -> right;
		}
		else if(p -> data > x)
		{
			p = p -> left;
		}
		else
		{
			break;
		}
	}
	if (p != NULL)
	{
		cout << "Вершина существует";
	}
	else
	{
		cout << "Вершина не сущестует";
	}
}

bool Tree(vertex *p)
{
	bool tree = true;
	if(p == NULL)
	{
		tree = false;	
	}
	else if(p != NULL && (p -> left != NULL && (p -> data <= p -> left -> data || !Tree(p -> left))) 
	|| (p -> right != NULL && (p -> data >= p -> right -> data || !Tree(p -> right))))
	{	
		tree = false;	
	}
	return tree;
}

void SDP(int d, int c, vertex*& p)
{
	if(p == NULL)
	{
		aa++;
		p = new vertex;
		p -> data = d;
		p -> right = NULL;
		p -> left = NULL;
		p -> ves = c;
		SSum += aa * c;
		aa = 0;
	}
	else if(d < p-> data)
	{
		aa++;
		SDP(d, c, p -> left);
	}
	else if(d > p -> data)
	{
		aa++;
		SDP(d, c, p -> right);
	}
}

void APAR(int aw[][size + 1], int ap[][size + 1], int ar[][size + 1], int* ves)
{
	int i, j, m, h, k, min, x;
	
	for(i = 0; i < size + 1; i++)
	{
		for(j = 0; j < size + 1; j++)
		{
			aw[i][j] = 0;
			ap[i][j] = 0;
			ar[i][j] = 0;
		}
	}
	
	for(i = 0; i < size + 1; i++)
	{
		for(j = i + 1; j < size + 1; j++)
		{
			aw[i][j] = aw[i][j - 1] + ves[j - 1];
		}
	}

	for(i = 0; i < size; i++)
	{
		j = i + 1;
		ap[i][j] = aw[i][j];
		ar[i][j] = j;
	}
	
	for(h = 2; h < size + 1; h++)
	{
		for(i = 0; i < size + 1 - h; i++)
		{
			j = i + h;
			m = ar[i][j - 1];
			min = ap[i][m - 1] + ap[m][j];
			for(k = m + 1; k <= ar[i + 1][j]; k++)
			{
				x = ap[i][k - 1] + ap[k][j];
				if(x < min)
				{
					m = k;
					min = x;
				}
			}
			ap[i][j] = aw[i][j] + min;
			ar[i][j] = m;
		}
	}
	
	/*for(i = 0; i < size + 1; i++)
	{
		for(j = 0; j < size + 1; j++)
		{
			cout << aw[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout << endl;
	
	for(i = 0; i < size + 1; i++)
	{
		for(j = 0; j < size + 1; j++)
		{
			cout << ap[i][j] << "\t";
		}
		cout << endl;
	}
	
	cout << endl;
	
	for(i = 0; i < size + 1; i++)
	{
		for(j = 0; j < size + 1; j++)
		{
			cout << ar[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;*/
}

void DOP(int l, int r, int ar[][size + 1], int* v, int* ves)
{
	int k;
	if(l < r)
	{
		k = ar[l][r];
		SDP(v[k - 1], ves[k - 1], root);
		DOP(l, k - 1, ar, v, ves);
		DOP(k, r, ar, v, ves);
	}
}

void QuickSort(int *a, int l, int n)
{
	int x = a[(l+n) / 2];
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
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
			j--;
		} 
	}
	if(l < j)
	{
		QuickSort(a, l, j);	
	}
	if(i < n)
	{
		QuickSort(a, i, n);	
	}
}

void SelectSort(int *Mas, int size)
{
	for (int i = 0; i < size - 1; i++) 
	{
		int min = i; 
		for(int j = i + 1; j < size; j++) 
		{
			if(Mas[j] < Mas[min]) 
			min = j;    
		}
		int temp = Mas[i];      
		Mas[i] = Mas[min];
		Mas[min] = temp;
	}
}

void A2(int l, int r, int* ves, int* Mas)
{
	int i;
	int wes = 0;
	int summa = 0;
	if(l <= r)
	{
		for(i = l; i <= r; i++)
		{
			wes = wes + ves[i]; 
		}
		for(i = l; i < r; i++)
		{
			if((summa < wes / 2) && (summa + ves[i] >= wes / 2))
			{
				break;
			}
			summa = summa + ves[i];
		}
		SDP(Mas[i], ves[i], root);
		A2(l, i - 1, ves, Mas);
		A2(i + 1, r, ves, Mas);
	}
}

void gotoxy(int x, int y)
{
	COORD place = {x, y};
	SetConsoleCursorPosition(console, place);
} 

void print(vertex* p, int x, int y, int s, int h)
{
	if(p)
	{
		if(s == 0)
		{
			gotoxy(x, y);
		}
		else if(s == -1)
		{
			gotoxy(x + 1, y - 1);
			cout << "/";
			gotoxy(x, y);	
		}
		else if(s == 1)
		{
			gotoxy(x - 1, y - 1);
			printf("%c", 92);
			gotoxy(x, y);
		}
		cout << p -> data;
		cout << "(" << p -> ves << ")";
		print(p -> left, x - pow(2, h), y += 3, -1, h - 1);
		print(p -> right, x + pow(2, h), y, 1, h - 1);
	}
}

void FillInc(int *Mas, int msize)
{
	for(int i = 0; i < msize; i++)
	Mas[i] = i;
}

void FillRand(int *Mas, int msize)
{
	for(int i = 0; i < msize; i++)
	Mas[i] = rand() % 10000;
}

void PrintMas(int *Mas, int msize)
{
	for(int i = 0; i < msize; i++)
	cout << Mas[i] << " ";
	cout << '\n';
}
	
int main()
{
	srand(time(NULL));

	int x;
	int key;
	int VESUM;
	int Tsize, sum, height, tves; 
	float MidHeight, SSumHeight;
	bool tree;
		
	int ves[size];
	int Mas[size];
	int aw[size + 1][size + 1];
	int ap[size + 1][size + 1];
	int ar[size + 1][size + 1];

	FillRand(Mas, size);
	FillRand(ves, size);

	SelectSort(Mas, size);
	APAR(aw, ap, ar, ves);
	DOP(0, size, ar, Mas, ves);
	
	float q = ap[0][size];
	float f = aw[0][size];
	cout << "Средневзвешенная высота по матрицам - " << q / f << endl;
	
	cout <<"\nИсходные данные для ДОП - ";
	PrintMas(Mas, size);
	
	cout <<"\nМассив весов - ";
	PrintMas(ves, size);
	
	cout <<"\nДОП - Дерево-";
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
		
	Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	tves = TreeVes(root);
	cout <<"Вес дерева - " << tves << endl;
	sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	height = TreeHeight(root);
	cout <<"Высота дерева - " << height << endl;
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"Средняя высота дерева - " << MidHeight << endl;
	cout << "Взвешенная высота дерева - " << SSum << endl;
	SSumHeight = (float)SSum / tves;
	cout << "Средневзвешенная высота - " << SSumHeight << endl;
	SSum = 0;
	
	tree = Tree(root);
	if(tree == false)
	{
		cout <<"\nЭто не дерево поиска";
		_getch();
	}
	else
	{
		cout <<"\nЭто дерево поиска";
		cout <<"\nВведите ключ поиска - ";
		cin >> key;
		TreeSearch(root, key);
	}
	
	system("CLS");
	cout <<"\nДерево:\n";
	print(root, pow(2, 5 + 1), 10, 0, 5);
	cout << endl << endl << endl << endl;
	_getch();
	////////////////////
	////////////////////
	//////////////////////
	system("CLS");
	root = NULL;
	
	FillRand(Mas, size);
	QuickSort(ves, 0, size - 1);
	for(int i = 0; i < size; i++)
	{
		SDP(Mas[i], ves[i], root);
	}	
	
	cout <<"\nИсходные данные для ДОП(A1) - ";
	PrintMas(Mas, size);
	
	cout <<"\nМассив весов(A1) - ";
	PrintMas(ves, size);
	
	cout <<"\nДОП - Дерево(A1)-";
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
		
	Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	tves = TreeVes(root);
	cout <<"Вес дерева - " << tves << endl;
	sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	height = TreeHeight(root);
	cout <<"Высота дерева - " << height << endl;
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"Средняя высота дерева - " << MidHeight << endl;
	cout << "Взвешенная высота дерева - " << SSum << endl;
	SSumHeight = (float)SSum / tves;
	cout << "Средневзвешенная высота - " << SSumHeight << endl;
	SSum = 0;
	
	tree = Tree(root);
	if(tree == false)
	{
		cout <<"\nЭто не дерево поиска";
		_getch();
	}
	else
	{
		cout <<"\nЭто дерево поиска";
		cout <<"\nВведите ключ поиска - ";
		cin >> key;
		TreeSearch(root, key);
	}
	
	system("CLS");
	cout <<"\nДерево:\n";
	print(root, pow(2, 4 + 1), 10, 0, 4);
	cout << endl << endl << endl << endl;
	_getch();
	
	system("CLS");
	root = NULL;
	SelectSort(Mas, size);
	A2(0, size - 1, ves, Mas);
	
	cout <<"\nИсходные данные для ДОП(A2) - ";
	PrintMas(Mas, size);
	
	cout <<"\nМассив весов(A2) - ";
	PrintMas(ves, size);
	
	cout <<"\nДОП - Дерево(A2)-";
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
		
	Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	tves = TreeVes(root);
	cout <<"Вес дерева - " << tves << endl;
	sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	height = TreeHeight(root);
	cout <<"Высота дерева - " << height << endl;
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"Средняя высота дерева - " << MidHeight << endl;
	cout << "Взвешенная высота дерева - " << SSum << endl;
	SSumHeight = (float)SSum / tves;
	cout << "Средневзвешенная высота - " << SSumHeight << endl;
	SSum = 0;
	
	tree = Tree(root);
	if(tree == false)
	{
		cout <<"\nЭто не дерево поиска";
		_getch();
	}
	else
	{
		cout <<"\nЭто дерево поиска";
		cout <<"\nВведите ключ поиска - ";
		cin >> key;
		TreeSearch(root, key);
	}
	
	system("CLS");
	cout <<"\nДерево:\n";
	print(root, pow(2, SSumHeight + 1), 10, 0, SSumHeight);
	cout << endl << endl << endl << endl;
	_getch();
	
	cout << endl << endl;
	root = NULL;
	
	system("CLS");	
	cout <<"N = 100\tРазмер\tКонтр.Сумма\tСредн.взвеш.Высота" << endl;

	int Mas1[size];
	int ves1[size];
	int aw1[size + 1][size + 1];
	int ap1[size + 1][size + 1];
	int ar1[size + 1][size + 1];
	
	FillRand(Mas1, size);
	FillRand(ves1, size);
	
	QuickSort(ves, 0, size - 1);
	
	for(int i = 0; i < size; i++)
	{
		SDP(Mas1[i], ves1[i], root);
	}
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	tves = TreeVes(root);
	SSumHeight = (float)SSum / tves;
	
	cout << "A1" << "\t";
	cout << Tsize  << "\t";
	cout << sum << "\t\t"; 
	cout << SSumHeight << "\t";
	SSum = 0;
	
	cout << endl;
	root = NULL;
	
	SelectSort(Mas1, size);
	
	A2(0, size - 1, ves1, Mas1);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	tves = TreeVes(root);
	SSumHeight = (float)SSum / tves;
		
	cout << "A2" << "\t";
	cout << Tsize  << "\t";
	cout << sum << "\t\t"; 
	cout << SSumHeight << "\t";
	SSum = 0;
	
	cout << endl;
	root = NULL;
	
	APAR(aw1, ap1, ar1, ves1);
	DOP(0, size, ar1, Mas1, ves1);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	tves = TreeVes(root);
	SSumHeight = (float)SSum / tves;
	
	cout << "ДОП" << "\t";
	cout << Tsize  << "\t";
	cout << sum << "\t\t"; 
	cout << SSumHeight << "\t";
	
	return 0;
}
