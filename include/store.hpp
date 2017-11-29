/**
* @file store.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções que salvam os valores da pilha em variáveis(Vetor de variveis locais).
*/

#ifndef STORE_H
#define STORE_H

#include "instruction.hpp"
#include "stack.hpp"
#include "class.hpp"
#include <math.h>

/**
*   @fn void i_istore(Frame*, uint8_t)
*   @brief Desempilha o inteiro e salva na variável indicada pelo index.
*   @param frame Frame corrente.
*   @param index Indice para localização do inteiro no vetor de variáveis locais.
*   @return
*/
void i_istore(Frame*, uint8_t);

/**
*   @fn void i_istore(Frame*, uint8_t)
*   @brief Desempilha o long e salva na variável indicada pelo index.
*   @param frame Frame corrente.
*   @param index Indice para localização do long no vetor de variáveis locais.
*   @return
*/
void i_lstore(Frame*, uint8_t);

/**
*   @fn void i_fstore(Frame*, uint8_t)
*   @brief Desempilha o float e salva na variável indicada pelo index.
*   @param frame Frame corrente.
*   @param index Indice para localização do float no vetor de variáveis locais.
*   @return
*/
void i_fstore(Frame*, uint8_t);

/**
*   @fn void i_dstore(Frame*, uint8_t)
*   @brief Desempilha o double e salva na variável indicada pelo index.
*   @param frame Frame corrente.
*   @param index Indice para localização do double no vetor de variáveis locais.
*   @return
*/
void i_dstore(Frame*, uint8_t);

/**
*   @fn void i_astore(Frame*, uint8_t)
*   @brief Desempilha a referencia e salva na variável indicada pelo index.
*   @param frame Frame corrente.
*   @param index Indice para localização do da referencia no vetor de variáveis locais.
*   @return
*/
void i_astore(Frame*, uint8_t);

/**
*   @fn void i_istore_0(Frame*)
*   @brief Desempilha o inteiro e salva na posição 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_istore_0(Frame*);

/**
*   @fn void i_istore_1(Frame*)
*   @brief Desempilha o inteiro e salva na posição 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_istore_1(Frame*);

/**
*   @fn void i_istore_2(Frame*)
*   @brief Desempilha o inteiro e salva na posição 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_istore_2(Frame*);

/**
*   @fn void i_istore_3(Frame*)
*   @brief Desempilha o inteiro e salva na posição 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_istore_3(Frame*);

/**
*   @fn void i_lstore_0(Frame*)
*   @brief Desempilha o long e salva na posição 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lstore_0(Frame*);

/**
*   @fn void i_lstore_1(Frame*)
*   @brief Desempilha o long e salva na posição 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lstore_1(Frame*);

/**
*   @fn void i_lstore_2(Frame*)
*   @brief Desempilha o long e salva na posição 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lstore_2(Frame*);

/**
*   @fn void i_lstore_3(Frame*)
*   @brief Desempilha o long e salva na posição 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_lstore_3(Frame*);

/**
*   @fn void i_fstore_0(Frame*)
*   @brief Desempilha o float e salva na posição 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fstore_0(Frame*);

/**
*   @fn void i_fstore_1(Frame*)
*   @brief Desempilha o float e salva na posição 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fstore_1(Frame*);

/**
*   @fn void i_fstore_2(Frame*)
*   @brief Desempilha o float e salva na posição 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fstore_2(Frame*);

/**
*   @fn void i_fstore_3(Frame*)
*   @brief Desempilha o float e salva na posição 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_fstore_3(Frame*);

/**
*   @fn void i_dstore_0(Frame*)
*   @brief Desempilha o double e salva na posição 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dstore_0(Frame*);

/**
*   @fn void i_dstore_1(Frame*)
*   @brief Desempilha o double e salva na posição 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dstore_1(Frame*);

/**
*   @fn void i_dstore_2(Frame*)
*   @brief Desempilha o double e salva na posição 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dstore_2(Frame*);

/**
*   @fn void i_dstore_3(Frame*)
*   @brief Desempilha o double e salva na posição 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_dstore_3(Frame*);

/**
*   @fn void i_astore_0(Frame*)
*   @brief Desempilha a referencia e salva na posição 0 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_astore_0(Frame*);

/**
*   @fn void i_astore_1(Frame*)
*   @brief Desempilha a referencia e salva na posição 1 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_astore_1(Frame*);

/**
*   @fn void i_astore_2(Frame*)
*   @brief Desempilha a referencia e salva na posição 2 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_astore_2(Frame*);

/**
*   @fn void i_astore_3(Frame*)
*   @brief Desempilha a referencia e salva na posição 3 do vetor de variáveis locais.
*   @param frame Frame corrente.
*   @return
*/
void i_astore_3(Frame*);

/**
*   @fn void i_iastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(inteiro) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_iastore(Frame*);

/**
*   @fn void i_lastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(long) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_lastore(Frame*);

/**
*   @fn void i_fastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(float) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_fastore(Frame*);

/**
*   @fn void i_dastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(double) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_dastore(Frame*);

/**
*   @fn void i_iastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(referencia) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_aastore(Frame*);

/**
*   @fn void i_bastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(byte) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_bastore(Frame*);

/**
*   @fn void i_castore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(char) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_castore(Frame*);

/**
*   @fn void i_sastore(Frame*)
*   @brief Desempilha a referencia para o array, o indice e o valor(short) e salva o valor no array.
*   @param frame Frame corrente.
*   @return
*/
void i_sastore(Frame*);

#endif // STORE_H
