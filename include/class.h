/**
 * @file class.h
 * @authors Lukas Ferreira Machado (12/0127377)
 *
 * @todo Description
 */

#ifndef _CLASS_H
#define _CLASS_H

#include <stdbool.h>
#include <math.h>
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
    NAME_AND_TYPE = 12,
    METHOD_HANDLE = 15,
    METHOD_TYPE = 16,
    INVOKE_DYNAMIC = 18
} ConstTab;

/**
 * @brief Structure of the constant pool, separated by type.
 * The type definition of the structure is ConstPool.
 */
typedef struct _const_pool_info {
    /**
     * @brief Field tag from the constant pool.
     *
     * Field tag is common for all types.
     */
    uint8_t tag;
    /**
     * @brief Union of structs that have the constant_pool components
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
            uint16_t name_index;
        } class_const;
        /**
         * @brief FieldRef type.
         *
         * Contains the class index and the name and type index from the FieldRef.
         */
        struct {
            uint16_t class_index;
            uint16_t nameAndType_index;
        } fieldRef_const;
        /**
         * @brief Name and Type type.
         *
         * Contains the name index and the descriptor index.
         */
        struct {
            uint16_t name_index;
            uint16_t descriptor_index;
        } nameAndType_const;
        /**
         * @brief UTF8 type.
         *
         * Contains the lenght and the pointer for bytes from the UTF8.
         */
        struct {
            uint16_t length;
            uint8_t* bytes;
        } utf8_const;
        /**
         * @brief MethodRef type.
         *
         * Contains the class index and name and type index.
         */
        struct {
            uint16_t class_index;
            uint16_t nameAndType_index;
        } methodRef_const;
        /**
         * @brief InterfaceMethodRef type.
         *
         * Contains the class index and name and type index.
         */
        struct {
            uint16_t class_index;
            uint16_t nameAndType_index;
        } interfaceMethodRef_const;
        /**
         * @brief String type.
         *
         * Contains the string index.
         */
        struct {
            uint16_t string_index;
        } string_const;
        /**
         * @brief Inteiro type.
         *
         * Contains the bytes.
         */
        struct {
            uint32_t bytes;
        } integer_const;
        /**
         * @brief Float type.
         *
         * Contains the bytes.
         */
        struct {
            union {
                uint32_t bytes;
            };
        } float_const;
        /**
         * @brief Long type.
         *
         * Containing a sub-structure bytes, for high and low bytes.
         */
        struct {
            union {
                struct {
                    uint32_t lowBytes;
                    uint32_t highBytes;
                } bytes;
            };
        } long_const;
         /**
         * @brief Double type.
         *
         * Containing a sub-structure bytes, for high and low bytes.
         */
        struct {
            union {
                struct {
                    uint32_t lowBytes;
                    uint32_t highBytes;
                } bytes;
            };
        } double_const;
        /**
        * @brief MethodHandle type.
        *
        * Containing the reference_kind and reference_index for the MethodHandle.
        */
        struct{
    		uint8_t reference_kind;
    		uint16_t reference_index;
    	} methodHandle_const;
        /**
        * @brief MethodType type.
        *
        * Containing a descriptor_index for the MethodType.
        */
    	struct{
    		uint16_t descriptor_index;
    	} methodType_const;
        /**
        * @brief InvokeDynamic type.
        *
        * Containing bootstrap_method_attr_index and name_and_type_index for
        * the InvokeDynamicInfo.
        */
    	struct{
    		uint16_t bootstrap_method_attr_index;
        	uint16_t name_and_type_index;
    	} invokeDynamicInfo_const;
    };
}ConstPool;

/**
 * @brief Attribute info structure.
 *
 * Contains the name index, lenght, info and specific info.
 * The type definition of the structure is Attribute.
 */
typedef struct _attribute_info {
    uint16_t attributeName_index;
    uint32_t attributeLength;
    uint8_t *info;
    void *specific_info;
}Attribute;

/**
 * @brief Field info structure.
 *
 * Contains the acess flags, name index, descriptor index,
 * attributtes count and a pointer type Attribute Info.
 * The type definition of the structure is Field.
 */
typedef struct _field_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute *attributes;
}Field;

 /**
 * @brief Method info definition.
 *
 * Contains the acess flags, name index, descriptor index,
 * attributtes count and a pointer type Attribute Info.
 * The type definition of the structure is Method.
 */
typedef struct _method_info {
    uint16_t access_flags;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t attributes_count;
    Attribute *attributes;
}Method;

/**
 * @brief Constant value index definition.
 *
 * Contains the constant value index.
 * The type definition of the structure is ExceptionTableEntry.
 */
typedef struct _constant_value_attribute {
    uint16_t constantValue_index;
}ConstantValueAttribute;

