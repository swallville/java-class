/**
 * @file heap.hpp
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * @todo Description
 */

#ifndef _HEAP_H
#define _HEAP_H

#include <string.h>
#include <vector>
#include "class.hpp"
#include "mem-manager.hpp"

typedef struct tipoarray
{
    int8_t tag;
    uint32_t tamanho;
    uint32_t tamanho1;
    void* reference_helper;
    int array_pos;
    int base_array_pos;
    bool is_multarray;
    union
    {
        uint8_t *tipoBoolean;
        uint8_t *tipoByte;
        uint16_t *tipoChar;
        uint16_t *tipoShort;
        uint32_t *tipoReferencia;
        uint32_t *tipoInt;
        uint32_t *tipoFloat;
        uint64_t *tipoLong;
        uint64_t *tipoDouble;
    } info;
} tArray;

typedef struct tipoobjeto
{
    Class    *classe;
    uint16_t tamanhotipoField;
    std::vector<int32_t> tipofield;
    //uint32_t *tipofield;
} Objeto;

typedef struct
{
	char     *NomeClasse;
  char     *Type_name;
	uint16_t  fieldCount;
	std::vector<int32_t> valor;
} staticField;

typedef struct heap
{
    std::vector<staticField> listaStaticField;
    std::vector<tArray> listaDeArrays;
    std::vector<Objeto> listaDeObjetos;
    std::vector<Class> listaDeClasses;
    //struct pilhadeframes    *pilhaDeFrames;
} Heap;

/**
*   @fn Heap* InicializaHeap()
*   @brief Funcao que inicializa a Heap do programa.
*   @return Heap alocada.
*/
Heap* InicializaHeap();

/**
*   @fn void desalocaHeap(Heap *heap)
*   @brief Funcao que inicializa a Heap do programa.
*   @param Heap a ser desalocada.
*/
void desalocaHeap(Heap*);

#endif /* _HEAP_H */
