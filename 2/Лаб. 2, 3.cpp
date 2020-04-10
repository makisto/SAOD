#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <iomanip>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

struct vertex
{
	int data;
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
	vertex** p = &root;
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

void RecSDP(int d, vertex *&p)
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
	else
	{
		RecSDP(d, p -> right);	
	}
}

void DelSDP(int d, vertex*& root)
{
    vertex *r, *q, *s;
	vertex** p;
	p = &root;
	while((*p) != NULL)
	{
		if((*p) -> data < d)
		{
			p = &((*p) -> right);
		}
		else if((*p) -> data > d)
		{
			p = &((*p) -> left);
		}
		else 
		{
			break;
		}
	}
	if((*p) != NULL)
	{
        q = (*p);
        if(q -> left == NULL)
		{
			(*p) = q -> right;	
		}
        else if(q -> right == NULL)
		{
			(*p) = q -> left;	
		}
        else
        {
            r = q -> left;
            s = q;
			if(r -> right == NULL)
			{
				r -> right = q -> right;
				(*p) = r;
			}
			else
			{
				while(r -> right != NULL)
				{
					s = r;
					r = r -> right;
				}
            	s -> right = r -> left;
            	r -> left = q -> left;
           		r -> right = q -> right;
            	(*p) = r;
        	}
        }
    	delete(q);
	}
	else if((*p) == NULL)
	{
		cout << "Вы упустили шанс удалить вершину.Нажмите, чтобы продолжить";
		_getch();	
	}
}

void gotoxy(int x, int y)
{
	COORD place = {x, y};
	SetConsoleCursorPosition(console, place);
} 

void print(vertex* p, int x, int y, int a, char c)
{
char k = 'R';
if(p)
{
	if(a>0 && c != 'k')
	{
		if(c == '1')
		{
			x-= 20;
			k = '/';
		}
		else
		{
			x+=20;
			k = 92;
		}
	}
	else
	{
		if(c != 'k')
		{
			if(c == '1')
			{
				x-= 4;
				k = '/';
			}
			else
			{
				x+= 4;
				k = 92;
			}
		}
	}
	gotoxy(x, y++);
	a--;
	cout << setw(6) << k;
	gotoxy(x, y++);
	cout << setw(6) << p -> data;
	print(p -> left, x, y, a, '1');
	print(p -> right, x, y, a, 'r');
}
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
	srand(time(NULL));
	
	int x;
	int size;
	int vertex_del;
	int key;
	int Tsize, sum, height; 
	float MidHeight;
	bool tree;
	
	vertex* root = NULL;
	
	m:cout << "Количество вершин - ";
	cin >> size;
	
	cout << "\nСколько вершин вы хотите удалить?";
	cin >> vertex_del;
	
	if(size < vertex_del || size >= 500)
	{
		cout <<"Неверные данные.Нажмите, чтобы переделать";
		_getch();
		system("CLS");
		goto m;
	}
	
	int Mas[500];
	
	FillRand(Mas, size);

	for(int i = 0; i < size; i++)
	RecSDP(Mas[i], root);
	
	while(1)
	{
		system("CLS");
		cout << "Количество вершин - " << size;
		
		cout << "\nОсталось удалить вершин:" << vertex_del;
		
		cout <<"\nИсходные данные для СДП - ";
		PrintMas(Mas, size);
	
		cout <<"\nСДП - ";
	
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
		cout <<"Высота дерева - " << height << endl;
		MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
		cout <<"Средняя высота дерева - " << MidHeight << endl;

		if(root == NULL || vertex_del == 0)
		break;
		
		tree = Tree(root);
		if(tree == false)
		{
			cout <<"\nЭто не дерево поиска";
		}
		else
		{
			cout <<"\nЭто дерево поиска";
		}
		
		cout <<"\n\nКакую вершину вы хотите удалить? - ";
		cin >> x;
		DelSDP(x, root);
		vertex_del--;
	}	
	
	tree = Tree(root);
	if(tree == false)
	{
		cout <<"\nЭто не дерево поиска";
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
	print(root, 40, 10, 2, 'k');
	_getch();
	
	cout << endl << endl;
	
	system("CLS");	
	cout <<"N = 100\tРазмер\tКонтр.Сумма\tВысота\tСредн.Высота" << endl;
	
	FillRand(Mas, 100);
	root = ISDP(0, 99, Mas);
	
	Tsize = TreeSize(root);
	sum = TreeSum(root);
	height = TreeHeight(root);
	MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	
	cout << "ИСДП" << "\t";
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
	
	cout << "СДП" << "\t";
	cout << Tsize << "\t";
	cout << sum << "\t\t";
	cout << height << "\t";
	cout << MidHeight;
			
	return 0;
}
