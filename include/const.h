/**
* @file const.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de empilhamento de constantes.
*/

#ifndef CONST_H
#define CONST_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>

/**
*   @fn void i_aconst_null(Frame* frame)
*   @brief Função que empilha o valor NULL.
*   @param frame Frame corrente.
*   @return
*/
void i_aconst_null(Frame* frame);

/**
*   @fn void i_aconst_m1(Frame* frame)
*   @brief Função que empilha o inteiro de valor -1.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_m1(Frame* frame);

/**
*   @fn void i_iconst_0(Frame* frame)
*   @brief Função que empilha o inteiro de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_0(Frame* frame);

/**
*   @fn void i_iconst_1(Frame* frame)
*   @brief Função que empilha o inteiro de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_1(Frame* frame);

/**
*   @fn void i_iconst_2(Frame* frame)
*   @brief Função que empilha o inteiro de valor 2.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_2(Frame* frame);

/**
*   @fn void i_iconst_3(Frame* frame)
*   @brief Função que empilha o inteiro de valor 3.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_3(Frame* frame);

/**
*   @fn void i_iconst_4(Frame* frame)
*   @brief Função que empilha o inteiro de valor 4.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_4(Frame* frame);

/**
*   @fn void i_iconst_5(Frame* frame)
*   @brief Função que empilha o inteiro de valor 5.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_5(Frame* frame);

/**
*   @fn void i_lconst_0(Frame* frame)
*   @brief Função que empilha o long de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_lconst_0(Frame* frame);

/**
*   @fn void i_lconst_1(Frame* frame)
*   @brief Função que empilha o long de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_lconst_1(Frame* frame);

/**
*   @fn void i_lconst_1(Frame* frame)
*   @brief Função que empilha o float de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_0(Frame* frame);

/**
*   @fn void i_lconst_1(Frame* frame)
*   @brief Função que empilha o float de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_1(Frame* frame);

/**
*   @fn void i_lconst_2(Frame* frame)
*   @brief Função que empilha o float de valor 2.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_2(Frame* frame);

/**
*   @fn void i_dconst_0(Frame* frame)
*   @brief Função que empilha o double de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_dconst_0(Frame* frame);

/**
*   @fn void i_dconst_1(Frame* frame)
*   @brief Função que empilha o double de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_dconst_1(Frame* frame);

#endif // CONST_H
