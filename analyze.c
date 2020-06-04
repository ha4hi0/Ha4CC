// analyze.c
#include "Ha4CC.h"

int string_literal_label;

void swap(Node **lhs, Node **rhs)
{
	Node *tmp;
	tmp = *rhs;
	*rhs = *lhs;
	*lhs = tmp;
}

Type *type_int()
{
	Type *ret = malloc(sizeof(Type));
	ret->ty = TY_INT;
	ret->ptr_to = NULL;
	ret->byte = 4;
	return ret;
}

Type *type_char()
{
	Type *ret = malloc(sizeof(Type));
	ret->ty = TY_CHAR;
	ret->ptr_to = NULL;
	ret->byte = 1;
	return ret;
}

Type *ary2type(Type *type, int len)
{
	Type *ret = malloc(sizeof(Type));
	ret->ty = TY_ARRAY;
	ret->ary_to = type;
	ret->byte = type->byte;
	ret->len = len;
	return ret;
}

Type *ptr2type(Type *type)
{
	Type *ret = malloc(sizeof(Type));
	ret->ty = TY_PTR;
	ret->ptr_to = type;
	ret->byte = 8;
	return ret;
}

int match_type(Node *node, enum TY ty)
{
	return (node->type->ty == ty);
}

int match_type2(Node *lhs, Node *rhs, enum TY lty, enum TY rty)
{
	return (match_type(lhs, lty) && match_type(rhs, rty));
}

int match_type_int(Node *node)
{
	return match_type(node, TY_INT) || match_type(node, TY_CHAR);
}

