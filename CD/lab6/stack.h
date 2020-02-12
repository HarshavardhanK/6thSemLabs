#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdio.h>

struct stack_ {

	int top;

	int size;

	char* array;

};

typedef stack_ Stack;

Stack* create_stack(int size) {

	Stack* stack = (Stack*) malloc(sizeof(Stack));
	stack->array = (char*) malloc(sizeof(char) * size);

	stack->size = size;
	stack->top = -1;
	
	return stack;
}

int is_empty(Stack* stack) {

	if(stack->top == -1) {
		return 1;
	}

	return 0;
}

int is_full(Stack* stack) {

	if(stack->top == stack->size) {
		return 1;
	}

	return 0;
}

void push(Stack* stack, char terminal) {

	if(!is_empty(stack)) {
		stack->array[stack->top] = terminal;
	}

}

#endif