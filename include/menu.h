/**
 * @file menu.h
 * @brief Command-line Interface library header.
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * This file contains all the function signatures used in the menus
 * and in the user choices processing.
 */

#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include <stdint.h>
#include "class.h"

/**
 * @todo Brief
 * @todo Description
 */
void showConstantPool();

/**
 * @todo Brief
 * @todo Description
 */
void showInterfaces();

/**
 * @todo Brief
 * @todo Description
 */
void showFields();

/**
 * @todo Brief
 * @todo Description
 */
void showField(Field fieldInfo);

/**
 * @todo Brief
 * @todo Description
 */
void showMethods();

/**
 * @todo Brief
 * @todo Description
 */
void showMethod(Method methodInfo);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showAttributes(Attribute* attributes, int attributes_count);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showAttribute(Attribute attribute);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showCode(uint8_t* code, int codeLength);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showExceptionTable(ExceptionTableEntry* exceptionTable, int exceptionTableLength);

/**
 * @brief Menu to specify .class file.
 *
 * @todo Description
 */
void chooseFile();

/**
 * @brief Shows the .class main menu.
 *
 * Shows the application main menu as CLI and gets the user option to do some
 * action. The available options are "Choose a .class file" and "Quit".
 */
void menu(char* arquivoInicial);

/**
 * @brief Process the user's option received on the .class viewer menu.
 *
 * @todo Description
 */
void displayOption(int userOption);

/**
 * @brief Gets the name of the file .class.
 *
 * @todo Description
 */
char* getNewName();

/**
 * @brief Clear the screen.
 *
 * @todo Description
 */
void clearScreen();

#endif //_MENU_H
