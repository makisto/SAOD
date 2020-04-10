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

struct contributors
{
	char contributor_name[30];
	unsigned short int deposit;
	char date_of_deposit[10];
	char lawyer_name[22];
};

struct spis
{
    spis* next;
    contributors* data;
    int start_position;
};

struct SortQueue
{
	spis* head;
	spis* tail;
};

struct vertex
{
	vertex* left;
	vertex* right;
	contributors* data;
	int ves;
}*root, *search_root = NULL;

spis* ReadFile()
{ 	
	int f;
	spis *head, *p, *tail;

	f = open("testBase3.dat", O_RDONLY | O_BINARY);
	if(f == -1)
	{
		cout << "ОШИБКА: Не удалось открыть файл" << endl;
		system("PAUSE");
		exit(0);
    }
    
    tail = (spis *) & head;

    while (!eof(f))
	{
        p = new spis;
		if (p == NULL)
		{
			cout << "ОШИБКА: Не удалось выделить память под элемент списка" << endl;
			system("PAUSE");
		    exit(0);
        }
        p -> data = new contributors;
		if (p -> data == NULL)
		{
			cout << "ОШИБКА: Не удалось выделить память под данные" << endl;
			system("PAUSE");
			exit(0);
		}
		read(f, p -> data, sizeof(contributors));
		tail -> next = p;
    	tail = p;
	}
	close(f);
	return head;
}

void BaseHat()
{
	cout << "______________________________________________________________________________________________" << endl;
	cout << "Номер\t|" << "ФИО вкладчика\t\t\t|" << "Сумма вклада\t|" << "Дата вклада\t\t|" << "ФИО адвоката |" << endl;
	cout << "______________________________________________________________________________________________" << endl;
}

void ShowBase(contributors** contributors_mas)
{
	int base_size, base_index, base_end;
    char key;
	system("CLS");
	cout << "Введите размерность базы(1 - 4000):" << endl;
	cin >> base_size;
	try
	{
		if(base_size <= 0 || base_size > 4000)
		{
			cout << "Неверные данные." << endl;
			system("PAUSE");
			system("CLS");
			throw 20;
		}
	}
	catch(int i)
	{
		base_size = i;	
	}
    base_index = 0;
    base_end = base_size;
   	while(key != 27) 
	{
		system("CLS");
		BaseHat();
        for (int i = base_size * base_index; i < base_end; i++)
		{
            cout << i + 1 << "\t|";
            cout << contributors_mas[i] -> contributor_name << "\t|";
            cout << contributors_mas[i] -> deposit << "\t\t|";
            cout << contributors_mas[i] -> date_of_deposit << "\t\t|";
            cout << contributors_mas[i] -> lawyer_name << endl;
            cout << "______________________________________________________________________________________________|" << endl;
     	}
     	cout << endl << "Выход из базы данных - ESC" << endl;
     	cout << "Идти ниже по базе - стрелка вниз" << endl;
     	cout << "Идти выше по базе - стрелка вверх" << endl;
       	key = _getch();
        switch(key)
        {
        	case 80:
        		if(base_end == base_fields)
				{
					cout << "Вы достигли дна. Дальше только наверх" << endl;
					_getch();
					break;
				}
				if(base_end + base_size > base_fields)
				{	
					base_index++;
					base_end = base_end + (base_fields - base_end);
        			break;
				}
				else
				{
					base_index++;
        			base_end += base_size;
        			break;
				}
        		break;
			case 72:
				if(base_end == base_size)
				{
					cout << "Вы достигли потолка. Дальше только вниз" << endl;
					_getch();
					break;
				}
				if(base_size * (base_index - 1) < base_end - base_size)
				{	
					base_end = base_size;
					base_index--;
					system("cls");
					break;
				}
				else
				{
					base_index--; 
					base_end -= base_size;
					break;	
				}
			default:
				break;
		}
	}
}

void FillMas(int* index_mas, contributors** contributors_mas, spis* head)
{
	for(int i = 0; i < base_fields; i++)
	{
		index_mas[i] = i;	
	}
	
	spis* p;
	int i;
	for(p = head, i = 0; p != NULL; p = p -> next, i++)
	{	
		contributors_mas[i] = p -> data;
	}
}

