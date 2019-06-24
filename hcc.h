#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// parse.c
// value of token type
enum{
    TK_NUM = 256, // integer token
    TK_IDENT,     // identifier
    TK_RETURN,
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
    ND_LVAR,        // Node type of local variables
    ND_RETURN,
};

// Node type
typedef struct Node{
    int ty;         // Token type
    struct Node *lhs;      // left-hand side node
    struct Node *rhs;      // right-hand side node
    int val;        // in case ty is ND_NUM only
    int offset;     // in case ty is ND_LVAR only
}Node;

void tokenize();
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
void program();
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *term();
int consume(int ty);

// codegen.c
void gen(Node *node);
void gen_lval(Node *node);


// container.c
typedef struct{
    void **data;
    int capacity;
    int len;
}Vector;

Vector *new_vector();
void vec_push(Vector *vec, void *elem);
void expect(int line, int expected, int actual);
void runtest();

// main.c
// program inputted
extern char *user_input;

// Token sequence
extern Vector *tokens;
extern Vector *code;

// position of token read
extern int pos;

// declaration
void error_at(char *loc, char *msg);
void error(char *fmt, ...);
