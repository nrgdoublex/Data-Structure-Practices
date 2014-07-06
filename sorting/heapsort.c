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

void adjust(int *a,int root,int n){
	int child;
	int temp;

	temp=a[root];
	child=2*root;
	while(child<=n){
		if(child<n&&a[child]<a[child+1])
			child++;
		if(a[root]>a[child])
			break;
		else{
			a[child/2]=a[child];
			child*=2;
		}
	}
	a[child/2]=temp;
}

void heapsort(int *a,int n){
	int i;
	for(i=n/2;i>0;i--)
		adjust(a,i,n);
	for(i=n-1;i>0;i--){
		swap(&a[1],&a[i+1]);
		adjust(a,1,i);
	}
}

int main(int argc,char** argv)
{	
	int a[12]={-1,12,2,16,30,8,28,4,10,20,6,18};
	heapsort(a,11);

	int i;
	for(i=1;i<12;i++)
		printf("%d ",a[i]);
	printf("\n");

	return 0;
}