int Less(spis* x, spis* y)
{
	if(strncmp(x -> data -> contributor_name, y -> data -> contributor_name, 30) < 0)
	{
		return 1;
	}
	else if(strncmp(x -> data -> contributor_name, y -> data -> contributor_name, 30) > 0) 
	{
		return 0;
	}
	else if(strncmp(x -> data -> contributor_name, y -> data -> contributor_name, 30) == 0)
	{
		if(x -> data -> deposit < y -> data -> deposit)
		{
			return 1;
		}
		else if(x -> data -> deposit > y -> data -> deposit)
		{
			return 0;
		}
	}
}

int scrap(spis*& s, spis*& a, spis*& b)
{
	spis *k;
	spis *p;
	int n;
	a = s;
	b = s -> next;
	n = 1;
	k = a;
    p = b;
	while(p != NULL)
	{
		n++;
		k -> next = p -> next;
		k = p;
		p = p -> next;
	}
	return n;
}  

void merge(spis*& a, spis*& b, SortQueue& c, int q, int r)
{
	while((q != 0) && (r != 0))
	{
	    if(Less(a, b) == 1)
		{
		    c.tail -> next = a;
		    c.tail = a;
		    a = a -> next;                     
		    q--;                     
	    }
     	else
		{
		    c.tail -> next = b;
		    c.tail = b;
		    b = b -> next;            
		    r--;
     	}
	}
    while(q > 0)
	{
	    c.tail -> next = a;
	    c.tail = a;
	    a = a -> next;                         
	    q--;
    }
    while(r > 0)
	{
	    c.tail -> next = b;
	    c.tail = b;
	    b = b -> next;                                
	    r--;         
    }
} 

spis* MergeSort(spis* s)
{
	int q, r;
	spis *a, *b;
	SortQueue c[2];
	int n = scrap(s, a, b);
    int p = 1;
    int i, m;
    while(p < n)
	{
	    c[0].tail = (spis *) & c[0].head;
	    c[1].tail = (spis *) & c[1].head;         
	    i = 0;
	    m = n;
	    while(m > 0)
		{
			if(m >= p)
			{
				q = p;
			}
			else 
			{
				q = m;
			}
		    m -= q;
		    if(m >= p)
			{
		    	r = p;	
			}
			else
			{
				r = m;	
			}
		    m = m - r;           
			merge(a, b, c[i], q, r);
		    i = 1 - i; 
	    }
	    a = c[0].head;
	    b = c[1].head;
	    p = 2 * p;
	}  
	c[0].tail -> next = NULL;
	s = c[0].head;
	return s;
}

spis* BinSearch(contributors** contributors_mas, int* index_mas, char* search_key)
{
	int mid_mas;
	int left_mas = 0;
	int right_mas = base_fields - 1;
	char buf_search_key[3];

	spis* head;
	spis* tail;
	
	while(left_mas < right_mas)
	{
		mid_mas = (left_mas + right_mas) / 2;
		for(int i = 0; i < 3; i++) 
		{
			buf_search_key[i] = contributors_mas[index_mas[mid_mas]] -> contributor_name[i];		
		}
		if (strncmp(search_key, buf_search_key, 3) > 0)
		{
			left_mas = mid_mas + 1;
		} 
		else
		{
			right_mas = mid_mas;	
		}
	}
	
	for(int i = 0; i < 3; i++) 
	{
		buf_search_key[i] = contributors_mas[index_mas[left_mas]] -> contributor_name[i];	
	}	
	if(strncmp(search_key, buf_search_key, 3) == 0)
	{
		tail = (spis* ) & head;	
	}
	else
	{
		return NULL;
	}
	
	while(strncmp(search_key, buf_search_key, 3) == 0)
	{	
		spis* p = new spis;	
		if (p == NULL)
		{
			cout << "ОШИБКА: Не удалось выделить память под элемент очереди" << endl;
			system("PAUSE");
			exit(0);
		}
		p -> data = new contributors;
		if (p -> data == NULL)
		{
			cout << "ОШИБКА: Не удалось выделить память под данные" << endl;
			system("PAUSE");
			exit(0);
		}
		p -> data = contributors_mas[index_mas[left_mas]];
		p -> start_position = index_mas[left_mas];
		tail -> next = p;	
		tail = p;       
		left_mas++;
		if(left_mas == base_fields)
		{
			break;
		}
		for(int i = 0; i < 3; i++) 
		{
			buf_search_key[i] = contributors_mas[index_mas[left_mas]] -> contributor_name[i];	
		}
	}	
	return head;
}

