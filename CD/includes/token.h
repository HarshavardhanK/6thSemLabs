#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "definitions"

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

Lex* TOKEN_ARRAY[250];
int TOKEN_ARRAY_INDEX = 0;

Lex* create_lexeme(int row, int col, char* name, char* item) {

	Lex* lex = (Lex*) malloc(sizeof(Lex));

	lex->row = row;
	lex->col = col;

	lex->item_name = (char*) malloc(sizeof(char) * 10);
	lex->name = (char*) malloc(sizeof(char) * 10);

	strcpy(lex->name, name);
	strcpy(lex->item_name, item);

	//lex->_token_type =

	return lex;
}

Lex* make_lex() {

    Lex* lex = (Lex*) malloc(sizeof(Lex));
    lex->item_name = (char*) malloc(sizeof(char) * 10);
	lex->name = (char*) malloc(sizeof(char) * 10);

    return lex;
}

int compare_func(const void* tokenA, const void* tokenB) {

    Lex* _tokenA = (Lex*) tokenA;
    Lex* _tokenB = (Lex*) tokenB;

    if(_tokenA->row == _tokenB->row) {
        return _tokenA->col - _tokenB->col;

    } else {
        return _tokenA->row - _tokenB->row;
    }
}

void sort_tokens() {
    qsort(TOKEN_ARRAY, TOKEN_ARRAY_INDEX, sizeof(Lex*), compare_func);
}

void print_tokens() {

    for(int i = 0; i < TOKEN_ARRAY_INDEX; i++) {
        print_lexeme(*TOKEN_ARRAY[i]);
    }
}

#endif