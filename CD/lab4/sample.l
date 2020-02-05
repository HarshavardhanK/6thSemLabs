%{
	int lines = 0;
%}

%%

\n {lines++;}
%%

int main(int argc, char** argv) {
	yylex();
	printf("\nLines are: %d\n", lines);
}

int yywrap() {
	return 1;
}