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

typedef enum {data,sublist} tagfield;
typedef struct gennode *genpt;
typedef struct gennode{
	tagfield tag;
	union{
		genpt list;
		char c;
	}u;
	genpt link;
};

typedef struct{
	char ch;
	genpt pt;
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

int push(char c,genpt p){
	if(!isfull()){
		fprintf(stderr,"stack full\n");
		return -1;
	}
	else{
		stack[++top].ch=c;
		stack[top].pt=p;
		return 0;
	}
}	

int pop(char *c,genpt *p){
	if(!isempty()){
		fprintf(stderr,"stack empty\n");
		return -1;
	}
	else{
		*c=stack[top].ch;
		*p=stack[top--].pt;
		return 0;
	}	
}

genpt getnode(char c,genpt list){
	genpt p;
	MALLOC(p,sizeof(*p));
	if(c){
		p->tag=data;
		p->u.c=c;
	}
	else{
		p->tag=sublist;
		p->u.list=list;
	}
	p->link=NULL;
	return p;
}

genpt combine(genpt a,genpt b){
	if(a->link==NULL){
		a->link=b;
		return a;
	}
//	else{
//		genpt list=getnode(NULL,a);
//		list->link=b;
//		return list;
//	}
}

genpt combinerootchild(genpt root,genpt child){
	if(root->link==NULL){
		root->link=child;
		genpt list=getnode(NULL,root);
		return list;
	}
//	else{
//		genpt list=getnode(NULL,a);
//		list->link=b;
//		return list;
//	}
}

genpt readtree(char *input){
	int i;
	int len =(int)strlen(input);
	genpt temp=NULL;

	char c;
	for(i=0;i<len;i++){
		c=input[i];

		if(c>='A' && c<='Z'){
			if(!temp)
				temp=getnode(c,NULL);
			else{
				genpt temp1=getnode(c,NULL);
				temp=combine(temp,temp1);
			}
		}
		else if(c=='('){
			if(temp){
				push('a',temp);
				push('(',NULL);
				temp=NULL;
			}
		}
		else if(c==')'){
			if(temp){
				element e;
				while(!pop(&(e.ch),&(e.pt)) && e.ch!='(')
					temp=combine(e.pt,temp);
				pop(&(e.ch),&(e.pt));
				temp=combinerootchild(e.pt,temp);
			}
		}
		else if(c==','){
			if(temp){
				push('a',temp);
				temp=NULL;
			}
		}
	}
	return temp;
}

void writenode(genpt p){
	genpt temp=p;

	if(temp->tag==data){
		printf("%c",temp->u.c);
	}
	printf("(");
	for(temp=temp->link;temp!=NULL;temp=temp->link){
		if(temp->tag==data)
			printf("%c",temp->u.c);
		else{
			genpt temp_list=temp->u.list;
			writenode(temp_list);
		}
		if(temp->link!=NULL)
			printf(",");
	}
	printf(")");
}

void writetree(genpt p){
	genpt temp=p->u.list;
	writenode(temp);
}

int isequalnode(genpt a,genpt b){
	
	if(a->tag!=b->tag)
		return -1;
	if(a->tag==data && a->u.c!=b->u.c)
		return -1;
	return 0;
}

int isequal(genpt a,genpt b){
	genpt temp_a=a,temp_b=b;

	while(temp_a!=NULL && temp_b!=NULL){
		if(isequalnode(temp_a,temp_b))
			return -1;
		if(temp_a->tag==sublist){
			genpt la=temp_a->u.list;
			genpt lb=temp_b->u.list;
			if(isequal(la,lb))
				return -1;
		}
		temp_a=temp_a->link;
		temp_b=temp_b->link;
	}
	return 0;
}

genpt copytree(genpt a){
	genpt temp=a;
	genpt ret,front=NULL;
	genpt final;
	int flag=0;

	while(temp!=NULL){
		if(temp->tag==data){
			ret=getnode(temp->u.c,NULL);
		}
		else
			ret=getnode(NULL,copytree(temp->u.list));
		if(flag==0){
			final=ret;
			flag=1;
		}
		if(front!=NULL)
			front->link=ret;
		ret->tag=temp->tag;
		ret->link=temp->link;
		front=ret;
		temp=temp->link;
	}
	return final;
}

void deltree(genpt a){
	genpt temp=a,front;

	while(temp!=NULL){
		front=temp;
		temp=temp->link;
		if(front->tag==sublist){
			deltree(front->u.list);
		}
		if(front->tag==data)
			printf("the node deleted is data %c\n",front->u.c);
		else
			printf("the node deleted is sublist \n");
		free(front);
	}
}

int main(int argc,char** argv)
{
	char *c="A(B(E(K,L),F),C(G),D(H(M),I,J))";
	char *a="A(B(C,D,E),F(G(H,I),K(L,M,N)),O(P,Q))";
	char *b="A(B(C(D(E))))";
	char *d="A(B(C,D),E(F(G(H(I,J)))),K)";

	genpt p=readtree(c);
	writetree(p);
	printf("\n");

//	printf("%d\n",top);

	genpt q=copytree(p);
	
	writetree(q);
	printf("\n");

	deltree(q);

//	printf("%d\n",top);

/*	if(!isequal(p,q))
		printf("two trees are equal\n");
	else
		printf("two trees are different\n");
	printf("\n");
*/

	return 0;
}
