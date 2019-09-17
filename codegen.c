// codegen.c
#include "hcc.h"

void gen(Node *node){
    if(node->ty == ND_IF){
        gen_if(node);
        return;
    }

    if(node->ty == ND_WHILE){
        gen_while(node);
        return;
    }

    if(node->ty == ND_RETURN){
        gen(node->lhs);
        printf("    pop rax\n");
        printf("    mov rsp, rbp\n");
        printf("    pop rbp\n");
        printf("    ret\n");
        return;
    }

    if(node->ty == ND_NUM){
        printf("    push %d\n", node->val);
        return;
    }
    
    if(node->ty == ND_LVAR){
        gen_lval(node);
        printf("    pop rax\n");
        printf("    mov rax, [rax]\n");
        printf("    push rax\n");
        return;
    }

    if(node->ty == ND_FOR){
        gen_for(node);
        return;
    }

    if(node->ty == '='){
        gen_lval(node->lhs);
        gen(node->rhs);

        printf("    pop rdi\n");
        printf("    pop rax\n");
        printf("    mov [rax], rdi\n");
        printf("    push rdi\n");
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
    if(node->cond != NULL){
        gen(node->cond);
        printf("    pop rax\n");
        printf("    cmp rax, 0\n");
        printf("    je .Lend%d\n", Lend);
    }
    gen(node->stmts);
    gen(node->inc);
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
    gen(node->stmts);
    printf("    jmp .Lbegin%d\n", Lbegin);
    printf(".Lend%d:\n", Lend);
}
