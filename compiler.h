#ifndef COMPILER_H
#define COMPILER_H

#include "object.h"
#include "vm.h"

ObjFunction* compile(const char* source);
void markCompilerRoots();

#endif //COMPILER_H
