#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>

using namespace std;

struct spis{
    spis *next;
	int x;
}*head;

void FillInc(int n){
	head=NULL;
    for (int i=n;i>0;i--){
	spis *temp=new spis;
	temp->x=i;
	temp->next=head;
	head=temp;
}
}
void FillDec(int n){
    head=NULL;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=i;
	temp->next=head;
	head=temp;
}
}
void FillRand(int n){
    head=NULL;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=rand()%n;
	temp->next=head;
	head=temp;
}
}
void CheckSum(){
	int z=0;
	spis *temp=head;
	while(temp!=NULL){
		z+=temp->x;
		temp=temp->next;
	}
	cout<<z;
}
void RunNumber(){
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
void PrintSpis(){
	spis *temp=head;
	while(temp!=NULL){
		cout<<temp->x<<" ";
		temp=temp->next;
	}
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
	FillInc(n); 
    cout<<"Список возрастающих чисел:"<<"\n";PrintSpis();cout<<"\n"; 
    cout<<"Контрольная сумма:";CheckSum();cout<<"\n";
    cout<<"Количество серий:";RunNumber();cout<<"\n";
    FillDec(n); 
    cout<<"Список убывающих чисел:"<<"\n";;PrintSpis();cout<<"\n";
    cout<<"Контрольная сумма:";CheckSum();cout<<"\n";
    cout<<"Количество серий:";RunNumber();cout<<"\n";
    FillRand(n); 
    cout<<"Список случайных чисел:"<<"\n";;PrintSpis();cout<<"\n"; 
    cout<<"Контрольная сумма:";CheckSum();cout<<"\n";
    cout<<"Количество серий:";RunNumber();cout<<"\n";
    getch();
}
