/**
* @file load.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de load(empilham valores que estão contidos em variaveis locais).
*/

#ifndef LOAD_H
#define LOAD_H

#include "instruction.hpp"
#include "class.hpp"
#include "others.hpp"
#include <math.h>

/**
*   @fn void i_iload(Frame*, int8_t)
*   @brief Empilha o inteiro localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_iload(Frame*, int8_t);

/**
*   @fn void i_lload(Frame*, int8_t)
*   @brief Empilha o long localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_lload(Frame*, int8_t);

/**
*   @fn void i_fload(Frame*, int8_t)
*   @brief Empilha o float localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_fload(Frame*, int8_t);

/**
*   @fn void i_dload(Frame*, int8_t)
*   @brief Empilha o double localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_dload(Frame*, int8_t);

/**
*   @fn void i_aload(Frame*, int8_t)
*   @brief Empilha a referência ao objeto localizado no indice do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_aload(Frame*, int8_t);

/**
*   @fn void i_iload_0(Frame*)
*   @brief Empilha o inteiro localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_iload_0(Frame*);

/**
*   @fn void i_iload_1(Frame*)
*   @brief Empilha o inteiro localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_1(Frame*);

/**
*   @fn void i_iload_2(Frame*)
*   @brief Empilha o inteiro localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_2(Frame*);

/**
*   @fn void i_iload_3(Frame*)
*   @brief Empilha o inteiro localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_iload_3(Frame*);

/**
*   @fn void i_lload_0(Frame*)
*   @brief Empilha o long localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_0(Frame*);

/**
*   @fn void i_lload_1(Frame*)
*   @brief Empilha o long localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_1(Frame*);

/**
*   @fn void i_lload_2(Frame*)
*   @brief Empilha o long localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_2(Frame*);

/**
*   @fn void i_lload_3(Frame*)
*   @brief Empilha o long localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lload_3(Frame*);

/**
*   @fn void i_fload_0(Frame*)
*   @brief Empilha o float localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_0(Frame*);

/**
*   @fn void i_fload_1(Frame*)
*   @brief Empilha o float localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_1(Frame*);

/**
*   @fn void i_fload_2(Frame*)
*   @brief Empilha o float localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_2(Frame*);

/**
*   @fn void i_fload_3(Frame*)
*   @brief Empilha o float localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fload_3(Frame*);

/**
*   @fn void i_dload_0(Frame*)
*   @brief Empilha o double localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_0(Frame*);

/**
*   @fn void i_dload_1(Frame*)
*   @brief Empilha o double localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_1(Frame*);

/**
*   @fn void i_dload_2(Frame*)
*   @brief Empilha o double localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_2(Frame*);

/**
*   @fn void i_dload_3(Frame*)
*   @brief Empilha o double localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dload_3(Frame*);

/**
*   @fn void i_aload_0(Frame*)
*   @brief Empilha o referência ao objeto localizado no indice 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_0(Frame*);

/**
*   @fn void i_aload_1(Frame*)
*   @brief Empilha o referência ao objeto localizado no indice 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_1(Frame*);

/**
*   @fn void i_aload_2(Frame*)
*   @brief Empilha o referência ao objeto localizado no indice 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_2(Frame*);

/**
*   @fn void i_aload_3(Frame*)
*   @brief Empilha o referência ao objeto localizado no indice 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_aload_3(Frame*);

/**
*   @fn void i_iaload(Frame*)
*   @brief Empilha um inteiro a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_iaload(Frame*);

/**
*   @fn void i_laload(Frame*)
*   @brief Empilha um long a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_laload(Frame*);

/**
*   @fn void i_faload(Frame*)
*   @brief Empilha um float a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_faload(Frame*);

/**
*   @fn void i_daload(Frame*)
*   @brief Empilha um double a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_daload(Frame*);

/**
*   @fn void i_aaload(Frame*)
*   @brief Empilha a referência a um objeto a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_aaload(Frame*);

/**
*   @fn void i_baload(Frame*)
*   @brief Empilha um byte a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_baload(Frame*);

/**
*   @fn void i_iaload(Frame*)
*   @brief Empilha um char a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_caload(Frame*);

/**
*   @fn void i_iaload(Frame*)
*   @brief Empilha um short a partir de um array. Desempilha a referência ao array e o indice, posterior a isso empilha o valor.
*   @param frame Frame corrente.
*   @return
*/
void i_saload(Frame*);

#endif
