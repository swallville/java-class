/**
 * @file class.c
 * @brief Classfile operations library source
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the class.h file.
 */
#include <string.h>
#include "mem-manager.h"
#include "file.h"
#include "convert.h"
#include "class.h"

Class* getClassfile(FILE* fp) {
    int bytecount = 0;
    Class* class = (Class*) allocate(sizeof(Class));

    // Read magic
    class->magic = get4bytesBigEndian(fp, bytecount);
    bytecount += 4;

    // Read minor version
    class->minor_version = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read major version
    class->major_version = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read constant pool count
    class->constantPool_count = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read constant pool
    class->constant_pool = getConstantPool(fp, &bytecount, class->constantPool_count - 1);

    // Read access flags
    class->access_flags = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read this class
    class->thisClass = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read super class
    class->superClass = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read interfaces count
    class->interfaces_count = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read interfaces
    class->interfaces = getInterfaces(fp, &bytecount, class->interfaces_count);

    // Read fields count
    class->fields_count = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read fields
    class->fields = getFields(fp, &bytecount, class->fields_count, class->constant_pool);

    // Read methods count
    class->methods_count = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read methods
    class->methods = getMethods(fp, &bytecount, class->methods_count, class->constant_pool);

    // Read attributes count
    class->attributes_count = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read attributes
    class->attributes = getAttributes(fp, &bytecount, class->attributes_count, class->constant_pool);

    return class;
}

char* getUtf8FromConstantPool(int index, ConstPoolInfo* constant_pool, bool isRef) {
    if (index != 0) {
        return utf8ToString(constant_pool[index - 1].utf8_const.bytes, constant_pool[index - 1].utf8_const.length, isRef);
    } else {
        char* invalid = (char*) allocate(16 * sizeof(char));
        strcpy(invalid, "invalid constant");
        return invalid;
    }
}

u2 get2bytes(FILE* fp, int bytecount) {
    return getWord(fp, bytecount);
}

u2 get2bytesBigEndian(FILE *fp, int bytecount) {
    return smallEndianToBigEndian2Bytes(getWord(fp, bytecount));
}

u4 get4bytes(FILE* fp, int bytecount) {
    return getDoubleWord(fp, bytecount);
}

u4 get4bytesBigEndian(FILE *fp, int bytecount) {
    return smallEndianToBigEndian4Bytes(get4bytes(fp, bytecount));
}

u1 get1bytesFromByteArray(u1* byteArr, int bytecount) {
    return byteArr[bytecount];
}

u2 get2bytesFromByteArray(u1* byteArr, int bytecount) {
    return ((u2) byteArr[bytecount + 1] << 8) | (u2) byteArr[bytecount];
}

u2 get2bytesBigEndianFromByteArray(u1* byteArr, int bytecount) {
    return smallEndianToBigEndian2Bytes(get2bytesFromByteArray(byteArr, bytecount));
}

u4 get4bytesFromByteArray(u1* byteArr, int bytecount) {
    return ((u4) byteArr[bytecount + 3] << 24) | ((u4) byteArr[bytecount + 2] << 16) | ((u4) byteArr[bytecount + 1] << 8) | (u4) byteArr[bytecount + 0];
}

u4 get4bytesBigEndianFromByteArray(u1* byteArr, int bytecount) {
    return smallEndianToBigEndian4Bytes(get4bytesFromByteArray(byteArr, bytecount));
}

double getDouble (u4 high, u4 low){
    double result;
    uint64_t aux;

    aux = (uint64_t)high;
    aux = aux << 32;
    aux |= (uint64_t)low;

    result = (double) aux;

    return result;

}

long getLong(u4 high, u4 low) {
    return ((uint64_t)high) << 32 | low;
}

