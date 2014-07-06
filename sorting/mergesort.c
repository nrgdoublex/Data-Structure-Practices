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

void merge(int *init,int *merged,int start,int mid,int end){
	int i,j,k,t;
	i=start;
	j=mid+1;
	k=start;

	while(i<=mid&&j<=end){
		if(init[i]<=init[j])
			merged[k++]=init[i++];
		else
			merged[k++]=init[j++];
	
	}
	if(i>mid){
		for(t=j;t<=end;t++)
			merged[k++]=init[t];
	}
	else{
		for(t=i;t<=mid;t++)
			merged[k++]=init[t];
		
	}
}

void mergepass(int *init,int *merged,int num,int sect){
	int i,j;
	for(i=0;i<=num-2*sect+1;i+=2*sect)
		merge(init,merged,i,i+sect-1,i+2*sect-1);
	if(i+sect-1<num)
		merge(init,merged,i,i+sect-1,num);
	else
		for(j=i;j<num;j++)
			merged[j]=init[j];
}

void mergesort(int *a,int n){
	int s=1,i;
	int temp[n];

	while(s<n){
		mergepass(a,temp,n,s);


	for(i=0;i<n;i++)
		printf("%d ",temp[i]);
	printf("\n");

		s*=2;
		mergepass(temp,a,n,s);


	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");

		s*=2;
	}
}

int main(int argc,char** argv)
{
	int a[11]={12,2,16,30,8,28,4,10,20,6,18};
	mergesort(a,11);
/*
	int i;
	for(i=0;i<11;i++)
		printf("%d ",a[i]);
	printf("\n");
*/
	return 0;
}
