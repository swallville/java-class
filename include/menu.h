/**
 * @file menu.h
 * @brief Command-line Interface library header.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
 *
 * This file contains all the function signatures used in the menus
 * and in the user choices processing.
 */

#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include "class.h"

/**
 * @brief Shows the JVM main menu.
 *
 * Shows the application main menu as CLI and gets the user option to do some
 * action. The available options are "Choose a .class file" and "Quit".
 * Here, the user can choose to set a .class file and after this,
 * the class file structure is shown in this menu.
 */
void viewer();

/**
 * @brief Process the user's option received on the .class viewer menu.
 *
 * @todo Description
 */
void viewerOption(int userOption);

/**
 * @todo Brief
 * @todo Description
 */
void showConstantPool();

/**
 * @todo Brief
 * @todo Description
 */
void showConstant(ConstPoolInfo cpInfo);

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
void showField(FieldInfo fieldInfo);

/**
 * @todo Brief
 * @todo Description
 */
void showMethods();

/**
 * @todo Brief
 * @todo Description
 */
void showMethod(MethodInfo methodInfo);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showAttributes(AttributeInfo* attributes, int attributesCount);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showAttribute(AttributeInfo attribute);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showCode(u1* code, int codeLength);

/**
 * @todo Brief
 * @todo Description
 * @todo Parameters
 */
void showExceptionTable(ExceptionTableEntry* exceptionTable, int exceptionTableLength);

/**
 * @brief Shows the menu that let the user to choose some .class file.
 *
 * @todo Description
 */
void chooseFile();

/**
 * @brief Gets the short name of the local userfilePath.
 *
 * @todo Description
 */
char* getShortName();

/**
 * @brief Clears the current screen.
 *
 * @todo Description
 */
void clearScreen();

#endif //_MENU_H
