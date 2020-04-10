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

void DelSDP(int d, vertex*& root)
{
    vertex *r, *q, *s;
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
	if((*p) != NULL)
	{
            q = (*p);
            if(q -> left == NULL)(*p) = q -> right;
            else if(q -> right == NULL)(*p) = q -> left;
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
	
	int size;
	int key;
	int x;
	
	vertex* root = NULL;
	
	cout << "Количество вершин - ";
	cin >> size;
	int Mas[size];
	
	cout <<"\nИсходные данные для СДП - ";
	FillRand(Mas, size);
	PrintMas(Mas, size);
	
	for(int i = 0; i < size; i++)
	SDP(Mas[i], root);
	
	cout <<"\nОбход дерева слева направо - ";
	LeftObhod(root);
	cout <<"\nОбход дерева снизу вверх - ";
	UndRootObhod(root);
	cout <<"\nОбход дерева сверху вниз - ";
	RootObhod(root);
	
	for(int i = 0; i < 10; i++)
	{
		cout <<"\n\nКакую вершину вы хотите удалить? - ";
		cin >> x;
		system("CLS");
		DelSDP(x, root);
		cout <<"\nИсходные данные для СДП - ";
		PrintMas(Mas, size);
		cout <<"\nОбход дерева слева направо - ";
		LeftObhod(root);
		cout <<"\nОбход дерева снизу вверх - ";
		UndRootObhod(root);
		cout <<"\nОбход дерева сверху вниз - ";
		RootObhod(root);
		cout << root;
	}
	
	int Tsize = TreeSize(root);
	cout <<"\nРазмер дерева - " << Tsize << endl;
	int sum = TreeSum(root);
	cout <<"Контрольная сумма дерева - " << sum << endl;
	int height = TreeHeight(root);
	cout <<"Высота дерева - " << height << endl;
	float MidHeight = (float)TreeSizeSum(root, 1) / TreeSize(root);
	cout <<"Средняя высота дерева - " << MidHeight << endl;
		
	bool tree = Tree(root);
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
	
	/*cout <<"\nДерево:\n";
	PrintTree(root, 0);*/
	
	//getch();
	return 0;
}
