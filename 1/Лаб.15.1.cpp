#include <iostream>
#include <string.h>
#include <conio.h>
#include <locale.h>

using namespace std;

int C = 0;

void Search(char *t, char *s){
	cout<<"Строка:"<<t<<"\n";
	cout<<"Подстрока:"<<s<<"\n";
	int n = strlen(t);
	int m = strlen(s);
	int j;
	int i = -1, k = 0, Q = 0;
	do
	{
		i++;
		j = 0;
		Q++;
		while((j < m) && (t[i+j] == s[j])) { 
		Q++; 
		j++; 
		if(j == m)
		{
		cout<<"Индекс вхождения:"<<i + 1<<"\n";
		Q--;
		k++;
		}
		}
	}
	while(i < n - m);
	if(k == 0)cout<<"В строке нет подстроки\n";
	else cout<<"Количество подстрок в строке:"<<k<<"\n";
	cout<<"Сравнения:"<<Q<<"\n";
}

int RabinKarp(char *t, char *s)//крутая функция
{
	cout<<"Строка:"<<t<<"\n";
	cout<<"Подстрока:"<<s<<"\n";
	int n = strlen(t);
    int m = strlen(s);
    int j;
    int Hs = 0, Ht = 0, k = 0, h = 1, d = 256;
	
    for (int i = 0; i < m-1; i++)
        h = (h * d) % 5;

    for (int i = 0; i < m; i++)
    {
        Hs = (d * Hs + s[i]) % 5;
        Ht = (d * Ht + t[i]) % 5;
    }
 
    for (int i = 0; i <= n - m; i++)
    {
		C++;
        if ( Hs == Ht )
        {
            for (j = 0; j < m; j++)
            {	
                if (t[i + j] != s[j])
                break;
            }
            if (j == m)
            {
            cout<<"Индекс вхождения:"<<i + 1<<"\n";
            k++;
        	}
        }
        if ( i < n-m )
        {
            Ht = (d * (Ht - t[i] * h) + t[i + m]) % 5;
            if (Ht < 0)
            Ht = (Ht + 5);
        }
    }
    if(k == 0)cout<<"В строке нет подстроки\n";
	else cout<<"Количество подстрок в строке:"<<k<<"\n";
	cout<<"Сравнения:"<<C<<"\n";
}
  
main(){
	//setlocale(LC_ALL, "rus");
	char t[600], s[600];
	cout<<"Введите строку:";gets(t);
	cout<<"Введите подстроку:";gets(s);
	cout<<"\nПрямой поиск:\n";
	Search(t, s);
	cout<<"\nМетод Рабина-Карпа:\n";
	RabinKarp(t, s);
	cout<<"\n";
	C = 0;
	char k[] = {"digital"};
	char y[] = {"d"};
	RabinKarp(k, y);
	C = 0;
	char a[] = {"di"};
	RabinKarp(k, a);
    C = 0;
	char b[] = {"dig"};
	RabinKarp(k, b);
	C = 0;
	char c[] = {"digi"};
	RabinKarp(k, c);
	C = 0;
	char d[] = {"digit"};
	RabinKarp(k, d);
	C = 0;
	char e[] = {"digita"};
	RabinKarp(k, e);
	C = 0;
	char f[] = {"digital"};
	RabinKarp(k, f);
	C = 0;
	getch();
}
