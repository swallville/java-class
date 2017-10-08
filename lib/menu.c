/**
 * @file menu.c
 * @brief Command-line Interface library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 * @authors Raphael Luís Souza de Queiroz (13/0154989)
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
 * @todo Brief
 * @todo Description
 */
Class* class = NULL;

void viewer(char* arquivoInicial) {
    int userOption;
    char* shortname = NULL;
    FILE* tempPointer = NULL;

    if (arquivoInicial != NULL) {
        // Check if the file is a .class
        if (strstr(arquivoInicial, ".class") != NULL) {
            tempPointer = openFile(arquivoInicial, "rb");
            if (tempPointer != NULL) {
                // Close the previous file
                if (userfilePointer != NULL) {
                    closeFile(&userfilePointer);
                }

                // Update with new userfile reference and path
                userfilePointer = tempPointer;
                strcpy(userfilePath, arquivoInicial);

                // Update classfile
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

    infloop {

        // Get short name of the userfile path
        if (userfilePointer != NULL && userfilePath[0] != '\0') {
            shortname = getShortName();
        }

        printf("|==============================================================|\n");
        printf("|                       Classfile Viewer                       |\n");
        printf("|==============================================================|\n");
        // Only the userfile path is sets prints the short name
        if (userfilePointer != NULL && userfilePath[0] != '\0') {

            char* thisClass = getUtf8FromConstantPool(class->constantPool[class->thisClass - 1].classConst.nameIndex, class->constantPool, true);
            char* superClass = getUtf8FromConstantPool(class->constantPool[class->superClass - 1].classConst.nameIndex, class->constantPool, true);

            printf("| Chosen file: %-47s |\n", shortname);
            printf("| Size (bytes): %-46d |\n", fileSize(userfilePointer));
            printf("|--------------------------------------------------------------|\n");
            printf("| General Information:                                         |\n");
            printf("|                                                              |\n");
            printf("| Magic:              0x%.8X                               |\n", class->magic);
            printf("| Minor version:      %-40u |\n", class->minorVersion);
            printf("| Major version:      %-40u |\n", class->majorVersion);
            printf("| Contant pool count: %-40d |\n", class->constantPoolCount);
            printf("| Access flags:       0x%.4X                                   |\n", class->accessFlags);
            printf("| This class:         cp_info #%-4d %-26s |\n", class->thisClass, thisClass);
            printf("| Super class:        cp_info #%-4d %-26s |\n", class->superClass, superClass);
            printf("| Interfaces count:   %-40u |\n", class->interfacesCount);
            printf("| Fields count:       %-40u |\n", class->fieldsCount);
            printf("| Methods count:      %-40u |\n", class->methodsCount);
            printf("| Attributes count:   %-40u |\n",class->attributesCount);
            printf("|--------------------------------------------------------------|\n");
            printf("| -1) Constant pool                                            |\n");
            printf("| -2) Interfaces                                               |\n");
            printf("| -3) Fields                                                   |\n");
            printf("| -4) Methods                                                  |\n");
            printf("| -5) Attributes                                               |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose another .class file                                |\n");

            deallocate( (void**) &thisClass );
            deallocate( (void**) &superClass );

        } else {

            printf("| Chosen file: none                                            |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose a .class file                                      |\n");

        }
        printf("| 2) Quit                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');
        printf("\n");
        // Option #3: Go back to last page
        if (userOption == 2) {
            // Close file and erase userfile path
            strcpy(userfilePath, "");
            if (userfilePointer != NULL) {
                closeFile(&userfilePointer);
            }
            // Free all allocated memory
            freeMemManager();

            break;
        }
        // Process other options
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
                showAttributes(class->attributes, class->attributesCount);
            } else {
                printf("Invalid option! Please choose a valid one.\n");
            }
            break;

        default:
            printf("Invalid option! Please choose a valid one.\n");
    }
}

void showConstantPool() {
    int userOption;

    if (class->constantPoolCount == 0) {
        printf("Empty array.\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                         Constant Pool                        |\n");
        printf("|==============================================================|\n");
        int cpIndex;
        for (cpIndex = 0; cpIndex < class->constantPoolCount - 1; cpIndex++) {
            switch(class->constantPool[cpIndex].tag) {
                case LARGE_NUMERIC_CONTINUED:
                    printf("| [%-3d] (large numeric continued)                              |\n", cpIndex + 1);
                    break;

                case UTF8:
                    printf("| [%-3d] CONSTANT_Utf8_Info                                     |\n", cpIndex + 1);
                    break;

                case INTEGER:
                    printf("| [%-3d] CONSTANT_Integer_Info                                  |\n", cpIndex + 1);
                    break;

                case FLOAT:
                    printf("| [%-3d] CONSTANT_Float_Info                                    |\n", cpIndex + 1);
                    break;

                case LONG:
                    printf("| [%-3d] CONSTANT_Long_Info                                     |\n", cpIndex + 1);
                    break;

                case DOUBLE:
                    printf("| [%-3d] CONSTANT_Double_Info                                   |\n", cpIndex + 1);
                    break;

                case CLASS:
                    printf("| [%-3d] CONSTANT_Class_Info                                    |\n", cpIndex + 1);
                    break;

                case STRING:
                    printf("| [%-3d] CONSTANT_String_Info                                   |\n", cpIndex + 1);
                    break;

                case FIELD_REF:
                    printf("| [%-3d] CONSTANT_Fieldref_Info                                 |\n", cpIndex + 1);
                    break;

                case METHOD_REF:
                    printf("| [%-3d] CONSTANT_Methodref_Info                                |\n", cpIndex + 1);
                    break;

                case INTERFACE_METHOD_REF:
                    printf("| [%-3d] CONSTANT_InterfaceMethodref_Info                       |\n", cpIndex + 1);
                    break;

                case NAME_AND_TYPE:
                    printf("| [%-3d] CONSTANT_NameAndType_Info                              |\n", cpIndex + 1);
                    break;
            }
        }
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a constant                                         |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Choose a contant
            infloop {

                // Ask for the constant index
                int chosenConst;
                printf("Index: ");
                scanf("%d", &chosenConst);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenConst > 0 && chosenConst < (class->constantPoolCount)) {
                    clearScreen();
                    if (class->constantPool[chosenConst - 1].tag == LARGE_NUMERIC_CONTINUED) {
                        // Show the previous element, which has to be a long or a double
                        showConstant(class->constantPool[chosenConst - 2]);
                    }
                    showConstant(class->constantPool[chosenConst - 1]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showConstant(ConstPoolInfo cpInfo) {
    printf("|==============================================================|\n");
    switch(cpInfo.tag) {
        case UTF8:
            printf("|                      CONSTANT_Utf8_Info                      |\n");
            break;

        case INTEGER:
            printf("|                     CONSTANT_Integer_Info                    |\n");
            break;

        case FLOAT:
            printf("|                      CONSTANT_Float_Info                     |\n");
            break;

        case LONG:
            printf("|                      CONSTANT_Long_Info                      |\n");
            break;

        case DOUBLE:
            printf("|                     CONSTANT_Double_Info                     |\n");
            break;

        case CLASS:
            printf("|                      CONSTANT_Class_Info                     |\n");
            break;

        case STRING:
            printf("|                     CONSTANT_String_Info                     |\n");
            break;

        case FIELD_REF:
            printf("|                    CONSTANT_Fieldref_Info                    |\n");
            break;

        case METHOD_REF:
            printf("|                    CONSTANT_Methodref_Info                   |\n");
            break;

        case INTERFACE_METHOD_REF:
            printf("|               CONSTANT_InterfaceMethodref_Info               |\n");
            break;

        case NAME_AND_TYPE:
            printf("|                  CONSTANT_NameAndType_Info                   |\n");
            break;
    }
    printf("|==============================================================|\n");
    char* string = NULL;
    switch(cpInfo.tag) {
        case UTF8:
            string = utf8ToString(cpInfo.utf8Const.bytes, cpInfo.utf8Const.length, false);
            printf("| Length of bytes array: %-37d |\n", cpInfo.utf8Const.length);
            printf("| Length of string:      %-37zu |\n", strlen(string));
            printf("| String:                %-37s |\n", string);
            deallocate( (void**) &string );
            break;

        case INTEGER:
            printf("| Bytes:   0x%.8X                                          |\n", cpInfo.integerConst.bytes);
            printf("| Integer: %-51d |\n", cpInfo.integerConst.bytes);
            break;

        case FLOAT:
            printf("| Bytes: 0x%.8X                                            |\n", cpInfo.integerConst.bytes);
            printf("| Float: %-53f |\n", cpInfo.floatConst.value);
            break;

        case LONG:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.longConst.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.longConst.bytes.lowBytes);
            printf("| Long:       %-48ld |\n", cpInfo.longConst.value);
            break;

        case DOUBLE:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.doubleConst.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.doubleConst.bytes.lowBytes);
            printf("| Double:     %-48lf |\n", cpInfo.doubleConst.value);
            break;

        case CLASS:
            string = getUtf8FromConstantPool(cpInfo.classConst.nameIndex, class->constantPool, true);
            printf("| Class name: cp_info #%-4d %-34s |\n", cpInfo.classConst.nameIndex, string);
            deallocate( (void**) &string );
            break;

        case STRING:
            string = getUtf8FromConstantPool(cpInfo.stringConst.stringIndex, class->constantPool, true);
            printf("| String: cp_info #%-4d %-38s |\n", cpInfo.stringConst.stringIndex, string);
            deallocate( (void**) &string );
            break;

        case FIELD_REF:
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.fieldRefConst.classIndex - 1].classConst.nameIndex, class->constantPool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.fieldRefConst.classIndex, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.fieldRefConst.nameAndTypeIndex - 1].nameAndTypeConst.nameIndex, class->constantPool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.fieldRefConst.nameAndTypeIndex, string);
            deallocate( (void**) &string );
            break;

        case METHOD_REF:
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.methodRefConst.classIndex - 1].classConst.nameIndex, class->constantPool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.methodRefConst.classIndex, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.methodRefConst.nameAndTypeIndex - 1].nameAndTypeConst.nameIndex, class->constantPool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.methodRefConst.nameAndTypeIndex, string);
            deallocate( (void**) &string );
            break;

        case INTERFACE_METHOD_REF:
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.interfaceMethodRefConst.classIndex - 1].classConst.nameIndex, class->constantPool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.interfaceMethodRefConst.classIndex, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constantPool[cpInfo.interfaceMethodRefConst.nameAndTypeIndex - 1].nameAndTypeConst.nameIndex, class->constantPool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.interfaceMethodRefConst.nameAndTypeIndex, string);
            deallocate( (void**) &string );
            break;

        case NAME_AND_TYPE:
            string = getUtf8FromConstantPool(cpInfo.nameAndTypeConst.nameIndex, class->constantPool, true);
            printf("| Name:       cp_info #%-4d %-34s |\n", cpInfo.nameAndTypeConst.nameIndex, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(cpInfo.nameAndTypeConst.descriptorIndex, class->constantPool, true);
            printf("| Descriptor: cp_info #%-4d %-34s |\n", cpInfo.nameAndTypeConst.descriptorIndex, string);
            deallocate( (void**) &string );
            break;
    }
    printf("|==============================================================|\n");
    printf("Press ENTER to return...");
    while(getchar() != '\n');
    clearScreen();
}

