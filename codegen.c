// codegen.c
#include "Ha4CC.h"

const char *reg_name(int byte, int i)
{
	const char *rreg[] = {
		"rax", "rdi", "rsi", "rdx", "rcx", "r8", "r9"
	};
	
	const char *ereg[] = {
		"eax", "edi", "esi", "edx", "ecx", "r8d", "r9d"
	};

	switch(byte){
		case 4:
			return ereg[i];
			
		case 8:
			return rreg[i];
	}
}

void gen(Node *node){
	switch(node->ty){
		case ND_EMPTY:
			return;

		case ND_LVAR_DECL:
			return;

		case ND_FUNCDEF:
			gen_funcdef(node);
			return;

		case ND_FUNCCALL:
			gen_funccall(node);
			return;

		case ND_IF:
        	gen_if(node);
        	return;

		case ND_BLOCK:
			gen_block(node);
			return;

		case ND_FOR:
			gen_for(node);
			return;

		case ND_WHILE:
			gen_while(node);
			return;

		case ND_RETURN:
        	gen(node->lhs);
        	printf("    pop %s\n", reg_name(8, 0));
        	printf("    mov rsp, rbp\n");
        	printf("    pop rbp\n");
        	printf("    ret\n");
        	return;

		case ND_NUM:
        	printf("    push %d\n", node->val);
        	return;

		case ND_LVAR:
        	gen_lval(node);
        	printf("    pop rax\n");
        	printf("    mov rax, [rax]\n");
        	printf("    push rax\n");
        	return;

		case '=':
        	gen_lval(node->lhs);
        	gen(node->rhs);

        	printf("    pop rdi\n");
        	printf("    pop rax\n");
        	printf("    mov [rax], %s\n", reg_name(node->lhs->type->byte, 1));
        	printf("    push rdi\n");
        	return;

		case ND_ADDR:
			gen_lval(node->lhs);
			return;

		case ND_DEREF:
			gen(node->lhs);
			printf("    pop rax\n");
			printf("    mov rax, [rax]\n");
			break;

        case '+':
    		gen(node->lhs);
    		gen(node->rhs);
			printf("    pop rdi\n");
			if(match_type(node, TY_PTR)){
				printf("    push %d\n", node->type->ptr_to->byte);
				printf("    pop rax\n");
				printf("    imul rdi, rax\n");
			}
			printf("    pop rax\n");
			printf("    add rax, rdi\n");
            break;

        case '-':
    		gen(node->lhs);
    		gen(node->rhs);
			printf("    pop rdi\n");
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_INT)){
				printf("    push %d\n", node->type->ptr_to->byte);
				printf("    pop rax\n");
				printf("    imul rdi, rax\n");
			}
    		printf("    pop rax\n");
            printf("    sub rax, rdi\n");
			if(match_type2(node->lhs, node->rhs, TY_PTR, TY_PTR)){
				printf("    push %d\n", node->type->ptr_to->byte);
				printf("    pop rdi\n");
				printf("    cqo\n");
				printf("    div rdi\n");
			}
            break;

        case '*':
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
            printf("    imul eax, edi\n");
            break;

        case '/':
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
			printf("    cltd\n");
            printf("    idiv edi\n");
            break;

        case '<':
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
            printf("    cmp %s, %s\n", reg_name(node->lhs->type->byte, 0), reg_name(node->lhs->type->byte, 1));
            printf("    setl al\n");
            printf("    movzb eax, al\n");
            break;

        case ND_LE:
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
            printf("    cmp %s, %s\n", reg_name(node->lhs->type->byte, 0), reg_name(node->lhs->type->byte, 1));
            printf("    setle al\n");
            printf("    movzb eax, al\n");
            break;

        case ND_EQ:
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
            printf("    cmp %s, %s\n", reg_name(node->lhs->type->byte, 0), reg_name(node->lhs->type->byte, 1));
            printf("    sete al\n");
            printf("    movzb eax, al\n");
            break;

        case ND_NE:
    		gen(node->lhs);
    		gen(node->rhs);
    		printf("    pop rdi\n");
    		printf("    pop rax\n");
            printf("    cmp %s, %s\n", reg_name(node->lhs->type->byte, 0), reg_name(node->lhs->type->byte, 1));
            printf("    setne al\n");
            printf("    movzb eax, al\n");
            break;
	}
    printf("    push rax\n");
}

