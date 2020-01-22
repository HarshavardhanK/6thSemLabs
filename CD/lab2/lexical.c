#include "recog.h"
#include "../includes/token_store.h"

void test_lex() {

	char** KEYS = KEYWORDS();
	FILE* fp = fopen("./recog.h", "r");

	char* line = (char*) malloc(sizeof(char) * 300);
	size_t len = 0;

	int read = 0;

	int line_num = 0;

	while((read = getline(&line, &len, fp)) != -1) {
		line_num++;
		Lex *lex = check_keyword(line, KEYS, 5, line_num);
		//print_lexeme(*lex);
		//insert_token();

		if(lex) {
			insert_token(lex);
		}

	}


}

void test_operators() {

	Lex** lex;// = is_operator

	FILE* fp = fopen("./recog.h", "r");

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

int main() {

	test_lex();
	//test_operators();

	//sort_tokens();
	//print_tokens();

	//

	printf("Reading alll tokens\n");
	read_token();

	return 0;
	
}