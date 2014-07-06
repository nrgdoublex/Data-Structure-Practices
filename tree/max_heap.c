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

#define MAX_ELEMENTS 4
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
		return (p->top==0)?0:-1;
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
	temp=p->heap[p->top--];
	parent=1;
	child=2;
	while(child<=p->top){
		if(p->heap[child].key<p->heap[child+1].key)
			child++;
		if(temp.key>=p->heap[child].key) break;
		p->heap[parent]=p->heap[child];
		parent=child;
		child*=2;
	}
	p->heap[parent]=temp;
	return item;
}

int pushfast(heappt p,element e){
	element *q;
	int i;
	if(!isfull(p)){
		REALLOC(q,p->heap,2*sizeof(*(p->heap))*(p->size));
		p->heap=q;
	}
	++p->top;
	i=p->top;

	while(e.key>p->heap[i/2].key&&i!=1)
		i=i/2;
	int j;
	for(j=p->top;j>i;j=j/2)
		p->heap[j]=p->heap[j/2];
	p->heap[i]=e;
	return 0;
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
	while(i!=1 && e.key>p->heap[i/2].key){
		p->heap[i]=p->heap[i/2];
		i=i/2;
	}
	p->heap[i]=e;
	return 0;
}

int changepriority(heappt p,int in, int out){
	element e;
	int i;

	if(!isempty(p)){
		fprintf(stderr,"heap empty\n");
		return -1;
	}

	i=1;
	while(i<=p->top&&p->heap[i].key!=in)
		i++;
	if(i>(p->top)){
		fprintf(stderr,"Could not find the number to replace\n");
		return -1;
	}
	else
		p->heap[i].key=out;
	
	if(i!=1 && p->heap[i].key > p->heap[i/2].key){
		element e=p->heap[i];
		while(i!=1&& e.key > p->heap[i/2].key){
			p->heap[i]=p->heap[i/2];
			i/=2;
		}
		p->heap[i]=e;
	}
	else if(2*i<=p->top && p->heap[i].key < p->heap[2*i].key){
		element e=p->heap[i];
		while(2*i<=p->top && e.key < p->heap[2*i].key){
			p->heap[i]=p->heap[2*i];
			i*=2;
		}
		p->heap[i]=e;
	}
	return 0;
}

int delete(heappt p,int del){	
	element e;
	int i;

	if(!isempty(p)){
		fprintf(stderr,"heap empty\n");
		return -1;
	}
	
	i=1;
	while(i<=p->top && p->heap[i].key!=del)
		i++;
	if(i>(p->top)){
		fprintf(stderr,"Could not find the number to replace\n");
		return -1;
	}
	p->heap[i].key=p->heap[1].key+1;
			
	if(i!=1 && p->heap[i].key > p->heap[i/2].key){
		element e=p->heap[i];
		while(i!=1&& e.key > p->heap[i/2].key){
			p->heap[i]=p->heap[i/2];
			i/=2;
		}
		p->heap[i]=e;
	}
	else if(2*i<=p->top && p->heap[i].key < p->heap[2*i].key){
		element e=p->heap[i];
		while(2*i<=p->top && e.key < p->heap[2*i].key){
			p->heap[i]=p->heap[2*i];
			i*=2;
		}
		p->heap[i]=e;
	}
	pop(p);
	return 0;	
}

int search(heappt p,int num){	
	element e;
	int i;

	if(!isempty(p)){
		fprintf(stderr,"heap empty\n");
		return -1;
	}
	
	i=1;
	while(i<=p->top && p->heap[i].key!=num)
		i++;
	if(i>(p->top)){
		fprintf(stderr,"Could not find the number to replace\n");
		return -1;
	}
	return 0;
}

int main(int argc,char** argv)
{
	heappt p=create_maxheap();
	element e;
	int i;

	e.key=7;
	pushfast(p,e);
	e.key=16;
	pushfast(p,e);
	e.key=49;
	pushfast(p,e);
	e.key=82;
	pushfast(p,e);
	e.key=5;
	pushfast(p,e);
	e.key=31;
	pushfast(p,e);
	e.key=6;
	pushfast(p,e);
	e.key=2;
	pushfast(p,e);
	e.key=44;
	pushfast(p,e);
	for(i=1;i<=p->top;i++){
		printf("The %dth element of heap is %d\n",i,p->heap[i].key);
	}
	printf("\n");
	changepriority(p,82,1);
	for(i=1;i<=p->top;i++){
		printf("The %dth element of heap is %d\n",i,p->heap[i].key);
	}
	printf("\n");
	delete(p,31);
	for(i=1;i<=p->top;i++){
		printf("The %dth element of heap is %d\n",i,p->heap[i].key);
	}

	int num=49;
	if(!search(p,num))
		printf("Search num %d is success\n",num);
	else
		printf("Search num %d is failed\n",num);
/*
	printf("\n");
	changepriority(&p,2,45);
	for(i=1;i<=p->top;i++){
		printf("The %dth element of heap is %d\n",i,p->heap[i].key);
	}
*/
	return 0;
}
