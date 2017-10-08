/**
 * @file class.h
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * @todo Description
 */

#ifndef _CLASS_H
#define _CLASS_H

#include <stdbool.h>
#include "utils.h"

/**
 * @brief Enum with a type name assignment with the bytecode number that represents that name.
 * Contains the constants types matching with its tag.
 */
enum {
    LARGE_NUMERIC_CONTINUED = 0,
    UTF8 = 1,
    INTEGER = 3,
    FLOAT = 4,
    LONG = 5,
    DOUBLE = 6,
    CLASS = 7,
    STRING = 8,
    FIELD_REF = 9,
    METHOD_REF = 10,
    INTERFACE_METHOD_REF = 11,
    NAME_AND_TYPE = 12
} ContantsInfo;

/**
 * @brief Structure of the constant pool, separated by type.
 * The type definition of the structure is ConstPoolInfo.
 */
typedef struct _const_pool_info {
    /**
     * @brief Field tag from the constant pool.
     *
     * Field tag is common for all types.
     */
    u1 tag;
    /**
     * @brief Union of structs containing the types within the constant pool.
     *
     * Each type has its own structure.
     */
    union {
        /**
         * @brief Class type.
         *
         * Contains the name index from the class.
         */
        struct {
            u2 name_index;
        } class_const;
        /**
         * @brief FieldRef type.
         *
         * Contains the class index and the name and type index from the FieldRef.
         */
        struct {
            u2 class_index;
            u2 nameAndType_index;
        } fieldRef_const;
        /**
         * @brief Name and Type type.
         *
         * Contains the name index and the descriptor index.
         */
        struct {
            u2 name_index;
            u2 descriptor_index;
        } nameAndType_const;
        /**
         * @brief UTF8 type.
         *
         * Contains the lenght and the pointer for bytes from the UTF8.
         */
        struct {
            u2 length;
            u1* bytes;
        } utf8_const;
        /**
         * @brief MethodRef type.
         *
         * Contains the class index and name and type index.
         */
        struct {
            u2 class_index;
            u2 nameAndType_index;
        } methodRef_const;
        /**
         * @brief InterfaceMethodRef type.
         *
         * Contains the class index and name and type index.
         */
        struct {
            u2 class_index;
            u2 nameAndType_index;
        } interfaceMethodRef_const;
        /**
         * @brief String type.
         *
         * Contains the string index.
         */
        struct {
            u2 string_index;
        } string_const;
        /**
         * @brief Inteiro type.
         *
         * Contains the bytes.
         */
        struct {
            u4 bytes;
        } integer_const;
        /**
         * @brief Float type.
         *
         * Contains the bytes and the value.
         */
        struct {
            union {
                u4 bytes;
                float value;
            };
        } float_const;
        /**
         * @brief Long type.
         *
         * Containing a sub-structure bytes, for high and low bytes, and the long type value.
         */
        struct {
            union {
                struct {
                    u4 lowBytes;
                    u4 highBytes;
                } bytes;
                long int value;
            };
        } long_const;
         /**
         * @brief Double type.
         *
         * Containing a sub-structure bytes, for high and low bytes, and the double type value.
         */
        struct {
            union {
                struct {
                    u4 lowBytes;
                    u4 highBytes;
                } bytes;
                double value;
            };
        } double_const;
    };
}ConstPoolInfo;

/**
 * @brief Attribute info structure.
 *
 * Contains the name index, lenght, info and specific info.
 * The type definition of the structure is AttributeInfo.
 */
typedef struct _attribute_info {
    u2 attributeName_index;
    u4 attributeLength;
    u1 *info;
    void *specific_info;
}AttributeInfo;

/**
 * @brief Field info structure.
 *
 * Contains the acess flags, name index, descriptor index,
 * attributtes count and a pointer type Attribute Info.
 * The type definition of the structure is FieldInfo.
 */
typedef struct _field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo *attributes;
}FieldInfo;

 /**
 * @brief Method info definition.
 *
 * Contains the acess flags, name index, descriptor index,
 * attributtes count and a pointer type Attribute Info.
 * The type definition of the structure is MethodInfo.
 */
typedef struct _method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    AttributeInfo *attributes;
}MethodInfo;

/**
 * @brief Constant value index definition.
 *
 * Contains the constant value index.
 * The type definition of the structure is ExceptionTableEntry.
 */
typedef struct _constant_value_attribute {
    u2 constantValue_index;
}ConstantValueAttribute;

/**
 * @brief Exception table entry definition.
 *
 * Contains the start PC, end PC, handler PC and catch type.
 * The type definition of the structure is ExceptionTableEntry.
 */
typedef struct _exception_table_entry {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
}ExceptionTableEntry;

/**
 * @brief Code Attribute definition.
 *
 * Contains the max stack, max locals, code lenght, pointer for code, exception table lenght,
 * a pointer type ExceptionTableEntry, attribute count and a pointer type AttributeInfo.
 * The type definition of the structure is CodeAttribute.
 */
typedef struct _code_attribute {
    u2 max_stack;
    u2 max_locals;
    u4 codeLength;
    u1 *code;
    u2 exceptionTableLength;
    ExceptionTableEntry *exceptionTable;
    u2 attributes_count;
    AttributeInfo *attributes;
}CodeAttribute;

/**
 * @brief Exception Attribute type.
 *
 * Contains the number of exceptions and a pointer type U2 for the exception table index.
 * The type definition of the Inner Class structure is ExceptionAttribute.
 */
typedef struct _exception_attribute {
    u2 numberOfExceptions;
    u2 *exception_indexTable;
}ExceptionAttribute;

/**
 * @brief Inner Class definition.
 *
 * Contains the index for inner and outer class, inner name index and inner class acess flags.
 * The type definition of the Inner Class structure is InnerClass.
 */
