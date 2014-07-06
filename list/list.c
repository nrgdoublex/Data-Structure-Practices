#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MALLOC(p,s) \
	if(!((p)=malloc(s))){ \
		fprintf(stderr,"allocate error\n"); \
		exit(EXIT_FAILURE); \
	}

typedef struct listnode *listpt;
typedef struct listnode{
	int num;
	listpt link;
};

listpt createnode(int num){
	listpt p;
	MALLOC(p,sizeof(*p));
	p->link=NULL;
	p->num=num;
	return p;
}

#define isempty(first) (!(first))

void insert(listpt *first,listpt x,int num){
	listpt temp;
	MALLOC(temp,sizeof(*temp));
	temp->num=num;
	if(*first){
		temp->link=x->link;
		x->link=temp;
	}
	else{
		*first=temp;
		temp->link=NULL;
	}
}

void delete(listpt *first, listpt trail){
	if(trail){
		trail->link=trail->link->link;
	}
	else{
		*first=(*first)->link;
	}
}

void printlist(listpt first){
	printf("The list contains :");
	for(;first;first=first->link)
		printf("%d ",first->num);
	printf("\n");
}

listpt searchnum(listpt first,int num){
	if(first){
		for(;(first->num)!=num&&(first->link!=NULL);first=first->link)
			;
		if(first->num!=num)
			return NULL;		
		else
			return first;
	}
	else
		return NULL;
}

void delete1(listpt *first, int num){
	if(*first){
		listpt p=searchnum(*first,num);
		listpt temp=*first;
		if(p==NULL)
			return;
		else{
			if(p!=*first){
				for(;temp->link!=p;temp=temp->link)
					;
				delete(first,temp);
			}
			else
				delete(first,NULL);
		}
			
	}
	else{
		printf("empty list\n");
	}
}

int countlist(listpt first){
	int count=0;
	if(first){
		count=1;
		for(;first->link!=NULL;first=first->link,count++)
			;
		return count;
	}
	else{
		printf("empty list\n");
		return 0;
	}
}
void deletecross1(listpt *first){
	listpt p;
	for(p=*first;(p!=NULL) && p->link!=NULL;p=p->link)
		delete(first,p);
}

int main(int argc,char** argv)
{
	listpt p=createnode(150);
	listpt x;
	int i;

	for(i=0,x=p; i<10;i++){
		insert(&p,x,i*100);
		x=x->link;
	}
	printlist(p);

	printf("the number of elements in list is %d\n",countlist(p));
	delete1(&p,150);

	printlist(p);
	deletecross1(&p);
	printlist(p);
	return 0;
}
