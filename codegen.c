// codegen.c
#include "Ha4CC.h"

char *reg_args[6] = {
	"rdi", "rsi", "rdx", "rcx", "r8", "r9"
};

void gen(Node *node){
	switch(node->ty){
		case ND_INT:
			printf("    push 0\n");
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
        	printf("    pop rax\n");
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
        	printf("    mov [rax], rdi\n");
        	printf("    push rdi\n");
        	return;
		case ND_ADDR:
			gen_lval(node->lhs);
			return;
		case ND_DEREF:
			gen(node->lhs);
			printf("    pop rax\n");
			printf("    mov rax, [rax]\n");
			printf("    push rax\n");
			return;
	}
    gen(node->lhs);
    gen(node->rhs);

    printf("    pop rdi\n");
    printf("    pop rax\n");

    switch(node->ty){
        case '+':
            printf("    add rax, rdi\n");
            break;
        case '-':
            printf("    sub rax, rdi\n");
            break;
        case '*':
            printf("    imul rdi\n");
            break;
        case '/':
            printf("    cqo\n");
            printf("    idiv rdi\n");
            break;
        case '<':
            printf("    cmp rax, rdi\n");
            printf("    setl al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_LE:
            printf("    cmp rax, rdi\n");
            printf("    setle al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_EQ:
            printf("    cmp rax, rdi\n");
            printf("    sete al\n");
            printf("    movzb rax, al\n");
            break;
        case TK_NE:
            printf("    cmp rax, rdi\n");
            printf("    setne al\n");
            printf("    movzb rax, al\n");
            break;
    }
    printf("    push rax\n");
}

void gen_lval(Node *node)
{
    if(node->ty != ND_LVAR){
        error("lvalue requred as left operand of assignment");
    }
    printf("    mov rax, rbp\n");
    printf("    sub rax, %d\n", node->offset);
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
		gen((Node *)(node->stmts->data[i]));
		printf("    pop rax\n");
	}
	gen((Node *)(node->stmts->data[len-1]));
}

void gen_funccall(Node *node)
{
	for(int i=0; i<node->args->len; i++){
		gen((Node *)(node->args->data[i]));
	}
	for(int i=0; i<node->args->len; i++){
		printf("    pop %s\n", reg_args[node->args->len-i-1]);
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
	printf(".global %s\n", node->deffuncname);
	printf("%s:\n", node->deffuncname);
	// prologue
	printf("    push rbp\n");
	printf("    mov rbp, rsp\n");
	printf("    sub rsp, %d*8\n", map_len(node->local_var));

	for(int i=0; i<node->argname->len; i++){
		void *ret=map_get(node->local_var, node->argname->data[i]);
		printf("    mov [rbp-%d], %s\n", (int)ret, reg_args[i]);
	}

	gen(node->defbody);

	// epilogue
	printf("    mov rsp, rbp\n");
	printf("    pop rbp\n");
	printf("    ret\n");
}
