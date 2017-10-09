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

            char* thisClass = getUtf8FromConstantPool(class->constant_pool[class->thisClass - 1].class_const.name_index, class->constant_pool, true);
            char* superClass = getUtf8FromConstantPool(class->constant_pool[class->superClass - 1].class_const.name_index, class->constant_pool, true);
            char* access_flags = map_flags(class->access_flags);

            printf("| Chosen file: %-47s |\n", shortname);
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

            deallocate( (void**) &thisClass );
            deallocate( (void**) &superClass );
            deallocate( (void**) &access_flags );

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
        // Option #2: Quit the program
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
                showAttributes(class->attributes, class->attributes_count);
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

    if (class->constantPool_count == 0) {
        printf("Empty array.\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                         Constant Pool                        |\n");
        printf("|==============================================================|\n");
        int cp_index;
        for (cp_index = 0; cp_index < class->constantPool_count - 1; cp_index++) {
            switch(class->constant_pool[cp_index].tag) {
                case LARGE_NUMERIC_CONTINUED:
                    printf("| [%-3d] (large numeric continued)                              |\n", cp_index + 1);
                    break;

                case UTF8:
                    printf("| [%-3d] CONSTANT_Utf8_Info                                     |\n", cp_index + 1);
                    break;

                case INTEGER:
                    printf("| [%-3d] CONSTANT_Integer_Info                                  |\n", cp_index + 1);
                    break;

                case FLOAT:
                    printf("| [%-3d] CONSTANT_Float_Info                                    |\n", cp_index + 1);
                    break;

                case LONG:
                    printf("| [%-3d] CONSTANT_Long_Info                                     |\n", cp_index + 1);
                    break;

                case DOUBLE:
                    printf("| [%-3d] CONSTANT_Double_Info                                   |\n", cp_index + 1);
                    break;

                case CLASS:
                    printf("| [%-3d] CONSTANT_Class_Info                                    |\n", cp_index + 1);
                    break;

                case STRING:
                    printf("| [%-3d] CONSTANT_String_Info                                   |\n", cp_index + 1);
                    break;

                case FIELD_REF:
                    printf("| [%-3d] CONSTANT_Fieldref_Info                                 |\n", cp_index + 1);
                    break;

                case METHOD_REF:
                    printf("| [%-3d] CONSTANT_Methodref_Info                                |\n", cp_index + 1);
                    break;

                case INTERFACE_METHOD_REF:
                    printf("| [%-3d] CONSTANT_InterfaceMethodref_Info                       |\n", cp_index + 1);
                    break;

                case NAME_AND_TYPE:
                    printf("| [%-3d] CONSTANT_NameAndType_Info                              |\n", cp_index + 1);
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
                printf("index: ");
                scanf("%d", &chosenConst);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenConst > 0 && chosenConst < (class->constantPool_count)) {
                    clearScreen();
                    if (class->constant_pool[chosenConst - 1].tag == LARGE_NUMERIC_CONTINUED) {
                        // Show the previous element, which has to be a long or a double
                        showConstant(class->constant_pool[chosenConst - 2]);
                    }
                    showConstant(class->constant_pool[chosenConst - 1]);
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
            string = utf8ToString(cpInfo.utf8_const.bytes, cpInfo.utf8_const.length, false);
            printf("| Length of bytes array: %-37d |\n", cpInfo.utf8_const.length);
            printf("| Length of string:      %-37zu |\n", strlen(string));
            printf("| String:                %-37s |\n", string);
            deallocate( (void**) &string );
            break;

        case INTEGER:
            printf("| Bytes:   0x%.8X                                          |\n", cpInfo.integer_const.bytes);
            printf("| Integer: %-51d |\n", cpInfo.integer_const.bytes);
            break;

        case FLOAT:
            printf("| Bytes: 0x%.8X                                            |\n", cpInfo.integer_const.bytes);
            printf("| Float: %-53f |\n", cpInfo.float_const.value);
            break;

        case LONG:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.long_const.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.long_const.bytes.lowBytes);
            printf("| Long:       %-48ld |\n", cpInfo.long_const.value);
            break;

        case DOUBLE:
            printf("| High bytes: 0x%.8X                                       |\n", cpInfo.double_const.bytes.highBytes);
            printf("| Low bytes:  0x%.8X                                       |\n", cpInfo.double_const.bytes.lowBytes);
            printf("| Double:     %-48lf |\n", cpInfo.double_const.value);
            break;

        case CLASS:
            string = getUtf8FromConstantPool(cpInfo.class_const.name_index, class->constant_pool, true);
            printf("| Class name: cp_info #%-4d %-34s |\n", cpInfo.class_const.name_index, string);
            deallocate( (void**) &string );
            break;

        case STRING:
            string = getUtf8FromConstantPool(cpInfo.string_const.string_index, class->constant_pool, true);
            printf("| String: cp_info #%-4d %-38s |\n", cpInfo.string_const.string_index, string);
            deallocate( (void**) &string );
            break;

        case FIELD_REF:
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.fieldRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.fieldRef_const.class_index, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.fieldRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.fieldRef_const.nameAndType_index, string);
            deallocate( (void**) &string );
            break;

        case METHOD_REF:
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.methodRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.methodRef_const.class_index, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.methodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.methodRef_const.nameAndType_index, string);
            deallocate( (void**) &string );
            break;

        case INTERFACE_METHOD_REF:
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.interfaceMethodRef_const.class_index - 1].class_const.name_index, class->constant_pool, true);
            printf("| Class name:    cp_info #%-4d %-31s |\n", cpInfo.interfaceMethodRef_const.class_index, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(class->constant_pool[cpInfo.interfaceMethodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool, true);
            printf("| Name and type: cp_info #%-4d %-31s |\n", cpInfo.interfaceMethodRef_const.nameAndType_index, string);
            deallocate( (void**) &string );
            break;

        case NAME_AND_TYPE:
            string = getUtf8FromConstantPool(cpInfo.nameAndType_const.name_index, class->constant_pool, true);
            printf("| Name:       cp_info #%-4d %-34s |\n", cpInfo.nameAndType_const.name_index, string);
            deallocate( (void**) &string );
            string = getUtf8FromConstantPool(cpInfo.nameAndType_const.descriptor_index, class->constant_pool, true);
            printf("| Descriptor: cp_info #%-4d %-34s |\n", cpInfo.nameAndType_const.descriptor_index, string);
            deallocate( (void**) &string );
            break;
    }
    printf("|==============================================================|\n");
    printf("Press ENTER to return...");
    while(getchar() != '\n');
    clearScreen();
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
        deallocate( (void**) &interface);
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

    infloop {
        printf("|==============================================================|\n");
        printf("|                            Fields                            |\n");
        printf("|==============================================================|\n");

        for (int field_index = 0; field_index < class->fields_count; field_index++) {
            char* name = getUtf8FromConstantPool(class->fields[field_index].name_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", field_index, name);
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
                printf("index: ");
                scanf("%d", &chosenField);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenField >= 0 && chosenField < class->fields_count) {
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
        char* name = getUtf8FromConstantPool(fieldInfo.name_index, class->constant_pool, false);
        char* nameRef = getUtf8FromConstantPool(fieldInfo.name_index, class->constant_pool, true);
        char* descriptorRef = getUtf8FromConstantPool(fieldInfo.descriptor_index, class->constant_pool, true);
        char* access_flags = map_flags(fieldInfo.access_flags);

        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", fieldInfo.name_index, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", fieldInfo.descriptor_index, descriptorRef);
        deallocate( (void**) &name );
        deallocate( (void**) &nameRef );
        deallocate( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X %-34s  |\n", fieldInfo.access_flags, access_flags);
        printf("| Attributes count: %-42d |\n", fieldInfo.attributes_count);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");
        deallocate( (void**) &access_flags );

        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Show attributes
            clearScreen();
            showAttributes(fieldInfo.attributes, fieldInfo.attributes_count);
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

    if (class->methods_count == 0) {
        printf("Empty Array\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                           Methods                            |\n");
        printf("|==============================================================|\n");

        for (int method_index = 0; method_index < class->methods_count; method_index++) {
            char* name = getUtf8FromConstantPool(class->methods[method_index].name_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", method_index, name);
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
                printf("index: ");
                scanf("%d", &chosenMethod);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenMethod >= 0 && chosenMethod < class->methods_count) {
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
        char* name = getUtf8FromConstantPool(methodInfo.name_index, class->constant_pool, false);
        char* nameRef = getUtf8FromConstantPool(methodInfo.name_index, class->constant_pool, true);
        char* descriptorRef = getUtf8FromConstantPool(methodInfo.descriptor_index, class->constant_pool, true);
        char* access_flags = map_flags(methodInfo.access_flags);

        printf("|==============================================================|\n");
        printf("| %-60s |\n", name);
        printf("|==============================================================|\n");
        printf("| Name:             cp_info #%-4d %-28s |\n", methodInfo.name_index, nameRef);
        printf("| Descriptor:       cp_info #%-4d %-28s |\n", methodInfo.descriptor_index, descriptorRef);
        deallocate( (void**) &name );
        deallocate( (void**) &nameRef );
        deallocate( (void**) &descriptorRef );

        printf("| Access flag:      0x%.4X %-34s  |\n", methodInfo.access_flags, access_flags);
        printf("| Attributes count: %-42d |\n", methodInfo.attributes_count);
        printf("|--------------------------------------------------------------|\n");
        printf("| 1) Attributes                                                |\n");
        printf("| 2) Back                                                      |\n");
        printf("|==============================================================|\n");
        printf("Choose one of the options: ");
        deallocate( (void**) &access_flags );
        // Read and process user's option
        scanf("%d", &userOption);
        while(getchar() != '\n');

        // Process user option
        if (userOption == 1) { // Option #1: Show attributes
            clearScreen();
            showAttributes(methodInfo.attributes, methodInfo.attributes_count);
        } else if (userOption == 2) { // Option #2: Go back to previous page
            clearScreen();
            break;
        } else { // Invalid option
            clearScreen();
            printf("Invalid option! Please choose a valid one.\n");
        }
    }
}

void showAttributes(AttributeInfo* attributes, int attributes_count) {
    int userOption;

    if (attributes_count == 0) {
        printf("Empty Array\n");
        return;
    }

    infloop {
        printf("|==============================================================|\n");
        printf("|                        Attributes                            |\n");
        printf("|==============================================================|\n");

        int attr_index;
        for (attr_index = 0; attr_index < attributes_count; attr_index++) {
            char* string = getUtf8FromConstantPool(attributes[attr_index].attributeName_index, class->constant_pool, false);
            printf("| [%-3d] %-54s |\n", attr_index, string);
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
                printf("index: ");
                scanf("%d", &chosenAttribute);
                while(getchar() != '\n');

                // Verify index correctness
                if (chosenAttribute >= 0 && chosenAttribute < class->attributes_count) {
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
            //TODO: Get from constant value
            //constantValue = getUtf8FromConstantPool(specific_info->constantValue_index, class->constant_pool, true);
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

            // Read and process user's option
            scanf("%d", &userOption);
            while(getchar() != '\n');

            // Process user option
            if (userOption == 1) { // Option #1: Show Code
                clearScreen();
                showCode(specific_info->code, specific_info->codeLength);
            } else if (userOption == 2) { // Option #2: Show Exception Table
                clearScreen();
                showExceptionTable(specific_info->exceptionTable, specific_info->exceptionTableLength);
            } else if (userOption == 3) { // Option #3: Show Attributes
                clearScreen();
                showAttributes(specific_info->attributes, specific_info->attributes_count);
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

            InnerClassesAttribute* specific_info = (InnerClassesAttribute*) attrInfo.specific_info;
            printf("|--------------------------------------------------------------|\n");
            printf("|   | Inner Class  | Outer Class  | Inner Name  | Access _flags |\n");
            printf("|--------------------------------------------------------------|\n");
            for (int innerClass_index = 0; innerClass_index < specific_info->numberOfClasses; innerClass_index++) {
                char* innerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].innerClassInfo_index - 1].class_const.name_index, class->constant_pool, false);
                char* outerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].outerClassInfo_index - 1].class_const.name_index, class->constant_pool, false);
                char* innerName = getUtf8FromConstantPool(specific_info->classes[innerClass_index].innerName_index, class->constant_pool, false);
                printf("|%3d| %-12.12s | %-12.12s | %-11.11s | 0x%.4X       |\n", innerClass_index, innerClass, outerClass, innerName, specific_info->classes[innerClass_index].innerClassAccess_flags);
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

            SourceFileAttribute* specific_info = (SourceFileAttribute*) attrInfo.specific_info;
            char* sourceFileName = getUtf8FromConstantPool(specific_info->sourceFile_index, class->constant_pool, true);
            printf("| Source file name index: cp_info #%-4d %-22s |\n", specific_info->sourceFile_index, sourceFileName);
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
