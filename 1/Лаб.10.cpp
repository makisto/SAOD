#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <graphics.h>

using namespace std;

int C=0,M=0;
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
void FillInc(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = i;
}

void FillDec(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = size - i;
}

void FillRand(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	Mas[i] = rand()%size;
}

int CheckSum(int *Mas, int size)
{
	int sum = 0;
	for(int i = 0; i < size; i++)
	sum += Mas[i];
	cout << "Контрольная сумма - " << sum << '\n';
}

int RunNumber(int *Mas, int size)
{
	int flag = 1;
	for (int i = 0; i < size; i++)
	{
		if(Mas[i] > Mas[i + 1])
		flag++;
	}
	cout << "Количество серий - " << flag << '\n';
}

void PrintMas(int *Mas, int size)
{
	for(int i = 0; i < size; i++)
	cout << Mas[i] << " ";
	cout << '\n';
}

main(){
srand(time(NULL));
setlocale(LC_ALL,"Rus");
int n;
cout<<"Количество элементов:"; 
cin>>n;
int A[1000];
cout<<"Исходный массив случайных чисел:";
cout<<endl;
FillRand(A,n);
//PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
QuickSort(A,0,n-1);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив случайных чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
//PrintMas(A,n);
cout<<endl;
M=0;C=0;
cout<<"Исходный массив убывающих чисел:";
cout<<endl;
FillDec(A,n);
//PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
QuickSort(A,0,n-1);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив убывающих чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
//PrintMas(A,n);
cout<<endl;
M=0;C=0;
cout<<"Исходный массив возрастающих чисел:";
cout<<endl;
FillInc(A,n);
//PrintMas(A,n);
CheckSum(A,n);
RunNumber(A,n);
QuickSort(A,0,n-1);
cout<<"Перестановки:"<<M<<endl;
cout<<"Сравнения:"<<C<<endl;
cout<<"Трудоёмкость:"<<M+C<<endl;
cout<<"Отсортированный массив возрастающих чисел:";
cout<<endl;
CheckSum(A,n);
RunNumber(A,n);
//PrintMas(A,n);
cout<<endl;
cout<<"Теоретические сравнения:"<<(n*n+5*n-4)/2<<endl;
cout<<"Теоретические перестановки:"<<3*(n-1)<<endl;
cout<<"\n";
M=0;C=0;
cout << "n\tInc\tDec\tRand\n";
	for (int i=100;i<=500;i+=100){
	cout << i << "\t"; FillInc(A,i); QuickSort(A,0,i-1); cout << M+C << "\t"; M=0;C=0; 
	FillDec(A,i); QuickSort(A,0,i-1); cout << M+C << "\t"; M=0;C=0; 
	FillRand(A,i); QuickSort(A,0,i-1); cout << M+C << "\n"; M=0;C=0; 
	}
	M=0;C=0;
	initwindow(640,480);	 
	moveto(0,480);
	setcolor(GREEN);
	FillRand(A, 1000);
	outtextxy(120,120,"Heap");
	for(int i=0;i<1000;i++){
	HeapSort(A, i);
	lineto(A[i]*25,M+C);
}
	M=0;C=0;
	moveto(0,480);
	setcolor(LIGHTMAGENTA);
	FillRand(A, 1000);
	outtextxy(120,150,"Shell");
	for(int i=0;i<1000;i++){
	ShellSort(A, 1000, M, C);
	lineto(A[i]*25,M+C);
}
	M=0;C=0;
	moveto(0,480);
	setcolor(RED);
	FillRand(A, 1000);
	outtextxy(120,180,"Quick");
	for(int i=0;i<1000;i++){
	QuickSort(A, 0, 1000-1);
	lineto(A[i]*25,M+C);
}
getch();
}
