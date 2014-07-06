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

#define TRUE 1
#define FALSE 0

typedef struct node *nodept;
typedef struct node{
	int data;
	nodept parent;
	nodept left;
	nodept right;
};

nodept getnode(int data){
	nodept p;
	MALLOC(p,sizeof(*p));
	p->parent=NULL;
	p->left=NULL;
	p->right=NULL;
	p->data=data;
	return p;
}

int isempty(nodept p){
	return (!p)?0:-1;
}

nodept combine(nodept a,nodept b){
	nodept lead,rear,temp,ret;

	if(a->data > b->data){
		lead=a;
		rear=b;
	}
	else{
		lead=b;
		rear=a;
	}
	ret=lead;
	while(lead->data > rear->data){
		if(lead->left==NULL){
			lead->left=rear;
			rear->parent=lead;
			break;
		}
		else if(lead->right==NULL){
			lead->right=rear;
			rear->parent=lead;
			break;
		}
		else if(lead->left->data > rear->data && lead->right->data <= rear->data){
			temp=lead->right;
			lead->right=rear;
			rear->parent=lead;
			combine(temp,rear);
			break;
		}
		else if(lead->left->data <= rear->data && lead->right->data > rear->data){
			temp=lead->left;
			lead->left=rear;
			rear->parent=lead;
			combine(temp,rear);
			break;
		}
		else if(rear->data > lead->left->data && rear->data > lead->right->data){
			temp=lead->left;
			lead->left=rear;
			rear->parent=lead;
			combine(temp,rear);
			break;
		}
		else{
			lead=lead->right;
		}
	}
	return ret;
}

void push(nodept *p,int data){
	nodept ret=getnode(data);
	
	if(!isempty(*p))
		(*p)=ret;
	else{
		(*p)=combine((*p),ret);
		(*p)->parent=NULL;
	}	
}

nodept pop(nodept *p){
	nodept temp;
	
	if(!isempty(*p)){
		fprintf(stderr,"the tree is invalid\n");
		exit(EXIT_FAILURE);
	}
	else{
		temp=*p;
		(*p)=combine((*p)->left,(*p)->right);
		(*p)->parent=NULL;
	}
	return temp;
}

void printtree(nodept p){
	if(!isempty(p)){
		fprintf(stderr,"the tree is invalid\n");
		exit(EXIT_FAILURE);
	}
	printf("The node is %d\n",p->data);
	if(p->left!=NULL)
		printtree(p->left);
	if(p->right!=NULL)
		printtree(p->right);
}

int main(int argc,char** argv)
{
	nodept p=getnode(7);
	nodept q;

	push(&p,16);
	push(&p,49);
	push(&p,82);
	push(&p,5);
	push(&p,31);
	push(&p,6);
	push(&p,2);
	push(&p,44);


	printtree(p);
	q=pop(&p);
	
	printf("The node popped is %d\n",q->data);
	printtree(p);

	return 0;
}
