#include<stdio.h>
#include<ctype.h>
#include "token.c"
#include<string.h>

Token lookahead;
Table tb;
FILE *f;

void proc_e();

void proc_f()
{
	printf("in f\n");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(!strcmp(lookahead->lexeme,"("))
	{
		proc_e();
		//lookahead=getNextToken(f,&tb);
		printf("%s\n",lookahead->lexeme);
		if(!strcmp(lookahead->lexeme,")"))
			return;
		else
			printf("Error\n");
	}
	else if(!strcmp(lookahead->lexeme,"id"))
		return;
}

void proc_t1()
{
	printf("in t1\n");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(!strcmp(lookahead->lexeme,"*"))
	{
		proc_f();
		proc_t1();
	}
}

void proc_t()
{
	printf("in t\n");
	proc_f();
	proc_t1();
}

void proc_e1()
{
	printf("in e1\n");
	lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(!strcmp(lookahead->lexeme,"+"))
	{
		proc_t();
		proc_e1();
	}
}

void proc_e()
{
	printf("in e\n");
	proc_t();
	proc_e1();
}

int main()
{
	f=fopen("ip.txt","r");
	proc_e();
	//printf("Back to main");
	//lookahead=getNextToken(f,&tb);
	printf("%s\n",lookahead->lexeme);
	if(strcmp(lookahead->lexeme,"$")==0)
		printf("Successfull\n");
	else
		printf("Error3");
	return 0;
}