/**
 * @file classe.c
 * @brief Classfile operations library source
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * Definitions for all the classe.h functions
 */
#include <string.h>
#include "mem-manager.hpp"
#include "utils.hpp"
#include "class.hpp"
/**
 * @brief Get the classe file components
 *
 * Magic number, minor versin, major version
 * constant pool count, constant pool, access flags
 * thisClass, superClass, interfaces count, interfaces
 * fields count, fields, methods count, methods, attributes count
 * attributes.
 */

void sum2(int* bytecount){
      (*bytecount) +=2;
}

void sum4(int* bytecount){
      (*bytecount) +=4;
}

 char* getUtf8FromConstantPool(int index, ConstPool* constant_pool) {
     if (index != 0) {
         return utf8ToString(constant_pool[index - 1].utf8_const.bytes, constant_pool[index - 1].utf8_const.length);
     } else {
         char* invalid = (char*) set_mem(32 * sizeof(char));
         strcpy(invalid, "invalid constant pool reference");
         invalid[31] = '\0';
         return invalid;
     }
 }

 uint8_t get1bytesFromByteArray(uint8_t* byteArr, int bytecount) {
     return byteArr[bytecount];
 }

 uint16_t get2bytesFromByteArray(uint8_t* byteArr, int bytecount) {
     return ((uint16_t) byteArr[bytecount + 1] << 8) | (uint16_t) byteArr[bytecount];
 }

 uint32_t get4bytesFromByteArray(uint8_t* byteArr, int bytecount) {
     return ((uint32_t) byteArr[bytecount + 3] << 24) | ((uint32_t) byteArr[bytecount + 2] << 16) | ((uint32_t) byteArr[bytecount + 1] << 8) | (uint32_t) byteArr[bytecount + 0];
 }

 double decodeDouble(uint32_t high, uint32_t low){
    double result;
    uint64_t valor;
    float value;

    valor = ((uint64_t)high) << 32 | low;

  	 int8_t s = ((valor >> 63) == 0) ? 1 : -1;
  	 int16_t e = ((valor >> 52) & 0x7ffL);
  	 uint64_t m = (e == 0) ? ((valor & 0xfffffffffffffL) << 1) : ((valor & 0xfffffffffffffL) | 0x10000000000000L);

    value = (pow(2, e - 1075) > 0 ? (m) * (pow(2, e - 1075)) : (m) / (pow(2, 1075 - e)));

    result = (s) * value;

    return result;
 }

 float decodeFloat(uint32_t bytes) {
  	float result;
   float value;

  	int s = ((bytes>>31) == 0) ? 1 : -1;
  	int e = ((bytes>>23) & 0xff);
  	int m = (e == 0) ? (bytes & 0x7fffff) << 1 : (bytes & 0x7fffff) | 0x800000;

   value = ((pow(2, e - 150)) > 0 ? (m) * (pow(2, e - 150)) : (m) / (pow(2, 150 - e)));

  	result = (s) * value;

  	return result;
}

 long decodeLong(uint32_t high, uint32_t low) {
     return ((uint64_t)high) << 32 | low;
 }

 ConstPool* getConstantPool(FILE* fp, int* bytecount, uint16_t cp_count) {
     int index = 0;
     ConstPool* cp = (ConstPool*) set_mem(cp_count * sizeof(ConstPool));

     while (index < cp_count) {
         cp[index].tag = getByte(fp, (*bytecount));
         (*bytecount)++;

         switch(cp[index].tag) {
             case UTF8:
                 cp[index].utf8_const.length = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 cp[index].utf8_const.bytes = (uint8_t*) set_mem((cp[index].utf8_const.length) * sizeof(uint8_t));
                 for (int utf8_index = 0; utf8_index < (cp[index].utf8_const.length); utf8_index++) {
                     cp[index].utf8_const.bytes[utf8_index] = getByte(fp, (*bytecount));
                     (*bytecount)++;
                 }
                 break;
             case INTEGER:
                 cp[index].integer_const.bytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 break;
             case FLOAT:
                 cp[index].float_const.bytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 break;
             case LONG:
                 cp[index].long_const.bytes.highBytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 cp[index].long_const.bytes.lowBytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 index++;
                 cp[index].tag = LARGE_NUMERIC_CONTINUED;
                 break;
             case DOUBLE:
                 cp[index].double_const.bytes.highBytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 cp[index].double_const.bytes.lowBytes = to4Bytes(getDoubleWord(fp, (*bytecount)));
                 sum4(bytecount);
                 index++;
                 cp[index].tag = LARGE_NUMERIC_CONTINUED;
                 break;
             case CLASS:
                 cp[index].class_const.name_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
             case STRING:
                 cp[index].string_const.string_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
             case FIELD_REF:
                 cp[index].fieldRef_const.class_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 cp[index].fieldRef_const.nameAndType_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
             case METHOD_REF:
                 cp[index].methodRef_const.class_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 cp[index].methodRef_const.nameAndType_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
             case INTERFACE_METHOD_REF:
                 cp[index].interfaceMethodRef_const.class_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 cp[index].interfaceMethodRef_const.nameAndType_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
             case NAME_AND_TYPE:
                 cp[index].nameAndType_const.name_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 cp[index].nameAndType_const.descriptor_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
              case METHOD_HANDLE:
                 cp[index].methodHandle_const.reference_kind = getByte(fp, (*bytecount));
                 (*bytecount)++;
                 cp[index].methodHandle_const.reference_index = to2Bytes(getWord(fp, (*bytecount)));
                 sum2(bytecount);
                 break;
              case METHOD_TYPE:
                cp[index].methodType_const.descriptor_index = to2Bytes(getWord(fp, (*bytecount)));
                sum2(bytecount);
                break;
              case INVOKE_DYNAMIC:
                cp[index].invokeDynamicInfo_const.bootstrap_method_attr_index = to2Bytes(getWord(fp, (*bytecount)));
                sum2(bytecount);
                cp[index].invokeDynamicInfo_const.name_and_type_index = to2Bytes(getWord(fp, (*bytecount)));
                sum2(bytecount);
                break;
             default:
                 printf("Error mounting constant pool!\n");
         }
         index++;
     }

     return cp;
 }

 uint16_t* getInterfaces(FILE* fp, int* bytecount, uint16_t interfaces_count) {
     uint16_t* interfaces = (uint16_t*) set_mem(interfaces_count * sizeof(uint16_t));

     for (int interfaces_index = 0; interfaces_index < interfaces_count; interfaces_index++) {
         interfaces[interfaces_index] = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
     }

     return interfaces;
 }

 Field* getFields(FILE* fp, int* bytecount, uint16_t fields_count, ConstPool* constant_pool) {
     // Put into Memory
     Field* field = (Field*) set_mem(fields_count * sizeof(Field));
     int index = 0;

     while(index < fields_count) {
         field[index].access_flags = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         field[index].name_index = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         field[index].descriptor_index = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         field[index].attributes_count = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         field[index].attributes = getAttributes(fp, bytecount, field[index].attributes_count, constant_pool);
         index++;
     }
     return field;
 }

 Method* getMethods(FILE* fp, int* bytecount, uint16_t methods_count, ConstPool* constant_pool) {
     Method* method = (Method*) set_mem(methods_count * sizeof(Method));
     int index = 0;

     while (index < methods_count) {
         method[index].access_flags = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         method[index].name_index = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         method[index].descriptor_index = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         method[index].attributes_count = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);
         method[index].attributes = getAttributes(fp, bytecount, method[index].attributes_count, constant_pool);
         index++;
     }
     return method;
 }

 Attribute* getAttributes (FILE* fp, int* bytecount, uint16_t attributes_count, ConstPool* constant_pool) {
     Attribute* attribute = (Attribute*) set_mem(attributes_count * sizeof(Attribute));
     int index = 0;

     while(index < attributes_count) {
         attribute[index].attributeName_index = to2Bytes(getWord(fp, (*bytecount)));
         sum2(bytecount);

         attribute[index].attributeLength = to4Bytes(getDoubleWord(fp, (*bytecount)));
         sum4(bytecount);

         attribute[index].info = (uint8_t*) set_mem(attribute[index].attributeLength * sizeof(uint8_t));
         for (int attribute_index = 0; attribute_index < (attribute[index].attributeLength); attribute_index++) {
             attribute[index].info[attribute_index] = getByte(fp, (*bytecount));
             (*bytecount)++;
         }
         attribute[index].specific_info = decodeInfo(attribute[index], constant_pool);
         index++;
     }

     return attribute;
 }

 Attribute* getAttributesFromByteArray(uint8_t* info, int* bytecount, uint16_t attributes_count, ConstPool* constant_pool) {
     Attribute* attribute = (Attribute*) set_mem(attributes_count * sizeof(Attribute));
     int index = 0;

     while (index < attributes_count) {
         attribute[index].attributeName_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         attribute[index].attributeLength = to4Bytes(get4bytesFromByteArray(info, (*bytecount)));
         sum4(bytecount);

         if (attribute[index].attributeLength > 0) {
             int attribute_index = 0;
             attribute[index].info = (uint8_t*) set_mem((attribute[index].attributeLength) * sizeof(uint8_t));
             while (attribute_index < (attribute[index].attributeLength)) {
               attribute[index].info[attribute_index] = get1bytesFromByteArray(info, (*bytecount));
               (*bytecount)++;
               attribute_index++;
             }

             attribute[index].specific_info = decodeInfo(attribute[index], constant_pool);
         }
         index++;
     }
     return attribute;
 }

 void* decodeInfo(Attribute attribute, ConstPool* constant_pool) {
     int bytecount = 0;
     void* specific_info = NULL;
     char* attributeName = getUtf8FromConstantPool(attribute.attributeName_index, constant_pool);

     if (strncmp(attributeName, "ConstantValue", strlen(attributeName)) == 0) {
         ConstantValueAttribute* ref = (ConstantValueAttribute*) set_mem(sizeof(ConstantValueAttribute));
         ref->constantValue_index = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         specific_info = ref;

     } else if (strncmp(attributeName, "Code", strlen(attributeName)) == 0) {
         CodeAttribute* ref = (CodeAttribute*) set_mem(sizeof(CodeAttribute));
         int count = 0;
         ref->max_stack = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->max_locals = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->codeLength = to4Bytes(get4bytesFromByteArray(attribute.info, bytecount));
         bytecount += 4;
         ref->code = (uint8_t*) set_mem(ref->codeLength * sizeof(uint8_t));
         while (count < ref->codeLength) {
           ref->code[count] = get1bytesFromByteArray(attribute.info, bytecount);
           bytecount++;
           count++;
         }
         ref->exceptionTableLength = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->exceptionTable = getExceptionTable(attribute.info, &bytecount, ref->exceptionTableLength);
         ref->attributes_count = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->attributes = getAttributesFromByteArray(attribute.info, &bytecount, ref->attributes_count, constant_pool);
         specific_info = ref;

    } else if (strncmp(attributeName, "StackMapTable", strlen(attributeName)) == 0) {
         StackMapTable* ref = (StackMapTable*) set_mem(sizeof(StackMapTable));
         int count = 0;
         ref->number_of_entries = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         if (ref->number_of_entries > 0) {
             ref->entries = (StackMapFrame*) set_mem(ref->number_of_entries * sizeof(StackMapFrame));
             while (count < ref->number_of_entries) {
                  ref->entries[count] = *(getStackMapFrame(attribute.info, &bytecount, ref->number_of_entries));
                  count++;
             }
         }
         specific_info = ref;

    } else if (strncmp(attributeName, "Exceptions", strlen(attributeName)) == 0) {
         ExceptionAttribute* ref = (ExceptionAttribute*) set_mem(sizeof(ExceptionAttribute));
         int count = 0;
         ref->numberOfExceptions = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->exception_indexTable = (uint16_t*) set_mem(ref->numberOfExceptions * sizeof(uint16_t));
         while (count < ref->numberOfExceptions) {
             ref->exception_indexTable[count] = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
             bytecount += 2;
             count++;
         }
         specific_info = ref;

     } else if (strncmp(attributeName, "InnerClasses", strlen(attributeName)) == 0) {
         InnerClassesAttribute* ref = (InnerClassesAttribute*) set_mem(sizeof(InnerClassesAttribute));
         ref->numberOfClasses = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->classes = getInnerClasses(attribute.info, &bytecount, ref->numberOfClasses);
         specific_info = ref;

     } else if (strncmp(attributeName, "SourceFile", strlen(attributeName)) == 0) {
         SourceFileAttribute* ref = (SourceFileAttribute*) set_mem(sizeof(SourceFileAttribute));
         ref->sourceFile_index = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         specific_info = ref;

     } else if (strncmp(attributeName, "Signature", strlen(attributeName)) == 0) {
         Signature_attribute* ref = (Signature_attribute*) set_mem(sizeof(Signature_attribute));
         ref->signature_index = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         specific_info = ref;

     } else if (strncmp(attributeName, "LineNumberTable", strlen(attributeName)) == 0) {
         LineNumberTableAttribute* ref = (LineNumberTableAttribute*) set_mem(sizeof(LineNumberTableAttribute));
         ref->lineNumberTableLength = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->lineNumberTable = getLineNumberTable(attribute.info, &bytecount, ref->lineNumberTableLength);
         specific_info = ref;

     } else if (strncmp(attributeName, "LocalVariableTable", strlen(attributeName)) == 0) {
         LocalVariableTableAttribute* ref = (LocalVariableTableAttribute*) set_mem(sizeof(LocalVariableTableAttribute));
         ref->localVariableTableLength = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
         bytecount += 2;
         ref->localVariableTable = getLocalVariableTable(attribute.info, &bytecount, ref->localVariableTableLength);
         specific_info = ref;
     } else if (strncmp(attributeName, "BootstrapMethods", strlen(attributeName)) == 0) {
        BootstrapMethods_attribute* ref = (BootstrapMethods_attribute*) set_mem(sizeof(BootstrapMethods_attribute));
        ref->num_bootstrap_methods = to2Bytes(get2bytesFromByteArray(attribute.info, bytecount));
        bytecount += 2;
        ref->bootstrap_methods = getBootstrapMethods(attribute.info, &bytecount, ref->num_bootstrap_methods);
        specific_info = ref;
     }
     free_mem( (void**) &attributeName );
     return specific_info;
 }

 Bootstrap_methods* getBootstrapMethods(uint8_t* info, int* bytecount, int num_bootstrap_methods) {
     Bootstrap_methods* bootstrap_methods = (Bootstrap_methods*) set_mem(num_bootstrap_methods * sizeof(Bootstrap_methods));
     int index = 0;
     int inner_index = 0;

     while (index < num_bootstrap_methods) {
         bootstrap_methods[index].bootstrap_method_ref = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         bootstrap_methods[index].num_bootstrap_arguments = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         while (inner_index < bootstrap_methods[index].num_bootstrap_arguments) {
            bootstrap_methods[index].bootstrap_arguments[inner_index] = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
            sum2(bytecount);

            inner_index++;
         }

         index++;
         inner_index = 0;
     }
     return bootstrap_methods;
 }

 StackMapFrame* getStackMapFrame(uint8_t* info, int* bytecount, int localVariableTableLength) {
     StackMapFrame *stack_map_frame = (StackMapFrame*) set_mem(sizeof(StackMapFrame));
	stack_map_frame->frame_type = get1bytesFromByteArray(info, (*bytecount));
     (*bytecount)++;

     if (stack_map_frame->frame_type >= 64 && stack_map_frame->frame_type <= 127) {
		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame.stack = (VerificationTypeInfo*) set_mem(sizeof(VerificationTypeInfo));
		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame.stack = getVerificationTypeInfo(info, bytecount);

	} else if (stack_map_frame->frame_type == 247) {
		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.offset_delta = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

		stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = (VerificationTypeInfo*) set_mem(sizeof(VerificationTypeInfo));
	     stack_map_frame->map_frame_type.same_locals_1_stack_item_frame_extended.stack = getVerificationTypeInfo(info, bytecount);

	} else if (stack_map_frame->frame_type >= 248 && stack_map_frame->frame_type <= 250) {
		stack_map_frame->map_frame_type.chop_frame.offset_delta = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

	} else if (stack_map_frame->frame_type == 251) {
		stack_map_frame->map_frame_type.same_frame_extended.offset_delta = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

	} else if (stack_map_frame->frame_type >= 252 && stack_map_frame->frame_type <= 254) {
		stack_map_frame->map_frame_type.append_frame.offset_delta = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);
		uint16_t sizeMalloc = (stack_map_frame->frame_type - 251);

		stack_map_frame->map_frame_type.append_frame.locals = (VerificationTypeInfo*) set_mem(sizeof(VerificationTypeInfo));

		for (int posicao = 0; posicao < sizeMalloc; posicao++) {
			stack_map_frame->map_frame_type.append_frame.locals[posicao] = *(getVerificationTypeInfo(info, bytecount));
		}

	} else if (stack_map_frame->frame_type == 255) {
		stack_map_frame->map_frame_type.full_frame.offset_delta = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

		stack_map_frame->map_frame_type.full_frame.number_of_locals = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

		if (stack_map_frame->map_frame_type.full_frame.number_of_locals > 0) {
			stack_map_frame->map_frame_type.full_frame.locals = (VerificationTypeInfo*) set_mem(stack_map_frame->map_frame_type.full_frame.number_of_locals * sizeof(VerificationTypeInfo));

			for (int posicao = 0; posicao < stack_map_frame->map_frame_type.full_frame.number_of_locals; posicao++) {
				stack_map_frame->map_frame_type.full_frame.locals[posicao] = *(getVerificationTypeInfo(info, bytecount));
			}
		}

		stack_map_frame->map_frame_type.full_frame.number_of_stack_items = to2Bytes(get2bytesFromByteArray(info, *bytecount));
          sum2(bytecount);

		if (stack_map_frame->map_frame_type.full_frame.number_of_stack_items > 0) {
			stack_map_frame->map_frame_type.full_frame.stack = (VerificationTypeInfo*) set_mem(stack_map_frame->map_frame_type.full_frame.number_of_stack_items * sizeof(VerificationTypeInfo));

               for (int posicao = 0; posicao < stack_map_frame->map_frame_type.full_frame.number_of_stack_items; posicao++) {
				stack_map_frame->map_frame_type.full_frame.stack[posicao] = *(getVerificationTypeInfo(info, bytecount));
			}
		}
	}

	return stack_map_frame;
}

