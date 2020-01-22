
#ifndef RECOG_H
#define RECOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../includes/token.h"

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

	//print_lexeme(*lex);

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

#include "../lab3/symbol_table.h"

int has_function(char* buffer, int size) {

	int is_function = 0;

	int start = -1;
	int end = -1;

	for(int i = 0; i < size; i++) {

		if(buffer[i] == '(') {
			start = i;				
		}

		if(buffer[i] == ')') {
			end = i;
		}
	}

	//No. of arguments
	int args = 0;

	if(start != -1 && end != -1) {

		for(int i = start; i < end; i++) {
			if(buffer[i] == ',') {
				args++;
			}
		}

		if(!args) {

		} else {

			args++;
			//printf("Args: %d\n", args);

		}

		int name_begin = start;

		//Back track to the space character before the function name

		while(buffer[name_begin] != ' ') {
			name_begin--;
		}

		name_begin++;

		char name[20]; int name_index = 0;

		for(int i = name_begin; i < start; i++) {
			name[name_index++] = buffer[i];
		}

		//Append null character to the end of the char array

		name[name_index] = '\0';

		//printf("Function name: %s\n", name);

		//Find the return type of the function
		//Go back to the beginning of the buffer, and read till the nearest space

		int return_type_index = 0;
		char return_type[10];

		for(; buffer[return_type_index] != ' '; return_type_index++) {
			return_type[return_type_index] = buffer[return_type_index];
		}

		return_type[return_type_index] = '\0';

		//printf("Return type: %s\n", return_type);

		//TODO: 1. CHECK IF RETURN TYPE IS VALID KEYWORD FROM THE LIST OF KEYWORDS
		//TODO: 2. Get the names of the identifiers in arguments (Go between the commas)

		STE entry = create_entry("", name, 0, args, return_type);

		//mark is_function variable true to indicate the buffer had a function
		//return that  value from the function. If it weren't a function
		// the control would not have reached till here and is_function would be still 0
		is_function = 1;

		print_entry(entry);

	} 

	return is_function;
}

//LOGIC: If a buffer (holding all values of the read string till the semi-colon) is not a function
//then the statement (along with the KEYWORD) must be an identifier;

int is_variable(char* buffer, int size) {

	for(int i = 0; i < size; i++) {
		printf("%c", buffer[i]);
	}
	int space_index; //ONLY DECLARATION IS CONSIDERED IN THIS APPROACH

	//TODO: SEARCH THE SYMBOL TABLE FOR THE IDENTIFIER

	for(int i = 0; i < size; i++) {

		if(buffer[i] == ' ') {
			space_index = i;
			break;
		}
	}

	char identifier[20]; int identifier_index = 0;
	char type[10];

	//Get the return type of the variable. Return type index begins at 0 of the buffer, and
	// goes till space_index
	for(int i = 1; i < space_index; i++) {
		type[i] = buffer[i];
	}

	for(int i = space_index; i < size; i++) {
		identifier[identifier_index++] = buffer[i];
	}

	printf("\nType: %s\tName: %s\n", type, identifier);
}

#endif