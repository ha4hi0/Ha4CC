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
	if(node != NULL && node->ty != ND_LVAR && node->ty != ND_GVAR){
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
	Node *tmp = map_get(env->symbols, name);
	//if(map_get(env->symbols, name) != NULL){
	if(tmp != NULL){
		//fprintf(stderr, "%s %s %s\n", tmp->varname, node->varname, name);
		error("%s: same symbol already exist.", node->varname);
	}
	map_put(env->symbols, name, node);
	return node;
}

Node *add_var(Scope *env, Node *node)
{
	Node *var = malloc(sizeof(Node));
	if(node->ty == ND_GVAR_DECL){
		var->ty = ND_GVAR;
	}else if(node->ty == ND_LVAR_DECL){
		var->ty = ND_LVAR;
		if(match_type(node, TY_ARRAY)){
			env->stack_idx -= node->type->byte*node->type->len;
		}else{
			env->stack_idx -= node->type->byte;
		}
		var->offset = env->stack_idx;
	}else{
		var = node;
	}
	if(env->stack_idx < *(env->max_idx)){
		*(env->max_idx) = env->stack_idx;
	}
	var->type = node->type;
	var->varname = node->varname;
	add_symbol(env, node->varname, var);
	return node;
}

Node *add_gvar(Scope *env, Node *node)
{
	Scope *tmp = env;
	while(tmp->parent != NULL)tmp=tmp->parent;
	add_var(tmp, node);
	return node;
}

Node *add_func(Scope *env, Node *node)
{
	add_symbol(env, node->fname, node);
	return node;
}
