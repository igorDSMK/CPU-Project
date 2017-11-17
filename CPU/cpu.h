#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct para instruções
struct command{
    char instruction_part[3][30];           //cada instrução tem 3 partes(strings de tamanho 10)
};

struct memory
{
    char status;
    int content;
};

struct cacheBlock
{
	char status;
	char tag;
	int content;
};

//array de instruções
struct command instruction_list[100];
struct memory memory_list[100];
struct cacheBlock *cache_memory;

int size_cache, associativity;
int cacheHit, cacheMiss;

char Decod(const char *current_command);
char Exec(struct command current_command, int op, int *inst_pointer);