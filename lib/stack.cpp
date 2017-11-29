#include "stack.hpp"
#include <stdio.h>
#include <stdlib.h>

Stack* create(void *element)
{
    Stack * n = alocate();
    n->next = NULL;
    n->value = element;

    return n;
}

Stack* alocate()
{
    Stack *n = (Stack*) set_mem(sizeof(Stack));
    if(!n){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else{
        return n;
    }
    return n;
}

int empty(Stack *stack)
{
    if(stack == NULL || stack->value == NULL)
        return 1;
    else
        return 0;
}

void push(void *element, Stack **_stack)
{
    if(empty(*_stack)){
        Stack *new_head = alocate();
        new_head->value= element;
        new_head->next = NULL;
        (*_stack) = new_head;
    }else{
        Stack *new_head = (*_stack);
        //new_head = alocate();
        new_head->next = (*_stack);
        new_head->value = element;
        (*_stack) = new_head;
    }
    //print(INTEGER_NUM, (*_stack));
}

Stack* pop(Stack **_stack)
{
    if((*_stack)->value == NULL){
        printf("PILHA ja vazia\n\n");
        return NULL;
    }

    Stack *head = (*_stack);
    (*_stack) = (*_stack)->next;
    head->next = NULL;

    //print(CHAR, (*_stack));
    return head;
}

void freeStack(Stack **_stack)
{
    if(!empty(*_stack)){
        free_mem((void**) _stack);
    }
}

void print(TYPE type, Stack *_stack)
{
    if(empty(_stack)){
        printf("PILHA vazia!\n\n");
        return ;
    }

    Stack *tmp;
    tmp = _stack;
    printf("PILHA:\n");
    while( tmp != NULL){
        switch (type) {
            case CHARACTER_VALUE:
                printf("%c\n", *((char *)tmp->value));
                break;
            case INTEGER_NUM:
                printf("STACK - %d\n", *((int32_t *)tmp->value));
                break;

            case FLOAT_NUM:
                printf("%f\n", *((float *)tmp->value));
                break;

            case DOUBLE_NUM:
                printf("%lf\n", *((double *)tmp->value));
                break;

            default:
                break;
        }

        tmp = tmp->next;
    }

    printf("\n\n");
}