/**
 * @brief Exception table entry definition.
 *
 * Contains the start PC, end PC, handler PC and catch type.
 * The type definition of the structure is ExceptionTableEntry.
 */
typedef struct _exception_table_entry {
    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;
}ExceptionTableEntry;

/**
 * @brief Code Attribute definition.
 *
 * Contains the max stack, max locals, code lenght, pointer for code, exception table lenght,
 * a pointer type ExceptionTableEntry, attribute count and a pointer type Attribute.
 * The type definition of the structure is CodeAttribute.
 */
typedef struct _code_attribute {
    uint16_t max_stack;
    uint16_t max_locals;
    uint32_t codeLength;
    uint8_t *code;
    uint16_t exceptionTableLength;
    ExceptionTableEntry *exceptionTable;
    uint16_t attributes_count;
    Attribute *attributes;
}CodeAttribute;

/**
 * @brief Exception Attribute type.
 *
 * Contains the number of exceptions and a pointer type U2 for the exception table index.
 * The type definition of the Inner Class structure is ExceptionAttribute.
 */
typedef struct _exception_attribute {
    uint16_t numberOfExceptions;
    uint16_t *exception_indexTable;
}ExceptionAttribute;

/**
 * @brief Inner Class definition.
 *
 * Contains the index for inner and outer class, inner name index and inner class acess flags.
 * The type definition of the Inner Class structure is InnerClass.
 */
typedef struct _inner_class {
    uint16_t innerClassInfo_index;
    uint16_t outerClassInfo_index;
    uint16_t innerName_index;
    uint16_t innerClassAccess_flags;
}InnerClass;

/**
 * @brief Inner Classes Attribute definition.
 *
 * Contains the number of classes and a pointer type InnerClass.
 * The type definition of the Inner Class structure is InnerClassesAttribute.
 */
typedef struct _inner_classes_attribute {
    uint16_t numberOfClasses;
    InnerClass *classes;
}InnerClassesAttribute;

/**
 * @brief Liner Number Table Entry definition.
 *
 * Contains the start PC and the line number.
 * The type definition of the structure is LineNumberTableEntry.
 */
typedef struct _line_number_table_entry {
    uint16_t start_pc;
    uint16_t lineNumber;
}LineNumberTableEntry;

/**
 * @brief Line Number Table Attribute definition.
 *
 * Contains the line number table lenght and a pointer type LineNumberTableEntry.
 * The type definition of the structure is LineNumberTableAttribute.
 */
typedef struct _line_number_table_attribute {
    uint16_t lineNumberTableLength;
    LineNumberTableEntry *lineNumberTable;
}LineNumberTableAttribute;

/**
 * @brief Local Variable Table Entry definition.
 *
 * Contains the start PC, lenght, name and descriptor index, and the index.
 * The type definition of the structure is LocalVariableTableEntry.
 */
typedef struct _local_variable_table_entry {
    uint16_t start_pc;
    uint16_t length;
    uint16_t name_index;
    uint16_t descriptor_index;
    uint16_t index;
}LocalVariableTableEntry;

/**
 * @brief  Local Variable Table Attribute definition.
 *
 * Contains the local variable table lenght and a pointer type  LocalVariableTableEntry.
 * The type definition of the structure is LocalVariableTableAttribute.
 */
typedef struct _local_variable_table_attribute {
    uint16_t localVariableTableLength;
    LocalVariableTableEntry *localVariableTable;
}LocalVariableTableAttribute;

/**
 * @brief Source File Attribute definition.
 *
 * Contains the source file index.
 * The type definition of the structure is SourceFileAttribute.
 */
typedef struct _source_file_attribute {
    uint16_t sourceFile_index;
}SourceFileAttribute;

typedef struct _verification_type_info{
	uint8_t tag;

	union{

		struct {

			//uint8_t tag; // possuira valor 0;

		} top_variable_info;

		struct {

			//uint8_t tag; // possuira valor 1;

		} integer_variable_info;

		struct {

			//uint8_t tag; // possuira valor 2;

		} float_variable_info;

		/**	 ATENCAo - Tanto para Long como Double (64bits ambas).
		This structure gives the contents of two locations
		in the operand stack or in the local variable array.
		If the location is a local variable, then:
		It must not be the local variable with the highest index.
		The next higher numbered local variable contains the verification type top.
		If the location is an operand stack entry, then:
		The current location must not be the topmost location of the operand stack.
		The next location closer to the top of the operand stack contains the verification type top.
		*/

		struct {

			//uint8_t tag; // possuira valor 4;

		} long_variable_info;

		struct{

			//uint8_t tag; // possuira valor 3;

		} double_variable_info;

		struct {

			//uint8_t tag; // possuira valor 5;

		} null_variable_info;

		struct {

			//uint8_t tag; // possuira valor 6;

		} uninitializedThis_variable_info;

		/**The Object_variable_info type indicates that the location
		contains an instance of the class represented by the CONSTANT_Class_info*/

		struct {

			//uint8_t tag; // possuira valor 7;
			uint16_t cpool_index; // index da classe na constant_pool

		} object_variable_info;

		struct {

			//uint8_t tag; // possuira valor 8
			uint16_t offset; /** The offset item indicates the offset, in the code array
						of the Code attribute that contains this StackMapTable
						attribute, of the new instruction (§new) that created the
						object being stored in the location.*/

		} uninitialized_variable_info;

	} type_info;

}VerificationTypeInfo;