ConstPoolInfo* getConstantPool(FILE* fp, int* bytecount, u2 cp_count) {
    int index = 0;

    // Allocate space for the costant pool
    ConstPoolInfo* cpInfo = (ConstPoolInfo*) allocate(cp_count * sizeof(ConstPoolInfo));

    while (index < cp_count) {
        // Read tag
        cpInfo[index].tag = getByte(fp, (*bytecount));
        (*bytecount)++;

        // Read cpInfo
        switch(cpInfo[index].tag) {
            // Read CONTANT_UTF8_Info
            case UTF8:
                cpInfo[index].utf8_const.length = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].utf8_const.bytes = (u1*) allocate((cpInfo[index].utf8_const.length) * sizeof(u1));
                for (int utf8_index = 0; utf8_index < (cpInfo[index].utf8_const.length); utf8_index++) {
                    cpInfo[index].utf8_const.bytes[utf8_index] = getByte(fp, (*bytecount));
                    (*bytecount)++;
                }
                break;

            // Read CONTANT_Integer_Info
            case INTEGER:
                cpInfo[index].integer_const.bytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                break;

            // Read CONTANT_Float_Info
            case FLOAT:
                cpInfo[index].float_const.bytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                break;

            // Read CONTANT_Long_Info
            case LONG:
                cpInfo[index].long_const.bytes.highBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                cpInfo[index].long_const.bytes.lowBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                // This field are stored in two indexes
                index++;
                cpInfo[index].tag = LARGE_NUMERIC_CONTINUED;
                break;

            // Read CONTANT_Double_Info
            case DOUBLE:
                cpInfo[index].double_const.bytes.highBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                cpInfo[index].double_const.bytes.lowBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                // This field are stored in two indexes
                index++;
                cpInfo[index].tag = LARGE_NUMERIC_CONTINUED;
                break;

            // Read CONTANT_Class_Info
            case CLASS:
                cpInfo[index].class_const.name_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_String_Info
            case STRING:
                cpInfo[index].string_const.string_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_Fieldref_Info
            case FIELD_REF:
                cpInfo[index].fieldRef_const.class_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].fieldRef_const.nameAndType_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_Methodref_Info
            case METHOD_REF:
                cpInfo[index].methodRef_const.class_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].methodRef_const.nameAndType_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_InterfaceMethodref_Info
            case INTERFACE_METHOD_REF:
                cpInfo[index].interfaceMethodRef_const.class_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].interfaceMethodRef_const.nameAndType_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_NameAndType_Info
            case NAME_AND_TYPE:
                cpInfo[index].nameAndType_const.name_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].nameAndType_const.descriptor_index = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Error while geting constant pool
            default:
                printf("Error while geting classfile on position: %ld\n", ftell(fp));
        }
        index++;
    }

    return cpInfo;
}

u2* getInterfaces(FILE* fp, int* bytecount, u2 interfaces_count) {
    u2* interfaces = (u2*) allocate(interfaces_count * sizeof(u2));

    for (int interfaces_index = 0; interfaces_index < interfaces_count; interfaces_index++) {
        interfaces[interfaces_index] = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) += 2;
    }

    return interfaces;
}

FieldInfo* getFields(FILE* fp, int* bytecount, u2 fields_count, ConstPoolInfo* constant_pool) {
    FieldInfo* field = (FieldInfo*) allocate(fields_count * sizeof(FieldInfo));
    int index = 0;

    while(index < fields_count) {

        // Read access flags
        field[index].access_flags = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read name index
        field[index].name_index = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read descriptor index
        field[index].descriptor_index = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes count
        field[index].attributes_count = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes
        field[index].attributes = getAttributes(fp, bytecount, field[index].attributes_count, constant_pool);

        index++;
    }

    return field;

}

MethodInfo* getMethods(FILE* fp, int* bytecount, u2 methods_count, ConstPoolInfo* constant_pool) {
    MethodInfo* method = (MethodInfo*) allocate(methods_count * sizeof(MethodInfo));
    int index = 0;

    while (index < methods_count) {
        // Read access flags
        method[index].access_flags = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read name index
        method[index].name_index = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read descriptor index
        method[index].descriptor_index = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes count
        method[index].attributes_count = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes
        method[index].attributes = getAttributes(fp, bytecount, method[index].attributes_count, constant_pool);

        index ++;
    }

    return method;
}

AttributeInfo* getAttributes (FILE* fp, int* bytecount, u2 attributes_count, ConstPoolInfo* constant_pool) {
    AttributeInfo* attribute = (AttributeInfo*) allocate(attributes_count * sizeof(AttributeInfo));
    int index = 0;

    while(index < attributes_count) {
        // Read attribute name index
        attribute[index].attributeName_index = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attribute length
        attribute[index].attributeLength = get4bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=4;

        // Read info
        attribute[index].info = (u1*) allocate(attribute[index].attributeLength * sizeof(u1));
        for (int attr_index = 0; attr_index < (attribute[index].attributeLength); attr_index++) {
            attribute[index].info[attr_index] = getByte(fp, (*bytecount));
            (*bytecount)++;
        }

        // Decode info
        attribute[index].specific_info = decodeInfo(attribute[index], constant_pool);
        index++;
    }

    return attribute;
}

