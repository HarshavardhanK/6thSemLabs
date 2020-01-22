#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMBER_OF_KEYWORDS 32
#define NUMBER_OF_OPERATORS 
#define NUMBER_OF_TOKEN_NAMES 13

struct token_type {

    int IDENTIFIER = 0;
    int KEYWORD = 1;

    int STRING_LITERAL = 2;

    int REL_OP = 3;
    int LOG_OP = 4;

    int RIGHT_PARENTHESES = 5;
    int LEFT_PARENTHESES = 6;

    int RIGHT_BRACKET = 7;
    int LEFT_BRACKET = 8;

    int RIGHT_SQUARE_BRACKET = 9;
    int LEFT_SQUARE_BRAKET = 10;

    int SYMBOL_HASH = 11;
    int SYMBOL_SEMICOLON = 12;

} TOKEN_TYPE;

struct token {

    struct token_type _token_type;
    char* _token_name;
};

const char* TOKEN_NAMES[NUMBER_OF_TOKEN_NAMES] = { 
    "IDENTIFIER", "KEYWORD", "STRING_LITERAL", 
    "RELOP", "LOGOP", "RP", "LP",
    "RB", "LB", "RSB", "LSB", "SS", "SS" 
};

const char* KEYWORDS[NUMBER_OF_KEYWORDS] = {
	"void", 	"int",		"char",		"float",	"double",	"long",		"short",	"switch",	
	"case",		"enum",		"register",	"break",	"typedef",	"main",		"return",	"union",	
	"continue",	"for",		"signed",	"auto",		"do",		"if",		"else",		"while",	
	"default",	"goto",		"sizeof",	"volatile",	"const",	"float",	"static",	"unsigned"
};

//extern const char* OPERATORS[] 

#endif