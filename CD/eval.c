
#include <stdio.h>
#include <stdlib.h>


#include <math.h>

int prime(int n) {

	int i;

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


	for(int i = 0; i < n; i++) {
		if(prime(x[i]))
			printf("Yes\n");
		else
			printf("not\n");
	}

	return 0;
}