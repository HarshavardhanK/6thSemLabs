#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen("content.txt", "r");
	if (fp == NULL)
	    exit(0);

	int flag = 0;

	printf("HI\n");

	while ((read = getline(&line, &len, fp)) != -1) {

		if(!strcmp("<TEXT>\n", line))
	    	flag = 1;
	    else if(!strcmp("</TEXT>\n", line))
	    	flag = 0;
	    else if(flag==1)
	    	printf("%s", line);
	}

    fclose(fp);
    if (line)
        free(line);
    exit(1);
}