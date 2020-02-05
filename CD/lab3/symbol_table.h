#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "../includes/token.h"

struct symbol_table_entry {

	char type[10];

	char name[100];

	int size;
	int args;

	char return_type[10];

};


typedef struct symbol_table_entry STE;

STE table[20];

STE create_entry(char type[10], char name[100], int size, int args, char ret_type[10]) {

	STE entry;

	strcpy(entry.name, name);
	strcpy(entry.return_type, ret_type);
	strcpy(entry.type, type);

	entry.size = size;
	entry.args = args;

	return entry;
}

void print_entry(STE entry) {
	printf("%s\t%s\t%d\t%d\t%s\n", entry.type, entry.name, entry.args, entry.size, entry.return_type);
}


#endif