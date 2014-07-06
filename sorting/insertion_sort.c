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

void insert(int value,int *a,int num){
	int i=num;
	while(i>=0&&value < a[i]){
		a[i+1]=a[i];
		i--;
	}
	a[i+1]=value;
}

void binsert(int value,int *a,int num){
	int i=num,j=num;
	while(i>=0&&value<a[i--])
		;
	while(j>=0&&value<a[j]){
		a[j+1]=a[j];
		j--;
	}
	a[j+1]=value;
}

void insertsort(int *a,int num){
	int i,j,temp;
	for(i=1;i<num;i++){
		temp=a[i];
		binsert(temp,a,i-1);
		for(j=0;j<11;j++)
			printf("%d ",a[j]);
		printf("\n");
	}
}

int main(int argc,char** argv)
{
	int i=11;
	int a[11]={12,2,16,30,8,28,4,10,20,6,18};

	insertsort(a,11);
/*	for(i=0;i<11;i++)
		printf("%d ",a[i]);
	printf("\n");
*/
	return 0;
}
