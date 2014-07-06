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

typedef struct polynode *polypt;
typedef struct polynode{
	int coef;
	int expo;
	polypt link;
};

polypt avail;	//available free polynode;

polypt getnode(){
	polypt p;
	if(avail){
		p=avail;
		avail=avail->link;
	}
	else
		MALLOC(p,sizeof(*p));
	return p;
}

void retnode(polypt p){
	p->link=avail;
	avail=p;
}

polypt initpoly(){
	polypt node;
	node=getnode();
	node->link=node;
	node->expo=-1;
	node->coef=0;
	return node;
}

polypt insertterm(polypt start,int coef,int expo){
	polypt node;
	node=getnode();
	node->coef=coef;
	node->expo=expo;
	node->link=start->link;
	start->link=node;
	return node;
}

void polyread(polypt p){
	int coef, expo;
	polypt temp=p,temp_front;	
	while(printf("please enter coef. and expo. of each term :\n") && \
		scanf("%d,%d",&coef,&expo)==2){
		if(p->link==p)
			insertterm(p,coef,expo);
		else{
			for(temp=p;(temp->link!=p)&&(temp->expo<expo);temp_front=temp,temp=temp->link)
				;
			if(temp->expo==expo)
				temp->coef+=coef;
			else if(temp->link==p && temp->expo<expo)
				insertterm(temp,coef,expo);
			else if(temp->link)
				insertterm(temp_front,coef,expo);
		}
	}
}

int polywrite(polypt input){
	polypt temp;
	if(!input){
		fprintf(stderr,"No poly node\n");
		return -1;
	}
	else if(input->link==input){
		fprintf(stderr,"It is zero poly.\n");
		return 0;
	}
	else{
		temp=input->link;
		printf("The polynomial is : ");
		for(;temp!=input;temp=temp->link){
			if(temp->coef<0 && temp->expo<0)
				printf("(%d)x^(%d)",temp->coef,temp->expo);	
			else if(temp->coef<0 && temp->expo>=0)
				printf("(%d)x^%d",temp->coef,temp->expo);
			else if(temp->coef>0 && temp->expo<0)
				printf("%dx^(%d)",temp->coef,temp->expo);
			else
				printf("%dx^%d",temp->coef,temp->expo);
			if(temp->link!=input)
				printf("+");
		}
		printf("\n");
		return 0;
	}
}

polypt padd(polypt a,polypt b){
	polypt a1=a->link,b1=b->link;
	polypt ret=initpoly();
	polypt temp=ret;

	if(!a || !b){
		fprintf(stderr,"invalid input poly\n");
		exit(EXIT_FAILURE);
	}

	while(a1!=a && b1!=b){
		if(a1->expo < b1->expo){
			insertterm(temp,a1->coef,a1->expo);
			a1=a1->link;
		}
		else if(a1->expo > b1->expo){
			insertterm(temp,b1->coef,b1->expo);
			b1=b1->link;
		}
		else{
			insertterm(temp,a1->coef+b1->coef,a1->expo);
			a1=a1->link;b1=b1->link;	
		}
		temp=temp->link;
	}
	if(a1==a){
		for(;b1!=b;b1=b1->link){
			insertterm(temp,b1->coef,b1->expo);
			temp=temp->link;
		}
	}
	else if(b1==b){
		for(;a1!=a;a1=a1->link){
			insertterm(temp,a1->coef,a1->expo);
			temp=temp->link;
		}
	}
	return ret;
}

polypt psub(polypt a,polypt b){
	polypt a1=a->link,b1=b->link;
	polypt ret=initpoly();
	polypt temp=ret;

	if(!a || !b){
		fprintf(stderr,"invalid input poly\n");
		exit(EXIT_FAILURE);
	}

	while(a1!=a && b1!=b){
		if(a1->expo < b1->expo){
			insertterm(temp,a1->coef,a1->expo);
			a1=a1->link;
		}
		else if(a1->expo > b1->expo){
			insertterm(temp,-(b1->coef),b1->expo);
			b1=b1->link;
		}
		else{
			insertterm(temp,(a1->coef)-(b1->coef),a1->expo);
			a1=a1->link;b1=b1->link;	
		}
		temp=temp->link;
	}
	if(a1==a){
		for(;b1!=b;b1=b1->link){
			insertterm(temp,-(b1->coef),b1->expo);
			temp=temp->link;
		}
	}
	else if(b1==b){
		for(;a1!=a;a1=a1->link){
			insertterm(temp,a1->coef,a1->expo);
			temp=temp->link;
		}
	}
	return ret;
}

void perase(polypt p){
	polypt temp;
	if(!p){
		fprintf(stderr,"zero poly\n");
		exit(EXIT_FAILURE);
	}
	for(temp=p;temp->link!=p;temp=temp->link)
		;
	temp->link=avail;
	avail=p;
}

int power(int base,int expo){
	int i,val=1;
	for(i=expo;i>0;i--)
		val*=base;
	return val;
}

int eval(polypt p,int x){
	polypt temp;	
	int val=0;
	if(!p){
		fprintf(stderr,"zero poly\n");
		exit(EXIT_FAILURE);
	}
	for(temp=p->link;temp!=p;temp=temp->link)
		val+=(temp->coef)*power(x,temp->expo);
	return val;
}

polypt pmult(polypt a, polypt b){
	polypt a1,b1;
	polypt ret=initpoly();
	polypt temp,temp_front;
	int coef,expo;

	if(!a || !b){
		fprintf(stderr,"invalid poly\n");
		exit(EXIT_FAILURE);
	}
	else if(a->link==a || b->link==b)
		return ret;

	for(a1=a->link;a1!=a;a1=a1->link){
		temp=ret->link;temp_front=temp;
		for(b1=b->link;b1!=b;b1=b1->link){
			coef=(a1->coef)*(b1->coef);
			expo=a1->expo+b1->expo;
			if(ret->link==ret){
				insertterm(ret,coef,expo);
			}
			else{
				for(;(temp->link!=ret)&&(temp->expo<expo);temp_front=temp,temp=temp->link)
					;
				if(temp->link==ret&&temp->expo<expo){
					insertterm(temp,coef,expo);
					temp_front=temp;temp=temp->link;
				}
				else if(temp->link==ret&&temp->expo>expo){
					insertterm(temp_front,coef,expo);
					temp_front=temp_front->link;
				}
				else if(temp->expo==expo)
					temp->coef+=coef;
				else{
					insertterm(temp_front,coef,expo);
					temp_front=temp_front->link;
				}
			}	
		}
	}
	return ret;
}

int main(int argc,char** argv)
{
	polypt a=initpoly();
	polyread(a);
	polywrite(a);

	char temp[100];
	scanf("%s",temp);

//	perase(a);
	polypt b=initpoly();
	polyread(b);
	polywrite(b);

	polypt mul=pmult(a,b);
	polywrite(mul);
	
//	printf("Please x value\n");
//	int val;
//	scanf("%d",&val);
//	printf("the eval of x in your poly is %d\n",eval(a,val));

	return 0;
}
