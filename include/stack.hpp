#ifndef _STACK_H
#define _STACK_H

#include "mem-manager.hpp"

/**
* @brief Structure of the stack.
* Contains the pointer for the element and ponter to the next element.
*/
typedef struct _stack{
    void *value;
    struct _stack *next;
}Stack;

/**
* @brief Enum with types for debug print.
*/
typedef enum {
    CHARACTER_VALUE,
    INTEGER_NUM,
    FLOAT_NUM,
    DOUBLE_NUM
} TYPE;

/**
*   @fn Stack* create(void *element)
*   @brief Create a Stack with an element
*   @param element pointer to the first element of the stack
*   @return pointer to the created Stack
*/
Stack* create(void*);

/**
*   @fn Stack* alocate(void)
*   @brief Create a Stack
*   @return pointer to the created Stack
*/
Stack* alocate(void);

/**
*   @fn int empty(Stack *)
*   @brief Check if the Stack is empty
*   @param Stack pointer to Stack
*   @return an interger telling if the stack is empty or not
*/
int empty(Stack *);

/**
*   @fn void push(void *, Stack **)
*   @brief Push an element into the Stack
*   @param void pointer to the element pushed into of the stack
*   @param Stack pointer to pointer for the Stack
*   @return
*/
void push(void *, Stack **);

/**
*   @fn Stack* pop(Stack **)
*   @brief Push an element into the Stack
*   @param Stack pointer to pointer for the Stack
*   @return pointer to the old Stack's head
*/
Stack* pop(Stack **);

/**
*   @fn void freeStack(Stack **)
*   @brief Free the entire stack
*   @param Stack pointer to pointer for the Stack
*   @return
*/
void freeStack(Stack **);

/**
*   @fn void print(TYPE, Stack *)
*   @brief Print the entire stack
*   @param Enum type for the printed element
*   @param Stack pointer to pointer for the Stack
*   @return
*/
void print(TYPE, Stack *);

#endif /* _STACK_H */
