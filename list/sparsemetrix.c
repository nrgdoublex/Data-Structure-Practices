#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MALLOC(p,s) \
	if(!(p=malloc(s))){ \
		fprintf(stderr,"allocate error\n"); \
		exit(EXIT_FAILURE);\
	}

#define MAX_SIZE 50
typedef enum {head,entry} tag;
typedef struct matrixnode *matrixpt;
typedef struct{
	int row;
	int col;
	int value;
}entrynode;

typedef struct matrixnode{
	matrixpt down;
	matrixpt right;
	tag t;
	union{
		matrixpt next;
		entrynode entry;
	}u;
};

matrixpt hdnode[MAX_SIZE];

matrixpt newnode(){
	matrixpt p;
	MALLOC(p,sizeof(*p));
	return p;
}

matrixpt mread(){
	int numrow,numcol,numterm,numhead,i;
	int row,col,value,currentrow;
	matrixpt temp,last,node;

	printf("Enter the number of rows, columns and number of nonzero terms: ");
	scanf("%d %d %d",&numrow,&numcol,&numterm);
	numhead=(numrow>numcol)?numrow:numcol;
	node=newnode();node->t=entry;
	node->u.entry.row=numrow;
	node->u.entry.col=numcol;

	if(!numhead) node->right=node;
	else{
		for(i=0;i<numhead;i++){
			temp=newnode();
			hdnode[i]=temp;hdnode[i]->t=head;
			hdnode[i]->right=temp;hdnode[i]->u.next=temp;
		}
		currentrow=0;
		last=hdnode[0];
		for(i=0;i<numterm;i++){
			printf("Enter row,column and value:");
			scanf("%d %d %d",&row,&col,&value);
			if(row>currentrow){
				last->right=hdnode[currentrow];
				currentrow=row;
				last=hdnode[row];
			}
			MALLOC(temp,sizeof(*temp));
			temp->t=entry;temp->u.entry.row=row;
			temp->u.entry.col=col;temp->u.entry.value=value;
			last->right=temp;
			last=temp;
			hdnode[col]->u.next->down=temp;
			hdnode[col]->u.next=temp;
		}
		last->right=hdnode[currentrow];
		for(i=0;i<numcol;i++)
			hdnode[i]->u.next->down=hdnode[i];
		for(i=0;i<numhead-1;i++)
			hdnode[i]->u.next=hdnode[i+1];
		hdnode[numhead-1]->u.next=node;
		node->right=hdnode[0];
	}
	return node;
}

void mwrite(matrixpt node){
	int i;
	matrixpt temp;
	matrixpt head=node->right;
	printf("\nnumrows=%d,numcols=%d\n",node->u.entry.row,node->u.entry.col);
	printf("The matrix by row,column and value \n\n");
	for(i=0;i<(node->u.entry.row);i++){
		for(temp=head->right;temp!=head;temp=temp->right)
			printf("%5d %5d %5d\n",temp->u.entry.row,temp->u.entry.col,temp->u.entry.value);
		head=head->u.next;
	}
}

void merase(matrixpt *node){
	matrixpt x,y, head=(*node)->right;
	int i;

	for(i=0;i<(*node)->u.entry.row;i++){
		y=head->right;
		while(y!=head){
			x=y;y=y->right;free(x);
		}
		x=head;head=head->u.next;free(x);
	}
	y=head;
	while(y!=*node){
		x=y;y=y->u.next;free(x);
	}
	free(*node);*node=NULL;
}	