int ShowQueue(spis* queue)
{
	spis* temp;
	int i;
	if(queue == NULL)
    {
        cout << "Данные не обнаружены" << endl;
        system("PAUSE");
	}
	else
	{
		BaseHat();
		for(temp = queue, i = 0; temp != NULL; i++, temp = temp -> next)
		{
		    cout << i + 1 << "\t|";
			cout << temp -> data -> contributor_name << "\t|";
			cout << temp -> data -> deposit << "\t\t|";
			cout << temp -> data -> date_of_deposit << "\t\t|";
			cout << temp -> data -> lawyer_name << endl; 
			cout << "______________________________________________________________________________________________|" << endl;
		}
		cout << "Количество найденных элементов:" << i << endl;
		system("PAUSE");
	}
	return i;
}

void SDP(char* s, contributors** contributors_mas, int c, vertex*& p, int* index_mas, int i)
{
	if(p == NULL)
	{
		p = new vertex;
		p -> data = new contributors;
		p -> data = contributors_mas[index_mas[i]];
		p -> left = NULL;
		p -> right = NULL;
		p -> ves = c;
	}
	else if(strncmp(s, p -> data -> date_of_deposit, strlen(p -> data -> date_of_deposit)) < 0)
	{
		SDP(s, contributors_mas, c, p -> left, index_mas, i);
	}
	else if(strncmp(s, p -> data -> date_of_deposit, strlen(p -> data -> date_of_deposit)) > 0)
	{
		SDP(s, contributors_mas, c, p -> right, index_mas, i);
	}
	else if(strncmp(s, p -> data -> date_of_deposit, strlen(p -> data -> date_of_deposit)) == 0)
	{
		SDP(s, contributors_mas, c, p -> right, index_mas, i);
	}
}

void A2(int l, int r, int* ves, contributors** contributors_mas, int* index_mas)
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
		SDP(contributors_mas[index_mas[i]] -> date_of_deposit, contributors_mas, ves[i], root, index_mas, i);
		A2(l, i - 1, ves, contributors_mas, index_mas);
		A2(i + 1, r, ves, contributors_mas, index_mas);
	}
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand() % 100;
}

int o = 1;
void LeftObhod(vertex *p)
{
	if(p != NULL) 
	{
		LeftObhod(p -> left);
		cout << o++ << "\t|";
		cout << p -> data -> contributor_name << "\t|";
        cout << p -> data -> deposit << "\t\t|";
        cout << p -> data -> date_of_deposit << "\t\t|";
        cout << p -> data -> lawyer_name << endl;
        cout << "______________________________________________________________________________________________|" << endl;
		LeftObhod(p -> right);
	}
}

vertex* TreeSearch(vertex *p, char* search_key)
{
	while(p != NULL)
	{
		if(strncmp(search_key, p -> data -> date_of_deposit, 8) < 0)
		{
			p = p -> left;
		}
		if(strncmp(search_key, p -> data -> date_of_deposit, 8) > 0)
		{
			p = p -> right;
		}
		else
		{
			return p;
		}
	}
	return NULL;
}

