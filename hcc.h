#pragma once
#ifndef HCC_H
#define HCC_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// container.c
typedef struct{
    void **data;
    int capacity;
    int len;
}Vector;

typedef struct{
    Vector *keys;
    Vector *vals;
} Map;

Vector *new_vector();
void vec_push(Vector *vec, void *elem);
void expect(int line, int expected, int actual);
void runtest();
Map *new_map();
void map_put(Map *map, char *key, void *val);
void *map_get(Map *map, char *key);
int map_len(Map *map);


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
    TK_IF,
    TK_ELS,
    TK_FOR,
    TK_WHILE,
    TK_EOF,       // EOF token
	TK_INT,
};

// Token type
typedef struct{
    int ty;         // Token type
    int val;        // value of TK_NUM token
    char *name;     // name of TK_IDENT token
    char *input;    // Token strings for error message
}Token;

// value of node type
enum{
    ND_NUM = 256,
    ND_LVAR,        // Node type of local variables
    ND_RETURN,
    ND_EQ,
    ND_NE,
    ND_LE,
    ND_IF,
    ND_FOR,
    ND_WHILE,
	ND_BLOCK,
	ND_FUNCCALL,
	ND_FUNCDEF,
	ND_ADDR,
	ND_DEREF,
	ND_INT,
};

// Node type
typedef struct Node{
    int ty;         // Token type

    union{
		//ND_FUNCDEF
		struct{
			char *deffuncname;
			Vector *argname;
			Map *local_var;
			struct Node *defbody;
		};

        //ND_FOR
        struct{
            struct Node *init;
            struct Node *for_cond;
            struct Node *iter;
            struct Node *body;
        };

        //ND_WHILE
        //ND_IF
        struct{
            struct Node *cond;
            struct Node *then;
            struct Node *els;
        };

        struct{
            struct Node *lhs;
            struct Node *rhs;
        };

		//ND_FUNCCALL
		struct{
			char *funcname;
			Vector *args;
		};

		Vector *stmts;

        // ND_NUM
        int val;
    
        // ND_LVAR
        int offset;
    };
}Node;

// for reserved words
typedef struct{
	char *name;
	int len;
	int val;
}Word;


void tokenize();
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *new_node_if(Node *cond, Node *then, Node *els);
void program();
Node *top_level();
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
void expect_token(int ty);
extern Vector *reservedwords;

// codegen.c
void gen(Node *node);
void gen_lval(Node *node);
void gen_if(Node *node);
void gen_for(Node *node);
void gen_while(Node *node);
void gen_block(Node *node);
void gen_funccall(Node *node);
void gen_funcdef(Node *node);

// main.c
// program inputted
extern char *user_input;

// Token sequence
extern Vector *tokens;
extern Vector *code;
extern Map *local_var;

// position of token read
extern int pos;
extern int count_local_var;
extern int count_begin;
extern int count_else;
extern int count_end;

// declaration
void error_at(char *loc, char *msg);
void error(char *fmt, ...);

#endif
