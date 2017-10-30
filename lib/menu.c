/**
 * @file menu.c
 * @brief Command-line Interface library source.
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the menu.h file.
 */
#include <string.h>
#include <inttypes.h>
#include "mem-manager.h"
#include "menu.h"
#include "utils.h"
#include "execute.h"

/**
 * @brief Stores the user's selected file.
 * @todo Description
 */
FILE* file = NULL;

/**
 * @brief Stores the user's selected path.
 * @todo Description
 */
char path[255] = "";

/**
 * @brief Represents the file content
 * @todo Description
 */
Class* class = NULL;

double decoderVersion (uint16_t version) {

	double retorno;

	switch (version) {
		case 53:
			retorno = 1.9;
			break;
		case 52:
			retorno = 1.8;
			break;
		case 51:
			retorno = 1.7;
			break;
		case 50:
			retorno = 1.6;
			break;
		case 49:
			retorno = 1.5;
			break;
		case 48:
			retorno = 1.4;
			break;
		case 47:
			retorno = 1.3;
			break;
		case 46:
			retorno = 1.2;
			break;
		case 45:
			retorno = 1.1;
			break;
		default:
			retorno = 0;
			break;
	}

	return retorno;
}


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
				int for_method_handle = 0;
        char* string = NULL;
        char* aux = NULL;
        for (cp_index = 0; cp_index < class->constantPool_count - 1; cp_index++) {
            switch(class->constant_pool[cp_index].tag) {
                case LARGE_NUMERIC_CONTINUED:
                    printf("| [%-3d] (large numeric continued)                              |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case UTF8:
                    printf("| [%-3d] CONSTANT_Utf8_Info                                     |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = utf8ToString(class->constant_pool[cp_index].utf8_const.bytes, class->constant_pool[cp_index].utf8_const.length);
                    printf(" Length of bytes array: %-37d \n", class->constant_pool[cp_index].utf8_const.length);
                    printf(" Length of string:      %-37zu \n", strlen(string));
                    printf(" String:                %-37s \n", string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case INTEGER:
                    printf("| [%-3d] CONSTANT_Integer_Info                                  |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf(" Bytes:   0x%.8X                                          \n", class->constant_pool[cp_index].integer_const.bytes);
                    printf(" Integer: %-51d \n", class->constant_pool[cp_index].integer_const.bytes);
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case FLOAT:
                    printf("| [%-3d] CONSTANT_Float_Info                                    |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf(" Bytes: 0x%.8X                                            \n", class->constant_pool[cp_index].float_const.bytes);
                    printf(" Float: %-53f \n", decodeFloat(class->constant_pool[cp_index].float_const.bytes));
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case LONG:
                    printf("| [%-3d] CONSTANT_Long_Info                                     |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf(" High bytes: 0x%.8X                                       \n", class->constant_pool[cp_index].long_const.bytes.highBytes);
                    printf(" Low bytes:  0x%.8X                                       \n", class->constant_pool[cp_index].long_const.bytes.lowBytes);
                    printf(" Long:       %-48ld \n",decodeLong(class->constant_pool[cp_index].long_const.bytes.highBytes, class->constant_pool[cp_index].long_const.bytes.lowBytes));
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case DOUBLE:
                    printf("| [%-3d] CONSTANT_Double_Info                                   |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    printf(" High bytes: 0x%.8X                                       \n", class->constant_pool[cp_index].double_const.bytes.highBytes);
                    printf(" Low bytes:  0x%.8X                                       \n", class->constant_pool[cp_index].double_const.bytes.lowBytes);
                    printf(" Double:     %-48lf \n", decodeDouble(class->constant_pool[cp_index].double_const.bytes.highBytes, class->constant_pool[cp_index].double_const.bytes.lowBytes));
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case CLASS:
                    printf("| [%-3d] CONSTANT_Class_Info                                    |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].class_const.name_index, class->constant_pool);
                    printf(" Class name: cp_info #%-4d <%s> \n", class->constant_pool[cp_index].class_const.name_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case STRING:
                    printf("| [%-3d] CONSTANT_String_Info                                   |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].string_const.string_index, class->constant_pool);
                    printf(" String: cp_info #%-4d <%s> \n", class->constant_pool[cp_index].string_const.string_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case FIELD_REF:
                    printf("| [%-3d] CONSTANT_Fieldref_Info                                 |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.class_index - 1].class_const.name_index, class->constant_pool);
                    printf(" Class name:    cp_info #%-4d <%s> \n", class->constant_pool[cp_index].fieldRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
                    printf(" Name and type: cp_info #%-4d <%s> \n", class->constant_pool[cp_index].fieldRef_const.nameAndType_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case METHOD_REF:
                    printf("| [%-3d] CONSTANT_Methodref_Info                                |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.class_index - 1].class_const.name_index, class->constant_pool);
                    printf(" Class name:    cp_info #%-4d <%s> \n", class->constant_pool[cp_index].methodRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
                    aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.nameAndType_index - 1].nameAndType_const.descriptor_index, class->constant_pool);
										for_method_handle = cp_index;
                    printf(" Name and type: cp_info #%-4d <%s : %s> \n", class->constant_pool[cp_index].methodRef_const.nameAndType_index, string, aux);
                    free_mem( (void**) &string );
                    free_mem( (void**) &aux );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case INTERFACE_METHOD_REF:
                    printf("| [%-3d] CONSTANT_InterfaceMethodref_Info                       |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.class_index - 1].class_const.name_index, class->constant_pool);
                    printf(" Class name:    cp_info #%-4d <%s> \n", class->constant_pool[cp_index].interfaceMethodRef_const.class_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
                    printf(" Name and type: cp_info #%-4d <%s> \n", class->constant_pool[cp_index].interfaceMethodRef_const.nameAndType_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

                case NAME_AND_TYPE:
                    printf("| [%-3d] CONSTANT_NameAndType_Info                              |\n", cp_index + 1);
                    printf("|--------------------------------------------------------------|\n");
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].nameAndType_const.name_index, class->constant_pool);
                    printf(" Name:       cp_info #%-4d <%s> \n", class->constant_pool[cp_index].nameAndType_const.name_index, string);
                    free_mem( (void**) &string );
                    string = getUtf8FromConstantPool(class->constant_pool[cp_index].nameAndType_const.descriptor_index, class->constant_pool);
                    printf(" Descriptor: cp_info #%-4d <%s> \n", class->constant_pool[cp_index].nameAndType_const.descriptor_index, string);
                    free_mem( (void**) &string );
                    printf("|--------------------------------------------------------------|\n");
                    break;

							case METHOD_HANDLE:
										printf("| [%-3d] CONSTANT_MethodHandle                              	 |\n", cp_index + 1);
										printf("|--------------------------------------------------------------|\n");
										printf(" Reference Kind:  %s \n", map_methods_handle_types(class->constant_pool[cp_index].methodHandle_const.reference_kind));
										string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[for_method_handle].methodRef_const.class_index - 1].class_const.name_index, class->constant_pool);
										aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[for_method_handle].methodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
										printf(" Reference Index: cp_info #%-4d <%s.%s> \n", class->constant_pool[cp_index].methodHandle_const.reference_index, string, aux);
										free_mem( (void**) &string );
										free_mem( (void**) &aux );
										printf("|--------------------------------------------------------------|\n");
										break;

							 case METHOD_TYPE:
										printf("| [%-3d] CONSTANT_MethodType                              	   |\n", cp_index + 1);
										printf("|--------------------------------------------------------------|\n");
										string = getUtf8FromConstantPool(class->constant_pool[cp_index].methodType_const.descriptor_index, class->constant_pool);
										printf(" Descriptor:  cp_info #%-4d <%s> \n", class->constant_pool[cp_index].methodType_const.descriptor_index, string);
										free_mem( (void**) &string );
									  printf("|--------------------------------------------------------------|\n");
										break;

								case INVOKE_DYNAMIC:
										printf("| [%-3d] CONSTANT_InvokeDynamic                              	 |\n", cp_index + 1);
										printf("|--------------------------------------------------------------|\n");
										string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].invokeDynamicInfo_const.name_and_type_index - 1].nameAndType_const.name_index, class->constant_pool);
										aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].invokeDynamicInfo_const.name_and_type_index - 1].nameAndType_const.descriptor_index, class->constant_pool);
										printf(" Name and type:  cp_info #%-4d <%s : %s> \n", class->constant_pool[cp_index].invokeDynamicInfo_const.name_and_type_index, string, aux);
										free_mem( (void**) &string );
										free_mem( (void**) &aux );
										printf(" BootstrapMethods #%-4d \n", class->constant_pool[cp_index].invokeDynamicInfo_const.bootstrap_method_attr_index);
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
        printf("No data in Interfaces table\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                           Interfaces                         |\n");
    printf("|==============================================================|\n");

    for (interfaces_index = 0; interfaces_index < class->interfaces_count; interfaces_index++) {
        char* interface = getUtf8FromConstantPool(class->constant_pool[class->interfaces[interfaces_index] - 1].class_const.name_index, class->constant_pool);
        printf(" cp_info #%-4d <%s> \n", class->interfaces[interfaces_index], interface);
        free_mem( (void**) &interface);
    }
    printf("|==============================================================|\n");
    printf("Press enter to return...\n");
    while(getchar() != '\n');
    clearScreen();
}

void showFields() {
    if (class->fields_count == 0) {
        printf("No data in Fields Table\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                            Fields                            |\n");
        printf("|==============================================================|\n");

        for (int field_index = 0; field_index < class->fields_count; field_index++) {
            char* name = getUtf8FromConstantPool(class->fields[field_index].name_index, class->constant_pool);
            printf(" [%-3d] %-54s \n", field_index, name);
            free_mem( (void**) &name );
        }

				for (int i = 0; i < class->fields_count; i++) {
					char* name = getUtf8FromConstantPool(class->fields[i].name_index, class->constant_pool);
					char* nameRef = getUtf8FromConstantPool(class->fields[i].name_index, class->constant_pool);
					char* descriptorRef = getUtf8FromConstantPool(class->fields[i].descriptor_index, class->constant_pool);
					char* access_flags = map_flags(class->fields[i].access_flags);

					printf("|==============================================================|\n");
					printf("| %-60s |\n", name);
					printf("|==============================================================|\n");
					printf(" Name:             cp_info #%-4d <%s> \n", class->fields[i].name_index, nameRef);
					printf(" Descriptor:       cp_info #%-4d <%s> \n", class->fields[i].descriptor_index, descriptorRef);
					free_mem( (void**) &name );
					free_mem( (void**) &nameRef );
					free_mem( (void**) &descriptorRef );

					printf(" Access flags:      0x%.4X %-34s  \n", class->fields[i].access_flags, access_flags);
					printf(" Attributes count: %-42d \n", class->fields[i].attributes_count);
					free_mem( (void**) &access_flags );

					if (class->fields[i].attributes_count > 0) {
						showAttributes(class->fields[i].attributes, class->fields[i].attributes_count);
					}

				}

				printf("|==============================================================|\n");
				printf("Press ENTER to return...");
				while(getchar() != '\n');
				clearScreen();
				break;
	 }
}

void showMethods() {
    if (class->methods_count == 0) {
        printf("No data into Methods Table\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                           Methods                            |\n");
        printf("|==============================================================|\n");

        for (int method_index = 0; method_index < class->methods_count; method_index++) {
            char* name = getUtf8FromConstantPool(class->methods[method_index].name_index, class->constant_pool);
            printf(" [%-3d] %-54s \n", method_index, name);
            free_mem( (void**) &name );
        }

				for (int i = 0; i < class->methods_count; i++) {
					char* name = getUtf8FromConstantPool(class->methods[i].name_index, class->constant_pool);
	        char* nameRef = getUtf8FromConstantPool(class->methods[i].name_index, class->constant_pool);
	        char* descriptorRef = getUtf8FromConstantPool(class->methods[i].descriptor_index, class->constant_pool);
	        char* access_flags = (class->methods[i].access_flags > 0 ? map_method_flags(class->methods[i].access_flags) : "[ ]");

	        printf("|==============================================================|\n");
	        printf("| %-60s |\n", name);
	        printf("|==============================================================|\n");
	        printf(" Name:             cp_info #%-4d <%s> \n", class->methods[i].name_index, nameRef);
	        printf(" Descriptor:       cp_info #%-4d <%s> \n", class->methods[i].descriptor_index, descriptorRef);
	        free_mem( (void**) &name );
	        free_mem( (void**) &nameRef );
	        free_mem( (void**) &descriptorRef );

	        printf(" Access flags:      0x%.4X %-34s  \n", class->methods[i].access_flags, access_flags);
	        printf(" Attributes count: %-42d \n", class->methods[i].attributes_count);

					if (class->methods[i].access_flags > 0) {
						free_mem( (void**) &access_flags );
					}

					if (class->methods[i].attributes_count) {
						showAttributes(class->methods[i].attributes, class->methods[i].attributes_count);
					}
				}

				printf("|==============================================================|\n");
				printf("Press ENTER to return...");
				while(getchar() != '\n');
				clearScreen();
				break;
    }
}

void showAttributes(Attribute* attributes, int attributes_count) {
    if (attributes_count == 0) {
        printf("No data in Attributes Table\n");
        return;
    }

    while(true) {
        printf("|==============================================================|\n");
        printf("|                        Attributes                            |\n");
        printf("|==============================================================|\n");

        int attr_index;
        for (attr_index = 0; attr_index < attributes_count; attr_index++) {
            char* string = getUtf8FromConstantPool(attributes[attr_index].attributeName_index, class->constant_pool);
            printf("| [%-3d] %-54s |\n", attr_index, string);
            free_mem( (void**) &string );
        }

				for (int i = 0; i < attributes_count; i++) {
					showAttribute(attributes[i]);
				}

				clearScreen();
				break;
    }
}

void showAttribute(Attribute attrInfo) {
    while(true) {
        char* name = getUtf8FromConstantPool(attrInfo.attributeName_index, class->constant_pool);

        printf("|=====================================================================================|\n");
        printf(" %-60s  \n", name);
        printf("|=====================================================================================|\n");
        printf(" Attribute name index: cp_info #%-4d <%s> \n", attrInfo.attributeName_index, name);
        printf(" Attribute length:     %-38d \n", attrInfo.attributeLength);
        printf("|=====================================================================================|\n");
        if (strcmp(name, "ConstantValue") == 0) {
            ConstantValueAttribute* specific_info = (ConstantValueAttribute*) attrInfo.specific_info;
            printf(" Constant value index: cp_info #%-29d \n", specific_info->constantValue_index);
            printf("|=====================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "Code") == 0) {

            int userOption;
            CodeAttribute* specific_info = (CodeAttribute*) attrInfo.specific_info;

            printf(" Maximum stack:           %-35d \n", specific_info->max_stack);
            printf(" Maximum local variables: %-35d \n", specific_info->max_locals);
            printf(" Code length:             %-35d \n", specific_info->codeLength);
            printf(" Exception Table length:  %-35d \n", specific_info->exceptionTableLength);
            printf(" Attributes count:        %-35d \n", specific_info->attributes_count);
            printf("|-------------------------------------------------------------------------------------|\n");
            printf("| 1) Code                                                                             |\n");
            printf("| 2) Exception Table                                                                  |\n");
            printf("| 3) Attributes                                                                       |\n");
            printf("| 4) Back                                                                             |\n");
            printf("|=====================================================================================|\n");
            printf("Choose desired option: ");

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
                printf("The selected option is not valid! Try again.\n");
            }
						free_mem( (void**) &name);

        } else if (strcmp(name, "StackMapTable") == 0) {
						StackMapTable* specific_info = (StackMapTable*) attrInfo.specific_info;
						StackMapFrame* stack_map_frame = specific_info->entries;

						int offset = 0;
					  printf(" Number of entries: %d \n", specific_info->number_of_entries);
						printf(" Nr.\t\tStack Map Frame\n");

						for (int i = 0; i < specific_info->number_of_entries; i++) {

							if((stack_map_frame[i].frame_type >= 0) && (stack_map_frame[i].frame_type <= 63)) {
									offset += ((i == 0) ? (stack_map_frame[i].frame_type) : (stack_map_frame[i].frame_type + 1));
									printf(" %d\t\tSAME(%d),Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].frame_type);

							} else if((stack_map_frame[i].frame_type >= 64) && (stack_map_frame[i].frame_type <= 127)) {
									offset += ((i == 0) ? (stack_map_frame[i].frame_type) : ((stack_map_frame[i].frame_type) - 63));

									printf(" %d\t\tSAME_LOCALS_1_STACK_ITEM(%d), Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].frame_type - 64);
									printf(" \t\tStack verifications:\n");

									VerificationTypeInfo * ver_type = stack_map_frame[i].map_frame_type.same_locals_1_stack_item_frame.stack;

									switch (ver_type->tag) {
										case 0:
											printf(" \t\t\tTOP\n");
											break;
										case 1:
											printf(" \t\t\tINTEGER\n");
											break;
										case 2:
											printf(" \t\t\tFLOAT\n");
											break;
										case 3:
											printf(" \t\t\tLONG\n");
											break;
										case 4:
											printf(" \t\t\tDOUBLE\n");
											break;
										case 5:
											printf(" \t\t\tNULL\n");
											break;
										case 6:
											printf(" \t\t\tUNINITIALIZED THIS\n");
											break;
										case 7:
											printf(" \t\t\tOBJECT cp_info#%d ", ver_type->type_info.object_variable_info.cpool_index);
											get_instr_def((int)(ver_type->type_info.object_variable_info.cpool_index) - 1);
											printf("\n");
											break;
										case 8:
											printf(" \t\t\tUNINITIALIZED Offset: %d\n", ver_type->type_info.uninitialized_variable_info.offset);
											break;
									}

							} else if (stack_map_frame[i].frame_type == 247) {
									offset += ((i == 0) ? (stack_map_frame[i].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta) : (stack_map_frame[i].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta + 1));
									printf(" %d\t\tSAME_LOCALS_1_STACK_ITEM_EXTENDED(%d), Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta);
									printf(" \t\tStack verifications:\n");

									VerificationTypeInfo * ver_type = stack_map_frame[i].map_frame_type.same_locals_1_stack_item_frame_extended.stack;

									switch (ver_type->tag) {
										case 0:
											printf(" \t\t\tTOP\n");
											break;
										case 1:
											printf("\t\t\tINTEGER\n");
											break;
										case 2:
											printf(" \t\t\tFLOAT\n");
											break;
										case 3:
											printf(" \t\t\tLONG\n");
											break;
										case 4:
											printf(" \t\t\tDOUBLE\n");
											break;
										case 5:
											printf(" \t\t\tNULL\n");
											break;
										case 6:
											printf(" \t\t\tUNINITIALIZED THIS\n");
											break;
										case 7:
											printf(" \t\t\tOBJECT cp_info#%d ", ver_type->type_info.object_variable_info.cpool_index);
											get_instr_def((int)(ver_type->type_info.object_variable_info.cpool_index) - 1);
											printf("\n");
											break;
										case 8:
											printf(" \t\t\tUNINITIALIZED Offset: %d\n", ver_type->type_info.uninitialized_variable_info.offset);
											break;
									}

								} else if ((stack_map_frame[i].frame_type >= 248) && (stack_map_frame[i].frame_type <= 250)) {
									offset += ((i == 0) ? (stack_map_frame[i].map_frame_type.chop_frame.offset_delta) : (stack_map_frame[i].map_frame_type.chop_frame.offset_delta + 1));
									printf(" %d\t\tCHOP(%d),Offset: %d(+%d)\n",i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].map_frame_type.chop_frame.offset_delta);

								} else if (stack_map_frame[i].frame_type == 251) {
									offset += ((i == 0) ? (stack_map_frame[i].map_frame_type.same_frame_extended.offset_delta) : (stack_map_frame[i].map_frame_type.same_frame_extended.offset_delta + 1));
									printf(" %d\t\tSAME_FRAME_EXTENDED(%d),Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].map_frame_type.same_frame_extended.offset_delta);

								} else if ((stack_map_frame[i].frame_type >= 252) && (stack_map_frame[i].frame_type <= 254)) {
									offset += ((i == 0) ? (stack_map_frame[i].map_frame_type.append_frame.offset_delta) : (stack_map_frame[i].map_frame_type.append_frame.offset_delta + 1));
									printf(" %d\t\tAPPEND(%d),Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].map_frame_type.append_frame.offset_delta);
									VerificationTypeInfo * ver_type = stack_map_frame[i].map_frame_type.append_frame.locals;
									printf(" \t\t  Local verifications:\n");
									for (int posicaoVTI = 0; posicaoVTI < (stack_map_frame[i].frame_type - 251); posicaoVTI++) {
										switch (ver_type[posicaoVTI].tag) {
											case 0:
												printf(" \t\t\tTOP\n");
												break;
											case 1:
												printf(" \t\t\tINTEGER\n");
												break;
											case 2:
												printf(" \t\t\tFLOAT\n");
												break;
											case 3:
												printf(" \t\t\tLONG\n");
												break;
											case 4:
												printf(" \t\t\tDOUBLE\n");
												break;
											case 5:
												printf(" \t\t\tNULL\n");
												break;
											case 6:
												printf(" \t\t\tUNINITIALIZED THIS\n");
												break;
											case 7:
												printf(" \t\t\tOBJECT cp_info#%d ", ver_type[posicaoVTI].type_info.object_variable_info.cpool_index);
												get_instr_def((int)(ver_type[posicaoVTI].type_info.object_variable_info.cpool_index) - 1);
												printf("\n");
												break;
											case 8:
												printf(" \t\t\tUNINITIALIZED Offset: %d\n", ver_type[posicaoVTI].type_info.uninitialized_variable_info.offset);
												break;
										}
									}

								} else if (stack_map_frame[i].frame_type == 255) {
									offset += ((i == 0) ? (stack_map_frame[i].map_frame_type.full_frame.offset_delta) : (stack_map_frame[i].map_frame_type.full_frame.offset_delta + 1));
									printf(" %d\t\tFULL_FRAME(%d),Offset: %d(+%d)\n", i, stack_map_frame[i].frame_type, offset, stack_map_frame[i].map_frame_type.full_frame.offset_delta);
									VerificationTypeInfo * ver_type = stack_map_frame[i].map_frame_type.full_frame.locals;
									printf("\t\t  Local verifications:\n");
									for (int posicaoVTI = 0; posicaoVTI < stack_map_frame[i].map_frame_type.full_frame.number_of_locals; posicaoVTI++) {
										switch (ver_type[posicaoVTI].tag) {
											case 0:
												printf(" \t\t\tTOP\n");
												break;
											case 1:
												printf(" \t\t\tINTEGER\n");
												break;
											case 2:
												printf(" \t\t\tFLOAT\n");
												break;
											case 3:
												printf(" \t\t\tLONG\n");
												break;
											case 4:
												printf(" \t\t\tDOUBLE\n");
												break;
											case 5:
												printf(" \t\t\tNULL\n");
												break;
											case 6:
												printf(" \t\t\tUNINITIALIZED THIS\n");
												break;
											case 7:
												printf(" \t\t\tOBJECT cp_info#%d ", ver_type[posicaoVTI].type_info.object_variable_info.cpool_index);
												get_instr_def((int)(ver_type[posicaoVTI].type_info.object_variable_info.cpool_index) - 1);
												printf("\n");
												break;
											case 8:
												printf(" \t\t\tUNINITIALIZED Offset: %d\n", ver_type[posicaoVTI].type_info.uninitialized_variable_info.offset);
												break;
										}
									}

									ver_type = stack_map_frame[i].map_frame_type.full_frame.stack;
									printf(" \t\t  Stack verifications:\n");
									for (int posicaoVTI = 0; posicaoVTI < stack_map_frame[i].map_frame_type.full_frame.number_of_stack_items; posicaoVTI++) {
										switch (ver_type[posicaoVTI].tag) {
											case 0:
												printf(" \t\t\tTOP\n");
												break;
											case 1:
												printf(" \t\t\tINTEGER\n");
												break;
											case 2:
												printf(" \t\t\tFLOAT\n");
												break;
											case 3:
												printf(" \t\t\tLONG\n");
												break;
											case 4:
												printf(" \t\t\tDOUBLE\n");
												break;
											case 5:
												printf(" \t\t\tNULL\n");
												break;
											case 6:
												printf(" \t\t\tUNINITIALIZED THIS\n");
												break;
											case 7:
												printf(" \t\t\tOBJECT cp_info#%d ", ver_type[posicaoVTI].type_info.object_variable_info.cpool_index);
												get_instr_def((int)(ver_type[posicaoVTI].type_info.object_variable_info.cpool_index) - 1);
												printf("\n");
												break;
											case 8:
												printf(" \t\t\tUNINITIALIZED Offset: %d\n", ver_type[posicaoVTI].type_info.uninitialized_variable_info.offset);
												break;
										}
									}
								}
						}
            printf("|=====================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "Deprecated") == 0) {
            printf("|=====================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "Exceptions") == 0) {
						ExceptionAttribute* specific_info = (ExceptionAttribute*) attrInfo.specific_info;
						char* info = NULL;

						printf(" Exceptions Length: %d\n",(int)specific_info->numberOfExceptions);
					  printf(" Attribute Info: \n");

						printf("  Nr.\t\tException\t\tVerbose\n");
						for (int i = 0; i < specific_info->numberOfExceptions; i++) {
							info = getUtf8FromConstantPool(class->constant_pool[specific_info->exception_indexTable[i] - 1].class_const.name_index, class->constant_pool);
							printf("  %d\t\tcp_info #%d\t\t<%s> \n", i, specific_info->exception_indexTable[i], info);
							free_mem( (void**) &info);
						}
            printf("|=====================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "InnerClasses") == 0) {
            InnerClassesAttribute* specific_info = (InnerClassesAttribute*) attrInfo.specific_info;
            printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
            printf("| Nr.| %-22s | %-22s | %-31s | %-34s |\n", "Inner Class", "Outer Class", "Inner Name", "Access Flags");
						printf("|-----------------------------------------------------------------------------------------------------------------------------|\n");
            for (int innerClass_index = 0; innerClass_index < specific_info->numberOfClasses; innerClass_index++) {
                char* innerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].innerClassInfo_index - 1].class_const.name_index, class->constant_pool);
                char* outerClass = getUtf8FromConstantPool(class->constant_pool[specific_info->classes[innerClass_index].outerClassInfo_index - 1].class_const.name_index, class->constant_pool);
                char* innerName = getUtf8FromConstantPool(specific_info->classes[innerClass_index].innerName_index, class->constant_pool);
								printf("     | cp_info #%-13d | cp_info #%-13d | cp_info #%-12d\n", specific_info->classes[innerClass_index].innerClassInfo_index - 1, specific_info->classes[innerClass_index].outerClassInfo_index - 1, specific_info->classes[innerClass_index].innerName_index);
                printf(" %3d | %-22s | %-22s | %-31s | 0x%.4X - %s\n", innerClass_index, innerClass, outerClass, innerName, specific_info->classes[innerClass_index].innerClassAccess_flags, map_flags(specific_info->classes[innerClass_index].innerClassAccess_flags));
                free_mem( (void**) &innerClass );
                free_mem( (void**) &outerClass );
                free_mem( (void**) &innerName );
            }
            printf("|=============================================================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "Signature") == 0) {
					Signature_attribute* specific_info = (Signature_attribute*) attrInfo.specific_info;

					printf(" Signature index: cp_info #%-29d \n", specific_info->signature_index);
  				printf("|=====================================================================================|\n");					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

				} else if (strcmp(name, "EnclosingMethod") == 0) {
					EnclosingMethod* specific_info = (EnclosingMethod*) attrInfo.specific_info;

					printf(" Class index: cp_info #%-29d \n", specific_info->class_index);
					printf(" Method index: cp_info #%-29d \n", specific_info->method_index);
  				printf("|=====================================================================================|\n");					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

				} else if (strcmp(name, "SourceFile") == 0) {
            SourceFileAttribute* specific_info = (SourceFileAttribute*) attrInfo.specific_info;
            char* sourceFileName = getUtf8FromConstantPool(specific_info->sourceFile_index, class->constant_pool);
            printf(" Source file name index: cp_info #%-4d %-22s \n", specific_info->sourceFile_index, sourceFileName);
            free_mem( (void**) &sourceFileName );
  				  printf("|=====================================================================================|\n");            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "SourceDebugExtension") == 0) {
            char* debugName = getUtf8FromConstantPool(attrInfo.attributeName_index, class->constant_pool);
            printf(" Debug extension name index: cp_info #%-4d %-22s \n", attrInfo.attributeName_index, debugName);
            free_mem( (void**) &debugName );
  					printf("|=====================================================================================|\n");            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "LineNumberTable") == 0) {
					  LineNumberTableAttribute* specific_info = (LineNumberTableAttribute*) attrInfo.specific_info;

					  printf(" Line Number Table Length: %d\n",(int)specific_info->lineNumberTableLength);
					  printf(" Attribute Info: \n");
					  printf(" Nr.\t\tStartPC\t\tLineNumber\n");
					  for (int i = 0; i < specific_info->lineNumberTableLength; i++) {
							 printf(" %d\t\t%d\t\t%d\n", i, specific_info->lineNumberTable[i].start_pc, specific_info->lineNumberTable[i].lineNumber);
					  }
  					printf("|=====================================================================================|\n");            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "LocalVariableTable") == 0) {
					  LocalVariableTableAttribute* specific_info = (LocalVariableTableAttribute*) attrInfo.specific_info;

					  printf(" Attribute Info: \n");
					  printf(" Nr.\t\tStartPC\t\tLength\t\tName Index\t\tDescriptor Index\t\tIndex\n");
					  for (int i = 0; i < specific_info->localVariableTableLength; i++) {
							 printf(" %d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, specific_info->localVariableTable[i].start_pc, specific_info->localVariableTable[i].length, specific_info->localVariableTable[i].name_index, specific_info->localVariableTable[i].descriptor_index, specific_info->localVariableTable[i].index);
					  }
            printf("|=====================================================================================|\n");
            printf("Press ENTER to return...");
            while(getchar() != '\n');
            clearScreen();
						free_mem( (void**) &name);
            break;

        } else if (strcmp(name, "RuntimeVisibleAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "RuntimeInvisibleAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "RuntimeVisibleParameterAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "RuntimeInvisibleParameterAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "RuntimeVisibleTypeAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "RuntimeInvisibleTypeAnnotations") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "AnnotationDefault") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "BootstrapMethods") == 0) {
					BootstrapMethods_attribute* specific_info = (BootstrapMethods_attribute*) attrInfo.specific_info;

					printf(" Attribute Info: \n");
					printf(" Nr.\t\tBootstrap Method\t\tArguments\n");
					for (int i = 0; i < specific_info->num_bootstrap_methods; i++) {
						 printf(" %d\t\tcp_info #%d\t\t\n", i, specific_info->bootstrap_methods[i].bootstrap_method_ref);
						 for (int j = 0; j < specific_info->bootstrap_methods[i].num_bootstrap_arguments; j++) {
							 printf(" \t\t\t\t\t%d\n", specific_info->bootstrap_methods[i].bootstrap_arguments[j]);
						 }
					}

					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        } else if (strcmp(name, "MethodParameters") == 0) {
					printf("|=====================================================================================|\n");
					printf("Press ENTER to return...");
					while(getchar() != '\n');
					clearScreen();
					free_mem( (void**) &name);
					break;

        }
    }
}

void showCode(uint8_t* code, int codeLength) {
    if (codeLength == 0) {
        printf("No data in Byte Code\n");
        return;
    }

    printf("|==============================================================|\n");
    printf("|                         Byte Code                            |\n");
    printf("|==============================================================|\n");
    int code_index = 0;
    while(code_index < codeLength) {
        Instruction* instr = decode(code, &code_index, 1);
        if (instr->arguments_count == 0) {
            printf(" %-4d %-55s \n", instr->pc, instr->name);
        } else if (instr->arguments_count == 1) {
						if ((strstr(instr->name, "push") != NULL) || (strstr(instr->name, "store") != NULL) || (strstr(instr->name, "load") != NULL)) {
							printf(" %-4d %-15s %d                                    		 		 \n", instr->pc, instr->name, instr->arguments[0]);
						} else if (strstr(instr->name, "newarray") != NULL) {
							printf(" %-4d %-15s %d (%s)                                   		 \n", instr->pc, instr->name, instr->arguments[0], map_array_type(instr->arguments[0]));
						} else {
							printf(" %-4d %-15s cp_info #%d ", instr->pc, instr->name, instr->arguments[0]);
							get_instr_def((int)(instr->arguments[0]) - 1);
							printf("\n");
						}
        } else if (instr->arguments_count == 2) {
						if ((strstr(instr->name, "goto") != NULL) || (strstr(instr->name, "if") != NULL)) {
							printf(" %-4d %-15s %d +(%d)                                       \n", instr->pc, instr->name, (instr->pc + instr->arguments[1]), instr->arguments[1]);
						} else if (strstr(instr->name, "sipush") != NULL) {
							uint16_t nu2 = 0;
							nu2 = ((uint16_t)((uint8_t)instr->arguments[0] << 8 | (uint8_t)instr->arguments[1]));

							printf(" %-4d %-15s %" PRIu16 "\n", instr->pc, instr->name, nu2);
						} else if (strstr(instr->name, "iinc") != NULL) {
							printf(" %-4d %-15s %d by %d                                       \n", instr->pc, instr->name, instr->arguments[0], instr->arguments[1]);
						} else {
							uint16_t nu2 = 0;
							nu2 = ((uint16_t)((uint8_t)instr->arguments[0] << 8 | (uint8_t)instr->arguments[1]));

							printf(" %-4d %-15s cp_info #%d ", instr->pc, instr->name, instr->arguments[1]);
							get_instr_def((int)(nu2) - 1);
							printf("\n");
						}
        } else if (instr->arguments_count == 3) {
						if (strstr(instr->name, "multianewarray") != NULL) {
							uint16_t nu2 = 0;
							nu2 = ((uint16_t)((uint8_t)instr->arguments[0] << 8 | (uint8_t)instr->arguments[1]));

							char* thisClass = getUtf8FromConstantPool(class->constant_pool[(int)(nu2) - 1].class_const.name_index, class->constant_pool);

							printf(" %-4d %-15s cp_info #%" PRIu16 " <%s> dim %d                      \n", instr->pc, instr->name, nu2 , thisClass, instr->arguments[2]);
							free_mem( (void**) &thisClass );
						} else {
							printf(" %-4d %-15s cp_info #%d                                      \n", instr->pc, instr->name, instr->arguments[2]);
						}
        } else if (instr->arguments_count == 4) {
						if (strstr(instr->name, "invokeinterface") != NULL){
							printf(" %-4d %-15s cp_info #%" PRIu8 " ", instr->pc, instr->name, instr->arguments[1]);
							get_instr_def((int)(instr->arguments[1]) - 1);
							printf(" count %" PRIu8 "", instr->arguments[2]);
							printf("\n");
						} else if (strstr(instr->name, "invokedynamic") != NULL) {
							uint16_t nu2 = 0;
							nu2 = ((uint16_t)((uint8_t)instr->arguments[0] << 8 | (uint8_t)instr->arguments[1]));

							char* string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[(int)(nu2) - 1].invokeDynamicInfo_const.name_and_type_index - 1].nameAndType_const.name_index, class->constant_pool);

							printf(" %-4d %-15s cp_info #%" PRIu8 " <%s, BootstrapMethods #%d> \n", instr->pc, instr->name, instr->arguments[1], string, class->constant_pool[(int)(nu2) - 1].invokeDynamicInfo_const.bootstrap_method_attr_index);
							free_mem( (void**) &string );
						} else {
							printf(" %-4d %-15s cp_info #%" PRIu8 " ", instr->pc, instr->name, instr->arguments[1]);
							get_instr_def((int)(instr->arguments[1]) - 1);
							printf("\n");
						}
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
        printf("No data in the Exception Table\n");
        return;
    }

    printf("|===========================================================================|\n");
    printf("|                      Exception Table                                      |\n");
    printf("|===========================================================================| \n");
		printf(" Nr.\t\tStartPC\t\tEndPC\t\tHandlerPC\tCatchType\n");
		for (int i = 0; i < exceptionTableLength; i++) {
			 printf(" %d\t\t%d\t\t%d\t\t%d\t\tcp_info #%d\n", i, exceptionTable[i].start_pc, exceptionTable[i].end_pc, exceptionTable[i].handler_pc, exceptionTable[i].catch_type) ;
		}
    printf("|===========================================================================| \n");
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
        printf("Enter (\"none\" to return): ");
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
            printf("Are you sure to open the class file (Y-y or N-n)? ");
            scanf("%c", &confirmation);
            while(getchar() != '\n');

            if (confirmation == 'Y' || confirmation == 'y') {
                clearScreen();
                if (file != NULL) {
                    closeFile(&file);
                }
                file = tempPointer;
                strcpy(path, tempPath);
                if (class != NULL) {
                    deallocateClass(&class);
                }
                class = getClassfile(file);
                goto confirmation;

            } else if (confirmation == 'N' || confirmation == 'n') {
                clearScreen();
                strcpy(tempPath, "");
                closeFile(&tempPointer);
                goto noConfirmation;
            } else {
                printf("Chosen option is not valid. Try again!\n");
                continue;
            }
        }

        noConfirmation:
            continue;

        confirmation:
            break;
    }
}

void menu(char* nome) {

    if (nome != NULL) {
        if (strstr(nome, ".class") != NULL){
            if(file != NULL){
                closeFile(&file);
            }

            file = openFile(nome, "rb");
            if (file != NULL) {

                strcpy(path, nome);
                if (class != NULL) {
                    deallocateClass(&class);
                }
                class = getClassfile(file);

            } else {
                printf("The path is not valid! Try again!\n");
            }
        } else {
            printf("The file extension is not allowed. Try again!\n");
        }
    }

    int option;
    char *file_name;

    while(true) {
        if (file != NULL && path[0] != '\0') {
            file_name = getNewName();
        }

        printf("|==============================================================|\n");
        printf("|                       Classfile Viewer                       |\n");
        printf("|==============================================================|\n");

        if (file != NULL && path[0] != '\0') {

            char* thisClass = getUtf8FromConstantPool(class->constant_pool[class->thisClass - 1].class_const.name_index, class->constant_pool);
            char* superClass = getUtf8FromConstantPool(class->constant_pool[class->superClass - 1].class_const.name_index, class->constant_pool);
            char* access_flags = map_flags(class->access_flags);

            printf("| Chosen file: %-47s |\n", file_name);
            printf("| Size (bytes): %-46d |\n", fileSize(file));
            printf("|--------------------------------------------------------------|\n");
            printf("| General Information:                                         |\n");
            printf("|--------------------------------------------------------------|\n");
            printf(" Magic:              0x%.8X                               \n", class->magic);
            printf(" Minor version:      %u (%.1f) \n", class->minor_version, decoderVersion(class->minor_version));
            printf(" Major version:      %u (%.1f) \n", class->major_version, decoderVersion(class->major_version));
            printf(" Contant pool count: %-40d \n", class->constantPool_count);
            printf(" Access flags:       0x%.4X %-33s \n", class->access_flags, access_flags);
            printf(" This class:         cp_info #%-4d <%s>                      \n", class->thisClass, thisClass);
            printf(" Super class:        cp_info #%-4d <%s>                      \n", class->superClass, superClass);
            printf(" Interfaces count:   %-40u \n", class->interfaces_count);
            printf(" Fields count:       %-40u \n", class->fields_count);
            printf(" Methods count:      %-40u \n", class->methods_count);
            printf(" Attributes count:   %-40u \n",class->attributes_count);
            printf("|--------------------------------------------------------------|\n");
            printf("| 3) Constant pool                                             |\n");
            printf("| 4) Interfaces                                                |\n");
            printf("| 5) Fields                                                    |\n");
            printf("| 6) Methods                                                   |\n");
            printf("| 7) Attributes                                                |\n");
						printf("| 8) Run JVM                                                   |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose another .class file                                |\n");

            free_mem( (void**) &thisClass );
            free_mem( (void**) &superClass );
            free_mem( (void**) &access_flags );

        } else {

            printf("| No Chosen file                                               |\n");
            printf("|--------------------------------------------------------------|\n");
            printf("| 1) Choose a .class file                                      |\n");

        }
        printf("| 2) Quit                                                      |\n");
        printf("|==============================================================|\n");
        printf("Enter desired option: ");
        scanf("%d", &option);
        while(getchar() != '\n');
        printf("\n");
        if (option == 2) {
            strcpy(path, "");
            if (file != NULL) {
                closeFile(&file);
            }
            freeMemManager();
            break;
        }
        displayOption(option);
    }
}

void displayOption(int option) {
    clearScreen();

    switch(option) {
        case 1:
            chooseFile();
            break;
        case 3:
            showConstantPool();
            break;
        case 4:
           showInterfaces();
            break;
        case 5:
            showFields();
            break;
        case 6:
            showMethods();
            break;
        case 7:
            showAttributes(class->attributes, class->attributes_count);
            break;
				case 8:
		        run(*class);
						printf("|==============================================================|\n");
						printf("Press ENTER to return...");
						while(getchar() != '\n');
						clearScreen();
		        break;
        default:
            printf("The chosen option is not valid! Try again.\n");
    }
}

char* getNewName() {
    int delimeter_position = 0;
    int i = 0;

    if (strstr(path, "/") != NULL) {
        for (int pos = 0; path[pos] != '\0'; pos++) {
            if (path[pos] == '\\') {
                delimeter_position = pos;
            }
        }
    }

    while (path[i] != '\0') {
        if (path[i] == '/') {
            delimeter_position = i;
        }
        i++;
    }
    return &path[delimeter_position + 1];
}

void get_instr_def(int cp_index) {
	char* string = NULL;
	char* aux = NULL;

	switch(class->constant_pool[cp_index].tag) {
	    case LARGE_NUMERIC_CONTINUED:
	        break;

	    case UTF8:
	        string = utf8ToString(class->constant_pool[cp_index].utf8_const.bytes, class->constant_pool[cp_index].utf8_const.length);
	        printf("<%s>", string);
	        free_mem( (void**) &string );
	        break;

	    case INTEGER:
	        printf("<%.1d>", class->constant_pool[cp_index].integer_const.bytes);
	        break;

	    case FLOAT:
	        printf("<%.1f>", decodeFloat(class->constant_pool[cp_index].float_const.bytes));
	        break;

	    case LONG:
	        printf("<%.1ld>",decodeLong(class->constant_pool[cp_index].long_const.bytes.highBytes, class->constant_pool[cp_index].long_const.bytes.lowBytes));
	        break;

	    case DOUBLE:
	        printf("<%.1lf>", decodeDouble(class->constant_pool[cp_index].double_const.bytes.highBytes, class->constant_pool[cp_index].double_const.bytes.lowBytes));
	        break;

	    case CLASS:
	        string = getUtf8FromConstantPool(class->constant_pool[cp_index].class_const.name_index, class->constant_pool);
	        printf("<%s>", string);
	        free_mem( (void**) &string );
	        break;

	    case STRING:
	        string = getUtf8FromConstantPool(class->constant_pool[cp_index].string_const.string_index, class->constant_pool);
	        printf("<%s>", string);
	        free_mem( (void**) &string );
	        break;

	    case FIELD_REF:
	        string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.class_index - 1].class_const.name_index, class->constant_pool);
	        aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].fieldRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);

	        printf("<%s.%s>", string, aux);
	        free_mem( (void**) &string );
	        free_mem( (void**) &aux );
	        break;

	    case METHOD_REF:
	        string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.class_index - 1].class_const.name_index, class->constant_pool);
	        aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].methodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
	        printf("<%s.%s>", string, aux);

	        free_mem( (void**) &string );
	        free_mem( (void**) &aux );
	        break;

	    case INTERFACE_METHOD_REF:
	        string = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.class_index - 1].class_const.name_index, class->constant_pool);
	        aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].interfaceMethodRef_const.nameAndType_index - 1].nameAndType_const.name_index, class->constant_pool);
	        printf("<%s.%s>", string, aux);

	        free_mem( (void**) &string );
	        free_mem( (void**) &aux );
	        break;

	   case METHOD_TYPE:
	        string = getUtf8FromConstantPool(class->constant_pool[cp_index].methodType_const.descriptor_index, class->constant_pool);
	        printf("<%s>", string);
	        free_mem( (void**) &string );
	        break;

	    case INVOKE_DYNAMIC:
	        string = getUtf8FromConstantPool(class->constant_pool[cp_index].invokeDynamicInfo_const.bootstrap_method_attr_index, class->constant_pool);
	        aux = getUtf8FromConstantPool(class->constant_pool[class->constant_pool[cp_index].invokeDynamicInfo_const.name_and_type_index - 1].invokeDynamicInfo_const.name_and_type_index, class->constant_pool);
	        printf("<%s.%s>", string, aux);

	        free_mem( (void**) &string );
	        free_mem( (void**) &aux );
	        break;
	}
}

void clearScreen() {
    system("clear");
}
