/**
* @file load.h
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de load(empilham valores que estão contidos em variaveis locais).
*/

#ifndef LOAD_H
#define LOAD_H

#include "instruction.h"
#include "stack.h"
#include "class.h"
#include <math.h>

/**
*   @fn void i_iload(Frame* frame, uint8_t index)
*   @brief Empilha o inteiro localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_iload(Frame* frame, uint8_t index);

/**
*   @fn void i_lload(Frame* frame, uint8_t index)
*   @brief Empilha o long localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_lload(Frame* frame, uint8_t index);

/**
*   @fn void i_fload(Frame* frame, uint8_t index)
*   @brief Empilha o float localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_fload(Frame* frame, uint8_t index);

/**
*   @fn void i_dload(Frame* frame, uint8_t index)
*   @brief Empilha o double localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_dload(Frame* frame, uint8_t index);

/**
*   @fn void i_aload(Frame* frame, uint8_t index)
*   @brief Empilha a referência ao objeto localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_aload(Frame* frame, uint8_t index);

/**
*   @fn void i_iload_0(Frame* frame)
*   @brief Empilha o inteiro localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_iload_0(Frame* frame);

/**
*   @fn void i_iload_1(Frame* frame)
*   @brief Empilha o inteiro localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_1(Frame* frame);

/**
*   @fn void i_iload_2(Frame* frame)
*   @brief Empilha o inteiro localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_2(Frame* frame);

/**
*   @fn void i_iload_3(Frame* frame)
*   @brief Empilha o inteiro localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_3(Frame* frame);

/**
*   @fn void i_lload_0(Frame* frame)
*   @brief Empilha o long localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_0(Frame* frame);

/**
*   @fn void i_lload_1(Frame* frame)
*   @brief Empilha o long localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_1(Frame* frame);

/**
*   @fn void i_lload_2(Frame* frame)
*   @brief Empilha o long localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_2(Frame* frame);

/**
*   @fn void i_lload_3(Frame* frame)
*   @brief Empilha o long localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_3(Frame* frame);

/**
*   @fn void i_fload_0(Frame* frame)
*   @brief Empilha o float localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_0(Frame* frame);

/**
*   @fn void i_fload_1(Frame* frame)
*   @brief Empilha o float localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_1(Frame* frame);

/**
*   @fn void i_fload_2(Frame* frame)
*   @brief Empilha o float localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_2(Frame* frame);

/**
*   @fn void i_fload_3(Frame* frame)
*   @brief Empilha o float localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_3(Frame* frame);

/**
*   @fn void i_dload_0(Frame* frame)
*   @brief Empilha o double localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_0(Frame* frame);

/**
*   @fn void i_dload_1(Frame* frame)
*   @brief Empilha o double localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_1(Frame* frame);

/**
*   @fn void i_dload_2(Frame* frame)
*   @brief Empilha o double localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_2(Frame* frame);

/**
*   @fn void i_dload_3(Frame* frame)
*   @brief Empilha o double localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_3(Frame* frame);

/**
*   @fn void i_aload_0(Frame* frame)
*   @brief Empilha o referência ao objeto localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_0(Frame* frame);

/**
*   @fn void i_aload_1(Frame* frame)
*   @brief Empilha o referência ao objeto localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_1(Frame* frame);

/**
*   @fn void i_aload_2(Frame* frame)
*   @brief Empilha o referência ao objeto localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_2(Frame* frame);

/**
*   @fn void i_aload_3(Frame* frame)
*   @brief Empilha o referência ao objeto localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_3(Frame* frame);

/**
*   @fn void i_iaload(Frame* frame)
*   @brief Empilha um inteiro a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_iaload(Frame* frame);

/**
*   @fn void i_laload(Frame* frame)
*   @brief Empilha um long a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_laload(Frame* frame);

/**
*   @fn void i_faload(Frame* frame)
*   @brief Empilha um float a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_faload(Frame* frame);

/**
*   @fn void i_daload(Frame* frame)
*   @brief Empilha um double a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_daload(Frame* frame);

/**
*   @fn void i_aaload(Frame* frame)
*   @brief Empilha a referência a um objeto a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_aaload(Frame* frame);

/**
*   @fn void i_baload(Frame* frame)
*   @brief Empilha um byte a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_baload(Frame* frame);

/**
*   @fn void i_iaload(Frame* frame)
*   @brief Empilha um char a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_caload(Frame* frame);

/**
*   @fn void i_iaload(Frame* frame)
*   @brief Empilha um short a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_saload(Frame* frame);

#endif
