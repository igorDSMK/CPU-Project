#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

inline char Decod(const char* current_command);
char Exec(const struct command* current_command, const int* op, int* inst_pointer);
inline char GetBlockNumber(const char* address);
inline char setAssociativityAccess(const char* reg_id, const char* address, const int* associativity);
inline char AssociativityAccess(const char* reg_id, const char* address);
inline char DirectAccess(const char* reg_id, const char* address);

#endif //FUNCTIONS_H_
