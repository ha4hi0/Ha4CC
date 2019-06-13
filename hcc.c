#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// value of token type
enum{
    TK_NUM = 256, // integer token
    TK_EQ,        // EQual operator
    TK_NE,        // Not Equal operator
    TK_LE,        // Less than or Equal operator
    TK_GE,        // Grater than or Equal operator
    TK_EOF,       // EOF token
};

// Token type
typedef struct{
    int ty;         // Token type
    int val;        // value of token if ty is TK_NUM
    char *input;    // Token strings for error message
}Token;

// value of node type
enum{
    ND_NUM = 256,
};

// Node type
typedef struct Node{
    int ty;         // Token type
    struct Node *lhs;      // left-hand side node
    struct Node *rhs;      // right-hand side node
    int val;        // in case ty is ND_NUM only
}Node;

typedef struct{
    void **data;
    int capacity;
    int len;
}Vector;

// program inputted
char *user_input;

// Token sequence
Vector *tokens;

// position of token read
int pos;

// declaration
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *term();
int consume(int ty);
void gen(Node *node);
Vector *new_vector();
void vec_push(Vector *vec, void *elem);
void expect(int line, int expected, int actual);
void runtest();

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

        if(!strncmp(p, "==", 2)){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_EQ;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
        }

        if(!strncmp(p, "!=", 2)){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_NE;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
        }

        if(!strncmp(p, "<=", 2)){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_LE;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
        }
        
        if(!strncmp(p, ">=", 2)){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_GE;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
        }
        
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == ')' || *p == '(' || *p == '<' || *p == '>'){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = *p;
            t->input = p;
            vec_push(tokens, t);
            p++;
            continue;
        }

        if(isdigit(*p)){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_NUM;
            t->input = p;
            t->val = strtol(p, &p, 10);
            vec_push(tokens, t);
            i++;
            continue;
        }

        error_at(p, "failed to tokenize");
    }

    Token *t = (Token *)malloc(sizeof(Token));
    t->ty = TK_EOF;
    t->input = p;
    vec_push(tokens, t);
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
    if(((Token *)(tokens->data[pos]))->ty != ty){
        return 0;
    }
    pos++;
    return 1;
}

Node *expr()
{
    return equality();
}

Node *equality()
{
    Node *node = relational();

    while(1){
        if(consume(TK_EQ)){
            node = new_node(TK_EQ, node, relational());
        }else if(consume(TK_NE)){
            node = new_node(TK_NE, node, relational());
        }else{
            return node;
        }
    }
}

Node *relational()
{
    Node *node = add();

    while(1){
        if(consume('<')){
            node = new_node('<', node, add());
        }else if(consume('>')){
            node = new_node('<', add(), node);
        }else if(consume(TK_LE)){
            node = new_node(TK_LE, node, add());
        }else if(consume(TK_GE)){
            node = new_node(TK_LE, add(), node);
        }else{
            return node;
        }
    }
}

Node *add()
{
    Node *node = mul();

    for(;;){
        if(consume('+')){
            node = new_node('+', node, mul());
        }else if(consume('-')){
            node = new_node('-', node, mul());
        }else{
            return node;
        }
    }
}

Node *mul()
{
    Node *node = unary();

    for(;;){
        if(consume('*')){
            node = new_node('*', node, unary());
        }else if(consume('/')){
            node = new_node('/', node, unary());
        }else{
            return node;
        }
    }
}

Node *unary()
{
    if(consume('+')){
        return term();
    }else if(consume('-')){
        return new_node('-', new_node_num(0), term());
    }
    return term();
}

Node *term()
{
    Node *node;

    if(consume('(')){
        node = expr();
        if(!consume(')')){
            error_at(((Token *)(tokens->data[pos]))->input, 
                    ") expected");
        }
        return node;
    }

    if(((Token *)(tokens->data[pos]))->ty == TK_NUM){
        node = new_node_num(((Token *)(tokens->data[pos++]))->val);
    }else{
        error_at(((Token *)(tokens->data[pos]))->input, 
                "unexpected token: expected a number");
    }
    return node;
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
        case '*':
            printf("    imul rdi\n");
            break;
        case '/':
            printf("    cqo\n");
            printf("    idiv rdi\n");
            break;
        case '<':
            printf("    cmp rax, rdi\n");
            printf("    setl al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_LE:
            printf("    cmp rax, rdi\n");
            printf("    setle al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_EQ:
            printf("    cmp rax, rdi\n");
            printf("    sete al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_NE:
            printf("    cmp rax, rdi\n");
            printf("    setne al\n");
            printf("    movzb rax, al\n");
            break;
    }

    printf("    push rax\n");
}

// Vector
Vector *new_vector()
{
    Vector *vec = malloc(sizeof(Vector));
    vec->data = malloc(sizeof(void *)*16);
    vec->capacity = 16;
    vec->len = 0;
    return vec;
}

void vec_push(Vector *vec, void *elem)
{
    if(vec->capacity == vec->len){
        vec->capacity *= 2;
        vec->data = realloc(vec->data, sizeof(void *)*vec->capacity);
    }
    vec->data[vec->len++] = elem;
}

// test
void expect(int line, int expected, int actual)
{
    if(expected == actual){
        return;
    }
    fprintf(stderr, "%d: %d expected, but got %d\n", line, expected, actual);
    exit(1);
}

void runtest()
{
    Vector *vec = new_vector();
    expect(__LINE__, 0, vec->len);

    for(int i=0; i<100; i++){
        vec_push(vec, (void *)i);
    }

    expect(__LINE__, 100, vec->len);
    expect(__LINE__, 0, (long)vec->data[0]);
    expect(__LINE__, 50, (long)vec->data[50]);
    expect(__LINE__, 99, (long)vec->data[99]);

    printf("OK\n");
}

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
