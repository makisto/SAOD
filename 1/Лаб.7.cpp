#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <math.h>
int C=0,V,Z;

using namespace std;

void ShellSort(int *a, int N){
	int m=log10(N)/log10(2)-1;
	int H[m];
	H[0]=1;
	int z=1;
	for(int i=1;i<m;i++)
	H[i]=2*H[i-1]+1;
int k=H[m-1];
while(k>0){
	z++;
	for(int i=0;i<(N-k);i++){
		int j=i;
		while(j>=0&&a[j]>a[j+k]){
			int t=a[j];
			a[j]=a[j+k];
			a[j+k]=t;
			j--;
		}
	}
	k=H[m-z];
}
}

void FillRand(int *a,int b){
int i;
for(i=0;i<b;i++)
a[i]=rand()%b;
}

void search1(int N, int ch, int *a){
	int L=0, R=N; bool s=false;
	while (L<=R){
		V=(L+R)/2;
		C+=2;
		if (a[V]==ch) {s=true;break;};
		if (a[V]<ch) L=V+1; else
		R=V-1;
	}
	if(s==false)V=-1;
}

void search2(int N, int ch, int *a){
	int L=0, R=N,m; bool s=false;
	while (L<R)
	{
		m=(L+R)/2;
		C++;
		if (a[m]<ch) L=m+1; else
		R=m;
	}
	C++;
	if (a[R]==ch) {s=true;Z=R;} else {s=false;Z=-1;}
}
void PrintMas(int *a, int n){
     for(int i=0;i<n;i++)
     cout<<a[i]<<" ";
     }
main(){
	srand(time(NULL));
	setlocale(LC_ALL,"Rus");
	int a[1010],n,x;
	cout<<"Количество элементов:";
	cin>>n;
	FillRand(a,n);
	ShellSort(a,n);
	PrintMas(a,n);
	cout<<"\n";
	cout << "Введите число, которое требуется найти \n";
	cin >> x;
	search1(n,x,a);
	if(V==-1)cout<<"Search 1:Элемента нет";else
	cout<<"Search 1:Элемент находится в ячейке "<<V;
	cout<<"\n";
	search2(n,x,a);
	if(Z==-1)cout<<"Search 2:Элемента нет";else
	cout<<"Search 2:Элемент находится в ячейке "<<Z;
	cout<<"\n";
	cout << "n\tI\tII\n";
    initwindow(640,480);
    moveto(0,480);
	for (int i=100;i<1001;i+=100){
	cout << i << "\t"; FillRand(a,i); ShellSort(a,i);search1(n,x,a); cout << C << "\t"; C=0; search2(n,x,a); cout << C << "\n"; C=0;
	}
	setcolor(GREEN);
	C=0;
	for (int i=100;i<1000;i+=20){
     FillRand(a,i); ShellSort(a,i);search1(n,20,a); lineto(i-100,C*(-1)+480);
	}
 moveto(0,480);
	setcolor(RED);
	C=0;
	for (int i=100;i<1000;i+=20){
     FillRand(a,i); ShellSort(a,i);search2(n,20,a); lineto(i-100,C*(-1)+480);
	}
	setcolor(GREEN);
	outtextxy(120, 120, "search1");
	setcolor(RED);
	outtextxy(120, 140, "search2");
getch();
}
