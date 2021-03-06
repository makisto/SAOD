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
		p -> left = p -> right = NULL;
		p -> data = Mas[size];
		p -> left = ISDP(left, size - 1, Mas);
		p -> right = ISDP(size + 1, right, Mas);
		return p;
	}
}

void SDP(int d, vertex*& root)
{
	vertex** p;
	p = &root;
	while((*p) != NULL)
	{
		if(d < (*p) -> data)
		{
			p = &((*p) -> left);
		}
		else if(d > (*p) -> data)
		{
			p = &((*p) -> right);
		}
		else 
		{
			break;
		}
	}
	if((*p) == NULL)
	{
		(*p) = new vertex;
		(*p) -> data = d;
		(*p) -> right = NULL;
		(*p) -> left = NULL;
	}
}

void RecSDP(int d, vertex*& p)
{
	if(p == NULL)
	{
		p = new vertex;
		p -> data = d;
		p -> left = NULL;
		p -> right = NULL;
	}
	else if(d < p -> data)
	{
		RecSDP(d, p -> left);
	}
	else if(d > p -> data)
	{
		RecSDP(d, p -> right);
	}
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand() % (size * 15) + 1;
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
	
	int size;
	int key;
	
	vertex* root = NULL;
	
	cout << "���������� ������ - ";
	cin >> size;
	int Mas[500];
	
	cout <<"\n�������� ������ ��� ��� - ";
	FillRand(Mas, size);
	PrintMas(Mas, size);
	
	cout <<"\n��� � ������� ������������ - ";
	for(int i = 0; i < size; i++)
	SDP(Mas[i], root);
	
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
	
	root = NULL;
	
	cout <<"\n��� � �������������� - ";
	for(int i = 0; i < size; i++)
	RecSDP(Mas[i], root);
	
	cout <<"\n����� ������ ����� ������� - ";
	LeftObhod(root);
	cout <<"\n����� ������ ����� ����� - ";
	UndRootObhod(root);
	cout <<"\n����� ������ ������ ���� - ";
	RootObhod(root);
	
	Tsize = TreeSize(root);
	cout <<"\n������ ������ - " << Tsize << endl;
	sum = TreeSum(root);
	cout <<"����������� ����� ������ - " << sum << endl;
	height = TreeHeight(root);
	cout <<"������ ������ - " << height << endl;
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
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
	
	cout << endl << endl;
	
	root = NULL;
		
	cout <<"N = 100\t������\t�����.�����\t������\t�����.������" << endl;
	
	FillRand(Mas, 100);
	root = ISDP(0, 99, Mas);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	height = TreeHeight(root);
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	
	cout << "����" << "\t";
	cout << Tsize  << "\t";
	cout << sum << "\t\t"; 
	cout << height << "\t";
	cout << MidHeight;
	
	cout << endl;
	
	root = NULL;
	
	FillRand(Mas, 100);
	for(int i = 0; i < 100; i++)
	SDP(Mas[i], root);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	height = TreeHeight(root);
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	
	cout << "���" << "\t";
	cout << Tsize << "\t";
	cout << sum << "\t\t";
	cout << height << "\t";
	cout << MidHeight;
	
	cout <<"\n������:\n";
	PrintTree(root, 0);
	
	//getch();
	return 0;
}
