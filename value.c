#include <stdio.h>

#include "memory.h"
#include "value.h"

#include <string.h>

#include "object.h"

void initValueArray(ValueArray *array) {
    array->values = NULL;
    array->len = 0;
    array->count = 0;
}

void writeValueArray(ValueArray* array, Value value) {
    if (array->len < array->count + 1) {
        int oldLen = array->len;
        array->len = GROW_CAPACITY(oldLen);
        array->values = GROW_ARRAY(Value, array->values,
                                   oldLen, array->len);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->len);
    initValueArray(array);
}

static void printFunction(ObjFunction* function) {
    if (function->name == NULL) {
        printf("<script>");
        return;
    }
    printf("<fn %s>", function->name->chars);
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING:
            printf("%s", AS_CSTRING(value));
        break;
        case OBJ_FUNCTION:
            printFunction(AS_FUNCTION(value));
        break;
        case OBJ_CLOSURE:
            printFunction(AS_CLOSURE(value)->function);
        break;
        case OBJ_NATIVE:
            printf("<native fn>");
        break;
    }
}

void printValue(const Value value) {
    switch (value.type) {
        case VAL_BOOL:
            printf(AS_BOOL(value) ? "true" : "false");
        break;
        case VAL_NIL: printf("nil"); break;
        case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        case VAL_OBJ: printObject(value); break;
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) return false;
    switch (a.type) {
        case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL:    return true;
        case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
        default:         return false; // Unreachable.
    }
}