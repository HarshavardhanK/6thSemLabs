

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../includes/token.h"

char** KEYWORDS() {

	char** KEYS = (char**) malloc(5 * sizeof(char*));

	for(int i = 0; i < 4; i++) {
		KEYS[i] = (char*) malloc(sizeof(char) * 10);
	} 

	strcpy(KEYS[0], "Int");
	strcpy(KEYS[1], "class");
	strcpy(KEYS[2], "String");
	strcpy(KEYS[3], "concat");

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

		if(buffer[i] == '<') {

			if(buffer[i + 1] == '-') {
				lex[k++] = create_lexeme(line_num, offset, "OP", "<-");

			} 

		}

		if(buffer[i] == ':') {
			create_lexeme(line_num, offset, "OP", ":");
		}

		if(buffer[i] == '.') {
			create_lexeme(line_num, offset, "OP", ".");

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

			//printf("%s\n", key_name);

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

void print_buffer(char* buff, int size) {

	for(int i = 0; i < size; i++) {
		printf("%c", buff[i]);
	}
}

int has_function(char* buffer, int size) {

	int is_function = 0;

	int start = -1;
	int end = -1;

	print_buffer(buffer, size);

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
		args++;
	}

	if(start != -1 && end != -1) {

		for(int i = start; i < end; i++) {
			if(buffer[i] == ',') {
				args++;
			}
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

		STE entry = create_entry("func", name, 0, args, return_type);

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

	int type_index; //ONLY DECLARATION IS CONSIDERED IN THIS APPROACH

	//TODO: SEARCH THE SYMBOL TABLE FOR THE IDENTIFIER
	print_buffer(buffer, size);

	for(int i = 0; i < size; i++) {

		//printf("%c", buffer[i]);

		if(isalpha(buffer[i])) {

			type_index = i;
			break;
		}
	}

	char identifier[20]; int identifier_index = 0;
	char type[10]; int type_name_index = 0;

	//Get the return type of the variable. Return type index begins at 0 of the buffer, and
	// goes till space_index
	for(int i = type_index; buffer[i] != ' '; i++) {
		if(buffer[i] != '\n' && buffer[i] != '\t' && buffer[i] != ' ')
			type[type_name_index++] = buffer[i];
	}

	type[type_name_index] = '\0';
	int variable_name_begin = strlen(type) + type_index + 1;

	for(int i = variable_name_begin; buffer[i] != ';'; i++) {
		identifier[identifier_index++] = buffer[i];
	}

	identifier[identifier_index] = '\0';

	STE entry = create_entry("identifier", identifier, 4, 0, type);
	print_entry(entry);

	//printf("Type: %s\n", type);

	//printf("\nType: %s | identifier name: %s\n", type, identifier);
}

//#include "recog.h"
#include "../includes/token_store.h"

void test_lex() {

	char** KEYS = KEYWORDS();
	FILE* fp = fopen("./input2.cpp", "r");

	//printf("Work\n");

	char* line = (char*) malloc(sizeof(char) * 300);
	size_t len = 0;

	int read = 0;

	int line_num = 0;

	while((read = getline(&line, &len, fp)) != -1) {
		line_num++;
		Lex *lex = check_keyword(line, KEYS, 4, line_num);
		//print_lexeme(*lex);
		//insert_token();

		if(lex) {
			insert_token(lex);
		}

	}


}

void test_operators() {

	Lex** lex;// = is_operator

	FILE* fp = fopen("./input2.cpp", "r");

	//printf("Work\n");

	int n = 0;
	char c;

	char* buffer = (char*) malloc(sizeof(char) * 200);

	int line = 0;

	while ((c = fgetc(fp)) != EOF) {

        if(c == '\n') {

        	line++;
        	lex = is_operator(buffer, line, n);
			is_special(buffer, line, n);
			check_string_literals(buffer, line, n);
        	
        	n = 0;

        } else {
        	buffer[n++] = c;
        }

    }


}

void remove_comments(char* str, char* result) {


	for(int i = 0; i < strlen(str); i++) {

		if(str[i] == '-' && str[i + 1] == '-') {
			strcpy(result, "");
			return;
		}
	}

	strcpy(result, str);

}

void _comments(char* PATH, char* OUTPUT_PATH) {

	FILE* fp = fopen(PATH, "r");
	FILE* fp1 = fopen(OUTPUT_PATH, "w");

	char* line = (char*) malloc(sizeof(char) * 200);
	size_t len = 0;

	int read;

	char* res = (char*) malloc(sizeof(char) * 200);

	while((read = getline(&line, &len, fp)) != -1) {

		remove_comments(line, res);
		fputs(res, fp1);

	}

	fclose(fp);
	fclose(fp1);

}


int main() {

	_comments("./input.cpp", "./input2.cpp");

	printf("\nKEYWORDS\n\n");

	test_lex();

	printf("\nOPERATORS\n\n");

	test_operators();
	
	//test_func();

	return 0;
	
}