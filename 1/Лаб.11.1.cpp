#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>

using namespace std;

struct spis{
    spis *next;
    int x;
}*head,*tail;
void FillInc(spis *steck,int n){
	tail=(spis *)&head;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=i;
    tail->next=temp;
    tail=temp;
	}
}
void FillDec(spis *steck,int n){
    tail=(spis *)&head;
	for (int i=n;i>0;i--){
	spis *temp=new spis;
	temp->x=i;
	tail->next=temp;
    tail=temp;
}
}
void FillRand(spis *steck,int n){
    tail=(spis *)&head;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=rand()%n;
	tail->next=temp;
    tail=temp;;
}
}
void PrintSpis(spis *steck){
	spis *temp=head;
	while(temp!=NULL){
		cout<<temp->x<<" ";
		temp=temp->next;
	}
}
void CheckSum(spis *steck){
	int z=0;
	spis *temp=head;
	while(temp!=NULL){
		z+=temp->x;
		temp=temp->next;
	}
	cout<<z;
}
void RunNumber(spis *steck){
	int z=1;
	spis *temp=head;
	spis *p=head->next;
		while(p!=NULL){
		if(temp->x>p->x)
		z++;
		temp=temp->next;
		p=p->next;
	}
	cout<<z;
}
void Clear(spis *steck){
	while(head!=NULL){
		spis *temp=head->next;
		delete head;
		head=temp;
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int n;
	cout<<"Количество элементов:";
	cin>>n;
    spis *steck;
    FillInc(steck,n); 
    cout<<"Список возрастающих чисел:"<<"\n";PrintSpis(steck);cout<<"\n"; 
    cout<<"Контрольная сумма:";CheckSum(steck);cout<<"\n";
    cout<<"Количество серий:";RunNumber(steck);cout<<"\n";
    FillDec(steck,n); 
    cout<<"Список убывающих чисел:"<<"\n";;PrintSpis(steck);cout<<"\n";
    cout<<"Контрольная сумма:";CheckSum(steck);cout<<"\n";
    cout<<"Количество серий:";RunNumber(steck);cout<<"\n";
    Clear(steck);
    FillRand(steck,n); 
    cout<<"Список случайных чисел:"<<"\n";;PrintSpis(steck);cout<<"\n"; 
    cout<<"Контрольная сумма:";CheckSum(steck);cout<<"\n";
    cout<<"Количество серий:";RunNumber(steck);cout<<"\n";
    Clear(steck);
    getch();
}
