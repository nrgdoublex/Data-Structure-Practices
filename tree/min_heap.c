#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MALLOC(p,s) \
	if(!(p=malloc(s))){ \
		fprintf(stderr,"Allocating Error\n"); \
		exit(EXIT_FAILURE); \
	}

#define REALLOC(q,p,s) \
	if(!(q=realloc(p,s))){ \
		fprintf(stderr,"Reallocating Error\n"); \
		exit(EXIT_FAILURE); \
	}

#define MAX_ELEMENTS 200
typedef struct{
	int key;
}element;

typedef struct{
	element *heap;
	int top;
	int size;
}max_heap;
typedef max_heap *heappt;

#define TRUE 0
#define FALSE -1

heappt create_maxheap(){
	heappt p;
	MALLOC(p,sizeof(*p));
	if(!(p->heap=malloc(sizeof(*(p->heap)) * MAX_ELEMENTS))){
		fprintf(stderr,"Allocate heap array error\n");
		free(p);
		exit(EXIT_FAILURE);
	}
	p->top=0;
	p->size=MAX_ELEMENTS;
	return p;
}

int isempty(heappt p){
	if(!p){
		fprintf(stderr,"heap pointer invalid\n");
		exit(EXIT_FAILURE);
	}
	else
		return (p->top>0)?0:-1;
}

int isfull(heappt p){
	if(!p){
		fprintf(stderr,"heap pointer invalid\n");
		exit(EXIT_FAILURE);
	}
	else
		return (p->top==p->size-1)?0:-1;
}

element top(heappt p){
	element e;
	if(!isempty(p)){
		fprintf(stderr,"heap empty\n");
		exit(EXIT_FAILURE);
	}
	else{
		e.key=p->heap[1].key;
		return e;
	}
}

element pop(heappt p){
	int parent,child;
	element item,temp;
	if(!isempty(p)){
		fprintf(stderr,"heap empty\n");
		exit(EXIT_FAILURE);
	}
	item=p->heap[1];
	temp=p->heap[p->top];
	parent=1;
	child=2;
	while(child<=p->top){
		if(p->heap[child].key>p->heap[child+1].key)
			child++;
		if(temp.key>=p->heap[child].key) break;
		p->heap[parent]=p->heap[child];
		parent=child;
		child*=2;
	}
	p->heap[parent]=temp;
	return item;
}

int push(heappt p,element e){
	element *q;
	int i;
	if(!isfull(p)){
		REALLOC(q,p->heap,2*sizeof(*(p->heap))*(p->size));
		p->heap=q;
	}
	++p->top;
	i=p->top;
	while(i!=1 && e.key<p->heap[i/2].key){
		p->heap[i]=p->heap[i/2];
		i=i/2;
	}
	p->heap[i]=e;
	return 0;
}


int main(int argc,char** argv)
{
	heappt p=create_maxheap();
	element e;
	int i;

	e.key=7;
	push(p,e);
	e.key=16;
	push(p,e);
	e.key=49;
	push(p,e);
	e.key=82;
	push(p,e);
	e.key=5;
	push(p,e);
	e.key=31;
	push(p,e);
	e.key=6;
	push(p,e);
	e.key=2;
	push(p,e);
	e.key=44;
	push(p,e);
	for(i=1;i<=p->top;i++){
		printf("The %dth element of heap is %d\n",i,p->heap[i].key);
	}
	
	return 0;
}
