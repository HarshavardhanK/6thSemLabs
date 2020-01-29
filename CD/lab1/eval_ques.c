
#include <stdio.h>
#include <stdlib.h>

/* This is
a program*/

#include <math.h>

int prime(int n) {

	int i;

	//This uses math function
	//for(i = 0; i < sqrt(n); i++) {
		if(n % i == 0 && i <= n) {
			return 0;
		}
	}

	return 1;
}

int main() {

	int n, i;

	int x[10];

	printf("Enter a number:");
	scanf("%d", &n);

	/*
	Call and display whether prime or not */

	for(int i = 0; i < n; i++) {
		if(prime(x[i]))
			printf("Yes\n");
		else
			printf("not\n");
	}

	return 0;
}