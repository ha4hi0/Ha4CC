// parse.c
#include "Ha4CC.h"

int pos;

int is_alnum(char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           (c == '_');
}


Word *is_reservedword(char *key)
{
	for(int i=0; i<reservedwords->len; i++){
		if((strncmp(((Word *)(reservedwords->data[i]))->name, key, ((Word *)(reservedwords->data[i]))->len)==0)&&(!is_alnum(key[((Word *)(reservedwords->data[i]))->len]))){
			return (Word *)(reservedwords->data[i]);
		}
	}
	return NULL;
}

int is_oneletteroperator(char c)
{
	const char ops[] = {
        '+' ,'-' ,'*' ,'/' ,')' ,'(' ,'<' ,'>' ,'=', ';', '{', '}', ',', '&'
	};

	for(int i=0; i<sizeof(ops)/sizeof(char); i++){
		if(ops[i]==c)return 1;
	}
	return 0;
}

int is_twoletteroperator(char *c)
{
	const char *ops[] = {
		"==", "!=", "<=", ">="
	};

	int vals[] = {
		TK_EQ, TK_NE, TK_LE, TK_GE
	};

	for(int i=0; i<sizeof(vals)/sizeof(int); i++){
		if(!strncmp(c, ops[i], 2)){
			return vals[i];
		}
	}
	return 0;
}

// break string up into tokens
void tokenize(){
    char *p = user_input;

    while(*p){

        // skip space
        if(isspace(*p)){
            p++;
            continue;
        }

		Word *word=is_reservedword(p);
		if(word){
			Token *t = (Token *)malloc(sizeof(Token));
			t->ty = word->val;
			t->input = p;
			p+=word->len;
			vec_push(tokens, t);
			continue;
		}

		int val=is_twoletteroperator(p);
		if(val){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = val;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
		}

        if(is_oneletteroperator(*p)){
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
            continue;
        }

        if(is_alnum(*p)){
            int i=0;
            for(;is_alnum(*(p+i));i++);
            Token *t = malloc(sizeof(Token));
            t->ty = TK_IDENT;
            t->name = malloc(sizeof(char)*i);
            strncpy(t->name, p, i);
            t->name[i]='\0';
            t->input = p;
            vec_push(tokens,t);
            p+=i;
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

Node *new_node_if(Node *cond, Node *then, Node *els)
{
    Node *node = (Node *)(malloc(sizeof(Node)));
    node->ty = ND_IF;
    node->cond = cond;
    node->then = then;
    node->els = els;
    return node;
}

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
		node->args = new_vector();
		if(!consume(')')){
			vec_push(node->args, (void *)expr());
			while(!consume(')')){
				consume(',');
				vec_push(node->args, (void *)expr());
			}
		}
	}else{
		void* ret = map_get(local_var, varname);
		if(ret==NULL){
			error("%s is not defined.", varname);
		}
		node = (Node *)ret;
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

int consume(int ty)
{
    if(((Token *)(tokens->data[pos]))->ty != ty){
        return 0;
    }
    pos++;
    return 1;
}

void program()
{
    while(((Token *)(tokens->data[pos]))->ty!=TK_EOF){
		count_local_var = 0;
        vec_push(code, top_level());
    }
    vec_push(code, NULL);
}

Node *top_level()
{
	Node *node = (Node *)malloc(sizeof(Node));
	expect_token(TK_INT);
	expect_token(TK_IDENT);
	node->ty = ND_FUNCDEF;
	node->deffuncname = ((Token *)(tokens->data[pos-1]))->name;
	node->local_var = new_map();
	node->argname = new_vector();
	local_var = node->local_var;
	expect_token('(');
	if(!consume(')')){
		Type *ret = parse_type();
		if(ret == NULL){
			error("argument must have type specifier.");
		}
		char *argname = ((Token *)(tokens->data[pos++]))->name;
		//map_put(local_var, argname, (void *)((++count_local_var)*8));
		Node *lvar = malloc(sizeof(Node));
		lvar->ty = ND_LVAR;
		//lvar->offset = (++count_local_var)*8;
		count_local_var += ret->byte;
		lvar->offset = count_local_var;
		lvar->type = ret;
		map_put(local_var, argname, (void *)(lvar));
		vec_push(node->argname, argname);
		while(!consume(')')){
			expect_token(',');
			Type *tmpret = parse_type();
			if(ret == NULL){
				error("argument must have type specifier.");
			}
			Node *tmp = malloc(sizeof(Node));
			argname = ((Token *)(tokens->data[pos++]))->name;
			tmp->ty = ND_LVAR;
			//tmp->offset = (++count_local_var)*8;
			count_local_var += tmpret->byte;
			tmp->offset = count_local_var;
			tmp->type = tmpret;
			map_put(local_var, argname, (void *)(tmp));
			vec_push(node->argname, argname);
		}
	}
	node->defbody = new_node_block();
	return node;
}

Node *stmt()
{
    Node *node;
	Type *type = parse_type();
	//fprintf(stderr, "%d\n", type->ty);
	if(type != NULL){
		node = malloc(sizeof(Node));
		char *varname = ((Token *)(tokens->data[pos++]))->name;
		void* ret = map_get(local_var, varname);
		if(ret == (NULL)){
			node->ty = ND_LVAR;
			//node->offset = (++count_local_var)*8;
			count_local_var += type->byte;
			node->offset = count_local_var;
			node->type = type;
			map_put(local_var, varname, (void *)(node));
		}else{
			error_at(((Token *)(tokens->data[pos-1]))->input, "multiple definition");
		}
		expect_token(';');
		return stmt();
	}
    Token *t = tokens->data[pos];
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
    	node = malloc(sizeof(Node));
        node = expr();
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

    if(consume('+')){
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

void expect_token(int ty)
{
    Token *t = tokens->data[pos];
    if(!consume(ty)){
        error("%c (%d) expected, but got %c (%d)", ty, ty, t->ty, t->ty);
    }
}