void search(vertex *p, char* search_key)
{
	if (p != NULL)
	{
		search(p -> left, search_key);
		if(strncmp(search_key, p -> data -> date_of_deposit, 8) == 0)
		{
			cout << o++ << "\t|";
			cout << p -> data -> contributor_name << "\t|";
	        cout << p -> data -> deposit << "\t\t|";
	        cout << p -> data -> date_of_deposit << "\t\t|";
	        cout << p -> data -> lawyer_name << endl;
	        cout << "______________________________________________________________________________________________|" << endl;
		}
		search(p -> right, search_key);
	}
}

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
    FILE *fin = fopen("testBase3.dat", "rb5+");
    while (!feof(fin))
	{
		int j = fgetc(fin);
		P[j]++;
		count++;
    }
    count--;
    fclose(fin);
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
			cout << cou++ << "\t" << a[i] << "\t" << P[i] << "\t           "  << codewords[i].length() << "\t" << codewords[i] << endl;	
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
	int index_mas[base_fields];
	int i;
	char ch, bh;
	char bin_search_key[3];
	char tree_search_key[8];
	bool flag = true;
	bool isflag = true;
	int queue_fields;
	int ves_mas[base_fields];
	FillRand(ves_mas, base_fields);
	
	spis* head;
	spis* queue;
	spis* p;
	
	contributors* contributors_mas[base_fields];
	
	head = ReadFile();
	FillMas(index_mas, contributors_mas, head);
	
	while(1)
	{
		system("CLS");
		cout << "1.Формат отображения данных" << endl;
		cout << "2.Вывод базы данных" << endl;
		cout << "3.Поиск" << endl;
		cout << "4.Дерево" << endl;
		cout << "5.Кодирование" << endl;
		cout << "6.Выход" << endl;
		ch = _getch();
		switch(ch)
		{
			case '1':
				system("CLS");
				cout << "1.Исходный" << endl;
				cout << "2.Отсортированный" << endl;
				bh = _getch();
				switch(bh)
				{
					case '1':
						system("CLS");
						if(!flag)
						{
							head = ReadFile();
							for(p = head, i = 0; p != NULL; p = p -> next, i++)
							{	
								contributors_mas[i] = p -> data;
							}	
							flag = true;
						}
						else if(flag)
						{
							cout << "База уже в исходном виде" << endl;
							system("PAUSE");	
						}
						break;
					case '2':
						system("CLS");
						if(flag)
						{
							head = MergeSort(head);
							for(p = head, i = 0; p != NULL; p = p -> next, i++)
							{	
								contributors_mas[i] = p -> data;
							}
							flag = false;
						}
						else if(!flag)
						{
							cout << "База уже отсортирована" << endl;
							system("PAUSE");		
						}
						break;
					default:
						break;
				}
				break;
			case '2':
            	ShowBase(contributors_mas);
            	break;
			case '3':
				system("CLS");
				if(flag)
				{
					cout << "Сначала отсортируйте базу!" << endl;
					system("PAUSE");
					break;
				}
                cout << "Введите первые три буквы фамилии (формат Абв)" << endl;
                cin >> bin_search_key;
                system("CLS");
                queue = BinSearch(contributors_mas, index_mas, bin_search_key);
                queue_fields = ShowQueue(queue);
                break;
			case '4':
				system("CLS");
				if(flag || queue == NULL)
				{
					cout << "Невозможно создать дерево" << endl;
				}
				else
				{
					int last_position = queue -> start_position + queue_fields;
					A2(queue -> start_position, last_position - 1, ves_mas, contributors_mas, index_mas);
					BaseHat();
					LeftObhod(root);
					o = 1;
					system("PAUSE");
				}
				if(root != NULL)
				{
					system("CLS");
					cout << "Введите дату вложения (формат ДД-ММ-ГГ)" << endl;
                	cin >> tree_search_key;
                	system("CLS");
                	search_root = TreeSearch(root, tree_search_key);
                	if(search_root == NULL)
                	{
                		cout << "Данные не обнаружены" << endl;
					}
					else
					{
						BaseHat();
	                	search(search_root, tree_search_key);
	                	o = 1;
	            	}
				}
				search_root = NULL;
				root = NULL;
				system("PAUSE");
				break;
			case '5':
				if(isflag)
				{
					probabilities();
					shennon();
					isflag = false;
				}
				system("CLS");
				parametrs();
				system("PAUSE");
				break;
			case '6':
				exit(0);
			default:
				break;
		}
	}
	
	return 0;
}
