/**
 * @file mem-manager.h
 * @brief Memory management operations library header.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all type definitions and function signatures used to
 * manage dynamic allocation of memory.Contains a function that deallocates
 * all memory used,to avoid memory leak.
 */

#ifndef _MEM_MANAGER_H
#define _MEM_MANAGER_H

#include <stdlib.h>

/**
 * @brief Struct of Memory Manager
 *
 * This struct holds all components of the Memory Manager's struct.
 * Its a list that holds all memory allocation of the program into a single place.
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
 * Allocates a space of memory with a specific length.
 *
 * @param memorySpace - The length of the block of memory.
 * @returns Reference to the new block of memory.
 */
void* set_mem(size_t memorySpace);

/**
 * @brief Deallocates a space of memory.
 *
 * Deallocates a space of memory referenced by a pointer.
 *
 * @param pointer - The reference to the pointer that references to the space
 * of memory that is wanted to be deallocated.
 */
void free_mem(void** pointer);

/**
 * @brief Free all pointers from the memory manager.
 *
 * Free all nodes from the memory manager list.
 */
void freeMemManager();

/**
 * @brief Initializses a Memory Manager.
 *
 * Set space for a new memory manager.
 *
 * @param elemRef - Pointer of the first element of the new memory manager.
 * @returns The reference of the new memory manager.
 */
MemManager* memInit(void* elemRef);

/**
 * @brief Adds a new node to a memory manager.
 *
 * Adds a new element to the memory manager.
 *
 * @param managerRef - The reference of the memory manager that holds
 * all the memory allocation.
 * @param elemRef - The reference of the element to be added.
 */
void memAdd(MemManager** managerRef, void* elemRef);

/**
 * @brief Deletes a node from the memory manager.
 *
 * Deletes a node from the memory manager.
 *
 * @param managerRef - The reference of the memory manager that holds
 * all the memory allocation.
 * @param elemRef -The reference of the element to be deleted.
 * @returns The Reference of the node that was deleted from the memory manager.
 * return no value, if the element was not found.
 */
MemManager* memDelete(MemManager** managerRef, void* elemRef);

#endif // _MEM_MANAGER_H