Node *analyze_detail(Scope *env, Node *node)
{
	if(node == NULL) return NULL;
	switch(node->ty){
		case '+' :
			node->rhs = ary2ptr(analyze_detail(env, node->rhs));
			node->lhs = ary2ptr(analyze_detail(env, node->lhs));
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_PTR)){
				error("invalid operand to binary +");
			}
			if(match_type_int(node->lhs) && match_type(node->rhs, TY_PTR)){
				swap(&node->lhs, &node->rhs);
			}
			node->type = node->lhs->type;
			break;
		case '-' :
			node->rhs = ary2ptr(analyze_detail(env, node->rhs));
			node->lhs = ary2ptr(analyze_detail(env, node->lhs));
			if(match_type_int(node->lhs) && match_type(node->rhs, TY_PTR)){
				error("int - ptr is not allowed");
			}
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_PTR)){
				node->type = type_int();
			}else{
				node->type = node->lhs->type;
			}
			break;
		case '*' :
		case '/' :
			node->rhs = analyze_detail(env, node->rhs);
			node->lhs = analyze_detail(env, node->lhs);
			if(match_type(node->lhs, TY_PTR) || match_type(node->rhs, TY_PTR)){
				error("invalid operand to binary *");
			}
			node->type = node->lhs->type;
			break;
		case '%':
			node->rhs = analyze_detail(env, node->rhs);
			node->lhs = analyze_detail(env, node->lhs);
			if(!(match_type_int(node->lhs) && match_type_int(node->rhs))){
				error("invalid operand to binary %");
			}
			node->type = type_int();
			break;
		case '=':
			node->rhs = analyze_detail(env, node->rhs);
			node->lhs = analyze_detail(env, node->lhs);
			node->type = node->lhs->type;
			break;
		case ND_NUM:
			node->type = type_int();
			break;
		case ND_EQ:
		case ND_NE:
        case ND_LE:
		case ND_GE:
		case '<':
		case '>':
			node->lhs = analyze_detail(env, node->lhs);
			node->rhs = analyze_detail(env, node->rhs);
			node->type = type_int();
			if(node->ty == ND_GE){
				node->ty = ND_LE;
				swap(&node->lhs, &node->rhs);
			}
			if(node->ty == '>'){
				node->ty = '<';
				swap(&node->lhs, &node->rhs);
			}
			break;
		case ND_LOG_AND:
			node->lhs = analyze_detail(env, node->lhs);
			node->rhs = analyze_detail(env, node->rhs);
			if(!(match_type_int(node->lhs) && match_type_int(node->rhs))){
				error("invalid operand to binary &&");
			}
			node->type = type_int();
			break;
		case ND_LOG_OR:
			node->lhs = analyze_detail(env, node->lhs);
			node->rhs = analyze_detail(env, node->rhs);
			if(!(match_type_int(node->lhs) && match_type_int(node->rhs))){
				error("invalid operand to binary ||");
			}
			node->type = type_int();
			break;
        case ND_IF:
        case ND_WHILE:
			node->cond = analyze_detail(env, node->cond);
			node->then = analyze_detail(env, node->then);
			node->els = analyze_detail(env, node->els);
			node->type = NULL;
			break;
        case ND_FOR:
			node->init = analyze_detail(env, node->init);
			node->for_cond = analyze_detail(env, node->for_cond);
			node->iter = analyze_detail(env, node->iter);
			node->body = analyze_detail(env, node->body);
			node->type = NULL;
			break;
	    case ND_FUNCDEF:
			add_func(env, node);
			Scope *nenv = new_scope(env);
			node->env = nenv;
			for(int i=0; i<node->args->len; i++){
				add_var(node->env, node->args->data[i]);
			}
			node->defbody = analyze_detail(nenv, node->defbody);
			node->type = NULL;
			break;
	    case ND_BLOCK:
			{
				Scope *nenv = new_scope(env);
				for(int i=0; i<node->stmts->len; i++){
					analyze_detail(nenv, (Node *)(node->stmts->data[i]));
				}
				node->type = NULL;
				break;
			}
        case ND_RETURN:
			node->lhs = analyze_detail(env, node->lhs);
			node->type = NULL;
			break;
		case ND_LVAR_DECL:
		case ND_GVAR_DECL:
			add_var(env, node);
			break;
		case ND_LVAR_DECL_INIT:
			add_var(env, node);
			node->offset = get_var(env, node->varname)->offset;
			node->rhs_init = analyze_detail(env, node->rhs_init);
			if((node->rhs_init->ty == ND_ARRAY_INITIALIZER) && (node->type->ty != TY_ARRAY)){
				error("excess elements in scalar initializer.");
			}
			break;
        case ND_LVAR:
		case ND_GVAR:{
			Node *tmp = get_var(env, node->varname);
			if(tmp == NULL) error("%s is not declared", node->varname);
			node = ary2ptr(tmp);
			break;
					 }
	    case ND_FUNCCALL:
			{
				Node *def = get_func(env, node->funcname);
				if(def != NULL){
					node->type = def->ret_type;
				}else{
					node->type = type_int();
				}
				for(int i=0; i<node->callargs->len; i++){
					vec_set(node->callargs,i,analyze_detail(env, node->callargs->data[i]));
				}
				break;
			}
	    case ND_ADDR:
			node->lhs = analyze_detail(env, node->lhs);
			node->type = ptr2type(node->lhs->type);
			break;
	    case ND_DEREF:
			node->lhs = ary2ptr(analyze_detail(env, node->lhs));
			if(!match_type(node->lhs, TY_PTR)){
				error("invalid type argument of unary '*'");
			}
			node->type = node->lhs->type->ptr_to;
			break;

		case ND_SIZEOF:
		{
			node->lhs = analyze_detail(env, node->lhs);
			int tmp = node->lhs->type->byte;
			if(match_type(node->lhs, TY_ARRAY)){
				tmp *= node->lhs->type->len;
			}
			node->type = type_int();
			node->ty = ND_NUM;
			node->val = tmp;
			break;
		}

		case ND_STRING:
		{
			Node *ret;
			node->varname = malloc(sizeof(256));
			sprintf(node->varname, ".LC%d", string_literal_label++);
			node->type = ary2type(type_char(), sizeof(node->sval)+1);
			node->ty = ND_GVAR;
			add_gvar(env, node);
			ret = ary2ptr(node);
			return ret;
		}

		case ND_ARRAY_INITIALIZER:
		{
			node->type = ary2type(type_int(), sizeof(node->array_init->len));
			for(int i=0; i<node->array_init->len; i++){
				node->array_init->data[i] = analyze_detail(env, (Node *)(node->array_init->data[i]));
			}
			break;
		}
	}
	return node;
}

Vector *analyze(Vector *code, Scope *env)
{
	for(int i=0; code->data[i]!=NULL; i++){
		vec_set(code, i, analyze_detail(env, (Node *)(code->data[i])));
	}
	return code;
}

