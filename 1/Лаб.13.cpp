#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <stdio.h>
#include <math.h>

using namespace std;

struct spis{
    spis *next;
    union{
    	int x;
    	unsigned char digit[sizeof(int)];
	};
};
struct queue{
	spis *head;
	spis *tail;
}q[256];
int M=0;
void FillInc(spis *head,int n){
    head=NULL;
    for (int i=n;i>0;i--){
	spis *temp=new spis;
	temp->x=i;
	temp->next=head;
	head=temp;
}
}
void FillDec(spis *&head,int n){
    head=NULL;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=i;
	temp->next=head;
	head=temp;
}
}
void FillRand(spis *&head,int n){
    head=NULL;
	for (int i=0;i<n;i++){
	spis *temp=new spis;
	temp->x=rand()%n;
	temp->next=head;
	head=temp;
}
}
void CheckSum(spis *head){
	int z=0;
	spis *temp=head;
	while(temp!=NULL){
		z+=temp->x;
		temp=temp->next;
	}
	cout<<"CheckSum:"<<z<<endl;
}
void RunNumber(spis *head){
	int z=1;
	spis *temp=head;
	spis *p=head->next;
		while(p!=NULL){
		if(temp->x>p->x)
		z++;
		temp=temp->next;
		p=p->next;
	}
	cout<<"RunNumber:"<<z<<endl;
}
void PrintSpis(spis *head){
	spis *temp=head;
	while(temp!=NULL){
		cout<<temp->x<<" ";
		temp=temp->next;
	}
}
void DigitalSort(spis *&s,int l){
	spis *p;
	unsigned char d,k,KDI[sizeof(int)];
	for(int j=0;j<l;j++){
            KDI[j]=j;
		for(int i=0;i<256;i++){
			M++;
		q[i].tail=(spis *)&q[i].head;
	}
		p=s;
		k=KDI[j];
		while(p!=NULL){
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
		}
		p=(spis *)&s;
		for(int i=0;i<256;i++){
			M++;
			if(q[i].tail!=(spis *)&q[i].head){
				p->next=q[i].head;
				p=q[i].tail;
			}
		}
		p->next=NULL;
	}
}
main(){
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int n,l;
	spis *s;
	cout<<"Elements:";
	cin>>n;
	cout<<"L:";
	cin>>l;
	cout<<"Incspis:"<<endl;
	FillInc(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	DigitalSort(s,l);
    cout<<"T:"<<M<<endl; 
    M=0;
	cout<<"Sortspis:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"Decspis:"<<endl;
	FillDec(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	DigitalSort(s,l);
    cout<<"T:"<<M<<endl;
    M=0;
    cout<<"Sortspis:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"Randspis:"<<endl;
	FillRand(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	DigitalSort(s,l);
    cout<<"T:"<<M<<endl;
    cout<<"Sortspis:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"\n";
	cout<<"Teor T:"<<l*(256+n)<<endl;
    cout<<"\n";
    cout<<sizeof(int);
    M=0;
    getch();
}