typedef struct _inner_class {
    u2 innerClassInfo_index;
    u2 outerClassInfo_index;
    u2 innerName_index;
    u2 innerClassAccess_flags;
}InnerClass;

/**
 * @brief Inner Classes Attribute definition.
 *
 * Contains the number of classes and a pointer type InnerClass.
 * The type definition of the Inner Class structure is InnerClassesAttribute.
 */
typedef struct _inner_classes_attribute {
    u2 numberOfClasses;
    InnerClass *classes;
}InnerClassesAttribute;

/**
 * @brief Liner Number Table Entry definition.
 *
 * Contains the start PC and the line number.
 * The type definition of the structure is LineNumberTableEntry.
 */
typedef struct _line_number_table_entry {
    u2 start_pc;
    u2 lineNumber;
}LineNumberTableEntry;

/**
 * @brief Line Number Table Attribute definition.
 *
 * Contains the line number table lenght and a pointer type LineNumberTableEntry.
 * The type definition of the structure is LineNumberTableAttribute.
 */
typedef struct _line_number_table_attribute {
    u2 lineNumberTableLength;
    LineNumberTableEntry *lineNumberTable;
}LineNumberTableAttribute;

/**
 * @brief Local Variable Table Entry definition.
 *
 * Contains the start PC, lenght, name and descriptor index, and the index.
 * The type definition of the structure is LocalVariableTableEntry.
 */
typedef struct _local_variable_table_entry {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
}LocalVariableTableEntry;

/**
 * @brief  Local Variable Table Attribute definition.
 *
 * Contains the local variable table lenght and a pointer type  LocalVariableTableEntry.
 * The type definition of the structure is LocalVariableTableAttribute.
 */
typedef struct _local_variable_table_attribute {
    u2 localVariableTableLength;
    LocalVariableTableEntry *localVariableTable;
}LocalVariableTableAttribute;

/**
 * @brief Source File Attribute definition.
 *
 * Contains the source file index.
 * The type definition of the structure is SourceFileAttribute.
 */
typedef struct _source_file_attribute {
    u2 sourceFile_index;
}SourceFileAttribute;

/**
 * @brief Classfile definition.
 *
 * Structure of the Classfile.
 * The type definition of the structure is Class.
 */
typedef struct _class {
    /**
     * @brief Magic Number.
     */
    u4 magic;
     /**
     * @brief Mejor Version.
     */
    u2 major_version;
    /**
     * @brief Minor Version..
     */
    u2 minor_version;
   /**
     * @brief Counter for constant pool.
     */
    u2 constantPool_count;
    /**
     * @brief Pointer ConstantPool type ConstantPoolInfo
     */
    ConstPoolInfo* constant_pool;
   /**
     * @brief Acess Flags.
     */
    u2 access_flags;
    /**
     * @brief This Class.
     */
    u2 thisClass;
    /**
     * @brief Super Class.
     */
    u2 superClass;
    /**
     * @brief Counter for Interfaces.
     */
    u2 interfaces_count;
    /**
     * @brief Interfaces type U2.
     */
    u2 *interfaces;
    /**
     * @brief Counter for fields.
     */
    u2 fields_count;
    /**
     * @brief Fields type FieldInfo.
     */
    FieldInfo *fields;
    /**
     * @brief Coounter for Métodos.
     */
    u2 methods_count;
    /**
     * @brief Methods type MethodsInfo.
     */
    MethodInfo *methods;
    /**
     * @brief Counter of Attributes.
     */
    u2 attributes_count;
    /**
     * @brief Attributes type AttributeInfo.
     */
    AttributeInfo *attributes;
}Class;

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Class* getClassfile(FILE* fp);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* getUtf8FromConstantPool(int index, ConstPoolInfo* constantPool, bool isRef);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2 get2bytesBigEndian(FILE* fp, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u4 get4bytesBigEndian(FILE* fp, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u1 get1bytesFromByteArray(u1* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2 get2bytesFromByteArray(u1* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2 get2bytesBigEndianFromByteArray(u1* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u4 get4bytesFromByteArray(u1* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u4 get4bytesBigEndianFromByteArray(u1* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
double getDouble (u4 high, u4 low);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
long getLong(u4 high, u4 low);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
ConstPoolInfo* getConstantPool(FILE* fp, int* bytecount, u2 cpCount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
u2* getInterfaces(FILE* fp, int* bytecount, u2 interfacesCount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
FieldInfo * getFields(FILE* fp, int* bytecount, u2 fieldCount, ConstPoolInfo* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
MethodInfo* getMethods(FILE* fp, int* bytecount, u2 methodsCount, ConstPoolInfo* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
AttributeInfo* getAttributes(FILE* fp, int* bytecount, u2 attributesCount, ConstPoolInfo* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
AttributeInfo* getAttributesFromByteArray(u1* info, int* bytecount, u2 attributesCount, ConstPoolInfo* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
void* decodeInfo(AttributeInfo attribute, ConstPoolInfo* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
ExceptionTableEntry* getExceptionTable(u1* info, int* bytecount, int exceptionTableLength);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
InnerClass* getInnerClasses(u1* info, int* bytecount, int numberOfClasses);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
LineNumberTableEntry* getLineNumberTable(u1* info, int* bytecount, int lineNumberTableLength);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
LocalVariableTableEntry* getLocalVariableTable(u1* info, int* bytecount, int localVariableTableLength);

/**
 * @brief Deallocate the main elements of the .class strucure.
 *
 * Free memory from the main elements of the .class struct. It will be
 * important to save memory for the jvm tests with many .class files.
 *
 * @params class Referece of the pointer to the .class structure.
 */
void deallocateClass(Class** class);

#endif //_CLASS_H
