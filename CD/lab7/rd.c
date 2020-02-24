#include <stdio.h>

int program() {

	NODE* tok = get_next_token();

	if(strcmp(tok->type, "func") && strcmp(tok->name, "main") == 0) {

		tok = get_next_token();

		if(strcmp(tok->name, '(') == 0 && strcmp(get_next_token()->name, ')') == 0)
			return declarations();
	}

	return 0;
}

int declarations() {

	NODE* tok = get_next_token();

	if(strcmp(tok->type, "int") || strcmp(tok->type, "char")) {
		return identifier_list();
	}

	return 0;
}

int identifier_list() {

	NODE* tok = get_next_token();

	if(strcmp(tok->type, "id")) {
		return A_();
	}
}

int A_() {

	NODE* tok = get_next_token();

	if((tok->name, ",")) {
		return identifier_list();

	} else if(strcmp(tok->name, '[') == 0) {
		return B_();

		//else check for many other conditions...
	} else {
		return 0;
	}
}

int B_() {

	NODE* tok = get_next_token();

	if(strcmp(tok->name, ",") == 0) {
		return identifier_list();

		//check for other else cases
	} else {
		return 1; //implicit semi-colon case
	}

}