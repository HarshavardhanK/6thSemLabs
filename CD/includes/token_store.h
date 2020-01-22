#ifndef TOKEN_STORE_H
#define TOKEN_STORE_H

#define FILENAME "./token_store.bin"

#include "token.h"

int INSERT_INDEX = 0;

void insert_token(Lex* token) {

    FILE* file = NULL;
    
    if((file = fopen(FILENAME, "wb+")) != NULL) {

        fseek(file, INSERT_INDEX * sizeof(Lex), SEEK_SET);
        //print_lexeme(*token);
        fwrite(token, sizeof(Lex), 1, file);

        INSERT_INDEX++;

    }

    fclose(file);
}


int GET_INDEX = 0;

 Lex* read_token() {

    FILE* file;// = fopen(FILENAME, "rb");

    if((file = fopen(FILENAME, "rb")) != NULL) {

        Lex* lex;// = make_lex();

        //fseek(file, GET_INDEX * sizeof(Lex), SEEK_SET);
        fread(lex, sizeof(Lex), 1, file);

        print_lexeme(*lex);

        GET_INDEX++;

        fclose(file);

        return lex;

    } 

    return NULL;

    
}


#endif
