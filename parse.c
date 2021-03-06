// parse.c
#include "Ha4CC.h"

TokenSeq *new_tokenseq(Vector *tokens)
{
	TokenSeq *ret = malloc(sizeof(TokenSeq));
	ret->tokens = tokens;
	ret->pos = 0;
	return ret;
}

char *consume_token_name(TokenSeq *seq)
{
	return ((Token *)(seq->tokens->data[seq->pos++]))->name;
}

Token *get_token(TokenSeq *seq)
{
	return (Token *)(seq->tokens->data[seq->pos]);
}

Token *next(TokenSeq *seq)
{
	return (Token *)(seq->tokens->data[seq->pos++]);
}

Node *new_node_block(TokenSeq *seq)
{
	Node *node = (Node *)malloc(sizeof(Node));
	expect_token('{', seq);
	node->ty = ND_BLOCK;
	node->stmts = new_vector();
	while(!consume('}', seq)){
		vec_push((Vector *)(node->stmts), stmt(seq));
	}
	return node;
}

Node *new_node_ident(TokenSeq *seq)
{
	char *varname = malloc(sizeof(char)*256);
	strcpy(varname, consume_token_name(seq));
	Node *node = (Node *)(malloc(sizeof(Node)));
	if(consume('(', seq)){
		node->ty = ND_FUNCCALL;
		node->funcname = varname;
		node->callargs = new_vector();
		if(!consume(')', seq)){
			vec_push(node->callargs, (void *)expr(seq));
			while(!consume(')', seq)){
				consume(',', seq);
				vec_push(node->callargs, (void *)expr(seq));
			}
		}
	}else{
		node->ty = ND_LVAR;
		node->varname = varname;
	}
	return node;
}

Type *parse_type(TokenSeq *seq)
{
	Type *ret=NULL;
	if(consume(TK_INT, seq)){
		ret = type_int();
	}else if(consume(TK_CHAR, seq)){
		ret = type_char();
	}else{
		return ret;
	}
	while(consume('*', seq)){
		Type *tmp;
		tmp = ptr2type(ret);
		ret = tmp;
	}
	return ret;
}

Vector *parse_parameter_list(TokenSeq *seq)
{
	Vector *params = new_vector();
	if(!consume(')', seq)){
		Type *ret = parse_type(seq);
		if(ret == NULL){
			error("argument must have type specifier.");
		}
		char *argname = malloc(sizeof(char)*256);
		strcpy(argname, consume_token_name(seq));
		Node *lvar = malloc(sizeof(Node));
		lvar->ty = ND_LVAR_DECL;
		lvar->type = ret;
		lvar->varname = argname;
		vec_push(params, lvar);
		while(!consume(')', seq)){
			expect_token(',', seq);
			Type *ret = parse_type(seq);
			if(ret == NULL){
				error("argument must have type specifier.");
			}
			Node *lvar = malloc(sizeof(Node));
			argname = consume_token_name(seq);
			lvar->ty = ND_LVAR_DECL;
			lvar->type = ret;
			lvar->varname = argname;
			vec_push(params, lvar);
		}
	}
	return params;
}

Node *parse_funcdef(TokenSeq *seq)
{
	Node *node = malloc(sizeof(Node));
	Type *ret = parse_type(seq);
	if(ret == NULL) node->ret_type = type_int();
	else node->ret_type = ret;

	node->fname = expect_token(TK_IDENT, seq)->name;
	node->ty = ND_FUNCDEF;
	expect_token('(', seq);
	node->args = parse_parameter_list(seq);
	node->defbody = new_node_block(seq);
	return node;
}

int consume(int ty, TokenSeq *seq)
{
    if(((Token *)(seq->tokens->data[seq->pos]))->ty != ty){
        return 0;
    }
    seq->pos++;
    return 1;
}

Vector *program(Vector *tokens)
{
	Vector *asts = new_vector();
	TokenSeq *seq = new_tokenseq(tokens);
    while(get_token(seq)->ty!=TK_EOF){
        vec_push(asts, top_level(seq));
    }
    vec_push(asts, NULL);
	return asts;
}

Node *top_level(TokenSeq *seq)
{
	Node *node = malloc(sizeof(Node));
	Type *ret = parse_type(seq);
	if(ret == NULL) ret = type_int();
	char *varname = expect_token(TK_IDENT, seq)->name;
	if(consume('(', seq)){
		node->fname = varname;
		node->ty = ND_FUNCDEF;
		node->args = parse_parameter_list(seq);
		node->ret_type = ret;
		node->defbody = new_node_block(seq);
	}else{
		node->varname = varname;
		node->ty = ND_GVAR_DECL;
		if(consume('[', seq)){
			int len=expect_token(TK_NUM, seq)->val;
			node->type = ary2type(ret, len);
			expect_token(']', seq);
		}else{
			node->type = ret;
		}
		expect_token(';', seq);
	}
	return node;
}

