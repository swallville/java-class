/**
* @file const.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de empilhamento de constantes.
*/

#ifndef CONST_H
#define CONST_H

#include "instruction.hpp"
#include "class.hpp"
#include <math.h>

/**
*   @fn void i_aconst_null(Frame*)
*   @brief Função que empilha o valor NULL.
*   @param frame Frame corrente.
*   @return
*/
void i_aconst_null(Frame*);

/**
*   @fn void i_aconst_m1(Frame*)
*   @brief Função que empilha o inteiro de valor -1.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_m1(Frame*);

/**
*   @fn void i_iconst_0(Frame*)
*   @brief Função que empilha o inteiro de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_0(Frame*);

/**
*   @fn void i_iconst_1(Frame*)
*   @brief Função que empilha o inteiro de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_1(Frame*);

/**
*   @fn void i_iconst_2(Frame*)
*   @brief Função que empilha o inteiro de valor 2.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_2(Frame*);

/**
*   @fn void i_iconst_3(Frame*)
*   @brief Função que empilha o inteiro de valor 3.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_3(Frame*);

/**
*   @fn void i_iconst_4(Frame*)
*   @brief Função que empilha o inteiro de valor 4.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_4(Frame*);

/**
*   @fn void i_iconst_5(Frame*)
*   @brief Função que empilha o inteiro de valor 5.
*   @param frame Frame corrente.
*   @return
*/
void i_iconst_5(Frame*);

/**
*   @fn void i_lconst_0(Frame*)
*   @brief Função que empilha o long de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_lconst_0(Frame*);

/**
*   @fn void i_lconst_1(Frame*)
*   @brief Função que empilha o long de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_lconst_1(Frame*);

/**
*   @fn void i_lconst_1(Frame*)
*   @brief Função que empilha o float de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_0(Frame*);

/**
*   @fn void i_lconst_1(Frame*)
*   @brief Função que empilha o float de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_1(Frame*);

/**
*   @fn void i_lconst_2(Frame*)
*   @brief Função que empilha o float de valor 2.
*   @param frame Frame corrente.
*   @return
*/
void i_fconst_2(Frame*);

/**
*   @fn void i_dconst_0(Frame*)
*   @brief Função que empilha o double de valor 0.
*   @param frame Frame corrente.
*   @return
*/
void i_dconst_0(Frame*);

/**
*   @fn void i_dconst_1(Frame*)
*   @brief Função que empilha o double de valor 1.
*   @param frame Frame corrente.
*   @return
*/
void i_dconst_1(Frame*);

#endif // CONST_H
