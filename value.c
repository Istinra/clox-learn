#include <stdio.h>

#include "memory.h"
#include "value.h"

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