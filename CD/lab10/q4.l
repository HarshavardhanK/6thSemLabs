%{
	int pc=0;
	int sc=0;
%}

%%

%%

printf fprintf(yyout, "write"); pc++;
scanf fprintf(yyout, "read"); sc++;

. ECHO

%%

int main() {

	yyin = fopen("a.c", "r");
	yyout = fopen("b.c", "w");

	yylex();
}