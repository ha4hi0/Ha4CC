#include "hcc.h"

char *user_input;
Vector *tokens;
int pos;

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "Invalid argument");
			return 1;
	}

    // tokenize
    user_input = argv[1];
    if(!strncmp(argv[1], "-test", 5)){
        runtest();
        return 0;
    }
    tokens = new_vector();
    tokenize();
    Node *node = expr();

    // output the first half of assembly 
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

    // generate codes
    gen(node);

    // return top of stack
    // result of calculation
    printf("    pop rax\n");
    printf("    ret\n");
    return 0;
}

// report error
void error(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    exit(1);
}

// report the place of errors
void error_at(char *loc, char *msg){
    int pos = loc - user_input;
    fprintf(stderr, "%s\n", user_input);
    fprintf(stderr, "%*s", pos, "");
    fprintf(stderr, "^ %s\n", msg);
    exit(1);
}

