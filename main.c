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
Vector *reservedwords;
void init_reservedwords(Vector *array);

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
	reservedwords = new_vector();
	init_reservedwords(reservedwords);
    tokenize();
    program();

    // output the first half of assembly 
	printf(".intel_syntax noprefix\n");

    // generate codes
    for(int i=0; code->data[i]; i++){
        gen(((Node *)(code->data[i])));
    }

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

Word *new_word(char *name, int len, int val)
{
	Word *word = malloc(sizeof(Word));
	word->name = name;
	word->len = len;
	word->val = val;
	return word;
}

void init_reservedwords(Vector *array)
{
	vec_push(array, new_word("\0", 0, 0));
	vec_push(array, new_word("return", 6, TK_RETURN));
	vec_push(array, new_word("while", 5, TK_WHILE));
	vec_push(array, new_word("else", 4, TK_ELS));
	vec_push(array, new_word("for", 3, TK_FOR));
	vec_push(array, new_word("if", 2, TK_IF));
}
