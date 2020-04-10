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
	int bal;
	vertex *left;
	vertex *right;
};

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
	int size;
	if(p == NULL)
	{
		return 0;
	}
	else
	{
		size = 1 + TreeSize(p -> left) + TreeSize(p -> right);
		return size;
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

void PrintTree(vertex *p, int level) 
{
	if(p -> right)
	PrintTree(p -> right, level + 1);
	
	for(int i = 0; i < level + 1; i++)cout << "|";
	cout << p -> data << endl;
    
    if(p -> left)
	PrintTree(p -> left, level + 1);
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

bool rost, umen;

void LL(vertex*& p)
{
	vertex* q;
	q = p -> left;
	q -> bal = 0;
	p -> bal = 0;
	p -> left = q -> right;
	q -> right = p;
	p = q;
}

void LR(vertex*& p)
{
	vertex* q;
	vertex* r;
	q = p -> left;
	r = q -> right;
	if (r -> bal < 0) 
	{
		p -> bal = 1;	
	}
	else 
	{
		p -> bal = 0;	
	}
	if (r -> bal > 0) 
	{
		q -> bal = -1;	
	}
	else 
	{
		q -> bal = 0;	
	}
	r -> bal = 0;
	p -> left = r -> right;
	q -> right = r -> left;
	r -> left = q;
	r -> right = p;
	p = r;	
}

void RR(vertex*& p)
{
	vertex* q;
	q = p -> right;
	q -> bal = 0;
	p -> bal = 0;
	p -> right = q -> left;
	q -> left = p;
	p = q;
}

void RL(vertex*& p)
{
	vertex* q;
	vertex* r;
	q = p -> right;
	r = q -> left;
	if (r -> bal > 0)
	{
		p -> bal = -1;	
	}
	else 
	{
		p -> bal = 0;
	}
	if (r -> bal < 0)
	{
		q -> bal = 1;	
	} 
	else 
	{
		q -> bal = 0;	
	}
	r -> bal = 0;
	p -> right = r -> left;
	q -> left = r -> right;
	r -> left = p;
	r -> right = q;
	p = r;	
}

void AVL(int d, vertex*& p)
{
	if(p == NULL)
	{
		p = new vertex;
		p -> data = d;
		p -> left = NULL;
		p -> right = NULL;
		p -> bal = 0;
		rost = true;
	}
	else if(p -> data > d)
	{
		AVL(d, p -> left);
		if(rost == true)
		{
			if(p -> bal > 0)
			{
				p -> bal = 0;
				rost = false;
			}
			else if(p -> bal == 0)
			{
				p -> bal = -1;
				rost = true;
			}
			else
			{
				if(p -> left -> bal < 0)
				{
					LL(p);
					rost = false;
				}
				else 
				{
					LR(p);
					rost = false;
				}
			}
		}
	}
	else if(p -> data < d)
	{
		AVL(d, p -> right);
		if(rost == true)
		{
			if(p -> bal < 0)
			{
				p -> bal = 0;
				rost = false;
			}
			else if(p -> bal == 0)
			{
				p -> bal = 1;
				rost = true;
			}
			else
			{
				if(p -> right -> bal > 0)
				{
					RR(p);
					rost = false;	
				}
				else 
				{
					RL(p);
					rost = false;
				}
			}
		}
	}
	else 
	{
		AVL(d, p -> right);
		if(rost == true)
		{
			if(p -> bal < 0)
			{
				p -> bal = 0;
				rost = false;
			}
			else if(p -> bal == 0)
			{
				p -> bal = 1;
				rost = true;
			}
			else
			{
				if(p -> right -> bal > 0)
				{
					RR(p);
					rost = false;	
				}
				else 
				{
					RL(p);
					rost = false;
				}
			}
		}
	}
}

bool VR = true;
bool HR = true;

void btree(int d, vertex*& p)
{
	vertex* q;
	if(p == NULL)
	{
		p = new vertex;
		p -> data = d;
		p -> left = NULL;
		p -> right = NULL;
		p -> bal = 0;
		VR = true;
	}
	else if(p -> data > d)
	{
		btree(d, p -> left);
		if(VR == true)
		{
			if(p -> bal == 0)
			{
				q = p -> left;
				p -> left = q -> right;
				q -> right = p;
				p = q;
				q -> bal = 1;
				VR = false;
				HR = true;
			}
			else 
			{
				p -> bal = 0;
				VR = true;
				HR = false;
			}
		}
		else
		{
			HR = false;
		}
	}
	else if(p -> data < d)
	{
		btree(d, p -> right);
		if(VR == true)
		{
			p -> bal = 1;
			VR = false;
			HR = true;	
		}
		else if(HR == true)
		{
			if(p -> bal == 1)
			{
				q = p -> right;
				p -> bal = 0;
				q -> bal = 0;
				p -> right = q -> left;
				q -> left = p;
				p = q;
				VR = true;
				HR = false;
			}
			else
			{
				HR = false;
			}
		}
	}
	else
	{
		btree(d, p -> right);
		if(VR == true)
		{
			p -> bal = 1;
			VR = false;
			HR = true;	
		}
		else if(HR == true)
		{
			if(p -> bal == 1)
			{
				q = p -> right;
				p -> bal = 0;
				q -> bal = 0;
				p -> right = q -> left;
				q -> left = p;
				p = q;
				VR = true;
				HR = false;
			}
			else
			{
				HR = false;
			}
		}
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
			gotoxy(x + 1, y - 2);
			cout << "/";
			gotoxy(x, y);	
		}
		else if(s == 1)
		{
			gotoxy(x - 1, y - 2);
			printf("%c", 92);
			gotoxy(x, y);
		}
		cout << p -> data;
		cout << "(" << p -> bal << ")";
		print(p -> left, x - pow(2, h), y += 3, -1, h - 1);
		print(p -> right, x + pow(2, h), y, 1, h - 1);
	}
}

void FillInc(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = i;
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand() % size;
		//Mas[i] = i;
}

void PrintMas(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	cout << Mas[i] << " ";
	cout << '\n';
}

int main()
{
	srand(time(NULL));

	int x;
	int size;
	int key;
	int Tsize, sum, height; 
	float MidHeight;
	bool tree;
	
	vertex* root = NULL;
	
	cout << "Количество вершин - ";
	cin >> size;
	
	int Mas[size];
	
	FillRand(Mas, size);

	for(int i = 0; i < size; i++)
	btree(Mas[i], root);
	
	cout <<"\nИсходные данные для ДБД - ";
	PrintMas(Mas, size);
	
	cout <<"\nДБД - Дерево-";
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
		
	Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	height = TreeHeight(root);
	cout <<"Высота дерева - " << height / 2 + 1 << endl;
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"Средняя высота дерева - " << MidHeight << endl;
	
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
	print(root, pow(2, height + 1), 10, 0, height);
	cout << endl << endl << endl << endl;
	_getch();
		
	cout << endl << endl;
	
	root = NULL;
	
	system("CLS");	
	cout <<"N = 100\tРазмер\tКонтр.Сумма\tВысота\tСредн.Высота" << endl;
	
	int Mas2[100];
	FillRand(Mas2, 100);
	for(int i = 0; i < 100; i++)
	AVL(Mas2[i], root);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	height = TreeHeight(root);
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	
	cout << "АВЛ" << "\t";
	cout << Tsize  << "\t";
	cout << sum << "\t\t"; 
	cout << height << "\t";
	cout << MidHeight;
	
	cout << endl;
	
	root = NULL;
	
	for(int i = 0; i < 100; i++)
	btree(Mas2[i], root);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	height = TreeHeight(root);
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	
	cout << "ДБД" << "\t";
	cout << Tsize << "\t";
	cout << sum << "\t\t";
	cout << height << "\t";
	cout << MidHeight;
			
	return 0;
}