VerificationTypeInfo* getVerificationTypeInfo (uint8_t* info, int* bytecount) {
	VerificationTypeInfo *vtype = (VerificationTypeInfo*) set_mem(sizeof(VerificationTypeInfo));
	vtype->tag = get1bytesFromByteArray(info, (*bytecount));
     (*bytecount)++;

	switch (vtype->tag) {
		case 7:
			vtype->type_info.object_variable_info.cpool_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
               sum2(bytecount);
			break;
		case 8:
			vtype->type_info.uninitialized_variable_info.offset = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
               sum2(bytecount);
			break;
		default:
			break;
	}

	return vtype;
}

 ExceptionTableEntry* getExceptionTable(uint8_t* info, int* bytecount, int exceptionTableLength) {
     ExceptionTableEntry* exceptionTable = (ExceptionTableEntry*) set_mem(exceptionTableLength * sizeof(ExceptionTableEntry));
     int index = 0;

     while (index < exceptionTableLength) {
         exceptionTable[index].start_pc = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         exceptionTable[index].end_pc = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         exceptionTable[index].handler_pc = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         exceptionTable[index].catch_type = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         index++;
     }
     return exceptionTable;
 }

 InnerClass* getInnerClasses(uint8_t* info, int* bytecount, int numberOfClasses) {
     InnerClass* innerClasses = (InnerClass*) set_mem(numberOfClasses * sizeof(InnerClass));
     int index = 0;

     while (index < numberOfClasses) {
         innerClasses[index].innerClassInfo_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         innerClasses[index].outerClassInfo_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         innerClasses[index].innerName_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         innerClasses[index].innerClassAccess_flags = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         index++;
     }
     return innerClasses;
 }

 LineNumberTableEntry* getLineNumberTable(uint8_t* info, int* bytecount, int lineNumberTableLength) {
     LineNumberTableEntry* lineNumberTable = (LineNumberTableEntry*) set_mem(lineNumberTableLength * sizeof(LineNumberTableEntry));
     int index = 0;

     while (index < lineNumberTableLength) {
         lineNumberTable[index].start_pc = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         lineNumberTable[index].lineNumber = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         index++;
     }
     return lineNumberTable;
 }

 LocalVariableTableEntry* getLocalVariableTable(uint8_t* info, int* bytecount, int localVariableTableLength) {
     LocalVariableTableEntry* localVariableTable = (LocalVariableTableEntry*) set_mem(localVariableTableLength * sizeof(LocalVariableTableEntry));
     int index = 0;

     while (index < localVariableTableLength) {
         localVariableTable[index].start_pc = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         localVariableTable[index].length = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         localVariableTable[index].name_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         localVariableTable[index].descriptor_index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         localVariableTable[index].index = to2Bytes(get2bytesFromByteArray(info, (*bytecount)));
         sum2(bytecount);
         index++;
     }
     return localVariableTable;
 }

 void deallocateClass(Class** classe) {
     if ((*classe)->constant_pool != NULL) {
         free_mem((void**) &((*classe)->constant_pool));
     }

     if ((*classe)->interfaces != NULL) {
         free_mem((void**) &((*classe)->interfaces));
     }

     if ((*classe)->fields_count != 0 && (*classe)->fields != NULL) {
         for (int i = 0; i < (*classe)->fields_count; i++) {
             if ((*classe)->fields[i].attributes_count != 0 && (*classe)->fields[i].attributes != NULL) {
                 for (int j = 0; j < (*classe)->fields[i].attributes_count; j++) {
                     if ((*classe)->fields[i].attributes[j].info != NULL) {
                         free_mem((void**) &((*classe)->fields[i].attributes[j].info));
                     }
                     if ((*classe)->methods[i].attributes[j].specific_info != NULL) {
                         free_mem((void**) &((*classe)->fields[i].attributes[j].specific_info));
                     }
                 }
                 free_mem((void**) &((*classe)->fields[i].attributes));
             }
         }
         free_mem((void**) &((*classe)->fields));
     }

     if ((*classe)->methods_count != 0 && (*classe)->methods != NULL) {
         for (int i = 0; i < (*classe)->methods_count; i++) {
             if ((*classe)->methods[i].attributes_count != 0 && (*classe)->methods[i].attributes != NULL) {
                 for (int j = 0; j < (*classe)->methods[i].attributes_count; j++) {
                     if ((*classe)->methods[i].attributes[j].info != NULL) {
                         free_mem((void**) &((*classe)->methods[i].attributes[j].info));
                     }
                     if ((*classe)->methods[i].attributes[j].specific_info != NULL) {
                         free_mem((void**) &((*classe)->methods[i].attributes[j].specific_info));
                     }
                 }
                 free_mem((void**) &((*classe)->methods[i].attributes));
             }
         }
         free_mem((void**) &((*classe)->methods));
     }

     if ((*classe)->attributes != NULL) {
         for (int i = 0; i < (*classe)->attributes_count; i++) {
             if ((*classe)->attributes[i].info != NULL) {
                 free_mem((void**) &((*classe)->attributes[i].info));
             }
             if ((*classe)->attributes[i].specific_info != NULL) {
                 free_mem((void**) &((*classe)->attributes[i].specific_info));
             }
         }
         free_mem((void**) &((*classe)->attributes));
     }

     free_mem((void**) classe);
 }

Class* getClassfile(FILE* fp) {
    int bytecount = 0;
    Class* classe = (Class*) set_mem(sizeof(Class));

    classe->magic = to4Bytes(getDoubleWord(fp, bytecount));
    bytecount += 4;

    classe->minor_version = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->major_version = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->constantPool_count = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->constant_pool = getConstantPool(fp, &bytecount, classe->constantPool_count - 1);

    classe->access_flags = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->thisClass = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->superClass = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->interfaces_count = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->interfaces = getInterfaces(fp, &bytecount, classe->interfaces_count);

    classe->fields_count = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->fields = getFields(fp, &bytecount, classe->fields_count, classe->constant_pool);

    classe->methods_count = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->methods = getMethods(fp, &bytecount, classe->methods_count, classe->constant_pool);

    classe->attributes_count = to2Bytes(getWord(fp, bytecount));
    bytecount += 2;

    classe->attributes = getAttributes(fp, &bytecount, classe->attributes_count, classe->constant_pool);

    return classe;
}
