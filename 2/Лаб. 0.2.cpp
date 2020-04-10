#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>

using namespace std;

struct vertex
{
	int data;
	vertex *left;
	vertex *right;
};

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

void PrintTree(vertex *p, int level) 
{
	if(p -> left)
	PrintTree(p -> left, level + 1);
    
	for(int i = 0; i < level + 1; i++)cout << "     |";
	cout << p -> data << endl; 
    
    if(p -> right)
	PrintTree(p -> right, level + 1);
}

vertex *BuildTree(int *A)
{
       int size = 0;
       vertex *p = new vertex;
       p -> data = A[size];
       p -> right = new vertex;
       p -> right -> data = A[size + 1];
       p -> right -> left = new vertex;
       p -> right -> right = new vertex;
       p -> right -> left -> data = A[size + 2];
       p -> right -> right -> data = A[size + 3];
       p -> right -> right -> left = new vertex;
       p -> right -> right -> left -> data = A[size + 4]; 
       p -> right -> right -> left -> left = new vertex;
       p -> right -> right -> left -> left -> data = A[size + 5];
       return p;
}
 
void FillInc(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = i + 1;
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand() % size;
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
	
	vertex *root = NULL;
	
	int size = 6;
	int Mas[size];
	
	cout <<"\nИсходные данные для дерева - ";
	FillRand(Mas, size);
	PrintMas(Mas, size);
	
	root = BuildTree(Mas);
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
	
	int Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	int sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	int height = TreeHeight(root);
	cout <<"Высота дерева - " << height << endl;
	float MidHeight = (TreeSizeSum(root, 1) / TreeSize(root));
	cout <<"Средняя высота дерева - " << MidHeight << endl;
	
	PrintTree(root, 0);
	
	getch();
}
