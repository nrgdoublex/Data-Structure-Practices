#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct{
	int expo;
	float coef;
}poly;

void readpoly(int expo[],float coef[],poly *term,int len)
{
	int i;
	for(i=0;i<len;i++){
		term[i].expo=expo[i];
		term[i].coef=coef[i];
	}
}
void printpoly(poly *term,int len)
{
	int i;
	printf("The polonomial is ");
	for(i=0;i<len;i++){
		printf("%.1fx^%d",term[i].coef,term[i].expo);
		if(i!=len-1)
			printf("+");
	}
	printf("\n");
}


int main(int argc,char** argv)
{
	poly term[10];

	int expo[10]={0,1,2,3,4,5,6,7,8,9};
	float coef[10]={9,8,7,6,5,4,3,2,1,0};

	readpoly(expo,coef,term,10);
	printpoly(term,10);

	return 0;
}