typedef struct _stack_map_frame {
	uint8_t frame_type;
	union{
        /**
         * @brief Same frame.
         *
         * If the frame type is same_frame, it means the frame has exactly
         * the same locals as the previous stack map frame and
         * that the number of stack items is zero. From 0-63.
         */
		struct{
		} same_frame;
        /**
         * @brief same_locals_1_stack_item_frame.
         *
         * If the frame_type is same_locals_1_stack_item_frame,
         * it means the frame has exactly the same
         * locals as the previous stack map frame and that the number
         * of stack items is 1*. From 64-127.
         */
		struct{
			VerificationTypeInfo *stack;

		} same_locals_1_stack_item_frame;
        /**
         * @brief same_locals_1_stack_item_frame_extended.
         *
         * The frame type same_locals_1_stack_item_frame_extended indicates
         * that the frame has exactly the same locals as the previous
         * stack map frame and that the number of stack items is 1.
         * The offset_delta value for the frame is given explicitly.
         * frame_type == 247.
         */
		struct{
			uint16_t offset_delta;
    	    VerificationTypeInfo *stack;
		} same_locals_1_stack_item_frame_extended;

		struct{

			/**f the frame_type is chop_frame, it means that the operand stack
			is empty and the current locals are the same as the locals in the
			previous frame, except that the k last locals are absent.
			The value of k is given by the formula 251 - frame_type.*/

			//uint8_t frame_type; //= 248 a 250
			uint16_t offset_delta;
		} chop_frame;

		struct{

			/**If the frame type is same_frame_extended,
			it means the frame has exactly the same locals as
			the previous stack map frame and that the number of stack items is zero.*/

			//uint8_t frame_type; // == 251
			uint16_t offset_delta;

		} same_frame_extended;

		struct{

			/**If the frame_type is append_frame, it means that the
			operand stack is empty and the current locals are the same
			as the locals in the previous frame, except that k
			additional locals are defined. The value of k is given by
			the formula frame_type - 251*/


			//uint8_t frame_type;// == 252 a 254
			uint16_t offset_delta;
			VerificationTypeInfo *locals;

		} append_frame;

		struct{
			/**The frame type full_frame is represented by the tag value 255.*/
			//frame_type == 255
        	uint16_t offset_delta;
        	uint16_t number_of_locals;
        	VerificationTypeInfo *locals; // Vetor alocar com number_of_locals
        	uint16_t number_of_stack_items;
        	VerificationTypeInfo *stack; // Vetor alocar com number_of_stack_items
		} full_frame;
	} map_frame_type;
}StackMapFrame;

/**
 * @brief StackMapTable Attribute definition.
 *
 * Contains the StackMapTable attribute.
 * The type definition of the structure is StackMapTable.
 */
typedef struct _stackmaptable_attribute {
    uint16_t number_of_entries;
    StackMapFrame *entries;
}StackMapTable;

typedef struct _enclosing_method {
    uint16_t class_index;
    uint16_t method_index;
}EnclosingMethod;

typedef struct _signature_attribute {
    uint16_t signature_index;
}Signature_attribute;

typedef struct _sourceDebugExtension_attribute {
    uint8_t *debug_extension;
}SourceDebugExtension_attribute;

struct _annotation;
struct _element_value;

typedef struct _element_value{
    uint8_t tag;
    union {
        uint16_t const_value_index;

        struct{
            uint16_t type_name_index;
            uint16_t const_name_index;
        } enum_const_value;

        uint16_t class_info_index;

        struct _annotation *annotation_value;

        struct{
            uint16_t num_values;
            struct element_value* values;
        } array_value;
    } value;
}Element_value;


typedef struct _element_value_pairs{
    uint16_t element_name_index;
    Element_value *value;
}Element_value_pairs;

typedef struct _annotation {
    uint16_t type_index;
    uint16_t num_element_value_pairs;
    Element_value_pairs* value_pairs;
}Annotation;

typedef struct _parameter_annotations {
	uint16_t num_annotations;
	Annotation *annotations;
}Parameter_annotations;

typedef struct _runtimeVisibleAnnotations_attribute {
    Parameter_annotations *parameters_annotations;
}RuntimeVisibleAnnotations_attribute;

