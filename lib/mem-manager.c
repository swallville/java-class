/**
 * @file mem-manager.c
 * @brief Memory management operations library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the mem-manager.h file.
 */

#include "mem-manager.h"

/**
 * @brief Library-global variable for the Memory Manager.
 *
 * The variable that store the first element of the Memory Manager, this value
 * can be accessed for all the function of this file. This variable are
 * initialized with no value.
 */
MemManager* memList = NULL;

MemManager* memInit(void* elemRef) {

    // Allocate memory for the new memory manager.
    MemManager *manager = (MemManager*) malloc(sizeof(MemManager));
    // Set the element reference.
    manager->elemRef = elemRef;
    manager->next = NULL;

    return manager;
}

void memAdd(MemManager** managerRef, void* elemRef) {

    // Searches for previous node with this elemRef to avoid duplicates.
    MemManager* node =  NULL;
    for (node = (*managerRef); node != NULL; node = node->next) {
        if (node->elemRef == elemRef) {
            // Does not allocate a new node.
            return;
        }
    }

    // Alocate memory for the new node.
    MemManager* newNode = (MemManager*) malloc(sizeof(MemManager));
    // Set the element reference.
    newNode->elemRef = elemRef;
    // Set this new node to be the first node of the list.
    newNode->next = (*managerRef);
    (*managerRef) = newNode;
}

MemManager* memDelete(MemManager** managerRef, void* elemRef) {

    // Searches for some node with this specific Reference.
    MemManager* node = NULL;
    MemManager* previous = NULL;
    for (node = (*managerRef); node != NULL; node = node->next) {

        // Compares that element refence value with elemRef.
        if (node->elemRef == elemRef) {

            // Verifies if it's the first element with "previous" variable
            // before eliminating the node.
            if (previous == NULL) {
                (*managerRef) = node->next;
            } else {
                previous->next = node->next;
            }
            // Returns the eliminated node.
            return node;
        }

        // Stores the previous node in this loop.
        previous = node;
    }

    // The node was not found.
    return NULL;
}

void* allocate(size_t memorySpace) {

    // Allocate the space of memory.
    void *pointer = malloc(memorySpace);
    // Verify if occurred some error on the allocation.
    if (pointer == NULL) {
        return NULL;
    }

    // Adds a new node to the memory manager or initializes it, if it wasn't
    // initialized before.
    if (memList == NULL) {
        memList = memInit(pointer);
    } else {
        memAdd(&memList, pointer);
    }

    // Returns the reference to the memory allocated successfully.
    return pointer;
}

void deallocate(void** pointer) {

    if (memList != NULL && (*pointer) != NULL) {

        // Deletes the node referenced by this pointer's value.
        MemManager* deletedNode = memDelete(&memList, (*pointer));
        // Verifies if the node has already been deleted.
        if (deletedNode != NULL) {
            // Erase all references and free the memory.
            deletedNode->elemRef = NULL; // The space referece by this value
            // are deallocated in the final of this function.
            deletedNode->next = NULL;
            free(deletedNode);
            deletedNode = NULL;
        }
    }

    // Finally, deallocate the memory and erase its reference.
    if ((*pointer) != NULL) {
        free((*pointer));
    }
    (*pointer) = NULL;
}

void freeMemManager() {

    if (memList != NULL) {
        // Iterate until the memory manager list are empty.
        while (memList != NULL) {

            // Stores first node and updates new memory reference with the
            // second element.
            MemManager *previous = memList;
            memList = memList->next;

            // Deallocate element's reference of the first node
            if (previous->elemRef != NULL) {
                free(previous->elemRef);
            }

            // Erase references and deallocate the node's space of memory.
            previous->elemRef = NULL;
            previous->next = NULL;
            free(previous);
            previous = NULL;
        }
    }
}
