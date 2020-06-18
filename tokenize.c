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
        '+' ,'-' ,'*' ,'/' ,'%' ,')' ,'(' ,'<' ,'>' ,'=', ';', '{', '}', ',', '&', '[', ']'
	};

	for(int i=0; i<sizeof(ops)/sizeof(char); i++){
		if(ops[i]==c)return 1;
	}
	return 0;
}

int is_twoletteroperator(char *c)
{
	const char *ops[] = {
		"==", "!=", "<=", ">=", "&&", "||", "+=", "-=", "*=", "/="
	};

	int vals[] = {
		TK_EQ, TK_NE, TK_LE, TK_GE, TK_LOG_AND, TK_LOG_OR, TK_ADD_EQ, TK_SUB_EQ, TK_MUL_EQ, TK_DIV_EQ
	};

	for(int i=0; i<sizeof(vals)/sizeof(int); i++){
		if(!strncmp(c, ops[i], 2)){
			return vals[i];
		}
	}
	return 0;
}

// break string up into tokens
Vector* tokenize(){
	Vector *tokens = new_vector();
    char *p = user_input;

	reservedwords = new_vector();
	init_reservedwords(reservedwords);

    while(*p){

        // skip space
        if(isspace(*p)){
            p++;
            continue;
        }

		// skip line comments
		if(strncmp(p, "//", 2) == 0){
			p += 2;
			while(*p != '\n')p++;
			continue;
		}

		// skip block comments
		if(strncmp(p, "/*", 2) == 0){
			char *q = strstr(p+2, "*/");
			if(!q)error_at(p, "comment is not closed.");
			p = q+2;
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

		// string literal
		if(*p == '"'){
			Token *t = (Token *)malloc(sizeof(Token));
			t->ty = TK_STRING;
			t->input = p;
			p++;
			Vector *string = new_vector();
			while(*p != '"'){
				vec_push(string, (void *)*p);
				p++;
			}
			p++;
			char *ret = malloc(string->len+1);
			for(int i=0; i<string->len; i++){
				ret[i] = (char)(string->data[i]);
			}
			ret[string->len] = '\0';
			t->slen = string->len+1;
			t->sval = ret;
			vec_push(tokens, t);
			continue;
		}

		// character constant
		if(*p == '\''){
			Token *t = (Token *)malloc(sizeof(Token));
			t->ty = TK_NUM;
			t->input = p;
			p++;
			if(*p == '\''){
				error_at(p, "empty character constant");
			}
			t->val = *p;
			// skip second character and later
			while(*p != '\''){
				p++;
			}
			p++;
			vec_push(tokens, t);
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
	return tokens;
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
	vec_push(array, new_word("char", 4, TK_CHAR));
	vec_push(array, new_word("else", 4, TK_ELS));
	vec_push(array, new_word("int", 3, TK_INT));
	vec_push(array, new_word("for", 3, TK_FOR));
	vec_push(array, new_word("if", 2, TK_IF));
}
