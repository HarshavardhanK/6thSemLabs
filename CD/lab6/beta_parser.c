#include <stdio.h>

int S(char*, int*);
int T(char*, int*);
int T_(char*, int*);

int T_(char* buffer, int *iter) {

	if(buffer[*iter] == '$') {
		return 1;
	}


	if(buffer[*iter] == ',') {
		(*iter)++;

		if(S(buffer, iter)) {
			return T_(buffer, iter);
		}
	}
}

int T(char* buffer, int *iter) {

	if(S(buffer, iter)) {
		return T_(buffer, iter);
	}

	return 0;
}

int S(char* buffer, int *iter) {

	printf("%s | %d\n", buffer, *iter);

	if(buffer[*iter] == 'a' || buffer[*iter] == '>') {
		(*iter)++;
		
		if(buffer[*iter] == '$' && *iter == 1) {
			return 1;

		} else {
			return 1;
		}
	} 

	if(buffer[*iter] == ',') {
		return T_(buffer, iter);
	}

	if(buffer[*iter] == '(') {
		(*iter)++;

		return T(buffer, iter) && buffer[*iter] == ')';
	}

	return 0;

}

/*2. E -> TE'
	 E' -> +TE' | null
	 T -> FT'
	 T' -> *FT | null
*/

int T2(char*, int*);
int T_2(char*, int*);
int F(char*, int*);
int E_(char*, int*);
int E(char*, int*);
int F(char*, int*);

int T2_(char* buffer, int* iter) {

	if(buffer[*iter] == '*') {
		(*iter)++;

		if(F(buffer, iter)) {
			return T2(buffer, iter);
		}

	} else if(buffer[*iter] == '$') {
		return 1;
	}

	return 0;
}

int T2(char* buffer, int* iter) {

	if(F(buffer, iter)) {
		return T2_(buffer, iter);
	}

	return 0;
}

int E_(char* buffer, int *iter) {

	if(buffer[*iter] == '+') {
		(*iter)++;

		if(T2(buffer, iter)) {
			return E_(buffer, iter);
		}
	}

	if(buffer[*iter] == '$') {
		return 1;
	}

}

int E(char* buffer, int* iter) {

	if(T2(buffer, iter)) {
		return E_(buffer, iter);
	}

	return 0;
}

int F(char* buffer, int* iter) {

	if(buffer[*iter] == '(') {
		(*iter)++;

		if(buffer[*iter] == '$' && *iter) {
			return 1;
		}

		if(E_(buffer, iter)) {

			if(buffer[*iter] == ')') {
				return 1;
			}
		}

	} else if(buffer[*iter] == 'a') {
		return 1;
	}

	return 0;
}


int main(int argc, char** argv) {

	char buff[10];
	int iter;// = 0;
	//*iter = 0;

	printf("Enter string: ");

	scanf("%s", buff);

	if(F(buff, &iter)) {
		printf("Accepted\n");

	} else {
		printf("Not accepted\n");
	}

	return 0;
}