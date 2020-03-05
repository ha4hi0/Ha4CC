// node.c

#include "Ha4CC.h"

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

Node *new_node_lvar_decl(Type *type, char *name)
{
	Node *node = malloc(sizeof(Node));
	node->ty = ND_LVAR_DECL;
	node->type = type;
	node->varname = name;
	return node;
}

