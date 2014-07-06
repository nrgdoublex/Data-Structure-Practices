#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define CALLOC(p,n,s) \
	if(!((p)=calloc(n,s))) { \
		perror("Insufficient memory\n"); \
		exit(EXIT_FAILURE); \
	}

#define MALLOC(p,n,s) \
	if(!((p)=malloc(n,s))) { \
		perror("Insufficient memory\n"); \
		exit(EXIT_FAILURE); \
	}

int** make2darray(int row,int col)
{
	int **x, i;
	CALLOC(x,row,sizeof(*x));
	for(i=0;i<row;i++){
		CALLOC(x[i],col,sizeof(**x));
	}
	return x;
}

int** make2darray1(int row,int length[])
{
	int **x, i;
	CALLOC(x,row,sizeof(*x));
	for(i=0;i<row;i++){
		CALLOC(x[i],length[i],sizeof(**x));
	}
	return x;
}

void add(int **a,int **b,int ** c,int row,int col)
{
	int i,j;
	for(i=0;i<row;i++)
		for(j=0;j<col;j++)
			c[i][j]=a[i][j]+b[i][j];
}

void mul(int **a,int **b,int ** c,int row)
{
	int i,j,k;


	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			c[i][j]=0;

	for(i=0;i<row;i++)
		for(j=0;j<row;j++)
			for(k=0;k<row;k++)		
				c[i][j]+=a[i][k]*b[k][j];
}

void trans(int **a,int row)
{
	int i,j,temp;
	for(i=0;i<row;i++){
		for(j=0;j<i;j++){
			temp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=temp;
		}
	}
}

void trans1(int **a,int **b,int row,int col)
{
	int i,j;
	for(i=0;i<row;i++){
		for(j=0;j<col;j++){
			b[j][i]=a[i][j];
		}
	}
}

int main(int argc,char** argv)
{
	int i,j;
	int **x=make2darray(3,5);
	int **y=make2darray(5,3);
//	int **z=make2darray(5,5);
	
	for(i=0;i<3;i++){
		for(j=0;j<5;j++){
			x[i][j]=i*2+j;
//			y[i][j]=(i+j);
			
		}
	}

//	add(x,y,z,5,4);
//	mul(x,y,z,5);
	trans1(x,y,3,5);

	for(i=0;i<5;i++)
		for(j=0;j<3;j++)
			printf("(%d,%d) element is %d\n",i,j,y[i][j]);

/*
	int len[5]={1,2,3,4,5};

	int **x=make2darray1(5,len);
	
	for(i=0;i<5;i++)
		for(j=0;j<len[i];j++)
			x[i][j]=(i+j)*5;

	for(i=0;i<5;i++)
		for(j=0;j<len[i];j++)
		printf("(%d,%d) element is %d\n",i,j,x[i][j]);
*/
	return 0;
}
