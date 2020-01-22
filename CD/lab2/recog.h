
#ifndef RECOG_H
#define RECOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct lexeme {

	int row;
	int col;
	char* name;
	char* item_name;

};

typedef struct lexeme Lex;

void print_lexeme(Lex lex) {

	printf("<%s, %d, %d, %s>\n", lex.item_name, lex.row, lex.col, lex.name);
}

Lex* create_lexeme(int row, int col, char* name, char* item) {

	Lex* lex = (Lex*) malloc(sizeof(Lex));

	lex->row = row;
	lex->col = col;

	lex->item_name = (char*) malloc(sizeof(char) * 10);
	lex->name = (char*) malloc(sizeof(char) * 10);

	strcpy(lex->name, name);
	strcpy(lex->item_name, item);

	print_lexeme(*lex);

	return lex;
}

char** KEYWORDS() {

	char** KEYS = (char**) malloc(5 * sizeof(char*));

	for(int i = 0; i < 6; i++) {
		KEYS[i] = (char*) malloc(sizeof(char) * 10);
	} 

	strcpy(KEYS[0], "int");
	strcpy(KEYS[1], "main");
	strcpy(KEYS[2], "for");
	strcpy(KEYS[3], "return");
	strcpy(KEYS[4], "if");
	strcpy(KEYS[5], "char");

	return KEYS;

}

Lex** is_operator(char* buffer, int line_num, int size) {

	Lex** lex = (Lex**) malloc(sizeof(Lex*) * 20);

	for(int i = 0; i < 20; i++) {
		lex[i] = NULL;
	}

	int k = 0;

	int offset = 0;
	int start = 0;

	for(int i = 0; i < size; i++) {

		offset++;

		if(buffer[i] == '=') {

			if(buffer[i + 1] == '=') {
				lex[k++] = create_lexeme(line_num, offset, "ARITHMETIC OPERATOR", "==");


			} else {
				lex[k++] = create_lexeme(line_num, offset, "ASSIGNMENT OPERATOR", "=");
			}

		}

		if(buffer[i] == '<') {

			if(buffer[i + 1] == '=') {
				create_lexeme(line_num, offset, "RELATIONAL OPERATOR", "<=");

			} else {
				create_lexeme(line_num, offset, "RELATIONAL OPERATOR", "<");				
			}
		}

		if(buffer[i] == '>') {

			if(buffer[i + 1] == '=') {
				create_lexeme(line_num, offset, "RELATIONAL OPERATOR", "<=");

			} else {
				create_lexeme(line_num, offset, "RELATIONAL OPERATOR", "<");				
			}
		}

		if(buffer[i] == '!') {

			if(buffer[i + 1] != '=' && isalnum(buffer[i + 1]))
				create_lexeme(line_num, offset, "LOGICAL OPERATOR", "!");

			else 
				create_lexeme(line_num, offset, "RELATIONAL OPERATOR", "!=");

		}

	}

	return lex;

}

Lex** is_special(char* buffer, int line_num, int size) {

	Lex** lex = (Lex**) malloc(sizeof(Lex*) * 20);

	for(int i = 0; i < 20; i++) {
		lex[i] = NULL;
	}

	int k = 0;

	int offset = 0;
	int start = 0;

	for(int i = 0; i < size; i++) {

		offset++;

		if(buffer[i] == ';') {
			create_lexeme(line_num, offset, "SPECIAL", ";");
		}

		if(buffer[i] == ')') {
			create_lexeme(line_num, offset, "RB", ")");
		}

		if(buffer[i] == '(') {
			create_lexeme(line_num, offset, "LB", "(");
		}

		if(buffer[i] == '{') {
			create_lexeme(line_num, offset, "LC", "{");
		}

		if(buffer[i] == '}') {
			create_lexeme(line_num, offset, "RC", "}");
		}

		if(buffer[i] == '[') {
			create_lexeme(line_num, offset, "LP", "[");
		}

		if(buffer[i] == ']') {
			create_lexeme(line_num, offset, "RP", "]");
		}

	}

	return lex;

}

Lex* check_keyword(char* str, char** KEYS, size_t KEY_LEN, int line_num) {

	int col = -1;
	char* key_name = (char*) malloc(sizeof(char) * 10);

	Lex *lex;

	for(int i = 0; i < KEY_LEN; i++) {

		char *pos = strstr(str, KEYS[i]);

		if(pos != NULL) {

			char* res = (char*) malloc(sizeof(char) * strlen(KEYS[i]));

			strcpy(key_name, KEYS[i]);

			col = pos - str + 4;

		}

	}

	if(col != -1)
		lex = create_lexeme(line_num, col, "KEYWORD", key_name);

	else
		return NULL;

	return lex;
}

void find_indices_of(char* buffer, int size, int* indices, char item, int *length_indices) {

	int k = 0;

	for(int i = 0; i < size; i++) {

		if(buffer[i] == item) {
			indices[k++] = i;
		}

	}
	
	*length_indices = k;
}

void check_string_literals(char* buffer, int line, int size) {

	int* indices = (int*) malloc(sizeof(int) * 10);
	int num_indices;

	find_indices_of(buffer, size, indices, '"', &num_indices);

	for(int i = 0; i < num_indices - 1; i++) {
		char str[100];
		int k = 0;

		for(int j = indices[i] + 1; j < indices[i + 1]; j++) {
			str[k++] = buffer[j];
		}

		create_lexeme(line, indices[i], "LITERAL", str);
	}
}

#endif