// parse.c
#include "Ha4CC.h"

int pos;

Node *new_node_block()
{
	Node *node = (Node *)malloc(sizeof(Node));
	expect_token('{');
	node->ty = ND_BLOCK;
	node->stmts = new_vector();
	while(!consume('}')){
		vec_push((Vector *)(node->stmts), stmt());
	}
	return node;
}

Node *new_node_ident()
{
	char *varname = ((Token *)(tokens->data[pos++]))->name;
	Node *node = (Node *)(malloc(sizeof(Node)));
	if(consume('(')){
		node->ty = ND_FUNCCALL;
		node->funcname = varname;
		node->callargs = new_vector();
		if(!consume(')')){
			vec_push(node->callargs, (void *)expr());
			while(!consume(')')){
				consume(',');
				vec_push(node->callargs, (void *)expr());
			}
		}
	}else{
		node->ty = ND_LVAR;
		node->varname = varname;
	}
	return node;
}

Type *parse_type()
{
	Type *ret;
	if(consume(TK_INT)){
		ret = type_int();
		while(consume('*')){
			Type *tmp;
			tmp = ptr2type(ret);
			ret = tmp;
		}
		return ret;
	}
	return NULL;
}

Vector *parse_parameter_list()
{
	Vector *params = new_vector();
	if(!consume(')')){
		Type *ret = parse_type();
		if(ret == NULL){
			error("argument must have type specifier.");
		}
		char *argname = ((Token *)(tokens->data[pos++]))->name;
		Node *lvar = malloc(sizeof(Node));
		lvar->ty = ND_LVAR_DECL;
		lvar->type = ret;
		lvar->varname = argname;
		vec_push(params, lvar);
		while(!consume(')')){
			expect_token(',');
			Type *ret = parse_type();
			if(ret == NULL){
				error("argument must have type specifier.");
			}
			Node *lvar = malloc(sizeof(Node));
			argname = ((Token *)(tokens->data[pos++]))->name;
			lvar->ty = ND_LVAR_DECL;
			lvar->type = ret;
			lvar->varname = argname;
			vec_push(params, lvar);
		}
	}
	return params;
}

Node *parse_funcdef()
{
	Node *node = malloc(sizeof(Node));
	Type *ret = parse_type();
	if(ret == NULL) node->ret_type = type_int();
	else node->ret_type = ret;

	node->fname = expect_token(TK_IDENT)->name;
	node->ty = ND_FUNCDEF;
	expect_token('(');
	node->args = parse_parameter_list();
	node->defbody = new_node_block();
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

void program(Vector *asts)
{
    while(((Token *)(tokens->data[pos]))->ty!=TK_EOF){
        vec_push(asts, top_level());
    }
    vec_push(asts, NULL);
}

Node *top_level()
{
	Node *node = parse_funcdef();
	return node;
}

Node *stmt()
{
    Node *node;
    Token *t = tokens->data[pos];
	Type *type;
    switch(t->ty){
    case TK_IF:
    	node = malloc(sizeof(Node));
        pos++;
        node->ty = ND_IF;
        expect_token('(');
        node->cond = expr();
        expect_token(')');
        node->then = stmt();
        if(consume(TK_ELS)){
            node->els = stmt();
        }
        return node;
    case TK_FOR:
    	node = malloc(sizeof(Node));
        pos++;
        node->ty = ND_FOR;
        expect_token('(');
        if(!consume(';')){
            node->init = expr();
            expect_token(';');
        }
        if(!consume(';')){
            node->for_cond = expr();
            expect_token(';');
        }
        if(!consume(';')){
            node->iter = expr();
        }
        expect_token(')');
        node->body = stmt();
        return node;
    case TK_WHILE:
    	node = malloc(sizeof(Node));
        pos++;
        node->ty = ND_WHILE;
        expect_token('(');
        node->cond = expr();
        expect_token(')');
        node->then = stmt();
        node->els = NULL;
        return node;
    case TK_RETURN:
    	node = malloc(sizeof(Node));
        pos++;
        node->ty = ND_RETURN;
        node->lhs = expr();
        expect_token(';');
        return node;
	case '{':
		return new_node_block();
	case ';':
		pos++;
		node = malloc(sizeof(Node));
		node->ty = ND_EMPTY;
		return node;
    default:
	    type = parse_type();
	    node = malloc(sizeof(Node));
	    if(type != NULL){
	    	char *varname = ((Token *)(tokens->data[pos++]))->name;
	    	node->ty = ND_LVAR_DECL;
	    	node->type = type;
	    	node->varname = varname;
	    }else{
            node = expr();
	    }
            expect_token(';');
            return node;
    }
}

Node *expr()
{
    return assign();
}

Node *assign()
{
    Node *node = equality();
    if(consume('=')){
        node = new_node('=', node, assign());
    }
    return node;
}

Node *equality()
{
    Node *node = relational();

    while(1){
        if(consume(TK_EQ)){
            node = new_node(ND_EQ, node, relational());
        }else if(consume(TK_NE)){
            node = new_node(ND_NE, node, relational());
        }else{
            return node;
        }
    }
}

Node *relational()
{
    Node *node = add();
	int ND;

	while(1){
	    if(consume('<')){
			node = new_node('<', node, add());
	    }else if(consume('>')){
			node = new_node('>', node, add());
	    }else if(consume(TK_LE)){
			node = new_node(ND_LE, node, add());
	    }else if(consume(TK_GE)){
	        node = new_node(ND_GE, node, add());
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
	if(consume(TK_SIZEOF)){
		return new_node(ND_SIZEOF, unary(), (Node *)NULL);
	}else if(consume('+')){
        return term();
    }else if(consume('-')){
        return new_node('-', new_node_num(0), term());
    }else if(consume('&')){
		return new_node(ND_ADDR, unary(), (Node *)NULL);
	}else if(consume('*')){
		return new_node(ND_DEREF, unary(), (Node *)NULL);
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
    }else if(((Token *)(tokens->data[pos]))->ty == TK_IDENT){
		node = new_node_ident();
    }else{
        error_at(((Token *)(tokens->data[pos]))->input, 
                "unexpected token: expected a number");
    }
    return node;
}

Token *expect_token(int ty)
{
    Token *t = tokens->data[pos];
    if(!consume(ty)){
        error("%c (%d) expected, but got %c (%d)", ty, ty, t->ty, t->ty);
    }
	return t;
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
	// must push in order from the longest
	vec_push(array, new_word("return", 6, TK_RETURN));
	vec_push(array, new_word("sizeof", 6, TK_SIZEOF));
	vec_push(array, new_word("while", 5, TK_WHILE));
	vec_push(array, new_word("else", 4, TK_ELS));
	vec_push(array, new_word("for", 3, TK_FOR));
	vec_push(array, new_word("int", 3, TK_INT));
	vec_push(array, new_word("if", 2, TK_IF));
}
