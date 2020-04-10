#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <iostream>

using namespace std;

const int size = 4; 

struct abonent 
{
    char name[20];
    char surname[20];
    char fathername[20];
    char number[20];
};

void sortingname(int *Mas, abonent *index, int size)
{	
    for (int i = 0; i < size - 1; i++) 
	{
    	int min = i;
    	for(int j = i + 1; j < size; j++)
    	{
    		if(strcmp(index[Mas[j]].name, index[Mas[min]].name) < 0)
    		min = j;
		}
	int temp = Mas[i];      
	Mas[i] = Mas[min];
	Mas[min] = temp;
	}
}

void sortingnumber(int *Mas, abonent *index, int size)
{	
	int min;
    for (int i = 0; i < size - 1; i++) 
	{
    	min = i;
    	for(int j = i + 1; j < size; j++)
    	{
    		if(strcmp(index[Mas[j]].number, index[Mas[min]].number) < 0)
    		min = j;
		}
	int temp = Mas[i];      
	Mas[i] = Mas[min];
	Mas[min] = temp;
	}
}

void vyvod(abonent *index, int *Mas, int *Mas2)
{
	cout<<"\nИсходная книга:\n";
	for (int i = 0; i < size; i++) 
	{
        cout << index[i].name << "\t" << index[i].surname << "\t" << index[i].fathername << "\t" << index[i].number << endl;
    }
    
    cout << "\nОтсортированная книга по имени:\n";
    for (int i = 0; i < size; i++) 
	{
        cout << index[Mas[i]].name << "\t" << index[Mas[i]].surname << "\t" << index[Mas[i]].fathername << "\t" << index[Mas[i]].number << endl;
    }
    
    cout<<"\nОтсортированная книга по номеру:\n";
    for (int i = 0; i < size; i++) 
	{
        cout << index[Mas2[i]].name << "\t" << index[Mas2[i]].surname << "\t" << index[Mas2[i]].fathername << "\t" << index[Mas2[i]].number << endl;
	}
	
}

int main() 
{
	setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    
    abonent adressbook[size];
    int number[size];
    int name[size];
    
    for (int i = 0; i < size; i++) 
	{
        number[i]=i;
        name[i]=i;
        cout << "\nВведите данные абонента\n";
        
        cout << "Имя:";
		cin >> adressbook[i].name;
		
		cout << "Фамилия:";
		cin >> adressbook[i].surname;
		
		cout << "Отчество:";
		cin >> adressbook[i].fathername;
		
		cout << "Номер телефона:";
		cin >> adressbook[i].number;
    }
    
	sortingname(name, adressbook, size);
	sortingnumber(number, adressbook, size);
	vyvod(adressbook, name, number);
	
	return 0;
} 
