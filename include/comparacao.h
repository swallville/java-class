/**
* @file comparacao.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de comparação.
*/

#ifndef COMPARACAO_H
#define COMPARACAO_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>

/**
*   @fn void i_lcmp(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_lcmp(Frame* frame);

/**
*   @fn void i_fcmpl(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpl(Frame* frame);

/**
*   @fn void i_fcmpg(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpg(Frame* frame);

/**
*   @fn void i_dcmpl(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpl(Frame* frame);

/**
*   @fn void i_dcmpg(Frame* frame)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpg(Frame* frame);

#endif // COMPARACAO_H
