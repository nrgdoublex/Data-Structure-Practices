#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_SIZE 100

typedef struct {
	int key;
}element;

typedef struct {
	element stack[MAX_SIZE];
	int top;
}STACK;

STACK* createstack(){
	STACK *p=malloc(sizeof(STACK));
	if(p==NULL){
		perror("allocate error");
		return NULL;
	}
	else{
		p->top=-1;
		return p;	
	}
}

int isfull(STACK *input){
	return (input->top==MAX_SIZE-1)?0:-1;
}

int isempty(STACK *input){
	return (input->top==-1)?0:-1;
}

int push(STACK *input,element data){
	if(!isfull(input)){
		printf("stack full\n");
		return -1;
	}
	else{
		input->stack[++(input->top)].key=data.key;
		return 0;
	}
}

int pop(STACK *input,element *out){
	if(!isempty(input)){
		printf("stack empty\n");
		return -1;
	}
	else{
		out->key=input->stack[input->top--].key;
		return 0;
	}
}

void stackempty(STACK *input){
	input->top=-1;
}

int main(int argc,char** argv)
{
	STACK *p=createstack();
	int i;
	
	for(i=0;i<10;i++){
		element e;
		e.key=i*5;
		if(push(p,e)){
			printf("push error\n");
			return -1;
		}
	}	

	stackempty(p);

	for(i=0;i<11;i++){
		element e;
		if(pop(p,&e)==-1){
			printf("pop error\n");
			return -1;
		}
		else{
			printf("top element of the element of stack is %d\n",e.key);
		}	
	}

	return 0;
}
