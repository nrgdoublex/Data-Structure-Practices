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

poly *zero()
{
	poly *x;
	if((x=malloc(sizeof(poly)))==NULL){
		perror("Allocating fail!\n");
		exit(EXIT_FAILURE);
	}
	x[0].expo=0;
	x[0].coef=0;
	return x;
}

int iszero(poly *x)
{
	if(!x)
		perror("no poly");
	else
		
}

int main(int argc,char** argv)
{
	return 0;
}
