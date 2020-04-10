#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <math.h>
#include <graphics.h>

using namespace std;

struct spis
{
    spis *next;
    int x;
};

struct queue
{
	spis *head;
	spis *tail;
}c[2];

int M = 0, C = 0;

void QuickSort(int *a,int l, int n)
{
  int x=a[(l+n)/2];
  M++;
  int i=l;
  int j=n;
  while(i<=j){
  C++;
  while(a[i]<x){C++;i++;}
  C++;
  while(a[j]>x){C++;j--;}
  if(i<=j){
  	M+=3;
  	int temp = a[i];
  	a[i]=a[j];
  	a[j]=temp;
  	i++;
  	j--;
  } 
}
  if(l<j)
  QuickSort(a,l,j);
  if(i<n)
  QuickSort(a,i,n);
}
void HeapBuild(int *a, int l, int n)
{
  int x=a[l];
  int i=l;
  while(true){
  int j=2*i; 
  if(j>n)
  break;
  C++;
  if(j<n&&a[j+1]>=a[j])
  j++;
  C++;
    if (x>=a[j])
	break; 
	else
	M++;
    a[i]=a[j];
    i=j;
	}
	M++;
	a[i]=x;
}
void HeapSort(int *a, int n) 
{
  int l;
  if(n%2==0)l=n/2-1;
  else l=n/2+1;
  while(l>=0){
    HeapBuild(a,l,n);
    l--;
}
int R=n-1;
   while(R>0)
  {
  	M+=3;
    int temp=a[0];
    a[0]=a[R];
    a[R]=temp;
    R--;
    HeapBuild(a, 0, R);
  }
}
void FillInc(spis *&head,int n){
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
	cout<<"Контрольная сумма:"<<z<<endl;
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
	cout<<"Количество серий:"<<z<<endl;
}
void PrintSpis(spis *head){
	spis *temp=head;
	while(temp!=NULL){
		cout<<temp->x<<" ";
		temp=temp->next;
	}
}
void scrap(spis *s,spis *&a, spis *&b, int &n){
	spis *k;
	spis *p;
	a=s;
	b=s->next;
	n=1;
	k=a;
    p=b;
	while(p!=NULL){
		n=n+1;
		k->next=p->next;
		k=p;
		p=p->next;
	}
}  
void merge(spis *&a,spis *&b,int q,int r,int i,queue *c){
	while((q!=0)&&(r!=0)){
     C++;
     if(a->x<=b->x){
     M++;
     c[i].tail->next=a;
     c[i].tail=a;
     a=a->next;                     
     q--;                     
     }
     else{
     M++;
     c[i].tail->next=b;
     c[i].tail=b;
     b=b->next;            
     r--;
     }
}
     while(q>0){
     M++;
     c[i].tail->next=a;
     c[i].tail=a;
     a=a->next;                         
     q--;
    }
     while(r>0){
     M++;
     c[i].tail->next=b;
     c[i].tail=b;
     b=b->next;                                
     r--;         
    }
} 
void MergeSort(spis *&s,int n){
	 int q,r;
	 spis *a,*b;
     scrap(s,a,b,n);
     /*PrintSpis(a);cout<<"\n";
     PrintSpis(b);cout<<"\n";*/
     int p=1;
     while(p<n){
     c[0].tail=(spis *)&c[0].head;
     c[1].tail=(spis *)&c[1].head;         
     int i=0;
     int m=n;
     while(m>0){
     if(m>=p)q=p;else q=m; 
     m=m-q;
     if(m>=p)r=p; else r=m;
     m=m-r;           
	 merge(a,b,q,r,i,c);
     i=1-i; 
     }
     a=c[0].head;
     b=c[1].head;
     p=2*p;
}  
c[0].tail->next=NULL;
s=c[0].head;
}     
void FillRandM(int *a,int b)
{
for(int i=0;i<b;i++)
a[i]=rand()%b;
}
void FillDecM(int *a,int b)
{
for(int i=0;i<b;i++)
a[i]=b-i;
}
void FillIncM(int *a,int b)
{
for(int i=0;i<b;i++)
a[i]=i;
} 

void Clear(spis *&head){
	while(head!=NULL){
		spis *temp=head;
		head=temp->next;
		delete temp;
	}
}                            
int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int n;
	int A[10000];
	spis *s;
	cout<<"Количество элементов:";
	cin>>n;
	cout<<"Упорядоченный список:"<<endl;
	FillInc(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	MergeSort(s,n);
	cout<<"Перестановки:"<<M<<endl;
    cout<<"Сравнения:"<<C<<endl;
    cout<<"Трудоёмкость:"<<M+C<<endl; 
    M=0;C=0;
	cout<<"Отсортированный список:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"Обратно упорядоченный список:"<<endl;
	FillDec(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	MergeSort(s,n);
	cout<<"Перестановки:"<<M<<endl;
    cout<<"Сравнения:"<<C<<endl;
    cout<<"Трудоёмкость:"<<M+C<<endl;
    M=0;C=0;
    cout<<"Отсортированный список:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"Список случайных чисел:"<<endl;
	FillRand(s,n);
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	MergeSort(s,n);
	cout<<"Перестановки:"<<M<<endl;
    cout<<"Сравнения:"<<C<<endl;
    cout<<"Трудоёмкость:"<<M+C<<endl;
    cout<<"Отсортированный список:"<<endl;
	PrintSpis(s);cout<<"\n";
	CheckSum(s);
	RunNumber(s);
	cout<<"\n";
	cout<<"Теоретические сравнения:"<<(n*(log10(n)/log10(2)))<<endl;
    cout<<"Теоретические перестановки:"<<(n*(log10(n)/log10(2)))+n<<endl;
    cout<<"\n";
    M=0;C=0;
	cout << "n\tInc\tDec\tRand\n";
	for (int i=100;i<=500;i+=100){
	cout << i << "\t"; FillInc(s,i); MergeSort(s,n); cout << M+C << "\t"; M=0;C=0; 
	FillDec(s,i); MergeSort(s,n); cout << M+C << "\t"; M=0;C=0; 
	FillRand(s,i); MergeSort(s,n); cout << M+C << "\n"; M=0;C=0; 
	}
	M=0;C=0;
	
	initwindow(1024,768);	 
	moveto(0,768);
	setcolor(GREEN);
	outtextxy(120,120,"Heap");
	for(int i=0;i<20;i++){
	FillRandM(A, i*i*i);
	HeapSort(A, i*i*i);
	lineto(i*150-300,-1*(M+C)/10+733);
	M=0;C=0;
}
	M=0;C=0;
	moveto(0,768);
	setcolor(LIGHTMAGENTA);
	outtextxy(120,150,"Merge");
	for(int i=2;i<20;i++){
	FillRand(s, i*i*i);
	MergeSort(s,n);
	lineto(i*150-300,-1*(M+C)/10+733);
	Clear(s);
	M=0;C=0;
}
	M=0;C=0;
	moveto(0,768);
	setcolor(RED);
	outtextxy(120,180,"Quick");
	for(int i=0;i<20;i++){
	FillRandM(A, i*i*i);
	QuickSort(A, 0, i*i*i-1);
	lineto(i*150-300,-1*(M+C)/10+733);
	M=0;C=0;
}
    getch();
}
