#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

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
	int data;
	nodept left;
	nodept right;
};

nodept getnode(int data){
	nodept p;
	MALLOC(p,sizeof(*p));
	p->left=NULL;
	p->right=NULL;
	p->data=data;
	return p;
}

int isempty(nodept p){
	return (!p)?0:-1;
}

void insert(nodept p,int data){
	nodept temp,rear;
	if(!isempty(p)){
		fprintf(stderr,"the tree is invalid\n");
		exit(EXIT_FAILURE);
        }
	temp=p;
	while(temp!=NULL){
		rear=temp;
		if(data<temp->data)
			temp=temp->left;
		else
			temp=temp->right;
	}
	temp=getnode(data);
	if(data < rear->data)
		rear->left=temp;
	else
		rear->right=temp;
}

nodept search(nodept p,int data){
	nodept temp;
	if(!isempty(p)){
		fprintf(stderr,"the tree is invalid\n");
		exit(EXIT_FAILURE);
        }
	temp=p;
	while(temp!=NULL&&temp->data!=data){
		if(data<temp->data)
			temp=temp->left;
		else
			temp=temp->right;
	}
	if(temp==NULL)
		return NULL;
	else{
		printf("element %d found in binary search tree\n",data);
		return temp;
	}
}

nodept *threewayjoin(nodept *small,nodept *mid, nodept *big){
	if(!*small || !*mid || !*big){
		fprintf(stderr,"Invalid input for 3waysearch\n");
		exit(EXIT_FAILURE);
	}
	(*mid)->left=*small;
	(*mid)->right=*big;
	return mid;
}

nodept *twowayjoin(nodept *small,nodept *big){
	nodept temp,leftchild,front;

	if(!*small || !*big){
		fprintf(stderr,"Invalid input for 3waysearch\n");
		exit(EXIT_FAILURE);
	}
	temp=(*small);
	while(temp->right!=NULL){
		front=temp;
		temp=temp->right;
	}
	nodept *ret;
	if(temp!=*small){
		leftchild=temp->left;
		front->right=leftchild;
		ret=threewayjoin(small,&temp,big);
	}
	else{
		temp->right=*big;
		ret=small;
	}
	return ret;
}

void delete(nodept *p,int data){
	nodept temp,front;
	if(!isempty(*p)){
		fprintf(stderr,"the tree is invalid\n");
		exit(EXIT_FAILURE);
        }
	temp=*p;
	front=temp;
	while(temp!=NULL && temp->data!=data){
		front=temp;
		if(data < temp->data)
			temp=temp->left;
		else
			temp=temp->right;
	}
	if(temp==NULL)
		printf("No element found in delete\n");
	else if(temp==*p){
		nodept *combine=twowayjoin(&(temp->left),&(temp->right));
		p=combine;
	}
	else{
		if(temp->right==NULL){
			if(temp==front->left)
				front->left=temp->left;
			else
				front->right=temp->left;
		}
		else if(temp->left==NULL){
			if(temp==front->left)
				front->left=temp->right;
			else
				front->right=temp->right;
		}
		else{
			nodept *combine=twowayjoin(&(temp->left),&(temp->right));
			if(temp==front->left)
				front->left=*combine;
			else
				front->right=*combine;
		}
		free(temp);
	}
}

void inorder_travel(nodept p){
	nodept temp=p;

	if(temp->left!=NULL)
		inorder_travel(temp->left);
	printf("The node is %d\n",temp->data);
	if(temp->right!=NULL)
		inorder_travel(temp->right);
	
}

int main(int argc,char** argv)
{
	nodept p=getnode(7);

	insert(p,16);
	insert(p,49);
	insert(p,82);
	insert(p,5);
	insert(p,31);
	insert(p,6);
	insert(p,2);
	insert(p,44);

	inorder_travel(p);
	delete(&p,7);
	delete(&p,16);
	printf("\n");
	inorder_travel(p);

	return 0;
}
