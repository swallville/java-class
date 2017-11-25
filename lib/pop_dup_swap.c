#include "pop_dup_swap.h"


void i_pop(Frame* frame)
{
  (void)pop(&(frame->operandStack));

  return;
}

void i_pop2(Frame* frame)
{
    (void)pop(&(frame->operandStack));
    (void)pop(&(frame->operandStack));

  return;
}

void i_dup(Frame* frame)
{
    uint32_t valor = *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&valor,&(frame->operandStack));
    push(&valor,&(frame->operandStack));

  return;
}

void i_dup_x1(Frame* frame)
{
    uint32_t valueTop =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valor =  *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&valor,&(frame->operandStack));
    push(&valueTop,&(frame->operandStack));
    push(&valor,&(frame->operandStack));

  return;
}

void i_dup_x2(Frame* frame)
{
    uint32_t valueTop =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valor =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valuefloor = *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&valuefloor,&(frame->operandStack));
    push(&valor,&(frame->operandStack));
    push(&valueTop,&(frame->operandStack));
    push(&valuefloor,&(frame->operandStack));

  return;
}


void i_dup2(Frame* frame)
{
    uint32_t valueTop =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valor =  *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&valor,&(frame->operandStack));
    push(&valueTop,&(frame->operandStack));
    push(&valor,&(frame->operandStack));
    push(&valueTop,&(frame->operandStack));

  return;
}

void i_dup2_x1(Frame* frame)
{
    uint32_t valueTop =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valor =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t valuefloor = *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&valuefloor,&(frame->operandStack));
    push(&valor,&(frame->operandStack));
    push(&valueTop,&(frame->operandStack));
    push(&valuefloor,&(frame->operandStack));
    push(&valor,&(frame->operandStack));

  return;
}


void i_dup2_x2(Frame* frame)
{
    uint32_t value1 =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t value2 =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t value3 =  *((uint32_t*)pop(&(frame->operandStack))->value);
    uint32_t value4 =  *((uint32_t*)pop(&(frame->operandStack))->value);
    push(&value4,&(frame->operandStack));
    push(&value3,&(frame->operandStack));
    push(&value2,&(frame->operandStack));
    push(&value1,&(frame->operandStack));
    push(&value4,&(frame->operandStack));
    push(&value3,&(frame->operandStack));

  return;
}

void i_swap(Frame* frame)
{
     uint32_t value1 =  *((uint32_t*)pop(&(frame->operandStack))->value);
     uint32_t value2 =  *((uint32_t*)pop(&(frame->operandStack))->value);
     push(&value1,&(frame->operandStack));
     push(&value2,&(frame->operandStack));

  return;
}
