// parse.c
#include "hcc.h"

int is_alnum(char c)
{
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           (c == '_');
}

// break string up into tokens
void tokenize(){
    char *p = user_input;
    local_var = new_map();

    while(*p){
        //fprintf(stderr, "%s\n", p);

        // skip space
        if(isspace(*p)){
            p++;
            continue;
        }

        if(!(strncmp(p, "return", 6) || is_alnum(p[6]))){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_RETURN;
            t->input = p;
            p+=6;
            vec_push(tokens, t);
            continue;
        }

        if(!(strncmp(p, "else", 4) || is_alnum(p[4]))){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_ELS;
            t->input = p;
            p+=4;
            vec_push(tokens, t);
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

        if(!(strncmp(p, "if", 2) || is_alnum(p[2]))){
            Token *t = (Token *)malloc(sizeof(Token));
            t->ty = TK_IF;
            t->input = p;
            vec_push(tokens, t);
            p+=2;
            continue;
        }
        
        if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == ')' || *p == '(' || *p == '<' || *p == '>' || *p == '=' ||*p == ';'){
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
            count_local_var++;
            for(;is_alnum(*(p+i));i++);
            Token *t = malloc(sizeof(Token));
            t->ty = TK_IDENT;
            t->name = malloc(sizeof(char)*i);
            strncpy(t->name, p, i);
            t->name[i]='\0';
            //t->name = strdup(p);
            t->input = p;
            vec_push(tokens,t);
            map_put(local_var, t->name, (void *)(count_local_var*8));
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
        vec_push(code, stmt());
    }
    vec_push(code, NULL);
}

Node *stmt()
{
    Node *node;
    if(consume(TK_IF)){
        if(!consume('(')){
            error_at(((Token *)(tokens->data[pos]))->input, "( expected");
        }
        Node *cond = expr();
        if(!consume(')')){
            error_at(((Token *)(tokens->data[pos]))->input, ") expected");
        }
        Node *then = stmt();
        Node *els = NULL;
        if(consume(TK_ELS)){
            els = stmt();
        }
        node = new_node_if(cond, then, els);
    }else{
        if(consume(TK_RETURN)){
            node = malloc(sizeof(Node));
            node->ty = ND_RETURN;
            node->lhs = expr();
        }else{
            node = expr();
        }
        if(!consume(';')){
            error_at(((Token *)(tokens->data[pos]))->input, "expected ';' token");
        }
    }
    return node;
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
    }else if(((Token *)(tokens->data[pos]))->ty == TK_IDENT){
        char *varname = ((Token *)(tokens->data[pos++]))->name;
        node = malloc(sizeof(Node));
        node->ty = ND_LVAR;
        node->offset = (int)map_get(local_var, varname);
    }else{
        error_at(((Token *)(tokens->data[pos]))->input, 
                "unexpected token: expected a number");
    }
    return node;
}

