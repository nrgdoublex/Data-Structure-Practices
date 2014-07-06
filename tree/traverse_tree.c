#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MALLOC(p,s) \
	if(!(p=malloc(s))){ \
		fprintf(stderr,"allocate error\n"); \
		exit(EXIT_FAILURE); \
	}

typedef struct treenode *treept;
typedef struct treenode{
	int data;
	treept left,right;
};

typedef struct{
	int data;
	treept pt;
}element;

#define MAX_STACK 100

element stack[MAX_STACK];
int top=-1;

int isempty(){
	return (top==-1)?0:-1;
}

int isfull(){
	return (top==MAX_STACK)?0:-1;
}

int push(int data,treept p){
	if(!isfull()){
		fprintf(stderr,"stack full\n");
		return -1;
	}
	else{
		stack[++top].data=data;
		stack[top].pt=p;
		return 0;
	}
}	

int pop(int *data,treept *p){
	if(!isempty()){
		fprintf(stderr,"stack empty\n");
		return -1;
	}
	else{
		*data=stack[top].data;
		*p=stack[top--].pt;
		return 0;
	}	
}

int peek(int *data,treept*p){
	if(!isempty()){
		fprintf(stderr,"stack empty\n");
		return -1;
	}
	else{
		*data=stack[top].data;
		*p=stack[top].pt;
		return 0;
	}	
}

treept getnode(int data){
	treept p;
	MALLOC(p,sizeof(*p));
	p->data=data;
	p->left=NULL;
	p->right=NULL;
	
	return p;
}

void preorder(treept start){
	treept temp=start;

	push(start->data,start);
	element e;	
	while(top!=-1){
		pop(&(e.data),&(e.pt));
		printf("The traversed node is %c\n",(e.pt)->data);
		if((e.pt)->right!=NULL)
			push((e.pt)->right->data,(e.pt)->right);
		if((e.pt)->left!=NULL)
			push((e.pt)->left->data,(e.pt)->left);
	}
}

#define TRUE 1
#define FALSE 0

void postorder(treept start){
	treept temp=start;

	//push(FALSE,start);
	element e;	
	treept lastnode=NULL;
	while(top!=-1 || temp!=NULL){
		if(temp!=NULL){
			push(temp->data,temp);
			temp=temp->left;
		}
		else{
			element e;
			peek(&(e.data),&(e.pt));
			if((e.pt)->right!=NULL && lastnode!=(e.pt)->right)
				temp=(e.pt)->right;
			else{
				pop(&(e.data),&(e.pt));
				printf("The traversed node is %c\n",(e.pt)->data);
				lastnode=e.pt;
			}
		}
	}
}


void preorder_countleave(treept start){
	treept temp=start;
	int count=0;

	push(start->data,start);
	element e;	
	while(top!=-1){
		pop(&(e.data),&(e.pt));
		if((e.pt)->right==NULL&&(e.pt)->left==NULL)
			count++;
		if((e.pt)->right!=NULL)
			push((e.pt)->right->data,(e.pt)->right);
		if((e.pt)->left!=NULL)
			push((e.pt)->left->data,(e.pt)->left);
	}
	printf("the leave number of tree is %d\n",count);
}

treept swaptree(treept start){
	treept current;
	if(start==NULL)
		return NULL;
	current=getnode(start->data);
	current->left=swaptree(start->right);
	current->right=swaptree(start->left);
	return current;
}


int main(int argc,char** argv)
{
	treept a=getnode('A');
	treept b=getnode('B');
	treept c=getnode('C');
	treept d=getnode('D');
	treept e=getnode('E');

	// build tree
	a->left=b;
	b->left=c;
	b->right=d;
	c->left=e;

//	postorder(a);
//	preorder_countleave(a);
	treept reverse=swaptree(a);
	preorder(reverse);

	return 0;
}
