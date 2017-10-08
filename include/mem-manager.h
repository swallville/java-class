/**
 * @file mem-manager.h
 * @brief Memory management operations library header.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all type definitions and function signatures used to
 * manage dynamic allocation of memory. There is the definition of list that
 * contains pointers allocated and these will be stored until it's not usable.
 * It contains a function that deallocates all memory used, it is usuful to
 * avoid memory leak.
 */

#ifndef _MEM_MANAGER_H
#define _MEM_MANAGER_H

#include <stdlib.h>

/**
 * @brief Memory Manager structure definition.
 *
 * This definition represents the structure of each node of the list.
 * This list stores all allocated pointers to have the control in a single
 * place of all memory allocation of the program. The operation in this
 * structure has to follow the constraint that each node has to be a unique
 * element. The type definition of the structure is MemManager.
 */
typedef struct _mem_manager {

    /**
     * @brief Reference to the node's element.
     *
     * This member is a reference to the element of a specific node. It is
     * pointer to void exactly to support all kinds of pointers.
     */
    void* elemRef;

    /**
     * @brief Reference to the next node of the list.
     *
     * This member is a reference to the next node of the list.
     */
    struct _mem_manager* next;
}MemManager;

/**
 * @brief Initializses a Memory Manager.
 *
 * Allocates space for a new memory manager and set the reference to its first
 * element, received as parameter. And returns the reference of this manager.
 *
 * @param elemRef - The reference of the element of the first node of this new
 * memory manager.
 * @returns The reference of the new memory manager.
 */
MemManager* memInit(void* elemRef);

/**
 * @brief Adds a new node to a memory manager.
 *
 * Adds a new node to the memory manager, received by reference, with a
 * element, received as parameter. If there is some node with the same
 * element, this function avoids duplicates not allocating a new node.
 *
 * @param managerRef - The reference of the memory manager that it's wanted to
 * add a new node.
 * @param elemRef - The reference of the element of the new node.
 */
void memAdd(MemManager** managerRef, void* elemRef);

/**
 * @brief Deletes a node from the memory manager.
 *
 * Deletes a node from the memory manager, if it exists. It it doesn't, the
 * function returns no value. It follows the idea that each node is identified
 * by its element reference.
 *
 * @param managerRef - The reference of the memory manager that it's wanted
 * to delete some node.
 * @param elemRef - The reference of the element that identifies the node to
 * be deleted.
 * @returns The Reference of the node that was deleted from the memory manager.
 * return no value, if the node was not found.
 */
MemManager* memDelete(MemManager** managerRef, void* elemRef);

/**
 * @brief Allocates a new space of memory.
 *
 * Allocates a space of memory with a specific length, received as parameter.
 * This method adds a new node to the memory manager, if it was initialized
 * before, if it isn't, the memory manager is created and initalized with
 * a pointer to this new space of memory as first node's element.
 *
 * @param memorySpace - The length of the block of memory that it's needed to
 * be dinamically allocated.
 * @returns Reference to the new block of memory. This pointer needed to be
 * casted to a specific type of data.
 */
void* allocate(size_t memorySpace);

/**
 * @brief Deallocates a space of memory.
 *
 * Deallocates a space of memory referenced by a pointer, received as parameter.
 * It deletes this reference from the memory manager and the pointer with no
 * value to erase that reference from the memory.
 *
 * @param pointer - The reference to the pointer that references to the space
 * of memory that is wanted to be deallocated.
 */
void deallocate(void** pointer);

/**
 * @brief Free all pointers from the memory manager.
 *
 * Free all node from the memory manager list, erasing all references and
 * freeing all memories. This function is important to be used to avoid
 * memory leaking.
 */
void freeMemManager();

#endif // _MEM_MANAGER_H
