#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_SIZE 100

typedef struct{
	int q[MAX_SIZE+1];
	int front;
	int rear;
}deque;

deque *createdeque(){
	deque *p=malloc(sizeof(deque));
	if(p==NULL){
		fprintf(stderr,"allocate deque error\n");
		exit(EXIT_FAILURE);
	}
	p->front=MAX_SIZE;
	p->rear=MAX_SIZE;
	return p;
}

int isfull(deque *p){
	return (p->front)==(p->rear+1)%(MAX_SIZE+1)?0:-1;
}

int isempty(deque *p){
	return p->front==p->rear?0:-1;
}

int addhead(deque *p,int e){
	if(!isfull(p)){
		fprintf(stderr,"deque full\n");
		return -1;
	}
	p->q[p->front]=e;
	if(p->front==0)
		p->front=MAX_SIZE;
	else
		p->front--;
	return 0;
}

int addtail(deque *p,int e){
	if(!isfull(p)){
		fprintf(stderr,"deque full\n");
		return -1;
	}
	int i=(p->rear+1)%(MAX_SIZE+1);
	p->q[i]=e;
	p->rear=i;
	return 0;
}

int delhead(deque *p){
	if(!isempty(p)){
		fprintf(stderr,"deque empty\n");
		return -1;
	}
	int i=p->q[(p->front+1)%(MAX_SIZE+1)];
	p->front=(p->front+1)%(MAX_SIZE+1);
	return i;
}

int deltail(deque *p){	
	if(!isempty(p)){
		fprintf(stderr,"deque empty\n");
		return -1;
	}
	int i=p->q[p->rear];
	if(p->rear==0)
		p->rear=MAX_SIZE;
	else
		p->rear--;
	return i;
}

int main(int argc,char** argv)
{
	int i;
	deque *p=createdeque();

	for(i=0;i<8;i++){
		addhead(p,i+1);
	}

	for(i=0;i<10;i++){
		addtail(p,i*4);
	}
	for(i=0;i<6;i++){
		delhead(p);
	}
	for(i=0;i<6;i++){
		deltail(p);
	}
	
	int num=((p->rear-p->front)>0)?(p->rear-p->front):(MAX_SIZE+1)+(p->rear-p->front);
	for(i=0;i<num;i++){
		printf("the number of position %d is %d\n",(p->front+i+1)%(MAX_SIZE+1),p->q[(p->front+i+1)%(MAX_SIZE+1)]);
	}

	return 0;
}