typedef struct _runtimeInvisibleAnnotations_attribute {
    Parameter_annotations *parameters_annotations;
}RuntimeInvisibleAnnotations_attribute;

typedef struct _runtimeVisibleParameterAnnotations_attribute {
    uint8_t num_parameters;
    Parameter_annotations *parameters_annotations;
}RuntimeVisibleParameterAnnotations_attribute;

typedef struct _runtimeInvisibleParameterAnnotations_attribute {
    uint8_t num_parameters;
    Parameter_annotations *parameters_annotations;
}RuntimeInvisibleParameterAnnotations_attribute;

typedef struct _annotationDefault_attribute {
    Element_value *default_value;
}AnnotationDefault_attribute;

typedef struct _bootstrap_methods{
    uint16_t bootstrap_method_ref;
    uint16_t num_bootstrap_arguments;
    uint16_t *bootstrap_arguments;
}Bootstrap_methods;

typedef struct _BootstrapMethods_attribute {
    uint16_t attribute_name_index;
    uint32_t attribute_length;
    uint16_t num_bootstrap_methods;
    Bootstrap_methods * bootstrap_methods;
}BootstrapMethods_attribute;

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
    uint32_t magic;
     /**
     * @brief Mejor Version.
     */
    uint16_t major_version;
    /**
     * @brief Minor Version..
     */
    uint16_t minor_version;
   /**
     * @brief Counter for constant pool.
     */
    uint16_t constantPool_count;
    /**
     * @brief Pointer ConstantPool type ConstantPoolInfo
     */
    ConstPool* constant_pool;
   /**
     * @brief Acess Flags.
     */
    uint16_t access_flags;
    /**
     * @brief This Class.
     */
    uint16_t thisClass;
    /**
     * @brief Super Class.
     */
    uint16_t superClass;
    /**
     * @brief Counter for Interfaces.
     */
    uint16_t interfaces_count;
    /**
     * @brief Interfaces type U2.
     */
    uint16_t *interfaces;
    /**
     * @brief Counter for fields.
     */
    uint16_t fields_count;
    /**
     * @brief Fields type Field.
     */
    Field *fields;
    /**
     * @brief Coounter for Métodos.
     */
    uint16_t methods_count;
    /**
     * @brief Methods type MethodsInfo.
     */
    Method *methods;
    /**
     * @brief Counter of Attributes.
     */
    uint16_t attributes_count;
    /**
     * @brief Attributes type Attribute.
     */
    Attribute *attributes;
}Class;

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
void sum2(int* bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
void sum4(int* bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
char* getUtf8FromConstantPool(int index, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint8_t get1bytesFromByteArray(uint8_t* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint16_t get2bytesFromByteArray(uint8_t* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint32_t get4bytesFromByteArray(uint8_t* byteArr, int bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
double decodeDouble (uint32_t high, uint32_t low);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
float decodeFloat (uint32_t bytes);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
long decodeLong(uint32_t high, uint32_t low);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
ConstPool* getConstantPool(FILE* fp, int* bytecount, uint16_t cpCount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
uint16_t* getInterfaces(FILE* fp, int* bytecount, uint16_t interfacesCount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Field * getFields(FILE* fp, int* bytecount, uint16_t fieldCount, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Method* getMethods(FILE* fp, int* bytecount, uint16_t methodsCount, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Attribute* getAttributes(FILE* fp, int* bytecount, uint16_t attributesCount, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Attribute* getAttributesFromByteArray(uint8_t* info, int* bytecount, uint16_t attributesCount, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
void* decodeInfo(Attribute attribute, ConstPool* constantPool);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
StackMapFrame* getStackMapFrame(uint8_t* info, int* bytecount, int localVariableTableLength);

 /**
  * @brief
  * @todo Description
  * @todo Parameters
  * @todo Return
  */
VerificationTypeInfo* getVerificationTypeInfo (uint8_t* info, int* bytecount);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
ExceptionTableEntry* getExceptionTable(uint8_t* info, int* bytecount, int exceptionTableLength);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
InnerClass* getInnerClasses(uint8_t* info, int* bytecount, int numberOfClasses);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
LineNumberTableEntry* getLineNumberTable(uint8_t* info, int* bytecount, int lineNumberTableLength);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
LocalVariableTableEntry* getLocalVariableTable(uint8_t* info, int* bytecount, int localVariableTableLength);

/**
 * @brief Deallocate the main elements of the .class strucure.
 *
 * Free memory from the Class.
 *
 * @params class Referece of the pointer to the .class structure.
 */
void deallocateClass(Class** class);

/**
 * @brief
 * @todo Description
 * @todo Parameters
 * @todo Return
 */
Class* getClassfile(FILE* fp);

#endif //_CLASS_H
