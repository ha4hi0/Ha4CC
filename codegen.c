// codegen.c
#include "Ha4CC.h"

const char *reg_name(int byte, int i)
{
	const char *regl[] = {
		"al", "dil", "dil", "dl", "cl", "d8b", "d9b"
	};

	const char *regx[] = {
		"ax", "di", "si", "dx", "cx", "r8w", "r9w"
	};

	const char *ereg[] = {
		"eax", "edi", "esi", "edx", "ecx", "r8d", "r9d"
	};

	const char *rreg[] = {
		"rax", "rdi", "rsi", "rdx", "rcx", "r8", "r9"
	};

	switch(byte){
		case 1:
			return regl[i];
		case 2:
			return regx[i];
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

		case ND_GVAR_DECL:
			printf(".data\n");
			printf("%s:\n", node->varname);
			if(match_type(node, TY_ARRAY)){
				printf("    .zero %d\n", node->type->len * node->type->ary_to->byte);
			}else{
				printf("    .zero %d\n", node->type->byte);
			}
			printf(".text\n");
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
			switch(node->type->byte){
				case 1:
					//printf("    movsx %s, [rbp%d]\n", reg_name(1, 0), node->offset);
					printf("    lea rax, [rbp%d]\n", node->offset);
					printf("    movsx eax, BYTE PTR [rax]\n");
					break;
				case 2:
					//printf("    movsx %s, [rbp%d]\n", reg_name(2, 0), node->offset);
					printf("    lea rax, [rbp%d]\n", node->offset);
					printf("    movsx eax, [rbp%d]\n", node->offset);
					break;
				default:
					printf("    mov %s, [rbp%d]\n", reg_name(node->type->byte, 0), node->offset);
					break;
			}
			printf("    push rax\n");
        	return;

		case ND_GVAR:
			switch(node->type->byte){
				case 1:
					//printf("    movsx %s, %s[rip]\n", reg_name(1, 0), node->varname);
					printf("    lea rax, %s[rip]\n", node->varname);
					printf("    movsx eax, BYTE PTR [rax]\n");
					break;
				case 2:
					//printf("    movsx %s, %s[rip]\n", reg_name(2, 0), node->varname);
					printf("    lea rax, %s[rip]\n", node->varname);
					printf("    movsx eax, %s[rip]\n", node->varname);
					break;
				default:
					printf("    mov %s, %s[rip]\n", reg_name(node->type->byte, 0), node->varname);
					break;
			}
			printf("    push rax\n");
			return;

		case ND_ARY2PTR:
			if(node->ary->ty == ND_GVAR){
				printf("    lea rax, %s[rip]\n", node->ary->varname);
				printf("    push rax\n");
			}else{
				printf("    mov rax, rbp\n");
				printf("    sub rax, %d\n", -node->ary->offset);
				printf("    push rax\n");
			}
			return;

		case '=':
			gen(node->rhs);
			if(node->lhs->ty == ND_DEREF){
				gen(node->lhs->lhs);
        		printf("    pop rax\n");
        		printf("    pop rdi\n");
        		printf("    mov [rax], %s\n", reg_name(node->lhs->type->byte, 1));
        		printf("    push rdi\n");
			}else if(node->lhs->ty == ND_GVAR){
				printf("    pop rdi\n");
				printf("    mov %s[rip], %s\n", node->lhs->varname, reg_name(node->lhs->type->byte, 1));
				printf("    push rdi\n");
			}else if(node->lhs->ty == ND_LVAR){
				printf("    pop rdi\n");
				printf("    mov [rbp%d], %s\n", node->lhs->offset, reg_name(node->lhs->type->byte, 1));
				printf("    push rdi\n");
			}
        	return;

		case ND_ADDR:
			if(node->lhs->ty == ND_DEREF){
				gen(node->lhs->lhs);
			}else if(node->lhs->ty == ND_GVAR){
				printf("    lea rax, %s[rip]\n", node->lhs->varname);
				printf("    push rax\n");
			}else if(node->lhs->ty == ND_LVAR){
				printf("    mov rax, rbp\n");
				printf("    sub rax, %d\n", -node->lhs->offset);
				printf("    push rax\n");
			}
			return;

		case ND_DEREF:
			gen(node->lhs);
			printf("    pop rax\n");
			//printf("    mov rax, [rax]\n");
			switch(node->type->byte){
				case 1:
					printf("    movsx rax, BYTE PTR [rax]\n");
					break;
				case 2:
					printf("    movsx rax, WORD PTR [rax]\n");
					break;
				default:
					printf("    mov rax, [rax]\n");
					break;
			}
			break;

        case '+':
    		gen(node->lhs);
    		gen(node->rhs);
			printf("    pop rdi\n");
			if(match_type(node, TY_PTR)){
				printf("    push %d\n", node->type->ptr_to->byte);
				printf("    pop rax\n");
				printf("    cltq\n");
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
				printf("    cltq\n");
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
		printf("    jmp .Lend%d\n", Lend);
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

void gen_string(Scope *env)
{
	printf(".data\n");
	for(int i=0; i<env->symbols->vals->len; i++){
		Node *node = env->symbols->vals->data[i];
		if(node->ty == ND_GVAR && node->sval != NULL){
			printf("%s:\n", node->varname);
			printf("    .string \"%s\"\n", node->sval);
		}
	}
	printf(".text\n");
}

void start_gen(Vector *asts, Scope *env)
{
	printf(".intel_syntax noprefix\n");
	printf(".global main\n");

	gen_string(env);

    // generate codes
    for(int i=0; asts->data[i]; i++){
        gen(((Node *)(asts->data[i])));
    }
}
