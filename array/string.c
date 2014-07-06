#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void printcharfreq(char *input)
{
	int len =strlen(input);
	int nr[len];
	char ch[len];
	int i,j,count=0;

	for(i=0;i<len;i++){
		nr[i]=0;
		ch[len]=0;
	}

	for(i=0;i<len;i++){
		for(j=0;j<count && ch[j]!=input[i];j++)
			;
		if(j==count){
			ch[j]=input[i];
			count++;
		}
	}

	for(j=0;j<count;j++){
		for(i=0;i<len;i++){
			if(ch[j]==input[i]){
				nr[j]++;
			}
		}
	}
	for(j=0;j<count;j++)
		printf("The freq of char %c is %d\n",ch[j],nr[j]);
}	

char *strndel(char *input, int start,int length)
{
	int len = strlen(input);

	if(start>len || start+length > len){
		perror("invalid");
		exit(EXIT_FAILURE);
	}
	char *temp=malloc(sizeof(char)*(start+1));
	strncpy(temp,input,sizeof(char)*start);
	temp[start] = '\0';
	strcat(temp,&input[start+length]);
	return temp;
}

char *strdel(char *input,char a)
{
	int len=strlen(input);
	int i;
	for(i=0;i<len && input[i]!=a;i++)
		;
	if(i==len){
		perror("Not found");
		exit(EXIT_FAILURE);
	}
	char *temp=malloc(sizeof(char)*(i+1));
	strncpy(temp,input,i);
	temp[i]='\0';
	strcat(temp,&input[i+1]);
	return temp;
}

int strpos1(char *input,char a)
{
	int len = strlen(input);
	int i;
        for(i=0;i<len && input[i]!=a;i++)
                ;
        if(i==len){
                perror("Not found");
                return -1;
        }
	return i;
}

char* strchr1(char *input,char a)
{
	int len = strlen(input);
	int i;
        for(i=0;i<len && input[i]!=a;i++)
                ;
        if(i==len){
                perror("Not found");
                return NULL;
        }
	return &input[i];
}

char *strsearch(char *input,char *pat)
{
	int leninput = strlen(input);
	int lenpat = strlen(pat);
	if(leninput<lenpat){
		perror("pattern longer than string");
		exit(EXIT_FAILURE);
	}

	int i,j,k;
	
	for(i=0;i<leninput-lenpat;i++){
		for(j=0,k=i;j<lenpat && pat[j]== input[k];j++,k++)
			;
		if(j==lenpat)
			return &input[i];
	}
	return NULL;
}

int main(int argc,char** argv)
{
	char *a="sdaebaebaegkerkgjnc";
	
//	printcharfreq(a);

//	char *str=strndel(a,2,3);
//	char b='b';
//	char *nr=strchr1(a,b);
//	printf("Ths first occur address of %c is %p\n",b,(char *)nr);

	char *pat="cfg";
	char *addr;
	if((addr=strsearch(a,pat))!=NULL)
		printf("the match address is %p\n",addr);
	else
		printf("no matching\n");

	return 0;
}
