#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MALLOC(p,s) \
	if(!(p=malloc(s))){ \
		fprintf(stderr,"Allocating Error\n"); \
		exit(EXIT_FAILURE);\
	}

#define REALLOC(q,p,s) \
	if(!(q=realloc(p,s))){ \
		fprintf(stderr,"Reallocating Error\n"); \
		exit(EXIT_FAILURE);\
	}

#define TRUE 1
#define FALSE 0

void swap(int *a,int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

int median(int left,int mid,int right){

	int i=(left<mid)?mid:left;
	int j=(left>=mid)?mid:left;
	
	if(i<right)
		return i;
	else{
		return (right>j)?right:j;
	}
}

void quicksort(int *a,int left,int right){
	int i,j,pivot;
	int temp;

	if(left<right){
		i=left;j=right;
		pivot=median(a[left],a[(left+right)/2],a[right]);
		do{
			while(a[i]<pivot)
				i++;
			while(a[j]>pivot)
				j--;
			if(i<j )swap(&a[i],&a[j]);
		}while(i<j);
		quicksort(a,left,j-1);
		quicksort(a,j+1,right);
	}
}

typedef struct{
	int left;
	int right;
}interval;


#define MAX_STACK 100
interval stack[100];
int top=-1;

int isempty(){
	return (top==-1)?0:-1;
}

int isfull(){
	return (top==MAX_STACK-1)?0:-1;
}

void push(int left,int right){
	if(!isfull){
		fprintf(stderr,"stack full\n");
		exit(EXIT_FAILURE);
	}
	stack[++top].left=left;
	stack[top].right=right;
}
interval pop(){
	if(!isempty){
		fprintf(stderr,"stack empty\n");
		exit(EXIT_FAILURE);
	}
	interval i;
	i.left=stack[top].left;
	i.right=stack[top--].right;
	return i;
}

void quicksort_iter(int *a,int left,int right){
	int i,j,pivot;
	int temp;

	push(left,right);
	while(isempty()){
		interval inter=pop();
		left=inter.left;right=inter.right;
		if(left<right){
			i=left;j=right;
			pivot=median(a[left],a[(left+right)/2],a[right]);
			do{
				while(a[i]<pivot)
					i++;
				while(a[j]>pivot)
					j--;
				if(i<j)swap(&a[i],&a[j]);
			}while(i<j);
			push(left,j-1);
			push(j+1,right);
//			quicksort(a,left,j-1);
//			quicksort(a,j+1,right);
		}
	}
}

int main(int argc,char** argv)
{
	int i,len=11;
	int a[]={12,2,16,30,8,28,4,10,20,6,18};
	quicksort_iter(a,0,len-1);
	
	for(i=0;i<len;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
