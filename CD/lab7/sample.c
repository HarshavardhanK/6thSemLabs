#include<stdio.h>
#include<ctype.h>
#include "token.c"
#include<string.h>

Token lookahead;
Table tb;
FILE *f;

void proc_t();
void proc_e()
{
	//lookahead=getNextToken(f,&tb);
	//printf("%s\n",lookahead->lexeme);
	if(strcmp(lookahead->lexeme,"NUMBER")==0)
	{
		//lookahead=getNextToken(f,&tb);
		//printf("%s\n",lookahead->lexeme);
		proc_t();
	}
	else
		printf("\nError0");
}

void proc_t()
{
	lookahead=getNextToken(f,&tb);
	//printf("%s\n",lookahead->lexeme);
	if(strcmp(lookahead->lexeme,"*")==0)
	{
		lookahead=getNextToken(f,&tb);
		//printf("%s\n",lookahead->lexeme);
		if(strcmp(lookahead->lexeme,"NUMBER")==0)
		{
			//lookahead=getNextToken(f,&tb);
			//printf("%s\n",lookahead->lexeme);
			proc_t();
		}
		else
			printf("\nError1");
	}
}

int main()
{
	f=fopen("ip.txt","r");
	lookahead=getNextToken(f,&tb);
	//printf("%s\n",lookahead->lexeme);
	proc_e();
	if(strcmp(lookahead->lexeme,"$")==0)
		printf("Successfull\n");
	else
		printf("Error2");
	return 0;
}