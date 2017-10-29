/**
* @file cast.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de conversão de tipos.
*/

#ifndef CAST_H
#define CAST_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>
/**
*   @fn void i_i2l(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2l(Frame* frame);

/**
*   @fn void i_i2f(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2f(Frame* frame);

/**
*   @fn void i_i2d(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2d(Frame* frame);

/**
*   @fn void i_l2i(Frame* frame)
*   @brief Função que desempilha um long, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2i(Frame* frame);

/**
*   @fn void i_l2f(Frame* frame)
*   @brief Função que desempilha um long, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2f(Frame* frame);

/**
*   @fn void i_l2d(Frame* frame)
*   @brief Função que desempilha um long, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_l2d(Frame* frame);

/**
*   @fn void i_f2i(Frame* frame)
*   @brief Função que desempilha um float, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2i(Frame* frame);

/**
*   @fn void i_f2l(Frame* frame)
*   @brief Função que desempilha um float, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2l(Frame* frame);

/**
*   @fn void i_f2d(Frame* frame)
*   @brief Função que desempilha um float, converte para double e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_f2d(Frame* frame);

/**
*   @fn void i_d2i(Frame* frame)
*   @brief Função que desempilha um double, converte para inteiro e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2i(Frame* frame);

/**
*   @fn void i_d2l(Frame* frame)
*   @brief Função que desempilha um double, converte para long e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2l(Frame* frame);

/**
*   @fn void i_d2f(Frame* frame)
*   @brief Função que desempilha um double, converte para float e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_d2f(Frame* frame);

/**
*   @fn void i_i2b(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para byte e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2b(Frame* frame);

/**
*   @fn void i_i2c(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para char e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2c(Frame* frame);

/**
*   @fn void i_i2s(Frame* frame)
*   @brief Função que desempilha um inteiro, converte para short e empilha novamente.
*   @param frame Frame corrente.
*   @return
*/
void i_i2s(Frame* frame);

#endif // CAST_H
