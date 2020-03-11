#include<stdio.h>
#include<ctype.h>
#include "token.c"
#include<string.h>

Token lookahead;
Table tb;
FILE *f;

void proc_t();

void proc_s()
{
	printf("In s\n");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(!strcmp(lookahead->lexeme,"a"))
		return;
	if(!strcmp(lookahead->lexeme,">"))
		return;
	if(!strcmp(lookahead->lexeme,"("))
	{
		proc_t();
		if(!strcmp(lookahead->lexeme,")"))
			return;
		else
			printf("Error2\n");
	}
	printf("Error4\n");
}

void proc_t1()
{
	printf("In t1\n");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(!strcmp(lookahead->lexeme,","))
	{
		proc_s();
		proc_t1();
	}
}

void proc_t()
{
	printf("In t\n");
	proc_s();
	proc_t1();
}

int main()
{
	f=fopen("ip.txt","r");
	proc_s();
	//printf("Back to main");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(strcmp(lookahead->lexeme,"$")==0)
		printf("Successfull\n");
	else
		printf("Error3");
	return 0;
}