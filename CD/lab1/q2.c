#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_preprocessor(char* str, char* result) {

	if(str[0] == '#') {
		strcpy(result, "");

	} else {
		strcpy(result, str);
	}

}

void read_file(char* PATH, char* OUTPUT_PATH) {

	FILE* fp = fopen(PATH, "r+");
	FILE* fp1 = fopen(OUTPUT_PATH, "w+");

	char* line = (char*) malloc(sizeof(char) * 200);
	size_t len = 0;

	int read;

	char* res = (char*) malloc(sizeof(char) * 200);

	while((read = getline(&line, &len, fp)) != -1) {

		remove_preprocessor(line, res);
		fputs(res, fp1);

	}

}

int main() {

	read_file("./q1.c", "./sample_output_q1.c");

	return 0;


}