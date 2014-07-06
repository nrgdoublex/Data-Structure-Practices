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
	nodept link;
};

nodept getnode(int data){
	nodept p;
	MALLOC(p,sizeof(*p));
	p->data=data;
	p->link=NULL;
	return p;
}

int insert(nodept pre, nodept insert){
	nodept rear;
	if(!insert || !pre){
		fprintf(stderr,"inserted node is invalid\n");
		exit(EXIT_FAILURE);
	}
	else{
		rear=pre->link;
		pre->link=insert;
		insert->link=rear;
	}
	return 0;
}

int delete(nodept pre){
	nodept temp,rear;

	if(!pre){
		fprintf(stderr,"inserted node is invalid\n");
		exit(EXIT_FAILURE);
	}
	if(!pre->link)
		return 0;
	temp=pre->link;
	rear=temp->link;
	pre->link=rear;
	free(temp);
	return 0;
}

nodept createadjlist(int num){
	nodept p;
	int i;

	MALLOC(p,sizeof(*p)*num);
	for(i=0;i<num;i++){
		p[i].data=-1;
		p[i].link=NULL;
	}
	return p;
}

int releasenode(nodept p){
	if(!p){
		fprintf(stderr,"invalid node to release\n");
		return 0;
	}
	free(p);
	return 0;
}

void printlist(nodept p,int num){
	int i;
	if(!p){
		fprintf(stderr,"invalid list to print\n");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<num;i++){
		nodept start=&p[i];
		while((start=start->link)!=NULL){
			printf("the vertex %d is connected to vertex %d\n",i,start->data);
		}
	}
}

int creategraph(nodept *p){
	int num_v, num_e;

	printf("Please enter number of vertices and edges\n");
	if(scanf("%d %d",&num_v,&num_e)!=2){
		printf("Please enter correct format\n");
		return 0;
	}

	int head, tail;
	nodept list=createadjlist(num_v);
	nodept temp;
	while(num_e>0){
		printf("Please enter the edge, 1st number is the head vertex and 2nd one is tail\n");
		scanf("%d %d",&head,&tail);

		if(head >= num_v || tail >= num_v){
			printf("the number your key in is invalid, please enter again\n");
			continue;
		}

		temp=&list[head];
		while(temp->link!=NULL)
			temp=temp->link;
		nodept rear=getnode(tail);
		insert(temp,rear);

		temp=&list[tail];
		while(temp->link!=NULL)
			temp=temp->link;
		rear=getnode(head);
		insert(temp,rear);

		num_e--;
	}
	*p=list;
	return num_v;
}

void dfs(int vertex,nodept p,int num,int *visited){
	nodept w;
	int i;
	if(vertex>=num){
		fprintf(stderr,"no vertex in the graph\n");
		exit(EXIT_FAILURE);
	}

	visited[vertex]=TRUE;
	printf("the vertex visited is %d\n",vertex);
	for(w=&p[vertex];w;w=w->link){
		if(!visited[w->data])
			dfs(w->data,p,num,visited);
	}
}

int main(int argc,char** argv)
{
	nodept list;
	int i;
	int num=creategraph(&list);

	printlist(list,num);

	int visited[num];
	for(i=0;i<num;i++)
		visited[i]=FALSE;

	dfs(0,list,num,visited);

	return 0;
}