void showInterfaces() {
    int interfacesIndex;

    if (class->interfacesCount == 0) {
        printf("Empty array.\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                           Interfaces                         |\n");
    printf("|==============================================================|\n");

    for (interfacesIndex = 0; interfacesIndex < class->interfacesCount; interfacesIndex++) {
        char* interface = getUtf8FromConstantPool(class->constantPool[class->interfaces[interfacesIndex] - 1].classConst.nameIndex, class->constantPool, true);
        printf("| cp_info #%-4d %-46s |\n", class->interfaces[interfacesIndex], interface);
        deallocate( (void**) &interface);
    }
    printf("|==============================================================|\n");
    printf("Press enter to return...\n");
    while(getchar() != '\n');
    clearScreen();
}

void showFields() {
    int userOption;

    if (class->fieldsCount == 0) {
        printf("Empty Array\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                            Fields                            |\n");
        printf("|==============================================================|\n");

        for (int fieldIndex = 0; fieldIndex < class->fieldsCount; fieldIndex++) {
            char* name = getUtf8FromConstantPool(class->fields[fieldIndex].nameIndex, class->constantPool, false);
            printf("| [%-3d] %-54s |\n", fieldIndex, name);
            deallocate( (void**) &name );
        }

        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a field                                            |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Choose a contant
            infloop {

                // Ask for the field index
                int chosenField;
                printf("Index: ");
                scanf("%d", &chosenField);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenField >= 0 && chosenField < class->fieldsCount) {
                    clearScreen();
                    showField(class->fields[chosenField]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }

    }
}

void showField(FieldInfo fieldInfo) {
    int userOption;

    infloop {
        char* name = getUtf8FromConstantPool(fieldInfo.nameIndex, class->constantPool, false);
        char* nameRef = getUtf8FromConstantPool(fieldInfo.nameIndex, class->constantPool, true);
        char* descriptorRef = getUtf8FromConstantPool(fieldInfo.descriptorIndex, class->constantPool, true);
        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", fieldInfo.nameIndex, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", fieldInfo.descriptorIndex, descriptorRef);
        deallocate( (void**) &name );
        deallocate( (void**) &nameRef );
        deallocate( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X                                     |\n", fieldInfo.accessFlags);
        printf("| Attributes count: %-42d |\n", fieldInfo.attributesCount);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Show attributes
            clearScreen();
            showAttributes(fieldInfo.attributes, fieldInfo.attributesCount);
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showMethods() {
    int userOption;

    if (class->methodsCount == 0) {
        printf("Empty Array\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                           Methods                            |\n");
        printf("|==============================================================|\n");

        for (int methodIndex = 0; methodIndex < class->methodsCount; methodIndex++) {
            char* name = getUtf8FromConstantPool(class->methods[methodIndex].nameIndex, class->constantPool, false);
            printf("| [%-3d] %-54s |\n", methodIndex, name);
            deallocate( (void**) &name );
        }

        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a method                                           |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Choose a contant
            infloop {

                // Ask for the method index
                int chosenMethod;
                printf("Index: ");
                scanf("%d", &chosenMethod);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenMethod >= 0 && chosenMethod < class->methodsCount) {
                    clearScreen();
                    showMethod(class->methods[chosenMethod]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showMethod(MethodInfo methodInfo) {
    int userOption;

    infloop {
        char* name = getUtf8FromConstantPool(methodInfo.nameIndex, class->constantPool, false);
        char* nameRef = getUtf8FromConstantPool(methodInfo.nameIndex, class->constantPool, true);
        char* descriptorRef = getUtf8FromConstantPool(methodInfo.descriptorIndex, class->constantPool, true);
        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", methodInfo.nameIndex, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", methodInfo.descriptorIndex, descriptorRef);
        deallocate( (void**) &name );
        deallocate( (void**) &nameRef );
        deallocate( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X                                     |\n", methodInfo.accessFlags);
        printf("| Attributes count: %-42d |\n", methodInfo.attributesCount);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Show attributes
            clearScreen();
            showAttributes(methodInfo.attributes, methodInfo.attributesCount);
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showAttributes(AttributeInfo* attributes, int attributesCount) {
    int userOption;

    if (attributesCount == 0) {
        printf("Empty Array\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                        Attributes                            |\n");
        printf("|==============================================================|\n");

        int attrIndex;
        for (attrIndex = 0; attrIndex < attributesCount; attrIndex++) {
            char* string = getUtf8FromConstantPool(attributes[attrIndex].attributeNameIndex, class->constantPool, false);
            printf("| [%-3d] %-54s |\n", attrIndex, string);
            deallocate( (void**) &string );
        }

        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Choose a attribute                                        |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options (1-2): ");

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Choose a contant
            infloop {

                // Ask for the attribute index
                int chosenAttribute;
                printf("Index: ");
                scanf("%d", &chosenAttribute);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenAttribute >= 0 && chosenAttribute < class->attributesCount) {
                    clearScreen();
                    showAttribute(attributes[chosenAttribute]);
                    break;
                } else {
                    printf("Invalid option! Please choose a valid one.\n");
                }
            }
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }

    }
}

void showAttribute(AttributeInfo attrInfo) {

    infloop {
        char* name = getUtf8FromConstantPool(attrInfo.attributeNameIndex, class->constantPool, false);
        char* nameRef = getUtf8FromConstantPool(attrInfo.attributeNameIndex, class->constantPool, true);
        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Attribute name index: cp_info #%-4d %-24s |\n", attrInfo.attributeNameIndex, nameRef);
        printf("| Attribute length:     %-38d |\n", attrInfo.attributeLength);
        printf("|==============================================================|\n");
        if (strcmp(name, "ConstantValue") == 0) {

            ConstantValueAttribute* specificInfo = (ConstantValueAttribute*) attrInfo.specificInfo;
            //TODO: Get from constant value
            //constantValue = getUtf8FromConstantPool(specificInfo->constantValueIndex, class->constantPool, true);
            printf("| Constant value index: cp_info #%-29d |\n", specificInfo->constantValueIndex);
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "Code") == 0) {

            int userOption;
            CodeAttribute* specificInfo = (CodeAttribute*) attrInfo.specificInfo;

            printf("| Maximum stack:           %-35d |\n", specificInfo->maxStack);
            printf("| Maximum local variables: %-35d |\n", specificInfo->maxLocals);
            printf("| Code length:             %-35d |\n", specificInfo->codeLength);
            printf("| Exception Table length:  %-35d |\n", specificInfo->exceptionTableLength);
            printf("| Attributes count:        %-35d |\n", specificInfo->attributesCount);
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Code                                                      |\n");
            printf("| 2) Exception Table                                           |\n");
            printf("| 3) Attributes                                                |\n");
            printf("| 4) Back                                                      |\n");
            printf("|==============================================================|\n");
            printf("Choose one of the options: ");

            // Read and process user's option
            scanf("%d", &userOption);
            while(getchar() != '\n');

            // Process user option
            if (userOption == 1) { // Option #1: Show Code
                clearScreen();
                showCode(specificInfo->code, specificInfo->codeLength);
            } else if (userOption == 2) { // Option #2: Show Exception Table
                clearScreen();
                showExceptionTable(specificInfo->exceptionTable, specificInfo->exceptionTableLength);
            } else if (userOption == 3) { // Option #3: Show Attributes
                clearScreen();
                showAttributes(specificInfo->attributes, specificInfo->attributesCount);
            } else if (userOption == 4) { // Option #4: Go back to previous page
                clearScreen();
                break;
            } else { // Invalid option
                clearScreen();
                printf("Invalid option! Please choose a valid one.\n");
            }

        } else if (strcmp(name, "Deprecated") == 0) {

            // Don't have specific info
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "Exceptions") == 0) {

            // TODO: Viewer
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "InnerClasses") == 0) {

            InnerClassesAttribute* specificInfo = (InnerClassesAttribute*) attrInfo.specificInfo;
            printf("|--------------------------------------------------------------|\n");
            printf("|   | Inner Class  | Outer Class  | Inner Name  | Access Flags |\n");
            printf("|--------------------------------------------------------------|\n");
            for (int innerClassIndex = 0; innerClassIndex < specificInfo->numberOfClasses; innerClassIndex++) {
                char* innerClass = getUtf8FromConstantPool(class->constantPool[specificInfo->classes[innerClassIndex].innerClassInfoIndex - 1].classConst.nameIndex, class->constantPool, false);
                char* outerClass = getUtf8FromConstantPool(class->constantPool[specificInfo->classes[innerClassIndex].outerClassInfoIndex - 1].classConst.nameIndex, class->constantPool, false);
                char* innerName = getUtf8FromConstantPool(specificInfo->classes[innerClassIndex].innerNameIndex, class->constantPool, false);
                printf("|%3d| %-12.12s | %-12.12s | %-11.11s | 0x%.4X       |\n", innerClassIndex, innerClass, outerClass, innerName, specificInfo->classes[innerClassIndex].innerClassAccessFlags);
                deallocate( (void**) &innerClass );
                deallocate( (void**) &outerClass );
                deallocate( (void**) &innerName );
            }
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "SourceFile") == 0) {

            SourceFileAttribute* specificInfo = (SourceFileAttribute*) attrInfo.specificInfo;
            char* sourceFileName = getUtf8FromConstantPool(specificInfo->sourceFileIndex, class->constantPool, true);
            printf("| Source file name index: cp_info #%-4d %-22s |\n", specificInfo->sourceFileIndex, sourceFileName);
            deallocate( (void**) &sourceFileName );
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "LineNumberTable") == 0) {

            // TODO: Viewer
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } else if (strcmp(name, "LocalVariableTable") == 0) {

            // TODO: Viewer
            printf("|==============================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
            break;

        } // Ignore unknowm property
    }
}

void showCode(u1* code, int codeLength) {

    if (codeLength == 0) {
        printf("Empty Array\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                         Byte Code                            |\n");
    printf("|==============================================================|\n");
    int codeIndex = 0;
    while(codeIndex < codeLength) {
        Instruction* instr = decode(code, &codeIndex);
        if (instr->argumentsCount == 0) {
            printf("| %-4d %-55s |\n", instr->pc, instr->name);
        } else if (instr->argumentsCount == 1) {
            printf("| %-4d %-15s 0x%-2d                                    |\n", instr->pc, instr->name, instr->arguments[0]);
        } else if (instr->argumentsCount == 2) {
            printf("| %-4d %-15s 0x%.2d 0x%.2d                               |\n", instr->pc, instr->name, instr->arguments[0], instr->arguments[1]);
        }
        deallocate( (void**) &instr);
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

    infloop {
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

        infloop {
            printf("Are you sure (Y-y or N-n)? ");
            scanf("%c", &confirmation);
            while(getchar() != '\n');

            if (confirmation == 'Y' || confirmation == 'y') {

                clearScreen();
                // Close the previous file
                if (userfilePointer != NULL) {
                    closeFile(&userfilePointer);
                }
                // Update with new userfile reference and path
                userfilePointer = tempPointer;
                strcpy(userfilePath, tempPath);
                // Update classfile
                if (class != NULL) {
                    deallocateClass(&class);
                }
                class = getClassfile(userfilePointer);
                // Return the previous menu
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

char* getShortName() {
    int lastBar = 0, i;
    for (i = 0; userfilePath[i] != '\0'; i++) {
        if (userfilePath[i] == '/') {
            lastBar = i;
        }
    }
    if (lastBar == 0) {
        for (i = 0; userfilePath[i] != '\0'; i++) {
        if (userfilePath[i] == '\\') {
            lastBar = i;
        }
    }
    }
    return &userfilePath[lastBar+1];
}

void clearScreen() {
    system("clear");
}
