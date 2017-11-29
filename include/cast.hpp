/**
* @file cast.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de conversão de tipos.
*/

#ifndef CAST_H
#define CAST_H

#include "instruction.hpp"
#include "stack.hpp"
#include "class.hpp"
#include <math.h>
/**
*   @fn void i_i2l(Frame*)
*   @brief Função que desempilha um inteiro, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2l(Frame*);

/**
*   @fn void i_i2f(Frame*)
*   @brief Função que desempilha um inteiro, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2f(Frame*);

/**
*   @fn void i_i2d(Frame*)
*   @brief Função que desempilha um inteiro, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2d(Frame*);

/**
*   @fn void i_l2i(Frame*)
*   @brief Função que desempilha um long, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2i(Frame*);

/**
*   @fn void i_l2f(Frame*)
*   @brief Função que desempilha um long, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2f(Frame*);

/**
*   @fn void i_l2d(Frame*)
*   @brief Função que desempilha um long, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2d(Frame*);

/**
*   @fn void i_f2i(Frame*)
*   @brief Função que desempilha um float, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2i(Frame*);

/**
*   @fn void i_f2l(Frame*)
*   @brief Função que desempilha um float, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2l(Frame*);

/**
*   @fn void i_f2d(Frame*)
*   @brief Função que desempilha um float, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2d(Frame*);

/**
*   @fn void i_d2i(Frame*)
*   @brief Função que desempilha um double, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2i(Frame*);

/**
*   @fn void i_d2l(Frame*)
*   @brief Função que desempilha um double, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2l(Frame*);

/**
*   @fn void i_d2f(Frame*)
*   @brief Função que desempilha um double, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2f(Frame*);

/**
*   @fn void i_i2b(Frame*)
*   @brief Função que desempilha um inteiro, converte para byte e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2b(Frame*);

/**
*   @fn void i_i2c(Frame*)
*   @brief Função que desempilha um inteiro, converte para char e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2c(Frame*);

/**
*   @fn void i_i2s(Frame*)
*   @brief Função que desempilha um inteiro, converte para short e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2s(Frame*);

#endif // CAST_H