matrixpt madd(matrixpt a,matrixpt b){
	int numrow,numcol,numhead,i,currentrow;
	matrixpt node,temp,last;
	matrixpt head_a,temp_a;
	matrixpt head_b,temp_b;

	if(a->u.entry.row!=b->u.entry.row || a->u.entry.col!=b->u.entry.col){
		fprintf(stderr,"input matrices have different row or column numbers\n");
		exit(EXIT_FAILURE);
	}
	numrow=a->u.entry.row;numcol=a->u.entry.col;
	numhead=(numrow>numcol)?numrow:numcol;
	node=newnode();node->t=entry;
	node->u.entry.row=numrow;
	node->u.entry.col=numcol;

	if(!numhead)node->right=node;
	else{
		for(i=0;i<numhead;i++){
			temp=newnode();
			hdnode[i]=temp;hdnode[i]->t=head;
			hdnode[i]->right=temp;hdnode[i]->u.next=temp;
		}
		currentrow=0;
		last=hdnode[0];

		head_a=a->right;
		head_b=b->right;
		for(i=0;i<numrow;i++){
			currentrow=i;
			last=hdnode[i];

			temp_a=head_a->right;
			temp_b=head_b->right;
			while(temp_a!=head_a && temp_b!=head_b){
				MALLOC(temp,sizeof(*temp));
				if(temp_a->u.entry.col < temp_b->u.entry.col){
					temp->t=entry;
					temp->u.entry.row=temp_a->u.entry.row;
					temp->u.entry.col=temp_a->u.entry.col;
					temp->u.entry.value=temp_a->u.entry.value;
					temp_a=temp_a->right;
				}
				else if(temp_a->u.entry.col > temp_b->u.entry.col){
					temp->t=entry;
					temp->u.entry.row=temp_b->u.entry.row;
					temp->u.entry.col=temp_b->u.entry.col;
					temp->u.entry.value=temp_b->u.entry.value;
					temp_b=temp_b->right;
				}
				else{
					temp->t=entry;
					temp->u.entry.row=temp_b->u.entry.row;
					temp->u.entry.col=temp_b->u.entry.col;
					temp->u.entry.value=temp_a->u.entry.value+temp_b->u.entry.value;
					temp_a=temp_a->right;temp_b=temp_b->right;
				}
				last->right=temp;
				last=temp;
				hdnode[temp->u.entry.col]->u.next->down=temp;
				hdnode[temp->u.entry.col]->u.next=temp;
			}
			if(temp_a==head_a){
				while(temp_b!=head_b){
					MALLOC(temp,sizeof(*temp));
					temp->t=entry;
					temp->u.entry.row=temp_b->u.entry.row;
					temp->u.entry.col=temp_b->u.entry.col;
					temp->u.entry.value=temp_b->u.entry.value;
					temp_b=temp_b->right;
					last->right=temp;
					last=temp;
					hdnode[temp->u.entry.col]->u.next->down=temp;
					hdnode[temp->u.entry.col]->u.next=temp;
				}
			}
			else{
				while(temp_a!=head_a){
					MALLOC(temp,sizeof(*temp));
					temp->t=entry;
					temp->u.entry.row=temp_a->u.entry.row;
					temp->u.entry.col=temp_a->u.entry.col;
					temp->u.entry.value=temp_a->u.entry.value;
					temp_a=temp_a->right;
					last->right=temp;
					last=temp;
					hdnode[temp->u.entry.col]->u.next->down=temp;
					hdnode[temp->u.entry.col]->u.next=temp;
				}
			}
			last->right=hdnode[currentrow];
			head_a=head_a->u.next;
			head_b=head_b->u.next;
		}
		for(i=0;i<numcol;i++)
			hdnode[i]->u.next->down=hdnode[i];
		for(i=0;i<numhead-1;i++)
			hdnode[i]->u.next=hdnode[i+1];
		hdnode[numhead-1]->u.next=node;
		node->right=hdnode[0];
	}
	return node;
}

