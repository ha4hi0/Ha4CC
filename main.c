#include "hcc.h"

char *user_input;
Vector *tokens;
Vector *code;
int pos;
int count_local_var = 0;
int count_begin = 0;
int count_else = 0;
int count_end = 0;
Map *local_var;

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
    code = new_vector();
    tokens = new_vector();
    tokenize();
    program();

    // output the first half of assembly 
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");
	printf("main:\n");

    // prologue
    printf("    push rbp\n");
    printf("    mov rbp, rsp\n");
    printf("    sub rsp, %d*8\n", count_local_var);

    // generate codes
    for(int i=0; code->data[i]; i++){
        gen(((Node *)(code->data[i])));
        printf("    pop rax\n");
    }

    // return top of stack
    // result of calculation
    printf("    mov rsp, rbp\n");
    printf("    pop rbp\n");
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