AttributeInfo* getAttributesFromByteArray(u1* info, int* bytecount, u2 attributes_count, ConstPoolInfo* constant_pool) {
    AttributeInfo* attribute = (AttributeInfo*) allocate(attributes_count * sizeof(AttributeInfo));
    int index = 0;

    while (index < attributes_count) {
        // Read attribute name index
        attribute[index].attributeName_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) +=2;

        // Read attribute length
        attribute[index].attributeLength = get4bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) +=4;

        if (attribute[index].attributeLength > 0) {

            // Read info
            attribute[index].info = (u1*) allocate((attribute[index].attributeLength) * sizeof(u1));
            for (int attr_index = 0; attr_index < (attribute[index].attributeLength); attr_index++) {
                attribute[index].info[attr_index] = get1bytesFromByteArray(info, (*bytecount));
                (*bytecount)++;
            }

            // Decode info
            attribute[index].specific_info = decodeInfo(attribute[index], constant_pool);
        }
        index++;
    }

    return attribute;
}

void* decodeInfo(AttributeInfo attribute, ConstPoolInfo* constant_pool) {
    int bytecount = 0;
    void* specific_info = NULL;

    // Get attribute name
    char* attributeName = getUtf8FromConstantPool(attribute.attributeName_index, constant_pool, false);

    if (strcmp(attributeName, "ConstantValue") == 0) {
        // Allocate space
        ConstantValueAttribute* reference = (ConstantValueAttribute*) allocate(sizeof(ConstantValueAttribute));

        // Read contant value index
        reference->constantValue_index = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "Code") == 0) {

        CodeAttribute* reference = (CodeAttribute*) allocate(sizeof(CodeAttribute));

        // Read max stack
        reference->max_stack = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read max locals
        reference->max_locals = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read code length
        reference->codeLength = get4bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 4;

        // Read code
        reference->code = (u1*) allocate(reference->codeLength * sizeof(u1));
        for (int count = 0; count < reference->codeLength; count++) {
            reference->code[count] = get1bytesFromByteArray(attribute.info, bytecount);
            bytecount++;
        }

        // Read exception table length
        reference->exceptionTableLength = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read exception table
        reference->exceptionTable = getExceptionTable(attribute.info, &bytecount, reference->exceptionTableLength);

        // Read attributes count
        reference->attributes_count = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read attributes
        reference->attributes = getAttributesFromByteArray(attribute.info, &bytecount, reference->attributes_count, constant_pool);

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "Deprecated") == 0) {

        // Don't have specific info

    } else if (strcmp(attributeName, "Exceptions") == 0) {

        ExceptionAttribute* reference = (ExceptionAttribute*) allocate(sizeof(ExceptionAttribute));

        // Read number of exception
        reference->numberOfExceptions = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read exception index table
        reference->exception_indexTable = (u2*) allocate(reference->numberOfExceptions * sizeof(u2));
        for (int count = 0; count < reference->numberOfExceptions; count++) {
            reference->exception_indexTable[count] = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
            bytecount += 2;
        }

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "InnerClasses") == 0) {

        InnerClassesAttribute* reference = (InnerClassesAttribute*) allocate(sizeof(InnerClassesAttribute));

        // Read number of classes
        reference->numberOfClasses = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read classes
        reference->classes = getInnerClasses(attribute.info, &bytecount, reference->numberOfClasses);

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "SourceFile") == 0) {

        SourceFileAttribute* reference = (SourceFileAttribute*) allocate(sizeof(SourceFileAttribute));

        // Read source file index
        reference->sourceFile_index = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "LineNumberTable") == 0) {

        LineNumberTableAttribute* reference = (LineNumberTableAttribute*) allocate(sizeof(LineNumberTableAttribute));

        // Read line number table length
        reference->lineNumberTableLength = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read line number table
        reference->lineNumberTable = getLineNumberTable(attribute.info, &bytecount, reference->lineNumberTableLength);

        // Store reference
        specific_info = reference;

    } else if (strcmp(attributeName, "LocalVariableTable") == 0) {

        LocalVariableTableAttribute* reference = (LocalVariableTableAttribute*) allocate(sizeof(LocalVariableTableAttribute));

        // Read local variable table length
        reference->localVariableTableLength = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read local variable table length
        reference->localVariableTable = getLocalVariableTable(attribute.info, &bytecount, reference->localVariableTableLength);

        // Store reference
        specific_info = reference;

    } // Ignore unknowm property

    deallocate( (void**) &attributeName );
    return specific_info;
}

