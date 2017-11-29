/**
* @file pop_dup_swap.hpp
* @author Lukas Ferreira Machado
* @brief Arquivo com definição de protótipos pras funções que implementam as instruções de pop, dup e swap.
*/

#ifndef POP_DUP_SWAP_H
#define POP_DUP_SWAP_H

#include "instruction.hpp"
#include "stack.hpp"
#include "class.hpp"
#include <math.h>

/**
*   @fn void i_pop(Frame*)
*   @brief Descarta o valor no topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_pop(Frame*);

/**
*   @fn void i_pop2(Frame*)
*   @brief Descarta os dois valores no topo da pilha, ou um valor se for double ou long.
*   @param frame Frame corrente.
*   @return
*/
void i_pop2(Frame*);

/**
*   @fn void i_dup(Frame*)
*   @brief Duplica o valor no topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_dup(Frame*);

/**
*   @fn void i_dup_x1(Frame*)
*   @brief Duplica o valor no topo da pilha, inserindo a cópia dois valores abaixo da pilha. O valor no topo e imediatamente abaixo do topo, não podem ser do tipo Double ou Long.
*   @param frame Frame corrente.
*   @return
*/
void i_dup_x1(Frame*);

/**
*   @fn void i_dup_x2(Frame*)
*   @brief Duplica o valor no topo da pilha, inserindo a cópia 3 valores abaixo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_dup_x2(Frame*);

/**
*   @fn void i_dup2(Frame*)
*   @brief Duplica os dois valores no topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_dup2(Frame*);

/**
*   @fn void i_dup2_x1(Frame*)
*   @brief Duplica os dois valores no topo da pilha. Inserindo as cópias abaixo da terceira posição em relação ao topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_dup2_x1(Frame*);

/**
*   @fn void i_dup2_x2(Frame*)
*   @brief Duplica os dois valores no topo da pilha. Inserindo as cópias abaixo da quarta posição em relação ao topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_dup2_x2(Frame*);

/**
*   @fn void i_swap(Frame*)
*   @brief Troca a posição entre os dois valores no topo da pilha.
*   @param frame Frame corrente.
*   @return
*/
void i_swap(Frame*);

#endif
