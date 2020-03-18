#pragma once
#ifndef Ha4CC_H
#define Ha4CC_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DOKO(int i); // for debugging

typedef struct Scope Scope;

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

char *user_input;
Vector *tokens;
int count_begin;
int count_else;
int count_end;

Vector *new_vector();
void *vec_push(Vector *vec, void *elem);
void *vec_set(Vector *vec, int idx, void *elem);
void *vec_erase(Vector *vec, int idx);
void expect(int line, int expected, int actual);
void runtest();
Map *new_map();
void map_put(Map *map, const char *key, void *val);
void *map_get(Map *map, const char *key);
int map_len(Map *map);

// tokenize.c
Vector *reservedwords;
void init_reservedwords(Vector *array);
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
	TK_SIZEOF,
};

// Token type
typedef struct{
    int ty;         // Token type
	union{
    	int val;        // value of TK_NUM token
    	char *name;     // name of TK_IDENT token
	};
    char *input;    // Token strings for error message
}Token;


// for reserved words
typedef struct{
	char *name;
	int len;
	int val;
}Word;

Vector* tokenize();

// parse.c
// value of node type
enum{
    ND_NUM = 256,
    ND_LVAR,        // Node type of local variables
	ND_LVAR_DECL,
	ND_GVAR,
	ND_GVAR_DECL,
    ND_RETURN,
    ND_EQ,
    ND_NE,
    ND_LE,
	ND_GE,
    ND_IF,
    ND_FOR,
    ND_WHILE,
	ND_BLOCK,
	ND_FUNCCALL,
	ND_FUNCDEF,
	ND_ADDR,
	ND_DEREF,
	ND_EMPTY,
	ND_SIZEOF,
	ND_ARY2PTR,
};

enum TY{
	TY_INT,
	TY_PTR,
	TY_ARRAY,
};

typedef struct Type{
	enum TY ty;
	int byte;
	union{
		struct Type *ptr_to;

		struct{
			struct Type *ary_to;
			int len;
		};
	};
}Type;

// Node type
typedef struct Node Node;
struct Node{
    int ty;         // Node type
	Type *type;     // type of return value (!= ty)
	Scope *env;

    union{
		//ND_FUNCDEF
		struct{
			char *fname;
			Vector *args;
			Map *local_var; // unnecessary
			Type *ret_type;
			Node *defbody;
		};

        //ND_FOR
        struct{
            Node *init;
            Node *for_cond;
            Node *iter;
            Node *body;
        };

        //ND_WHILE
        //ND_IF
        struct{
            Node *cond;
            Node *then;
            Node *els;
        };

        struct{
            Node *lhs;
            Node *rhs;
        };

		//ND_FUNCCALL
		struct{
			char *funcname;
			Vector *callargs;
		};

        // ND_LVAR
		// ND_GVAR
		struct{
			char *varname;
        	int offset;
		};

		Vector *stmts;

		Node *ary; // ND_ARY2PTR

        // ND_NUM
        int val;
    };
};

typedef struct{
	Vector *tokens;
	int pos;
} TokenSeq;

TokenSeq *new_tokenseq(Vector *tokens);
char *get_token_name(TokenSeq *seq);

Vector *program(Vector *tokens);
Node *top_level(TokenSeq *seq);
Node *stmt(TokenSeq *seq);
Node *expr(TokenSeq *seq);
Node *assign(TokenSeq *seq);
Node *equality(TokenSeq *seq);
Node *relational(TokenSeq *seq);
Node *add(TokenSeq *seq);
Node *mul(TokenSeq *seq);
Node *unary(TokenSeq *seq);
Node *term(TokenSeq *seq);
int consume(int ty, TokenSeq *seq);
Token* expect_token(int ty, TokenSeq *seq);
Node *new_node_ident(TokenSeq *seq);
Vector *parse_parameter_list(TokenSeq *seq);
Node *parse_funcdef(TokenSeq *seq);
Type *parse_type(TokenSeq *seq);
Node *new_node_block(TokenSeq *seq);

// node.c
Node *new_node(int ty, Node *lhs, Node *rhs);
Node *new_node_num(int val);
Node *new_node_if(Node *cond, Node *then, Node *els);
Node *new_node_lvar_decl(Type *type, char *name);
Node *ary2ptr(Node *node);

// codegen.c
void gen(Node *node);
void gen_if(Node *node);
void gen_for(Node *node);
void gen_while(Node *node);
void gen_block(Node *node);
void gen_funccall(Node *node);
void gen_funcdef(Node *node);
void start_gen(Vector *asts);

// analyze.c
Vector *analyze(Vector *code);
Node *analyze_detail(Scope *env, Node *node);
Type *type_int();
Type *ptr2type(Type *type);
Type *ary2type(Type *type, int len);
int match_type(Node *node, enum TY ty);
int match_type2(Node *lhs, Node *rhs, enum TY lty, enum TY rty);

// scope.c
struct Scope{
	struct Scope *parent;
	Map *symbols;
	//Vector *local_vars;
	int stack_idx;
	int *max_idx;
};

Scope *new_scope(Scope *parent);
Node *get_symbol(Scope *env, const char *name);
Node *get_var(Scope *env, const char *name);
Node *get_func(Scope *env, const char *name);
Node *add_symbol(Scope *env, const char *name, Node *node);
Node *add_var(Scope *env, Node *node);
Node *add_func(Scope *env, Node *node);

// main.c
// program inputted
extern char *user_input;

// position of token read
extern int count_begin;
extern int count_else;
extern int count_end;

// declaration
void error_at(char *loc, char *msg);
void error(char *fmt, ...);

#endif
