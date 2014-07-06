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

void listsort(int *a,int *linka,int n,int first){

	int linkb[n];
	int i,current,prev;
	int temp;
	current=prev=0;
	for(current=first;current;current=linka[current]){
		linkb[current]=prev;
		prev=current;
	}

	for(i=1;i<n;i++){
		if(first!=i){
			if(linka[i]) linkb[linka[i]]=first;
			linka[linkb[i]]=first;
			swap(&a[i],&a[first]);
			swap(&linka[i],&linka[first]);
			swap(&linkb[i],&linkb[first]);
		}
		first=linka[i];
	}
}

void listsort2(int *a,int *linka,int n, int first){
	int i,temp;

	for(i=1;i<n;i++){
		while(first<i)first=linka[first];
		int q=linka[first];
		if(first!=i){
			swap(&a[i],&a[first]);
			linka[first]=linka[i];
			linka[i]=first;
		}
		first=q;
	}
}

void tablesort(int *a,int *t,int n){
	int i,current,next;
	int temp;

	for(i=1;i<n;i++){
		if(t[i]!=i){
			temp=a[i];current=i;
			do{
				next=t[current];
				a[current]=a[next];
				t[current]=current;
				current=next;
			}while(t[current]!=i);
			t[current]=current;
			a[current]=temp;
		}
	}
}

void countgen(int *a,int *count,int n){
	int i,j;

	for(i=0;i<n;i++)
		count[i]=0;

	for(i=1;i<n;i++){
		for(j=i;j<n;j++){
			if(a[i]<a[j])
				count[j]++;
			else if(a[j]<a[i])
				count[i]++;
		}
	}
}

void countsort(int *a,int *count,int n){
	int i,j;

	for(i=1;i<n;i++){
		j=i;
		while(count[j]!=i-1)
			j++;
		swap(&a[i],&a[j]);
		swap(&count[i],&count[j]);
	}
}

int main(int argc,char** argv)
{
	int i;
//	int a[11]={-1,26,5,77,1,61,11,59,15,48,19};
//	int linka[11]={-1,9,6,0,2,3,8,5,10,7,1};

//	listsort2(a,linka,11,4);

	int a[9]={-1,35,14,12,42,26,50,31,18};
	int t[9]={-1,3,2,8,5,7,1,4,6};
	int count[9];
//	tablesort(a,t,9);

	countgen(a,count,9);
	countsort(a,count,9);
	for(i=1;i<9;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
