#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// value of token type
enum{
    TK_NUM = 256, // integer token
    TK_EOF,       // EOF token
};

// Token type
typedef struct{
    int ty;         // Token type
    int val;        // value of token if ty is TK_NUM
    char *input;    // Token strings for error message
}Token;

enum{
    ND_NUM = 256,
};

typedef struct Node{
    int ty;         // Token type
    struct Node *lhs;      // left-hand side node
    struct Node *rhs;      // right-hand side node
    int val;        // in case ty is ND_NUM only
}Node;

// program inputted
char *user_input;

// Token sequence
Token tokens[100];

int pos;

// declaration
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *expr();
int consume(int ty);
void gen(Node *node);

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

// break string up into tokens
void tokenize(){
    char *p = user_input;

    int i=0;
    while(*p){
        // skip space
        if(isspace(*p)){
            p++;
            continue;
        }

        if(*p == '+' || *p == '-'){
            tokens[i].ty = *p;
            tokens[i].input = p;
            i++;
            p++;
            continue;
        }

        if(isdigit(*p)){
            tokens[i].ty = TK_NUM;
            tokens[i].input = p;
            tokens[i].val = strtol(p, &p, 10);
            i++;
            continue;
        }

        error_at(p, "failed to tokenize");
    }

    tokens[i].ty = TK_EOF;
    tokens[i].input = p;
}

// tree
Node *new_node(int ty, Node *lhs, Node *rhs)
{
    Node *node = (Node *)(malloc(sizeof(Node)));
    node->ty = ty;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val)
{
    Node *node = (Node *)(malloc(sizeof(Node)));
    node->ty = ND_NUM;
    node->val = val;
    return node;
}

int consume(int ty)
{
    if(tokens[pos].ty != ty){
        return 0;
    }
    pos++;
    return 1;
}
Node *expr()
{
    Node *node = new_node_num(tokens[pos++].val);

    for(;;){
        if(consume('+')){
            node = new_node('+', node, expr());
        }else if(consume('-')){
            node = new_node('-', node, expr());
        }else{
            return node;
        }
    }
}

void gen(Node *node){
    if(node->ty == ND_NUM){
        printf("    push %d\n", node->val);
        return;
    }
    
    gen(node->lhs);
    gen(node->rhs);

    printf("    pop rdi\n");
    printf("    pop rax\n");

    switch(node->ty){
        case '+':
            printf("    add rax, rdi\n");
            break;
        case '-':
            printf("    sub rax, rdi\n");
            break;
    }

    printf("    push rax\n");
}

int main(int argc, char **argv){
	if(argc != 2){
		fprintf(stderr, "Invalid argument");
			return 1;
	}

    // tokenize
    user_input = argv[1];
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
