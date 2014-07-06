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

element *que;
int num;

int rear;
int front;

element *createqueue(){
	element *p=malloc(MAX_SIZE*sizeof(element));
	if(p==NULL){
		fprintf(stderr,"allocate error\n");
		exit(EXIT_FAILURE);
	}
	rear=-1;
	front=-1;
	num=MAX_SIZE;
	return p;
}

int isempty(){
	return (front==rear)?0:-1;
}
int isfull(){
	return (rear==num-1)?0:-1;
}

void queueempty(){
	printf("queue is empty\n");
	return;
}

element delq(){
	if(front==rear){
		queueempty();
		exit(EXIT_FAILURE);
	}
	return que[++front];
}

void queuefull(){
	int i,num=rear-front;
	if(front>=0){
		for(i=0;i<num;i++){
			que[i].key=que[i+front+1].key;
		}
		front=-1;
		rear=rear-front-1;
	}
	else{
		
		element *q=malloc(2*num*sizeof(element));
		if(q==NULL){
			fprintf(stderr,"realloc error\n");
			return;
		}
		else{
			int i;
			for(i=0;i<num;i++){
				q[i].key=que[i].key;
			}
			num*=2;
			free(que);
			que=q;
		}
	}
}

void addq(element item){
        if(rear==num-1)
                queuefull();
        que[++rear].key=item.key;
}

element queuefront(){
	element e;
	if(que==NULL||!isempty()){
		fprintf(stderr,"queue empty\n");
		exit(EXIT_FAILURE);
	}
	e.key=que[front+1].key;
	return e;
}

int main(int argc,char** argv)
{
	int i;
	que=createqueue();

	for(i=0;i<100;i++){
		element e;
		e.key=100+i;
		addq(e);
	}
	for(i=0;i<50;i++){
		element e;
		e.key=100+i;
		delq(e);
	}
	for(i=0;i<100;i++){
		element e;
		e.key=100-i;
		addq(e);
	}

	element e=queuefront();
	printf("the front element is %d\n",e.key);
	int num=rear-front;
	for(i=front+1;i<=rear;i++){
		printf("the number of position %d is %d\n",i,que[i].key);
	}
	return 0;
}
