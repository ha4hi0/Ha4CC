// tokenize.c

#include "Ha4CC.h"

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

	reservedwords = new_vector();
	init_reservedwords(reservedwords);

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


