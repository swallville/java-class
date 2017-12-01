#include "pop_dup_swap.hpp"


void i_pop(Frame* frame)
{
  frame->operandStack.pop();

  return;
}

void i_pop2(Frame* frame)
{
    frame->operandStack.pop();
    frame->operandStack.pop();

  return;
}

void i_dup(Frame* frame)
{
    frame->operandStack.push(frame->operandStack.top());

  return;
}

void i_dup_x1(Frame* frame)
{
    Data valueTop = frame->operandStack.top();
    frame->operandStack.pop();

    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(valor);
    frame->operandStack.push(valueTop);
    frame->operandStack.push(valor);

  return;
}

void i_dup_x2(Frame* frame)
{
    Data valueTop = frame->operandStack.top();
    frame->operandStack.pop();

    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    Data valuefloor = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(valuefloor);
    frame->operandStack.push(valor);
    frame->operandStack.push(valueTop);
    frame->operandStack.push(valuefloor);

  return;
}

void i_dup2(Frame* frame)
{
    Data valueTop = frame->operandStack.top();
    frame->operandStack.pop();

    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(valor);
    frame->operandStack.push(valueTop);
    frame->operandStack.push(valor);
    frame->operandStack.push(valueTop);

  return;
}

void i_dup2_x1(Frame* frame)
{
    Data valueTop = frame->operandStack.top();
    frame->operandStack.pop();

    Data valor = frame->operandStack.top();
    frame->operandStack.pop();

    Data valuefloor = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(valuefloor);
    frame->operandStack.push(valor);
    frame->operandStack.push(valueTop);
    frame->operandStack.push(valuefloor);
    frame->operandStack.push(valor);

  return;
}


void i_dup2_x2(Frame* frame)
{
    Data value1 = frame->operandStack.top();
    frame->operandStack.pop();

    Data value2 = frame->operandStack.top();
    frame->operandStack.pop();

    Data value3 = frame->operandStack.top();
    frame->operandStack.pop();

    Data value4 = frame->operandStack.top();
    frame->operandStack.pop();

    frame->operandStack.push(value4);
    frame->operandStack.push(value3);
    frame->operandStack.push(value2);
    frame->operandStack.push(value1);
    frame->operandStack.push(value4);
    frame->operandStack.push(value3);

  return;
}

void i_swap(Frame* frame)
{
     Data value1 =  frame->operandStack.top();
     frame->operandStack.pop();

     Data value2 =  frame->operandStack.top();
     frame->operandStack.pop();

     frame->operandStack.push(value1);
     frame->operandStack.push(value2);

  return;
}