ExceptionTableEntry* getExceptionTable(u1* info, int* bytecount, int exceptionTableLength) {
    ExceptionTableEntry* exceptionTable = (ExceptionTableEntry*) allocate(exceptionTableLength * sizeof(ExceptionTableEntry));
    int index = 0;

    while (index < exceptionTableLength) {
        // Read start_pc
        exceptionTable[index].start_pc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read end_pc
        exceptionTable[index].end_pc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read handler_pc
        exceptionTable[index].handler_pc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read catch_type
        exceptionTable[index].catch_type = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        index++;
    }

    return exceptionTable;
}

InnerClass* getInnerClasses(u1* info, int* bytecount, int numberOfClasses) {
    InnerClass* innerClasses = (InnerClass*) allocate(numberOfClasses * sizeof(InnerClass));
    int index = 0;

    while (index < numberOfClasses) {
        // Read inner_class_info_index
        innerClasses[index].innerClassInfo_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read outer_class_info_index
        innerClasses[index].innerClassInfo_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read inner_name_index
        innerClasses[index].innerClassInfo_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read inner_class_access_flags
        innerClasses[index].innerClassAccess_flags = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        index++;
    }

    return innerClasses;
}

LineNumberTableEntry* getLineNumberTable(u1* info, int* bytecount, int lineNumberTableLength) {
    LineNumberTableEntry* lineNumberTable = (LineNumberTableEntry*) allocate(lineNumberTableLength * sizeof(LineNumberTableEntry));
    int index = 0;

    while (index < lineNumberTableLength) {
        // Read start_pc
        lineNumberTable[index].start_pc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read line_number
        lineNumberTable[index].lineNumber = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        index++;
    }

    return lineNumberTable;
}

LocalVariableTableEntry* getLocalVariableTable(u1* info, int* bytecount, int localVariableTableLength) {
    LocalVariableTableEntry* localVariableTable = (LocalVariableTableEntry*) allocate(localVariableTableLength * sizeof(LocalVariableTableEntry));
    int index = 0;

    while (index < localVariableTableLength) {
        // Read start_pc
        localVariableTable[index].start_pc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read length
        localVariableTable[index].length = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read name_index
        localVariableTable[index].name_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read descriptor_index
        localVariableTable[index].descriptor_index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read index
        localVariableTable[index].index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        index++;
    }

    return localVariableTable;
}

void deallocateClass(Class** class) {

    if ((*class)->constant_pool != NULL) {
        deallocate((void**) &((*class)->constant_pool));
    }

    if ((*class)->interfaces != NULL) {
        deallocate((void**) &((*class)->interfaces));
    }

    if ((*class)->fields_count != 0 && (*class)->fields != NULL) {
        for (int i = 0; i < (*class)->fields_count; i++) {
            if ((*class)->fields[i].attributes_count != 0 && (*class)->fields[i].attributes != NULL) {
                for (int j = 0; j < (*class)->fields[i].attributes_count; j++) {
                    if ((*class)->fields[i].attributes[j].info != NULL) {
                        deallocate((void**) &((*class)->fields[i].attributes[j].info));
                    }
                    if ((*class)->methods[i].attributes[j].specific_info != NULL) {
                        deallocate((void**) &((*class)->fields[i].attributes[j].specific_info));
                    }
                }
                deallocate((void**) &((*class)->fields[i].attributes));
            }
        }
        deallocate((void**) &((*class)->fields));
    }

    if ((*class)->methods_count != 0 && (*class)->methods != NULL) {
        for (int i = 0; i < (*class)->methods_count; i++) {
            if ((*class)->methods[i].attributes_count != 0 && (*class)->methods[i].attributes != NULL) {
                for (int j = 0; j < (*class)->methods[i].attributes_count; j++) {
                    if ((*class)->methods[i].attributes[j].info != NULL) {
                        deallocate((void**) &((*class)->methods[i].attributes[j].info));
                    }
                    if ((*class)->methods[i].attributes[j].specific_info != NULL) {
                        deallocate((void**) &((*class)->methods[i].attributes[j].specific_info));
                    }
                }
                deallocate((void**) &((*class)->methods[i].attributes));
            }
        }
        deallocate((void**) &((*class)->methods));
    }

    if ((*class)->attributes != NULL) {
        for (int i = 0; i < (*class)->attributes_count; i++) {
            if ((*class)->attributes[i].info != NULL) {
                deallocate((void**) &((*class)->attributes[i].info));
            }
            if ((*class)->attributes[i].specific_info != NULL) {
                deallocate((void**) &((*class)->attributes[i].specific_info));
            }
        }
        deallocate((void**) &((*class)->attributes));
    }

    deallocate((void**) class);
}