void gen_lval(Node *node)
{
	if(node->ty == ND_DEREF){
		if(node->lhs->type->ty != TY_PTR){
			error("invalid type argument of unary '*'");
		}
		gen(node->lhs);
	}else if(node->ty == ND_LVAR){
    	printf("    mov rax, rbp\n");
    	printf("    sub rax, %d\n", -node->offset);
    	printf("    push rax\n");
	}
	else{
        error("lvalue requred as left operand of assignment");
    }

}

void gen_if(Node *node)
{
    if(node->els == NULL){
        count_end++;
        int Lend = count_end;
        gen(node->cond);
        printf("    pop rax\n");
        printf("    cmp rax, 0\n");
        printf("    je .Lend%d\n", Lend);
        gen(node->then);
        printf(".Lend%d:\n", Lend);
    }else{
        count_end++;
        count_else++;
        int Lend = count_end;
        int Lelse = count_else;
        gen(node->cond);
        printf("    pop rax\n");
        printf("    cmp rax, 0\n");
        printf("    je .Lelse%d\n", Lelse);
        gen(node->then);
        printf(".Lelse%d:\n", Lelse);
        gen(node->els);
        printf(".Lend%d:\n", Lend);
    }
}

void gen_for(Node *node)
{
    count_begin++;
    count_end++;
    int Lbegin = count_begin;
    int Lend = count_end;
    if(node->init != NULL){
        gen(node->init);
    }
    printf(".Lbegin%d:\n", Lbegin);
    if(node->for_cond != NULL){
        gen(node->for_cond);
        printf("    pop rax\n");
        printf("    cmp rax, 0\n");
        printf("    je .Lend%d\n", Lend);
    }
    gen(node->body);
    gen(node->iter);
    printf("    jmp .Lbegin%d\n", Lbegin);
    printf(".Lend%d:\n", Lend);
}

void gen_while(Node *node)
{
    count_begin++;
    count_end++;
    int Lbegin = count_begin;
    int Lend = count_end;
    printf(".Lbegin%d:\n", Lbegin);
    gen(node->cond);
    printf("    pop rax\n");
    printf("    cmp rax, 0\n");
    printf("    je .Lend%d\n", Lend);
    gen(node->then);
    printf("    jmp .Lbegin%d\n", Lbegin);
    printf(".Lend%d:\n", Lend);
}

void gen_block(Node *node)
{
	int len = node->stmts->len;
	for(int i=0; i<len-1; i++){
		Node *tmp = (Node *)(node->stmts->data[i]);
		if(tmp->ty == ND_EMPTY || tmp->ty == ND_LVAR_DECL)continue;
		gen(tmp);
		printf("    pop rax\n");
	}
	gen((Node *)(node->stmts->data[len-1]));
}

void gen_funccall(Node *node)
{
	for(int i=0; i<node->callargs->len; i++){
		gen((Node *)(node->callargs->data[i]));
	}
	for(int i=0; i<node->callargs->len; i++){
		printf("    pop %s\n", reg_name(8, node->callargs->len-i));
	}
	printf("    mov r10, rsp\n");
	printf("    and rsp, -16\n");
	printf("    push r10\n");
	printf("    push r11\n");
	printf("    call %s\n", node->funcname);
	printf("    pop r11\n");
	printf("    pop r10\n");
	printf("    mov rsp, r10\n");
	printf("    push rax\n");
}
void gen_funcdef(Node *node)
{
	printf("%s:\n", node->fname);
	// prologue
	printf("    push rbp\n");
	printf("    mov rbp, rsp\n");
	printf("    sub rsp, %d\n", -*(node->env->max_idx));
	for(int i=0; i < node->args->len; i++){
		Node *tmp = (Node *)get_var(node->env, ((Node *)(node->args->data[i]))->varname);
		printf("    mov [rbp-%d], %s\n", -tmp->offset, reg_name(tmp->type->byte, i+1));
	}

	gen(node->defbody);

	// epilogue
	printf("    mov rsp, rbp\n");
	printf("    pop rbp\n");
	printf("    ret\n");
}

void start_gen(Vector *asts)
{
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");

    // generate codes
    for(int i=0; asts->data[i]; i++){
        gen(((Node *)(asts->data[i])));
    }
}
