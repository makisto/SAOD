#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <math.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

struct vertex
{
	int data;
	vertex *left;
	vertex *right;
}*root = NULL;

void RootObhod(vertex *p)
{
	if(p != NULL)
	{
		cout << p -> data << " ";
		RootObhod(p -> left);
		RootObhod(p -> right);
	}
}

void LeftObhod(vertex *p)
{
	if(p != NULL) 
	{
		LeftObhod(p -> left);
		cout << p -> data << " ";
		LeftObhod(p -> right);
	}
}

void UndRootObhod(vertex *p)
{
	if(p != NULL)
	{
		UndRootObhod(p -> left);
		UndRootObhod(p -> right);
		cout << p -> data << " ";
	}
}

int TreeSize(vertex *p)
{
	int size;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		size = 1 + TreeSize(p -> left) + TreeSize(p -> right);
	}
	return size;
}

void PrintTree(vertex *p, int level) 
{
	if(p -> right)
	PrintTree(p -> right, level + 1);
	
	for(int i = 0; i < level + 1; i++)cout << "|";
	cout << p -> data << endl;
    
    if(p -> left)
	PrintTree(p -> left, level + 1);
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
	}
	return sum;
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
	}
	return height;
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
	}
	return sum;
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
		cout << "������� ����������";
	}
	else
	{
		cout << "������� �� ���������";
	}
}

bool Tree(vertex *p)
{
	bool tree = true;
	if(p != NULL && (p -> left != NULL && (p -> data <= p -> left -> data || !Tree(p -> left))) 
	|| (p -> right != NULL && (p -> data >= p -> right -> data || !Tree(p -> right))))
	{
		tree = false;
	}
	return tree;
}

vertex *ISDP(int left, int right, int *Mas)
{
	if(left > right)
	{
		return NULL;
	}
	else
	{
		int size = (left + right) / 2;
		vertex *p = new vertex;
		p -> data = Mas[size];
		p -> left = p -> right = NULL;
		p -> left = ISDP(left, size - 1, Mas);
		p -> right = ISDP(size + 1, right, Mas);
		return p;
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
		print(p -> left, x - pow(2, h), y += 3, -1, h - 1);
		print(p -> right, x + pow(2, h), y, 1, h - 1);
	}
}

void FillInc(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = i;
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
	int key;
	
	cout << "���������� ������ - ";
	cin >> size;
	int Mas[size];
	
	cout <<"\n�������� ������ ��� ���� - ";
	FillInc(Mas, size);
	PrintMas(Mas, size);
	
	root = ISDP(0, size - 1, Mas);
		
	cout <<"\n����� ������ ����� ������� - ";
	LeftObhod(root);
	cout <<"\n����� ������ ����� ����� - ";
	UndRootObhod(root);
	cout <<"\n����� ������ ������ ���� - ";
	RootObhod(root);
	
	int Tsize = TreeSize(root);
	cout <<"\n������ ������ - " << Tsize << endl;
	int sum = TreeSum(root);
	cout <<"����������� ����� ������ - " << sum << endl;
	int height = TreeHeight(root);
	cout <<"������ ������ - " << height << endl;
	float MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"������� ������ ������ - " << MidHeight << endl;
	
	bool tree = Tree(root);
	if(tree == false)
	{
		cout <<"\n��� �� ������ ������";
	}
	else
	{
		cout <<"\n��� ������ ������";
		cout <<"\n������� ���� ������ - ";
		cin >> key;
		TreeSearch(root, key);
	}
	
	cout <<"\n������:\n";
	print(root, pow(2, 5 + 1), 10, 0, 5);
	
	return 0;
}
