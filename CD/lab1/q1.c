#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void condense(char* str, char* result) {

	int k = 0;

	int str_len = strlen(str);

	for(int i = 0; i < str_len - 1; i++) {

		if(str[i] == ' ' || str[i] == '\t') {
			result[k++] = ' ';

			int j = i + 1;

			while(j < str_len && str[j] == ' ' || str[j] == '\t') {
				j++;
			}

			i = j - 1;

		} else {
			result[k++] = str[i];
		}
	}

	result[k] = str[str_len - 1];

}

void read_file(char* PATH, char* OUTPUT_PATH) {

	FILE* fp = fopen(PATH, "r+");
	FILE* fp1 = fopen(OUTPUT_PATH, "w+");

	char* line = (char*) malloc(sizeof(char) * 200);
	size_t len = 0;

	int read;

	char* res = (char*) malloc(sizeof(char) * 200);

	while((read = getline(&line, &len, fp)) != -1) {

		condense(line, res);
		fputs(res, fp1);

	}

}

void try() {

	char* str = (char*) malloc(sizeof(char) * 100);
	strcpy(str, "hell      o         world   oo");

	printf("Initial str: %s\n", str);

	char* res = (char*) malloc(sizeof(char) * 100);

	condense(str, res);

	printf("%s\n", res);

}

#include <regex.h>

#define PI 100

int main() {

	read_file("./sample.txt", "./sample_output.txt");

	return 0;


}