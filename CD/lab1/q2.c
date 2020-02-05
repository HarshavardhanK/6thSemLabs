#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_preprocessor(char* str, char* result) {

	for(int i = 0; i < strlen(str); i++) {
		//printf("%c", str[i]);
		if(str[i] == '#') {
			strcpy(result, "");
			return;
		}

		//strcpy(result, "");
	}

	strcpy(result, str);

}

void remove_comments(char* str, char* result) {


	for(int i = 0; i < strlen(str); i++) {

		if(str[i] == '/' || str[i] == '/') {
			strcpy(result, "");
			return;
		}
	}

	strcpy(result, str);

}


void remove_pre(char* PATH, char* OUTPUT_PATH) {

	FILE* fp = fopen(PATH, "r");
	FILE* fp1 = fopen(OUTPUT_PATH, "w");

	char* line = (char*) malloc(sizeof(char) * 200);
	size_t len = 0;

	int read;

	char* res = (char*) malloc(sizeof(char) * 200);

	while((read = getline(&line, &len, fp)) != -1) {

		remove_preprocessor(line, res);
		//remove_comments(line, res);
		fputs(res, fp1);

	}

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

}

int main() {

	_comments("./eval_ques.c", "../eval.c");
	remove_pre("../eval.c", "../eval2.c");
	

	return 0;


}