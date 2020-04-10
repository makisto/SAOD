#include <iostream>
#include <conio.h>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

using namespace std;

int C=0,M=0;
void HeapBuild(int *a, int l, int n)
{
  int x=a[l];
  int i=l;
  while(true){
  int j=2*i; 
  if(j>n)
  break;
  C++;
  if(j<n&&a[j+1]<=a[j])
  j++;
  C++;
    if (x<=a[j])
	break; 
	M++;
    a[i]=a[j];
    i=j;
	}
	M++;
	a[i]=x;
}
void HeapSort(int *a, int n) 
{
  int l=n/2;
  while(l>=0){
    HeapBuild(a,l,n);
    l--;
}
int R=n;
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
void ShellSort(int mass[], int n, int &M, int &C)
{
    int i, j, k;
    int tmp;
    for (k = n / 2; k > 0; k /= 2)
        for (i = k; i < n; i++)
        {
            M++;
			tmp = mass[i];
            for (j = i; j >= k; j -= k)
            {
                C++;
				if (tmp < mass[j - k]) {
					M++;
                    mass[j] = mass[j - k];
                }
                else
                    break;
            }
            M++;
            mass[j] = tmp;
        }
}
int RunNumber(int *a,int b)
{
int i,flag=0;
for (i=0;i<b;i++)
{
if(a[i]>a[i+1])
flag++;
}
cout<<"Количество серий:"<<flag<<endl;
}
int CheckSum(int *a,int b)
{
int s=0,i;
for(i=0;i<b;i++)
s+=a[i];
cout<<"Контрольная сумма:"<<s<<endl;
}
void FillRand(int *a,int b)
{
int i;
for(i=0;i<b;i++)
a[i]=rand()%b;
}
void FillDec(int *a,int b)
{
int i;
for(i=0;i<b;i++)
a[i]=b-i;
}
void FillInc(int *a,int b)
{
int i;
for(i=0;i<b;i++)
a[i]=i;
}
void PrintMas(int *a,int b)
{
int i;
for(i=0;i<b;i++)
cout<<" "<<a[i];
cout<<endl;
}
main(){
srand(time(NULL));
setlocale(LC_ALL,"Rus");
int n;
cout<<"Количество элементов:"; 
cin>>n;
int A[500];
cout<<"Исходный массив случайных чисел:";
cout<<endl;
FillRand(A,n);
PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
HeapSort(A,n);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив случайных чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
PrintMas(A,n);
cout<<endl;
M=0;C=0;
cout<<"Исходный массив убывающих чисел:";
cout<<endl;
FillDec(A,n);
PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
HeapSort(A,n);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив убывающих чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
PrintMas(A,n);
cout<<endl;
M=0;C=0;
cout<<"Исходный массив возрастающих чисел:";
cout<<endl;
FillInc(A,n);
PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
HeapSort(A,n);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив возрастающих чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
PrintMas(A,n);
cout<<endl;
cout<<"Теоретические сравнения:"<<2*n*(log10(n)/log10(2))+n+2<<endl;
cout<<"Теоретические перестановки:"<<n*(log10(n)/log10(2))+6.5*n-4<<endl;
cout<<"\n";
M=0;C=0;
cout << "n\tInc\tDec\tRand\n";
	for (int i=100;i<=500;i+=100){
	cout << i << "\t"; FillInc(A,i); HeapSort(A,i); cout << M+C << "\t"; M=0;C=0; 
	FillDec(A,i); HeapSort(A,i); cout << M+C << "\t"; M=0;C=0; 
	FillRand(A,i); HeapSort(A,i); cout << M+C << "\n"; M=0;C=0; 
	}
	M=0;C=0;
	/*initwindow(640,480);	
	moveto(0,480);
	setcolor(GREEN);
	outtextxy(120,120,"Heap");
	FillRand(A, n);
	HeapSort(A, n);
	lineto(n*50,M+C);
	M=0;C=0;
	moveto(0,480);
	setcolor(LIGHTMAGENTA);
	outtextxy(120,150,"Shell");
	FillRand(A, n);
	ShellSort(A, n, M, C);
	lineto(n*50,M+C);*/
getch();
}
