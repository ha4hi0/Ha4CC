#include "Ha4CC.h"

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

Type *ptr2type(Type *type)
{
	Type *ret = malloc(sizeof(Type));
	ret->ty = TY_PTR;
	ret->ptr_to = type;
	ret->byte = 8;
	return ret;
}

Vector *analyze(Vector *code)
{
	for(int i=0; code->data[i]!=NULL; i++){
		vec_set(code, i, analyze_detail((Node *)(code->data[i])));
	}
	return code;
}

int match_type(Node *node, enum TY ty)
{
	return (node->type->ty == ty);
}

int match_type2(Node *lhs, Node *rhs, enum TY lty, enum TY rty)
{
	return (match_type(lhs, lty) && match_type(rhs, rty));
}

Node *analyze_detail(Node *node)
{
	if(node == NULL) return NULL;
	switch(node->ty){
		case '+' :
			node->rhs = analyze_detail(node->rhs);
			node->lhs = analyze_detail(node->lhs);
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_PTR)){
				error("invalid operand to binary +");
			}
			if(match_type2(node->lhs, node->rhs, TY_INT, TY_PTR)){
				swap(&node->lhs, &node->rhs);
			}
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_INT)){
				node->type = node->lhs->type;
			}else{
				node->type = node->lhs->type;
			}
			break;
		case '-' :
			node->rhs = analyze_detail(node->rhs);
			node->lhs = analyze_detail(node->lhs);
			if(match_type2(node->lhs, node->rhs, TY_INT, TY_PTR)){
				error("int - ptr is not allowed");
			}
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_PTR)){
				node->type = type_int();
			}else if(match_type2(node->lhs, node->rhs, TY_PTR, TY_INT)){
				node->type = node->lhs->type;
			}else{
				node->type = node->lhs->type;
			}
			break;
		case '*' :
		case '/' :
			node->rhs = analyze_detail(node->rhs);
			node->lhs = analyze_detail(node->lhs);
			node->type = type_int();
			break;
		case '=':
			node->rhs = analyze_detail(node->rhs);
			node->lhs = analyze_detail(node->lhs);
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
			node->lhs = analyze_detail(node->lhs);
			node->rhs = analyze_detail(node->rhs);
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
        case ND_IF:
        case ND_WHILE:
			node->cond = analyze_detail(node->cond);
			node->then = analyze_detail(node->then);
			node->els = analyze_detail(node->els);
			node->type = NULL;
			break;
        case ND_FOR:
			node->init = analyze_detail(node->init);
			node->for_cond = analyze_detail(node->for_cond);
			node->iter = analyze_detail(node->iter);
			node->body = analyze_detail(node->body);
			node->type = NULL;
			break;
	    case ND_FUNCDEF:
			node->defbody = analyze_detail(node->defbody);
			node->type = NULL;
			break;
	    case ND_BLOCK:
			for(int i=0; i<node->stmts->len; i++){
				analyze_detail((Node *)(node->stmts->data[i]));
			}
			node->type = NULL;
			break;
        case ND_RETURN:
			node->lhs = analyze_detail(node->lhs);
			node->type = NULL;
			break;
        case ND_LVAR:
			break;
	    case ND_FUNCCALL:
			node->type = type_int();
			break;
	    case ND_ADDR:
			node->lhs = analyze_detail(node->lhs);
			node->type = ptr2type(node->lhs->type);
			break;
	    case ND_DEREF:
			node->lhs = analyze_detail(node->lhs);
			node->type = node->lhs->type->ptr_to;
			break;
		case ND_SIZEOF:
		{
			node->lhs = analyze_detail(node->lhs);
			int tmp = node->lhs->type->byte;
			node->type = type_int();
			node->ty = ND_NUM;
			node->val = tmp;
		}
	}
	return node;
}
