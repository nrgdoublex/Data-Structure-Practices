#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


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

typedef struct node *nodept;
typedef struct node{
	int valid;
	int dis;
};

typedef struct{
	nodept root;
	int num;
}*tree;

tree gettree(int num){
	tree t;
	nodept p;
	
	int i;

	MALLOC(t,sizeof(*t));
	MALLOC(t->root,num*sizeof(*(t->root)));
	for(i=0;i<num;i++){
		t->root[i].valid=FALSE;
		t->root[i].dis=0;
	}
	t->num=num;
        return t;
}

void filltree(tree t,int idx,int dis){
	if(!t || !t->root){
		fprintf(stderr,"invalid tree\n");
		exit(EXIT_FAILURE);
	}

	if(idx==0 && dis>0){
		fprintf(stderr,"should not assign to root >0 length\n");
		return;
	}
	if(idx>=t->num){
		fprintf(stderr,"node you assign not exist\n");
		return;
	}
	t->root[idx].dis=dis;
	t->root[idx].valid=TRUE;
}

void freetree(tree t){
	if(!t || !t->root){
		fprintf(stderr,"invalid tree\n");
		exit(EXIT_FAILURE);
	}
	free(t->root);
	free(t);
}

void printtree(tree t){
	int i;

	if(!t || !t->root){
		fprintf(stderr,"invalid tree\n");
		exit(EXIT_FAILURE);
	}
	for(i=1;i<t->num;i++){
		if(t->root[i].valid==TRUE)
			printf("node %d has distance %d to its parent\n",i,t->root[i].dis);
	}
}

void printshortestpath(tree t){
	int i;

	int dis[t->num];
	for(i=0;i<t->num;i++)
		dis[i]=0;
	for(i=2;i<t->num;i++){
		dis[i]=dis[i/2]+t->root[i].dis;
	}
	for(i=2;i<t->num;i++)
		printf("node %d has distance %d to root 0\n",i,dis[i]);
}

int main(int argc,char** argv)
{	
	int i,num=16;
	tree t=gettree(num);
	
	for(i=2;i<t->num;i++){
		srand(i*5);
		filltree(t,i,rand()%10);
	}
	printtree(t);
	printf("\n");
	printshortestpath(t);
	
	freetree(t);
	return 0;
}
