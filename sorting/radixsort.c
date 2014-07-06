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

int getdigit(int input,int order,int base){
	int expo=1;
	int remain;
	while(order>0){
		expo*=base;
		order--;
	}
	remain=input/expo;
	remain=remain%base;
	return remain;
}

int radixsort(int *a,int *link,int digit,int base,int n){
	int front[base],rear[base];
	int i,bin,current,first,last;

	first=1;
	for(i=1;i<n;i++)
		link[i]=i+1;
	link[n]=0;

	for(i=0;i<=digit;i++){
		for(bin=0;bin<base;bin++)
			front[bin]=0;
		for(current=first;current;current=link[current]){
			bin=getdigit(a[current],i,base);
			if(front[bin]==0) front[bin]=current;
			else link[rear[bin]]=current;
			rear[bin]=current;
		}

		for(bin=0;!front[bin];bin++)
			;
		first=front[bin];
		last=rear[bin];

		for(bin++;bin<base;bin++){
			if(front[bin]){
				link[last]=front[bin];
				last=rear[bin];
			}
		}
		link[last]=0;
	}
	return first;

}

int main(int argc,char** argv)
{
	int a[12]={-1,12,2,16,30,8,28,4,10,20,6,18};
	int link[11];
	
	int i=radixsort(a,link,1,10,11);

	int j;
	for(j=0;j<11;j++,i=link[i])
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
