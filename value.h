#ifndef VALUE_H
#define VALUE_H

typedef double Value;

typedef struct {
    int len;
    int count;
    Value *values;
} ValueArray;

void initValueArray(ValueArray *array);

void writeValueArray(ValueArray *array, Value value);

void freeValueArray(ValueArray *array);

void printValue(Value value);

#endif //VALUE_H
