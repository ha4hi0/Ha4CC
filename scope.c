// scope.c

#include "Ha4CC.h"

Scope *new_scope(Scope *parent)
{
	Scope *ret=malloc(sizeof(Scope));
	ret->parent = parent;
	ret->symbols = new_map();
	if((parent == NULL) || (parent->parent == NULL)){
		ret->stack_idx = 0;
		ret->max_idx = malloc(sizeof(int));
		*(ret->max_idx) = 0;
	}else{
		ret->stack_idx = parent->stack_idx;
		ret->max_idx = parent->max_idx;
	}
	return ret;
}

Node *get_symbol(Scope *env, const char *name){
	Scope *tmp = env;
	while(tmp != NULL){
		Node *ret = map_get(tmp->symbols, name);
		if(ret != NULL) return ret;
		tmp = tmp->parent;
	}
	return NULL;
}

Node *get_var(Scope *env, const char *name)
{
	Node *node = get_symbol(env, name);
	if(node != NULL && node->ty != ND_LVAR){
		error("%s is not var", name);
	}
	return node;
}

Node *get_func(Scope *env, const char *name)
{
	Node *node = get_symbol(env, name);
	if(node != NULL && node->ty != ND_FUNCDEF){
		error("%s is not func", name);
	}
	return node;
}

Node *add_symbol(Scope *env, const char *name, Node *node)
{
	if(map_get(env->symbols, name) != NULL){
		error("%s: same symbol already exist.", node->varname);
	}
	map_put(env->symbols, name, node);
	return node;
}

Node *add_var(Scope *env, Node *node)
{
	Node *var = malloc(sizeof(Node));
	env->stack_idx -= node->type->byte;
	if(env->stack_idx < *(env->max_idx)){
		*(env->max_idx) = env->stack_idx;
	}
	var->type = node->type;
	var->varname = node->varname;
	var->ty = ND_LVAR;
	var->offset = env->stack_idx;
	add_symbol(env, node->varname, var);
	return node;
}

Node *add_func(Scope *env, Node *node)
{
	add_symbol(env, node->fname, node);
	return node;
}