Node *parse_if_stmt(TokenSeq *seq)
{
	Node *ret = malloc(sizeof(Node));
	next(seq);
	ret->ty = ND_IF;
	ret->cond = NULL;
	ret->then = NULL;
	ret->els = NULL;
	expect_token('(', seq);
	ret->cond = expr(seq);
	expect_token(')', seq);
	ret->then = stmt(seq);
	if(consume(TK_ELS, seq)){
		ret->els = stmt(seq);
	}
	return ret;
}

Node *parse_for_stmt(TokenSeq *seq)
{
	Node *ret = malloc(sizeof(Node));
	next(seq);
	ret->ty = ND_FOR;
	ret->init = NULL;
	ret->for_cond = NULL;
	ret->iter = NULL;
	ret->body = NULL;
	expect_token('(', seq);
	if(!consume(';', seq)){
		Type *type = parse_type(seq);
		if(type != NULL){
			ret->init = parse_lvar_decl(seq, type);
		}else{
			ret->init = expr(seq);
		}
		expect_token(';', seq);
	}
	if(!consume(';', seq)){
		ret->for_cond = expr(seq);
		expect_token(';', seq);
	}
	if(!consume(')', seq)){
		ret->iter = expr(seq);
		expect_token(')', seq);
	}
	ret->body = stmt(seq);
	return ret;
}

Node *parse_lvar_decl(TokenSeq *seq, Type *type)
{
	Node *node = malloc(sizeof(Node));
	char *varname = malloc(sizeof(char)*256);
	strcpy(varname, consume_token_name(seq));
	int len_is_determined = 0;
	int len = 0;
	if(consume('[', seq)){
		Token *tk = next(seq);
		node->type = ary2type(type, len);
		if(tk->ty == TK_NUM){
			len=tk->val;
			len_is_determined = 1;
			expect_token(']', seq);
		}else{
			if(tk->ty != ']'){
				error_at(tk->input, "number is expected.");
			}
		}
	}else{
		node->type = type;
	}
	node->varname = varname;

	if(consume('=', seq)){
		node->ty = ND_LVAR_DECL_INIT;
		if(node->type->ty != TY_ARRAY){
			node->rhs_init = expr(seq);
		}else{
			node->rhs_init = parse_array_initializer(seq);
			if(!len_is_determined){
				len = node->rhs_init->array_init->len;
			}
		}
	}else{
		node->ty = ND_LVAR_DECL;
	}
	if(node->type->ty == TY_ARRAY){
		node->type->len = len;
	}
	return node;
}

Node *parse_array_initializer(TokenSeq *seq)
{
	Node *node = malloc(sizeof(Node));
	node->ty = ND_ARRAY_INITIALIZER;
	node->array_init = new_vector();
	Token *t = get_token(seq);
	if(consume('{', seq)){
		do{
			Node *tmp = malloc(sizeof(Node));
			tmp = expr(seq);
			vec_push(node->array_init, tmp);
		}while(consume(',', seq));
		expect_token('}', seq);
	}else if(consume(TK_STRING, seq)){
		for(int i=0; i<t->slen; i++){
			Node *tmp = new_node_num(t->sval[i]);
			vec_push(node->array_init, tmp);
		}
		return node;
	}
	return node;
}

Node *stmt(TokenSeq *seq)
{
    Node *node;
    Token *t = get_token(seq);
	Type *type;
    switch(t->ty){
    case TK_IF:
		return parse_if_stmt(seq);
    case TK_FOR:
        return parse_for_stmt(seq);
    case TK_WHILE:
    	node = malloc(sizeof(Node));
		next(seq);
        node->ty = ND_WHILE;
        expect_token('(', seq);
        node->cond = expr(seq);
        expect_token(')', seq);
        node->then = stmt(seq);
        node->els = NULL;
        return node;
    case TK_RETURN:
    	node = malloc(sizeof(Node));
		next(seq);
        node->ty = ND_RETURN;
        node->lhs = expr(seq);
        expect_token(';', seq);
        return node;
	case '{':
		return new_node_block(seq);
	case ';':
		next(seq);
		node = malloc(sizeof(Node));
		node->ty = ND_EMPTY;
		return node;
    default:
	    type = parse_type(seq);
	    if(type != NULL){
			node = parse_lvar_decl(seq, type);
	    }else{
            node = expr(seq);
	    }
        expect_token(';', seq);
        return node;
    }
}

Node *expr(TokenSeq *seq)
{
    return assign(seq);
}

