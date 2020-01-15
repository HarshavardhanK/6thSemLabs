#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct lexeme {

	int row;
	int col;
	char* name;

};

typedef struct lexeme Lex;

Lex create_lexeme(int row, int col, char* name) {

	Lex lex;
	lex.row = row;
	lex.col = col;

	lex.name = (char*) malloc(sizeof(char) * 10);

	strcpy(lex.name, name);

	return lex;
}

Lex check_keyword(char* str, char** KEYS, size_t KEY_LEN, int line_num) {

	int col = -1;

	for(int i = 0; i < KEY_LEN; i++) {

		char *pos = strstr(str, KEYS[i]);

		if(pos != NULL) {

			char* res = (char*) malloc(sizeof(char) * strlen(KEYS[i]));
			strupr(KEYS[i], res);

			printf("%s", res);

			col = pos - str + 4;

			printf("\tFound at line %d \tFound at col %d\n", line_num, col);

		}

	}

	Lex lex = create_lexeme(line_num, col, "KEYWORD");


	return lex;
}