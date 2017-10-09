/**
 * @file menu.c
 * @brief Command-line Interface library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the menu.h file.
 */
#include <string.h>
#include "mem-manager.h"
#include "menu.h"
#include "convert.h"
#include "file.h"
#include "execute.h"

/**
 * @brief Global variable for the userfile pointer.
 *
 * @todo Description
 */
FILE* userfilePointer = NULL;

/**
 * @brief Global variable for the userfile path.
 *
 * @todo Description
 */
char userfilePath[255] = "";

/**
 * @brief Global variable for the main class variable.
 *
 * @todo Description
 */
Class* class = NULL;

void showConstantPool() {
    if (class->constantPool_count == 0) {
        printf("Empty array.\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                         Constant Pool                        |\n");
        printf("|==============================================================|\n");
        int cp_index;
        char* string = NULL;
        for (cp_index = 0; cp_index < class->constantPool_count - 1; cp_index++) {
            switch(class->constant_pool[cp_index].tag) {
                case LARGE_NUMERIC_CONTINUED:
                    printf("| [%-3d] (large numeric continued)                              |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case UTF8:
                    printf("| [%-3d] CONSTANT_Utf8_Info                                     |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = utf8ToString(class->constant_pool[cp_index].utf8_const.bytes, class->constant_pool[cp_index].utf8_const.length, false);
                    printf("| Length of bytes array: %-37d |\n", class->constant_pool[cp_index].utf8_const.length);
                    printf("| Length of string:      %-37zu |\n", strlen(string));
                    printf("| String:                %-37s |\n", string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case INTEGER:
                    printf("| [%-3d] CONSTANT_Integer_Info                                  |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf("| Bytes:   0x%.8X                                          |\n", class->constant_pool[cp_index].integer_const.bytes);
                    printf("| Integer: %-51d |\n", class->constant_pool[cp_index].integer_const.bytes);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case FLOAT:
                    printf("| [%-3d] CONSTANT_Float_Info                                    |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf("| Bytes: 0x%.8X                                            |\n", class->constant_pool[cp_index].integer_const.bytes);
                    printf("| Float: %-53f |\n", class->constant_pool[cp_index].float_const.value);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case LONG:
                    printf("| [%-3d] CONSTANT_Long_Info                                     |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf("| High bytes: 0x%.8X                                       |\n", class->constant_pool[cp_index].long_const.bytes.highBytes);
                    printf("| Low bytes:  0x%.8X                                       |\n", class->constant_pool[cp_index].long_const.bytes.lowBytes);
                    printf("| Long:       %-48ld |\n", class->constant_pool[cp_index].long_const.value);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case DOUBLE:
                    printf("| [%-3d] CONSTANT_Double_Info                                   |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf("| High bytes: 0x%.8X                                       |\n", class->constant_pool[cp_index].double_const.bytes.highBytes);
                    printf("| Low bytes:  0x%.8X                                       |\n", class->constant_pool[cp_index].double_const.bytes.lowBytes);
                    printf("| Double:     %-48lf |\n", class->constant_pool[cp_index].double_const.value);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case CLASS:
                    printf("| [%-3d] CONSTANT_Class_Info                                    |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].class_const.name_index, class->constant_pool, true);
                    printf("| Class name: cp_info #%-4d %-34s |\n", class->constant_pool[cp_index].class_const.name_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case STRING:
                    printf("| [%-3d] CONSTANT_String_Info                                   |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].string_const.string_index, class->constant_pool, true);
                    printf("| String: cp_info #%-4d %-38s |\n", class->constant_pool[cp_index].string_const.string_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case FIELD_REF:
                    printf("| [%-3d] CONSTANT_Fieldref_Info                                 |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
                    printf("| Class name:    cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].fieldRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
                    printf("| Name and type: cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].fieldRef_const.nameAndType_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case METHOD_REF:
                    printf("| [%-3d] CONSTANT_Methodref_Info                                |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
                    printf("| Class name:    cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].methodRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
                    printf("| Name and type: cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].methodRef_const.nameAndType_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case INTERFACE_METHOD_REF:
                    printf("| [%-3d] CONSTANT_InterfaceMethodref_Info                       |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
                    printf("| Class name:    cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].interfaceMethodRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
                    printf("| Name and type: cp_info #%-4d %-31s |\n", class->constant_pool[cp_index].interfaceMethodRef_const.nameAndType_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case NAME_AND_TYPE:
                    printf("| [%-3d] CONSTANT_NameAndType_Info                              |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].nameAndType_const.name_index, class->constant_pool, true);
                    printf("| Name:       cp_info #%-4d %-34s |\n", class->constant_pool[cp_index].nameAndType_const.name_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].nameAndType_const.descriptor_index, class->constant_pool, true);
                    printf("| Descriptor: cp_info #%-4d %-34s |\n", class->constant_pool[cp_index].nameAndType_const.descriptor_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;
            }
        }
        printf("|==============================================================|\n");
        printf("Press ENTER to return...");
        while(getchar() != '\n');
        clearScreen();
        break;
    }
}

void showInterfaces() {
    int interfaces_index;

    if (class->interfaces_count == 0) {
        printf("Empty array.\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                           Interfaces                         |\n");
    printf("|==============================================================|\n");

    for (interfaces_index = 0; interfaces_index < class->interfaces_count; interfaces_index++) {
        char* interface = getUtf8FromConstantPool(class->constant_pool[class->interfaces[interfaces_index] - 1].class_const.name_index, class->constant_pool, true);
        printf("| cp_info #%-4d %-46s |\n", class->interfaces[interfaces_index], interface);
        free_mem( (void**) &interface);
    }
    printf("|==============================================================|\n");
    printf("Press enter to return...\n");
    while(getchar() != '\n');
    clearScreen();
}

void showFields() {
    int userOption;

    if (class->fields_count == 0) {
        printf("Empty Array\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                            Fields                            |\n");
        printf("|==============================================================|\n");

        for (int field_index = 0; field_index < class->fields_count; field_index++) {
            char* name = getUtf8FromConstantPool(class->fields[field_index].name_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", field_index, name);
            free_mem( (void**) &name );
        }
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a field                                            |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");
        scanf("%d", &userOption);
        while(getchar() != '\n');
        if (userOption == 1) {
            while(true) {
                int chosenField;
                printf("index: ");
                scanf("%d", &chosenField);
                while(getchar() != '\n');

                if (chosenField >= 0 && chosenField < class->fields_count) {
                    clearScreen();
                    showField(class->fields[chosenField]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) {
            clearScreen();
            break;
        } else {
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }

    }
}

void showField(Field fieldInfo) {
    int userOption;

    while(true) {
        char* name = getUtf8FromConstantPool(fieldInfo.name_index, class->constant_pool, false);
        char* nameRef = getUtf8FromConstantPool(fieldInfo.name_index, class->constant_pool, true);
        char* descriptorRef = getUtf8FromConstantPool(fieldInfo.descriptor_index, class->constant_pool, true);
        char* access_flags = map_flags(fieldInfo.access_flags);

        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", fieldInfo.name_index, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", fieldInfo.descriptor_index, descriptorRef);
        free_mem( (void**) &name );
        free_mem( (void**) &nameRef );
        free_mem( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X %-34s  |\n", fieldInfo.access_flags, access_flags);
        printf("| Attributes count: %-42d |\n", fieldInfo.attributes_count);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");
        free_mem( (void**) &access_flags );

        scanf("%d", &userOption);
        while(getchar() != '\n');

        if (userOption == 1) {
            clearScreen();
            showAttributes(fieldInfo.attributes, fieldInfo.attributes_count);
        } else if (userOption == 2) {
            clearScreen();
            break;
        } else {
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showMethods() {
    int userOption;

    if (class->methods_count == 0) {
        printf("Empty Array\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                           Methods                            |\n");
        printf("|==============================================================|\n");

        for (int method_index = 0; method_index < class->methods_count; method_index++) {
            char* name = getUtf8FromConstantPool(class->methods[method_index].name_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", method_index, name);
            free_mem( (void**) &name );
        }

        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a method                                           |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");
        scanf("%d", &userOption);
        while(getchar() != '\n');

        if (userOption == 1) {
            while(true) {
                int chosenMethod;
                printf("index: ");
                scanf("%d", &chosenMethod);
                while(getchar() != '\n');
                if (chosenMethod >= 0 && chosenMethod < class->methods_count) {
                    clearScreen();
                    showMethod(class->methods[chosenMethod]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) {
            clearScreen();
            break;
        } else {
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showMethod(Method methodInfo) {
    int userOption;

    while(true) {
        char* name = getUtf8FromConstantPool(methodInfo.name_index, class->constant_pool, false);
        char* nameRef = getUtf8FromConstantPool(methodInfo.name_index, class->constant_pool, true);
        char* descriptorRef = getUtf8FromConstantPool(methodInfo.descriptor_index, class->constant_pool, true);
        char* access_flags = map_flags(methodInfo.access_flags);

        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", methodInfo.name_index, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", methodInfo.descriptor_index, descriptorRef);
        free_mem( (void**) &name );
        free_mem( (void**) &nameRef );
        free_mem( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X %-34s  |\n", methodInfo.access_flags, access_flags);
        printf("| Attributes count: %-42d |\n", methodInfo.attributes_count);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");
        free_mem( (void**) &access_flags );
        scanf("%d", &userOption);
        while(getchar() != '\n');
        if (userOption == 1) {
            clearScreen();
            showAttributes(methodInfo.attributes, methodInfo.attributes_count);
        } else if (userOption == 2) {
            clearScreen();
            break;
        } else {
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showAttributes(Attribute* attributes, int attributes_count) {
    int userOption;

    if (attributes_count == 0) {
        printf("Empty Array\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                        Attributes                            |\n");
        printf("|==============================================================|\n");

        int attr_index;
        for (attr_index = 0; attr_index < attributes_count; attr_index++) {
            char* string = getUtf8FromConstantPool(attributes[attr_index].attributeName_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", attr_index, string);
            free_mem( (void**) &string );
        }

        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a attribute                                        |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");
        scanf("%d", &userOption);
        while(getchar() != '\n');
        if (userOption == 1) {
            while(true) {
                int chosenAttribute;
                printf("index: ");
                scanf("%d", &chosenAttribute);
                while(getchar() != '\n');
                if (chosenAttribute >= 0 && chosenAttribute < class->attributes_count) {
                    clearScreen();
                    showAttribute(attributes[chosenAttribute]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) {
            clearScreen();
            break;
        } else {
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }

    }
}

void showAttribute(Attribute attrInfo) {
    while(true) {
        char* name = getUtf8FromConstantPool(attrInfo.attributeName_index, class->constant_pool, false);
        char* nameRef = getUtf8FromConstantPool(attrInfo.attributeName_index, class->constant_pool, true);
        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Attribute name index: cp_info #%-4d %-24s |\n", attrInfo.attributeName_index, nameRef);
        printf("| Attribute length:     %-38d |\n", attrInfo.attributeLength);
        printf("|==============================================================|\n");
        if (strcmp(name, "ConstantValue") == 0) {
            ConstantValueAttribute* specific_info = (ConstantValueAttribute*) attrInfo.specific_info;
            printf("| Constant value index: cp_info #%-29d |\n", specific_info->constantValue_index);
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "Code") == 0) {

            int userOption;
            CodeAttribute* specific_info = (CodeAttribute*) attrInfo.specific_info;

            printf("| Maximum stack:           %-35d |\n", specific_info->max_stack);
            printf("| Maximum local variables: %-35d |\n", specific_info->max_locals);
            printf("| Code length:             %-35d |\n", specific_info->codeLength);
            printf("| Exception Table length:  %-35d |\n", specific_info->exceptionTableLength);
            printf("| Attributes count:        %-35d |\n", specific_info->attributes_count);
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Code                                                      |\n");
            printf("| 2) Exception Table                                           |\n");
            printf("| 3) Attributes                                                |\n");
            printf("| 4) Back                                                      |\n");
            printf("|==============================================================|\n");
            printf("Choose one of the options: ");

            scanf("%d", &userOption);
            while(getchar() != '\n');

            if (userOption == 1) {
                clearScreen();
                showCode(specific_info->code, specific_info->codeLength);
            } else if (userOption == 2) {
                clearScreen();
                showExceptionTable(specific_info->exceptionTable, specific_info->exceptionTableLength);
            } else if (userOption == 3) {
                clearScreen();
                showAttributes(specific_info->attributes, specific_info->attributes_count);
            } else if (userOption == 4) {
                clearScreen();
                break;
            } else {
                clearScreen();
                printf("Invalid option! Please choose a valid one.\n");
            }

        } else if (strcmp(name, "Deprecated") == 0) {
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "Exceptions") == 0) {
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "InnerClasses") == 0) {
            InnerClassesAttribute* specific_info = (InnerClassesAttribute*) attrInfo.specific_info;
            printf("|--------------------------------------------------------------|\n");
            printf("|   | Inner Class  | Outer Class  | Inner Name  | Access _flags |\n");
            printf("|--------------------------------------------------------------|\n");
            for (int innerClass_index = 0; innerClass_index < specific_info->numberOfClasses; innerClass_index++) {
                char* innerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].innerClassInfo_index - 1].class_const.name_index, class->constant_pool, false);
                char* outerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].outerClassInfo_index - 1].class_const.name_index, class->constant_pool, false);
                char* innerName = getUtf8FromConstantPool(specific_info->classes[innerClass_index].innerName_index, class->constant_pool, false);
                printf("|%3d| %-12.12s | %-12.12s | %-11.11s | 0x%.4X       |\n", innerClass_index, innerClass, outerClass, innerName, specific_info->classes[innerClass_index].innerClassAccess_flags);
                free_mem( (void**) &innerClass );
                free_mem( (void**) &outerClass );
                free_mem( (void**) &innerName );
            }
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "SourceFile") == 0) {
            SourceFileAttribute* specific_info = (SourceFileAttribute*) attrInfo.specific_info;
            char* sourceFileName = getUtf8FromConstantPool(specific_info->sourceFile_index, class->constant_pool, true);
            printf("| Source file name index: cp_info #%-4d %-22s |\n", specific_info->sourceFile_index, sourceFileName);
            free_mem( (void**) &sourceFileName );
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "LineNumberTable") == 0) {
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "LocalVariableTable") == 0) {
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        }
    }
}

void showCode(uint8_t* code, int codeLength) {
    if (codeLength == 0) {
        printf("Empty Array\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                         Byte Code                            |\n");
    printf("|==============================================================|\n");
    int code_index = 0;
    while(code_index < codeLength) {
        Instruction* instr = decode(code, &code_index);
        if (instr->arguments_count == 0) {
            printf("| %-4d %-55s |\n", instr->pc, instr->name);
        } else if (instr->arguments_count == 1) {
            printf("| %-4d %-15s 0x%-2d                                    |\n", instr->pc, instr->name, instr->arguments[0]);
        } else if (instr->arguments_count == 2) {
            printf("| %-4d %-15s 0x%.2d 0x%.2d                               |\n", instr->pc, instr->name, instr->arguments[0], instr->arguments[1]);
        }
        free_mem( (void**) &instr);
    }
    printf("|==============================================================|\n");
    printf("Press ENTER to return...");
    while(getchar() != '\n');
    clearScreen();
}

void showExceptionTable(ExceptionTableEntry* exceptionTable, int exceptionTableLength) {
    if (exceptionTableLength == 0) {
        printf("Empty Array\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                      Exception Table                         |\n");
    printf("|==============================================================|\n");
    printf("|==============================================================|\n");
    printf("Press ENTER to return...");
    while(getchar() != '\n');
    clearScreen();
}

void chooseFile() {
    char tempPath[255], confirmation;
    FILE* tempPointer = NULL;

    while(true) {
        printf("|==============================================================|\n");
        printf("|                     Choose a .class file                     |\n");
        printf("|==============================================================|\n");
        printf("Set the path (\"none\" to return): ");
        scanf("%s", tempPath);
        while(getchar() != '\n');

        if (strcmp(tempPath, "none") == 0) {
            clearScreen();
            break;
        }

        tempPointer = openFile(tempPath, "rb");
        if (tempPointer == NULL) {
            clearScreen();
            printf("Please choose a valid path!\n");
            strcpy(tempPath, "");
            continue;
        }

        while(true) {
            printf("Are you sure (Y-y or N-n)? ");
            scanf("%c", &confirmation);
            while(getchar() != '\n');

            if (confirmation == 'Y' || confirmation == 'y') {

                clearScreen();
                if (userfilePointer != NULL) {
                    closeFile(&userfilePointer);
                }
                userfilePointer = tempPointer;
                strcpy(userfilePath, tempPath);
                if (class != NULL) {
                    deallocateClass(&class);
                }
                class = getClassfile(userfilePointer);
                goto fileAccepted;

            } else if (confirmation == 'N' || confirmation == 'n') {
                clearScreen();
                strcpy(tempPath, "");
                closeFile(&tempPointer);
                goto fileDeclined;
            } else {
                printf("Invalid option!\n");
                continue;
            }
        }

        fileDeclined:
            continue;

        fileAccepted:
            break;
    }
}

void menu(char* arquivoInicial) {
    int userOption;
    char* file_name = NULL;
    FILE* tempPointer = NULL;

    if (arquivoInicial != NULL) {
        // Check if the file is a .class
        if (strstr(arquivoInicial, ".class") != NULL) {
            tempPointer = openFile(arquivoInicial, "rb");
            if (tempPointer != NULL) {
                if (userfilePointer != NULL) {
                    closeFile(&userfilePointer);
                }
                userfilePointer = tempPointer;
                strcpy(userfilePath, arquivoInicial);
                if (class != NULL) {
                    deallocateClass(&class);
                }
                class = getClassfile(userfilePointer);

            } else {
                printf("Invalid path!\n");
            }
        } else {
            printf("Invalid file extension!\n");
        }
    }

    while(true) {
        if (userfilePointer != NULL && userfilePath[0] != '\0') {
            file_name = getNewName();
        }

        printf("|==============================================================|\n");
        printf("|                       Classfile Viewer                       |\n");
        printf("|==============================================================|\n");

        if (userfilePointer != NULL && userfilePath[0] != '\0') {

            char* thisClass = getUtf8FromConstantPool(class->constant_pool[class->thisClass - 1].class_const.name_index, class->constant_pool, true);
            char* superClass = getUtf8FromConstantPool(class->constant_pool[class->superClass - 1].class_const.name_index, class->constant_pool, true);
            char* access_flags = map_flags(class->access_flags);

            printf("| Chosen file: %-47s |\n", file_name);
            printf("| Size (bytes): %-46d |\n", fileSize(userfilePointer));
            printf("|--------------------------------------------------------------|\n");
            printf("| General Information:                                         |\n");
            printf("|                                                              |\n");
            printf("| Magic:              0x%.8X                               |\n", class->magic);
            printf("| Minor version:      %-40u |\n", class->minor_version);
            printf("| Major version:      %-40u |\n", class->major_version);
            printf("| Contant pool count: %-40d |\n", class->constantPool_count);
            printf("| Access flags:       0x%.4X %-33s |\n", class->access_flags, access_flags);
            printf("| This class:         cp_info #%-4d %-26s |\n", class->thisClass, thisClass);
            printf("| Super class:        cp_info #%-4d %-26s |\n", class->superClass, superClass);
            printf("| Interfaces count:   %-40u |\n", class->interfaces_count);
            printf("| Fields count:       %-40u |\n", class->fields_count);
            printf("| Methods count:      %-40u |\n", class->methods_count);
            printf("| Attributes count:   %-40u |\n",class->attributes_count);
            printf("|--------------------------------------------------------------|\n");
            printf("| -1) Constant pool                                            |\n");
            printf("| -2) Interfaces                                               |\n");
            printf("| -3) Fields                                                   |\n");
            printf("| -4) Methods                                                  |\n");
            printf("| -5) Attributes                                               |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose another .class file                                |\n");

            free_mem( (void**) &thisClass );
            free_mem( (void**) &superClass );
            free_mem( (void**) &access_flags );

        } else {

            printf("| Chosen file: none                                            |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose a .class file                                      |\n");

        }
        printf("| 2) Quit                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");
        scanf("%d", &userOption);
        while(getchar() != '\n');
        printf("\n");
        if (userOption == 2) {
            strcpy(userfilePath, "");
            if (userfilePointer != NULL) {
                closeFile(&userfilePointer);
            }
            freeMemManager();
            break;
        }
        viewerOption(userOption);
    }
}

void viewerOption(int userOption) {
    clearScreen();

    switch(userOption) {
        case 1:
            chooseFile();
            break;

        case -1:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showConstantPool();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        case -2:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showInterfaces();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        case -3:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showFields();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        case -4:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showMethods();
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        case -5:
            if (userfilePointer != NULL && userfilePath[0] != '\0') {
                showAttributes(class->attributes, class->attributes_count);
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        default:
            printf("Invalid option! Please choose a valid one.\n");
    }
}

char* getNewName() {
    int delimeter_position = 0;
    int i = 0;

    if (strstr(userfilePath, "/") != NULL) {
        for (int pos = 0; userfilePath[pos] != '\0'; pos++) {
            if (userfilePath[pos] == '\\') {
                delimeter_position = pos;
            }
        }
    }

    while (userfilePath[i] != '\0') {
        if (userfilePath[i] == '/') {
            delimeter_position = i;
        }
        i++;
    }
    return &userfilePath[delimeter_position + 1];
}

void clearScreen() {
    system("clear");
}
