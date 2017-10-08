/**
 * @file class.c
 * @brief Classfile operations library source
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * This file contains all the function source codes which has the
 * signatures declared on the class.h file.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    class->minorVersion = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read major version
    class->majorVersion = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read constant pool count
    class->constantPoolCount = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read constant pool
    class->constantPool = getConstantPool(fp, &bytecount, class->constantPoolCount - 1);

    // Read access flags
    class->accessFlags = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read this class
    class->thisClass = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read super class
    class->superClass = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read interfaces count
    class->interfacesCount = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read interfaces
    class->interfaces = getInterfaces(fp, &bytecount, class->interfacesCount);

    // Read fields count
    class->fieldsCount = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read fields
    class->fields = getFields(fp, &bytecount, class->fieldsCount, class->constantPool);

    // Read methods count
    class->methodsCount = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read methods
    class->methods = getMethods(fp, &bytecount, class->methodsCount, class->constantPool);

    // Read attributes count
    class->attributesCount = get2bytesBigEndian(fp, bytecount);
    bytecount += 2;

    // Read attributes
    class->attributes = getAttributes(fp, &bytecount, class->attributesCount, class->constantPool);

    return class;
}

char* getUtf8FromConstantPool(int index, ConstPoolInfo* constantPool, bool isRef) {
    if (index != 0) {
        return utf8ToString(constantPool[index - 1].utf8Const.bytes, constantPool[index - 1].utf8Const.length, isRef);
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

ConstPoolInfo* getConstantPool(FILE* fp, int* bytecount, u2 cpCount) {
    int index = 0;

    // Allocate space for the costant pool
    ConstPoolInfo* cpInfo = (ConstPoolInfo*) allocate(cpCount * sizeof(ConstPoolInfo));

    while (index < cpCount) {
        // Read tag
        cpInfo[index].tag = getByte(fp, (*bytecount));
        (*bytecount)++;

        // Read cpInfo
        switch(cpInfo[index].tag) {
            // Read CONTANT_UTF8_Info
            case UTF8:
                cpInfo[index].utf8Const.length = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].utf8Const.bytes = (u1*) allocate((cpInfo[index].utf8Const.length) * sizeof(u1));
                for (int utf8Index = 0; utf8Index < (cpInfo[index].utf8Const.length); utf8Index++) {
                    cpInfo[index].utf8Const.bytes[utf8Index] = getByte(fp, (*bytecount));
                    (*bytecount)++;
                }
                break;

            // Read CONTANT_Integer_Info
            case INTEGER:
                cpInfo[index].integerConst.bytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                break;

            // Read CONTANT_Float_Info
            case FLOAT:
                cpInfo[index].floatConst.bytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                break;

            // Read CONTANT_Long_Info
            case LONG:
                cpInfo[index].longConst.bytes.highBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                cpInfo[index].longConst.bytes.lowBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                // This field are stored in two indexes
                index++;
                cpInfo[index].tag = LARGE_NUMERIC_CONTINUED;
                break;

            // Read CONTANT_Double_Info
            case DOUBLE:
                cpInfo[index].doubleConst.bytes.highBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                cpInfo[index].doubleConst.bytes.lowBytes = get4bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 4;
                // This field are stored in two indexes
                index++;
                cpInfo[index].tag = LARGE_NUMERIC_CONTINUED;
                break;

            // Read CONTANT_Class_Info
            case CLASS:
                cpInfo[index].classConst.nameIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_String_Info
            case STRING:
                cpInfo[index].stringConst.stringIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_Fieldref_Info
            case FIELD_REF:
                cpInfo[index].fieldRefConst.classIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].fieldRefConst.nameAndTypeIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_Methodref_Info
            case METHOD_REF:
                cpInfo[index].methodRefConst.classIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].methodRefConst.nameAndTypeIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_InterfaceMethodref_Info
            case INTERFACE_METHOD_REF:
                cpInfo[index].interfaceMethodRefConst.classIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].interfaceMethodRefConst.nameAndTypeIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Read CONTANT_NameAndType_Info
            case NAME_AND_TYPE:
                cpInfo[index].nameAndTypeConst.nameIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                cpInfo[index].nameAndTypeConst.descriptorIndex = get2bytesBigEndian(fp, (*bytecount));
                (*bytecount) += 2;
                break;

            // Error while geting contant pool
            default:
                printf("Error while geting classfile on position: %ld\n", ftell(fp));
        }
        index++;
    }

    return cpInfo;
}

u2* getInterfaces(FILE* fp, int* bytecount, u2 interfacesCount) {
    u2* interfaces = (u2*) allocate(interfacesCount * sizeof(u2));

    for (int interfacesIndex = 0; interfacesIndex < interfacesCount; interfacesIndex++) {
        interfaces[interfacesIndex] = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) += 2;
    }

    return interfaces;
}

FieldInfo* getFields(FILE* fp, int* bytecount, u2 fieldsCount, ConstPoolInfo* constantPool) {
    FieldInfo* field = (FieldInfo*) allocate(fieldsCount * sizeof(FieldInfo));
    int index = 0;

    while(index < fieldsCount) {

        // Read access flags
        field[index].accessFlags = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read name index
        field[index].nameIndex = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read descriptor index
        field[index].descriptorIndex = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes count
        field[index].attributesCount = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes
        field[index].attributes = getAttributes(fp, bytecount, field[index].attributesCount, constantPool);

        index++;
    }

    return field;

}

MethodInfo* getMethods(FILE* fp, int* bytecount, u2 methodsCount, ConstPoolInfo* constantPool) {
    MethodInfo* method = (MethodInfo*) allocate(methodsCount * sizeof(MethodInfo));
    int index = 0;

    while (index < methodsCount) {
        // Read access flags
        method[index].accessFlags = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read name index
        method[index].nameIndex = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read descriptor index
        method[index].descriptorIndex = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes count
        method[index].attributesCount = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attributes
        method[index].attributes = getAttributes(fp, bytecount, method[index].attributesCount, constantPool);

        index ++;
    }

    return method;
}

AttributeInfo* getAttributes (FILE* fp, int* bytecount, u2 attributesCount, ConstPoolInfo* constantPool) {
    AttributeInfo* attribute = (AttributeInfo*) allocate(attributesCount * sizeof(AttributeInfo));
    int index = 0;

    while(index < attributesCount) {
        // Read attribute name index
        attribute[index].attributeNameIndex = get2bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=2;

        // Read attribute length
        attribute[index].attributeLength = get4bytesBigEndian(fp, (*bytecount));
        (*bytecount) +=4;

        // Read info
        attribute[index].info = (u1*) allocate(attribute[index].attributeLength * sizeof(u1));
        for (int attrIndex = 0; attrIndex < (attribute[index].attributeLength); attrIndex++) {
            attribute[index].info[attrIndex] = getByte(fp, (*bytecount));
            (*bytecount)++;
        }

        // Decode info
        attribute[index].specificInfo = decodeInfo(attribute[index], constantPool);
        index++;
    }

    return attribute;
}

AttributeInfo* getAttributesFromByteArray(u1* info, int* bytecount, u2 attributesCount, ConstPoolInfo* constantPool) {
    AttributeInfo* attribute = (AttributeInfo*) allocate(attributesCount * sizeof(AttributeInfo));
    int index = 0;

    while (index < attributesCount) {
        // Read attribute name index
        attribute[index].attributeNameIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) +=2;

        // Read attribute length
        attribute[index].attributeLength = get4bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) +=4;

        if (attribute[index].attributeLength > 0) {

            // Read info
            attribute[index].info = (u1*) allocate((attribute[index].attributeLength) * sizeof(u1));
            for (int attrIndex = 0; attrIndex < (attribute[index].attributeLength); attrIndex++) {
                attribute[index].info[attrIndex] = get1bytesFromByteArray(info, (*bytecount));
                (*bytecount)++;
            }

            // Decode info
            attribute[index].specificInfo = decodeInfo(attribute[index], constantPool);
        }
        index++;
    }

    return attribute;
}

void* decodeInfo(AttributeInfo attribute, ConstPoolInfo* constantPool) {
    int bytecount = 0;
    void* specificInfo = NULL;

    // Get attribute name
    char* attributeName = getUtf8FromConstantPool(attribute.attributeNameIndex, constantPool, false);

    if (strcmp(attributeName, "ConstantValue") == 0) {
        // Allocate space
        ConstantValueAttribute* reference = (ConstantValueAttribute*) allocate(sizeof(ConstantValueAttribute));

        // Read contant value index
        reference->constantValueIndex = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "Code") == 0) {

        CodeAttribute* reference = (CodeAttribute*) allocate(sizeof(CodeAttribute));

        // Read max stack
        reference->maxStack = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read max locals
        reference->maxLocals = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
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
        reference->attributesCount = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read attributes
        reference->attributes = getAttributesFromByteArray(attribute.info, &bytecount, reference->attributesCount, constantPool);

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "Deprecated") == 0) {

        // Don't have specific info

    } else if (strcmp(attributeName, "Exceptions") == 0) {

        ExceptionAttribute* reference = (ExceptionAttribute*) allocate(sizeof(ExceptionAttribute));

        // Read number of exception
        reference->numberOfExceptions = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read exception index table
        reference->exceptionIndexTable = (u2*) allocate(reference->numberOfExceptions * sizeof(u2));
        for (int count = 0; count < reference->numberOfExceptions; count++) {
            reference->exceptionIndexTable[count] = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
            bytecount += 2;
        }

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "InnerClasses") == 0) {

        InnerClassesAttribute* reference = (InnerClassesAttribute*) allocate(sizeof(InnerClassesAttribute));

        // Read number of classes
        reference->numberOfClasses = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read classes
        reference->classes = getInnerClasses(attribute.info, &bytecount, reference->numberOfClasses);

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "SourceFile") == 0) {

        SourceFileAttribute* reference = (SourceFileAttribute*) allocate(sizeof(SourceFileAttribute));

        // Read source file index
        reference->sourceFileIndex = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "LineNumberTable") == 0) {

        LineNumberTableAttribute* reference = (LineNumberTableAttribute*) allocate(sizeof(LineNumberTableAttribute));

        // Read line number table length
        reference->lineNumberTableLength = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read line number table
        reference->lineNumberTable = getLineNumberTable(attribute.info, &bytecount, reference->lineNumberTableLength);

        // Store reference
        specificInfo = reference;

    } else if (strcmp(attributeName, "LocalVariableTable") == 0) {

        LocalVariableTableAttribute* reference = (LocalVariableTableAttribute*) allocate(sizeof(LocalVariableTableAttribute));

        // Read local variable table length
        reference->localVariableTableLength = get2bytesBigEndianFromByteArray(attribute.info, bytecount);
        bytecount += 2;

        // Read local variable table length
        reference->localVariableTable = getLocalVariableTable(attribute.info, &bytecount, reference->localVariableTableLength);

        // Store reference
        specificInfo = reference;

    } // Ignore unknowm property

    deallocate( (void**) &attributeName );
    return specificInfo;
}

ExceptionTableEntry* getExceptionTable(u1* info, int* bytecount, int exceptionTableLength) {
    ExceptionTableEntry* exceptionTable = (ExceptionTableEntry*) allocate(exceptionTableLength * sizeof(ExceptionTableEntry));
    int index = 0;

    while (index < exceptionTableLength) {
        // Read start_pc
        exceptionTable[index].startPc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read end_pc
        exceptionTable[index].endPc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read handler_pc
        exceptionTable[index].handlerPc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read catch_type
        exceptionTable[index].catchType = get2bytesBigEndianFromByteArray(info, (*bytecount));
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
        innerClasses[index].innerClassInfoIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read outer_class_info_index
        innerClasses[index].outerClassInfoIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read inner_name_index
        innerClasses[index].innerNameIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read inner_class_access_flags
        innerClasses[index].innerClassAccessFlags = get2bytesBigEndianFromByteArray(info, (*bytecount));
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
        lineNumberTable[index].startPc = get2bytesBigEndianFromByteArray(info, (*bytecount));
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
        localVariableTable[index].startPc = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read length
        localVariableTable[index].length = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read name_index
        localVariableTable[index].nameIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read descriptor_index
        localVariableTable[index].descriptorIndex = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        // Read index
        localVariableTable[index].index = get2bytesBigEndianFromByteArray(info, (*bytecount));
        (*bytecount) += 2;

        index++;
    }

    return localVariableTable;
}

void deallocateClass(Class** class) {

    if ((*class)->constantPool != NULL) {
        deallocate((void**) &((*class)->constantPool));
    }

    if ((*class)->interfaces != NULL) {
        deallocate((void**) &((*class)->interfaces));
    }

    if ((*class)->fieldsCount != 0 && (*class)->fields != NULL) {
        for (int i = 0; i < (*class)->fieldsCount; i++) {
            if ((*class)->fields[i].attributesCount != 0 && (*class)->fields[i].attributes != NULL) {
                for (int j = 0; j < (*class)->fields[i].attributesCount; j++) {
                    if ((*class)->fields[i].attributes[j].info != NULL) {
                        deallocate((void**) &((*class)->fields[i].attributes[j].info));
                    }
                    if ((*class)->methods[i].attributes[j].specificInfo != NULL) {
                        deallocate((void**) &((*class)->fields[i].attributes[j].specificInfo));
                    }
                }
                deallocate((void**) &((*class)->fields[i].attributes));
            }
        }
        deallocate((void**) &((*class)->fields));
    }

    if ((*class)->methodsCount != 0 && (*class)->methods != NULL) {
        for (int i = 0; i < (*class)->methodsCount; i++) {
            if ((*class)->methods[i].attributesCount != 0 && (*class)->methods[i].attributes != NULL) {
                for (int j = 0; j < (*class)->methods[i].attributesCount; j++) {
                    if ((*class)->methods[i].attributes[j].info != NULL) {
                        deallocate((void**) &((*class)->methods[i].attributes[j].info));
                    }
                    if ((*class)->methods[i].attributes[j].specificInfo != NULL) {
                        deallocate((void**) &((*class)->methods[i].attributes[j].specificInfo));
                    }
                }
                deallocate((void**) &((*class)->methods[i].attributes));
            }
        }
        deallocate((void**) &((*class)->methods));
    }

    if ((*class)->attributes != NULL) {
        for (int i = 0; i < (*class)->attributesCount; i++) {
            if ((*class)->attributes[i].info != NULL) {
                deallocate((void**) &((*class)->attributes[i].info));
            }
            if ((*class)->attributes[i].specificInfo != NULL) {
                deallocate((void**) &((*class)->attributes[i].specificInfo));
            }
        }
        deallocate((void**) &((*class)->attributes));
    }

    deallocate((void**) class);
}
