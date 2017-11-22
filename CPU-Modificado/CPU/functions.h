#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

char Decod(const char* current_command);
char Exec(const struct command* current_command, const int* op, int* inst_pointer);
char GetBlockNumber(const char* address);
char setAssociativityAccess(const char* reg_id, const char* address, const int* associativity);
char AssociativityAccess(const char* reg_id, const char* address);
char DirectAccess(const char* reg_id, const char* address);

#endif //FUNCTIONS_H_
