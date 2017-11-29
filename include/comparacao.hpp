/**
* @file comparacao.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de comparação.
*/

#ifndef COMPARACAO_H
#define COMPARACAO_H

#include "instruction.hpp"
#include "class.hpp"
#include <math.h>

/**
*   @fn void i_lcmp(Frame*)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_lcmp(Frame*);

/**
*   @fn void i_fcmpl(Frame*)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpl(Frame*);

/**
*   @fn void i_fcmpg(Frame*)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_fcmpg(Frame*);

/**
*   @fn void i_dcmpl(Frame*)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpl(Frame*);

/**
*   @fn void i_dcmpg(Frame*)
*   @brief Função que desempilha dois longs, compara ambos e empilha o resultado da comparação. Se são iguais empilha 0, se o segundo número for maior empilha 1, caso contrário empilha -1.
*   @param frame Frame corrente.
*   @return
*/
void i_dcmpg(Frame*);

#endif // COMPARACAO_H