Node *assign(TokenSeq *seq)
{
    Node *lnode = logical_or(seq);
    if(consume('=', seq)){
        lnode = new_node('=', lnode, assign(seq));
    }else if(consume(TK_ADD_EQ, seq)){
		Node *rnode = assign(seq);
		rnode = new_node('+', lnode, rnode);
		lnode = new_node('=', lnode, rnode);
    }else if(consume(TK_SUB_EQ, seq)){
		Node *rnode = assign(seq);
		rnode = new_node('-', lnode, rnode);
		lnode = new_node('=', lnode, rnode);
    }else if(consume(TK_MUL_EQ, seq)){
		Node *rnode = assign(seq);
		rnode = new_node('*', lnode, rnode);
		lnode = new_node('=', lnode, rnode);
    }else if(consume(TK_DIV_EQ, seq)){
		Node *rnode = assign(seq);
		rnode = new_node('/', lnode, rnode);
		lnode = new_node('=', lnode, rnode);
	}
    return lnode;
}

Node *logical_or(TokenSeq *seq)
{
	Node *node = logical_and(seq);

	while(1){
		if(consume(TK_LOG_OR, seq)){
			node = new_node(ND_LOG_OR, node, logical_and(seq));
		}else{
			return node;
		}
	}
}

Node *logical_and(TokenSeq *seq)
{
	Node *node = equality(seq);

	while(1){
		if(consume(TK_LOG_AND, seq)){
			node = new_node(ND_LOG_AND, node, equality(seq));
		}else{
			return node;
		}
	}
}

Node *equality(TokenSeq *seq)
{
    Node *node = relational(seq);

    while(1){
        if(consume(TK_EQ, seq)){
            node = new_node(ND_EQ, node, relational(seq));
        }else if(consume(TK_NE, seq)){
            node = new_node(ND_NE, node, relational(seq));
        }else{
            return node;
        }
    }
}

Node *relational(TokenSeq *seq)
{
    Node *node = add(seq);

	while(1){
	    if(consume('<', seq)){
			node = new_node('<', node, add(seq));
	    }else if(consume('>', seq)){
			node = new_node('>', node, add(seq));
	    }else if(consume(TK_LE, seq)){
			node = new_node(ND_LE, node, add(seq));
	    }else if(consume(TK_GE, seq)){
	        node = new_node(ND_GE, node, add(seq));
	    }else{
	        return node;
	    }
	}
}

Node *add(TokenSeq *seq)
{
    Node *node = mul(seq);

    for(;;){
        if(consume('+', seq)){
            node = new_node('+', node, mul(seq));
        }else if(consume('-', seq)){
            node = new_node('-', node, mul(seq));
        }else{
            return node;
        }
    }
}

Node *mul(TokenSeq *seq)
{
    Node *node = unary(seq);

    for(;;){
        if(consume('*', seq)){
            node = new_node('*', node, unary(seq));
        }else if(consume('/', seq)){
            node = new_node('/', node, unary(seq));
        }else if(consume('%', seq)){
			node = new_node('%', node, unary(seq));
		}else{
            return node;
        }
    }
}

Node *unary(TokenSeq *seq)
{
	if(consume(TK_SIZEOF, seq)){
		return new_node(ND_SIZEOF, unary(seq), (Node *)NULL);
	}else if(consume('+', seq)){
        return term(seq);
    }else if(consume('-', seq)){
        return new_node('-', new_node_num(0), term(seq));
    }else if(consume('&', seq)){
		return new_node(ND_ADDR, unary(seq), (Node *)NULL);
	}else if(consume('*', seq)){
		return new_node(ND_DEREF, unary(seq), (Node *)NULL);
	}else if(consume(TK_INC, seq)){
		return new_node(ND_PREINC, unary(seq), (Node *)NULL);
	}
    return term(seq);
}

Node *term(TokenSeq *seq)
{
    Node *node;

    if(consume('(', seq)){
        node = expr(seq);
        if(!consume(')', seq)){
            error_at(get_token(seq)->input, 
                    ") expected");
        }
    }else{
    	if(get_token(seq)->ty == TK_NUM){
			int a = next(seq)->val;
    	    node = new_node_num(a);
    	}else if(get_token(seq)->ty == TK_IDENT){
			node = new_node_ident(seq);
		}else if(get_token(seq)->ty == TK_STRING){
			node = malloc(sizeof(Node));
			node->ty = ND_STRING;
			node->sval = next(seq)->sval;
    	}
		else{
    	    error_at(get_token(seq)->input, 
    	            "unexpected token: expected a number");
    	}
		if(consume('[', seq)){
			node = new_node(ND_DEREF, new_node('+', expr(seq), node), (Node *)NULL);
			expect_token(']', seq);
		}
	}
	if(consume(TK_INC, seq)){
		node = new_node(ND_POSTINC, node, (Node *)NULL);
	}
    return node;
}

Token *expect_token(int ty, TokenSeq *seq)
{
    Token *t = seq->tokens->data[seq->pos];
    if(!consume(ty, seq)){
        error("%c (%d) expected, but got %c (%d)", ty, ty, t->ty, t->ty);
    }
	return t;
}