matrixpt mtranspose(matrixpt p){
	int numrow,numcol,numhead,i,currentrow;
	matrixpt node,temp,last;
	matrixpt head_p,temp_p;

        numrow=p->u.entry.col;numcol=p->u.entry.row;
        numhead=(numrow>numcol)?numrow:numcol;
        node=newnode();node->t=entry;
        node->u.entry.row=numrow;
        node->u.entry.col=numcol;

        if(!numhead)node->right=node;
        else{
		for(i=0;i<numhead;i++){
			temp=newnode();
			hdnode[i]=temp;hdnode[i]->t=head;
			hdnode[i]->right=temp;hdnode[i]->u.next=temp;
		}

		head_p=p->right;
		for(i=0;i<numrow;i++){
			currentrow=i;
			last=hdnode[i];
			
			temp_p=head_p->down;
			while(temp_p!=head_p){
				MALLOC(temp,sizeof(*temp));
				temp->t=entry;
				temp->u.entry.row=temp_p->u.entry.col;
				temp->u.entry.col=temp_p->u.entry.row;
				temp->u.entry.value=temp_p->u.entry.value;
				temp_p=temp_p->down;
				last->right=temp;
				last=temp;
				hdnode[temp->u.entry.col]->u.next->down=temp;
				hdnode[temp->u.entry.col]->u.next=temp;
			}
			last->right=hdnode[currentrow];
			head_p=head_p->u.next;
		}
		for(i=0;i<numcol;i++)
			hdnode[i]->u.next->down=hdnode[i];
		for(i=0;i<numhead-1;i++)
			hdnode[i]->u.next=hdnode[i+1];
		hdnode[numhead-1]->u.next=node;
		node->right=hdnode[0];

	}
	return node;
}
#define TRUE 1
#define FALSE 0
matrixpt mmult(matrixpt a,matrixpt b){
	int numrow,numcol,numhead,i,j,currentrow,value;
	matrixpt node,temp,last;
	matrixpt head_a,temp_a;
	matrixpt head_b,temp_b;

	if(a->u.entry.col!=b->u.entry.row){
		fprintf(stderr,"no. of columns of 1st matrix <> no. of rows of 2nd matrix\n");
		exit(EXIT_FAILURE);
	}
	numrow=a->u.entry.row;numcol=b->u.entry.col;
	numhead=(numrow>numcol)?numrow:numcol;
	node=newnode();node->t=entry;
	node->u.entry.row=numrow;
	node->u.entry.col=numcol;

	if(!numhead)node->right=node;
	else{
		for(i=0;i<numhead;i++){
			temp=newnode();
			hdnode[i]=temp;hdnode[i]->t=head;
			hdnode[i]->right=temp;hdnode[i]->u.next=temp;
		}
		currentrow=0;
		last=hdnode[0];

		head_a=a->right;
		head_b=b->right;
		for(i=0;i<numrow;i++){
			currentrow=i;
			last=hdnode[i];

			for(j=0;j<numcol;j++){	
				temp_a=head_a->right;
				temp_b=head_b->down;	
				int have_value=FALSE;
				while(temp_a!=head_a && temp_b!=head_b){
					if(temp_a->u.entry.col < temp_b->u.entry.row)
						temp_a=temp_a->right;
					else if(temp_a->u.entry.col > temp_b->u.entry.row)
						temp_b=temp_b->down;
					else{
						if(have_value==FALSE){
							value=(temp_a->u.entry.value)*(temp_b->u.entry.value);
							have_value=TRUE;
						}
						else
							value+=(temp_a->u.entry.value)*(temp_b->u.entry.value);
						temp_a=temp_a->right;
						temp_b=temp_b->down;
					}
				}
		
				if(have_value==TRUE){
					MALLOC(temp,sizeof(*temp));
					temp->t=entry;
					temp->u.entry.row=i;
					temp->u.entry.col=j;
					temp->u.entry.value=value;
					last->right=temp;
					last=temp;
					hdnode[temp->u.entry.col]->u.next->down=temp;
					hdnode[temp->u.entry.col]->u.next=temp;
				}
				head_b=head_b->u.next;
			}
			last->right=hdnode[currentrow];
			head_a=head_a->u.next;
			head_b=b->right;
		}
		for(i=0;i<numcol;i++)
			hdnode[i]->u.next->down=hdnode[i];
		for(i=0;i<numhead;i++)
			hdnode[i]->u.next=hdnode[i+1];
		hdnode[numhead-1]->u.next=node;
		node->right=hdnode[0];
	}
	return node;
}

int main(int argc,char **argv){
	matrixpt p;
	p=mread();
	mwrite(p);

	
//	mwrite(mtranspose(p));
	matrixpt q;
	q=mread();
	mwrite(q);
	
//	matrixpt r=madd(p,q);
	matrixpt r=mmult(p,q);
	mwrite(r);


//	merase(&p);
//	merase(&q);
//	merase(&r);
	return 0;
}
