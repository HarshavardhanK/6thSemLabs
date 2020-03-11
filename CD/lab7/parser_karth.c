#include<stdio.h>
#include<string.h>
#include"token.c"

Token l;
FILE *f;
Table tb[27];

void dec();
void statement_list();
void d_type();
void id_list();

void prog()
{
	printf("IN prog\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,"main"))
	{
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(!strcmp(l->lexeme,"("))
		{
			l=getNextToken(f,tb);
			printf("%s\n",l->lexeme);
			if(!strcmp(l->lexeme,")"))
			{
				l=getNextToken(f,tb);
				printf("%s\n",l->lexeme);
				if(!strcmp(l->lexeme,"{"))
				{	
					dec();
					statement_list();
					l=getNextToken(f,tb);
					printf("%s\n",l->lexeme);
					if(!strcmp(l->lexeme,"}"))
						return;
					printf("Error\n");
				}
				else printf("Error\n");
			}
			else printf("Error\n");
		}
		else printf("Error\n");
	}
	else printf("Error\n");
}

void dec()
{
	printf("IN dec\n");
	printf("%s\n",l->lexeme);
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,"int") || !strcmp(l->lexeme,"char"))
	{
		d_type();
		id_list();
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
	    if(!strcmp(l->lexeme,";"))
			dec();
		return;
	}
	printf("OK\n");
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
}

void d_type()
{
	printf("IN dtype\n");
	if(l->type==KEYWORD)
		return;
	printf("Error");
}

void id_list2()
{
	printf("IN id_list2\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,","))
		id_list();
	else fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
}

void id_list1()
{
	printf("IN id_list1\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,"["))
	{
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(l->type==NUMBERICAL_CONSTANT)
		{
			l=getNextToken(f,tb);
			printf("%s\n",l->lexeme);
			if(!strcmp(l->lexeme,"]"))
				id_list2();
			else printf("Error");
		}
		else printf("Error");
	}
	else
	{
		fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
		id_list2();
	}
}

void id_list()
{
	printf("IN id_list\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(l->type==IDENTIFIER)
		id_list1();
	else printf("Error\n");
}

void relop()
{
	printf("In relop\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(l->type!=RELATIONAL_OPERATOR)
		printf("Error\n");	
}

void addop()
{
	printf("IN addop\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(strcmp(l->lexeme,"+") && strcmp(l->lexeme,"-"))
		printf("Error\n");
}

void mulop()
{
	printf("In mulop\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(strcmp(l->lexeme,"/") && strcmp(l->lexeme,"%") && strcmp(l->lexeme,"*"))
		printf("Error\n");
}

void factor()
{
	printf("In factor\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!(l->type==IDENTIFIER || l->type==NUMBERICAL_CONSTANT))
		printf("Error\n");
}

void tprime()
{
	printf("In tprime\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
	if(!strcmp(l->lexeme,"/") || !strcmp(l->lexeme,"%") || !strcmp(l->lexeme,"*"))
	{
		mulop();
		factor();
		tprime();
	}
}

void term()
{
	printf("In term\n");
	factor();
	tprime();
}

void seprime()
{
	printf("IN seprime\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
	if(!strcmp(l->lexeme,"+") || !strcmp(l->lexeme,"-"))
	{
		addop();
		term();
		seprime();
	}
}

void simple_expn()
{
	printf("IN simple_expn\n");
	term();
	seprime();
}

void eprime()
{
	printf("IN eprime\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
	if(l->type==RELATIONAL_OPERATOR)
	{
		relop();
		simple_expn();
	}
}

void expn()
{
	printf("IN expn\n");
	simple_expn();
	eprime();
}

void assign_stat()
{
	printf("IN assign_stat\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(l->type==IDENTIFIER)
	{
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(!strcmp(l->lexeme,"="))
			expn();
		else
			printf("Error");
	}
}

void dprime()
{
	printf("In dprime\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,"else"))
	{
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(!strcmp(l->lexeme,"{"))
			statement_list();
		else
		{
			printf("Error\n");
			return;
		}
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(strcmp(l->lexeme,"}"))
			printf("Error\n");
	}
	else
		fseek(f,-1*strlen(l->lexeme),SEEK_CUR);		
}

void decision_stat()
{
	printf("In decision_stat\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(!strcmp(l->lexeme,"if"))
	{
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(!strcmp(l->lexeme,"("))
			expn();
		else
		{
			printf("Error\n");
			return;
		}
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(!strcmp(l->lexeme,")"))
		{
			l=getNextToken(f,tb);
			printf("%s\n",l->lexeme);
			if(!strcmp(l->lexeme,"{"))
				statement_list();
			else
			{
				printf("Error\n");
				return;
			}
			l=getNextToken(f,tb);
			printf("%s\n",l->lexeme);
			if(!strcmp(l->lexeme,"}"))
				dprime();
			else
				printf("Error\n");
		}
		else printf("Error\n");
	}
	else printf("Error\n");
}

void statement()
{
	printf("IN statement\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
	if(l->type==IDENTIFIER)
	{
		assign_stat();
		l=getNextToken(f,tb);
		printf("%s\n",l->lexeme);
		if(strcmp(l->lexeme,";"))
		printf("Error\n");
	}
	else if(!strcmp(l->lexeme,"if"))
		decision_stat();
	//else
	//	looping_stat();
}

void statement_list()
{
	printf("IN statement_list\n");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	fseek(f,-1*strlen(l->lexeme),SEEK_CUR);
	if(l->type==IDENTIFIER || !strcmp(l->lexeme,"if"))// || !strcmp(l->lexeme,"while") || !strcmp(l->lexeme,"for"))
	{
		statement();
		statement_list();
	}
}

int main()
{
	l=malloc(sizeof(struct TOKEN));
	for(int i=0;i<27;i++)
		tb[i]=(Table)malloc(sizeof(struct TABLE));
	f=fopen("ip.txt","r");
	prog();
	printf("IN main\n");
	//printf("Back to main");
	l=getNextToken(f,tb);
	printf("%s\n",l->lexeme);
	if(strcmp(l->lexeme,"$")==0)
		printf("Successfull\n");
	else
		printf("Error");
	return 0;
}