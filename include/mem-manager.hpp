/**
 * @file mem-manager.hpp
 * @brief Memory management operations library header.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all type definitions and function signatures used to
 * manage dynamic allocation of memory.
 */

#ifndef _MEM_MANAGER_H
#define _MEM_MANAGER_H

#include <stdlib.h>

/**
 * @brief Struct of Memory Manager
 *
 * This struct holds all Memory Manager's struct.
 * Its a list that holds all memory of the program.
 * The type definition of the structure is MemManager.
 */
typedef struct _mem_manager {

    /**
     * @brief Pointer to the memory node.
     *
     * This pointer specifies a pointer to the memory instance allocated.
     */
    void* elemRef;

    /**
     * @brief Pointer to the next memory instance.
     *
     * Pointer to the next list node.
     */
    struct _mem_manager* next;
}MemManager;

/**
 * @brief Allocates a new space of memory.
 *
 * Set a memory block of length memorySpace.
 *
 * @param memorySpace - The length of the block of memory.
 * @returns Reference to the new block of memory.
 */
void* set_mem(size_t);

/**
 * @brief Deallocates a space of memory.
 *
 * Free a space of memory referenced by the param pointer.
 *
 * @param pointer - The reference to the pointer that references the memory
 * to be free.
 */
void free_mem(void**);

/**
 * @brief Free all pointers from the memory manager.
 *
 * Free all MemManager main instance.
 */
void freeMemManager();

/**
 * @brief Initializses a Memory Manager.
 *
 * Set space for a new memory manager.
 *
 * @param elemRef - Pointer of the first element of the new memory manager.
 * @returns Reference for the new MemManager instance.
 */
MemManager* memInit(void*);

/**
 * @brief Adds a new memory instance
 *
 * Adds a new element to the memory manager.
 *
 * @param managerRef - The reference of the memory manager.
 * @param elemRef - The reference of the element to be added.
 */
void memAdd(MemManager**, void*);

/**
 * @brief Deletes a memory instance
 *
 * Deletes a node from the memory manager.
 *
 * @param managerRef - The reference of the memory manager.
 * @param elemRef -The element to be deleted.
 * @returns The Reference of the instance deleted.
 * NULL with not found.
 */
MemManager* memDelete(MemManager**, void*);

#endif // _MEM_MANAGER_H
