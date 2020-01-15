#include "recog.h"

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

		if(lex)
			print_lexeme(*lex);

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
        	
        	n = 0;

        } else {
        	buffer[n++] = c;
        }

    }


}

int main() {

	test_lex();

	test_operators();

	return 0;
	
}