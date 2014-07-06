#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_SIZE 10

typedef struct{
	int key;
}element;

typedef struct{
	element q[MAX_SIZE+1];
	int rear;
	int front;
}queue;

queue *createqueue(){
	queue *p=malloc(sizeof(queue));
	if(p==NULL){
		fprintf(stderr,"allocate queue error\n");
		return NULL;
	}
	else{
		p->rear=MAX_SIZE;
		p->front=MAX_SIZE;
		return p;
	}
}

int isfull(queue *p){
	if((p->front)==(p->rear+1)%(MAX_SIZE+1))
		return 0;
	else return -1;
}

int isempty(queue *p){
	return (p->front==p->rear)?0:-1;
}

int addqueue(queue *p,element e){
	if(!isfull(p)){
		fprintf(stderr,"add error\n");
		return -1;
	}
	else{
		(p->rear==MAX_SIZE)?p->rear=0:p->rear++;
		p->q[p->rear].key=e.key;
		return 0;
	}
}

int delqueue(queue *p){
	if(!isempty(p)){
		fprintf(stderr,"del error\n");
		return -1;
	}
	else{
		//if(p->front==MAX_SIZE){
		printf("the element deleted is %d,position is %d\n",p->q[(p->front+1)%(MAX_SIZE+1)].key,(p->front+1)%(MAX_SIZE+1));
		p->front=(p->front+1)%(MAX_SIZE+1);
	//	}
	//	else{
	//		printf("the element deleted is %d,position is %d\n",p->q[p->front+1].key,p->front+1);
	//		p->front++;
	//	}
		return 0;
	}
}

int delnum(queue *p,int k){
	int num=(p->rear-p->front)>0?(p->rear-p->front):(MAX_SIZE+1)+(p->rear-p->front);
	if(k>num){
		fprintf(stderr,"delete invalid\n");
		return -1;
	}
	int i;
	for(i=k;i<num;i++){
		p->q[(p->front+i)%(MAX_SIZE+1)].key= \
		p->q[(p->front+i+1)%(MAX_SIZE+1)].key;
	}
	p->rear=(p->rear-1)%(MAX_SIZE+1);
	return 0;
}

int insnum(queue *p,int k,element e){

	int num=(p->rear-p->front)>0?(p->rear-p->front):(MAX_SIZE+1)+(p->rear-p->front);
	if(k>num || num==MAX_SIZE){
		fprintf(stderr,"insert invalid\n");
		return -1;
	}
	int i;
	for(i=num+1;i>k+1;i--){
		p->q[(p->front+i)%(MAX_SIZE+1)].key= \
		p->q[(p->front+i-1)%(MAX_SIZE+1)].key;
	}
	p->q[(p->front+k+1)%(MAX_SIZE+1)].key=e.key;
}


int main(int argc,char** argv)
{
	queue *p=createqueue();
	if(p==NULL){
		exit(EXIT_FAILURE);
	}
	else{
		int i;
		for(i=0;i<9;i++){
			element e;
			e.key=i*2;
			addqueue(p,e);
		}

		for(i=0;i<6;i++){
			delqueue(p);
		}
		for(i=0;i<6;i++){
			element e;
			e.key=i*5;
			addqueue(p,e);
		}
		//delnum(p,5);
		element e;
		e.key=100;
		insnum(p,5,e);
		for(i=0;i<10;i++)
			delqueue(p);
	}

	return 0;
}
