#include "cpu.h"
const int total_blocks;

int main(void)
{
    //getline
    FILE *fp, *fpMemory;
    char *line = NULL, *lineMemory = NULL;
    size_t len = 0, lenMemory = 0;
    ssize_t read, readMemory;

    //strtok
    char *pch, *pchMemory;
    
    //strtol
    char *pEndMemory;

    //instruction pointer
    int inst_pointer = 1, end = 0;
    char operation, stage='F';

    cacheHit = 0;
    cacheMiss = 0;

    struct command current_command;    

    printf("Tamanho da cache: ");
    scanf("%d", &size_cache);
    cache_memory = (struct cacheLine*) malloc(size_cache * sizeof(struct cacheLine));        //Definição da Cache(Array de blocos de memória cache)
    
    for(int i = 0; i < size_cache; i++)
    {
        cache_memory[i].status = 0;
    }

    block_size = 100/total_blocks;              //Tamanho do bloco = tamanho da memória principal / número total de blocos

    printf("Nível de Associatividade: ");
    scanf("%d", &associativity);

    fp = fopen("memory/teste_cache.txt", "r");
    fpMemory = fopen("memory.txt", "r");
    if ((fp == NULL) || (fpMemory == NULL))
    {
        exit(EXIT_FAILURE);
    }

    int nInstructions = 0;                      //funciona no loop de leitura das instruções e serve como número total de insts
    int nData = 0;

    //loop para leitura do arquivo de instruções
    while ((read = getline(&line, &len, fp)) != -1)
    {        

        pch = strtok(line, " ");                //necessário para começar a dividir tokens
        //if(strlen(&line) < 3) continue;
        int i;                                  // 0 a 2
        for(i = 0; pch != NULL; i++)            //copia as instruções do arquivo pro array de instruções
        {             
            strcpy(instruction_list[nInstructions].instruction_part[i], pch);
            //printf("%s ", instruction_list[i].instruction_part[i]);
            pch = strtok(NULL, " ");
        }
        nInstructions++;
    }

    //loop para leitura do arquivo de dados
    while ((readMemory = getline(&lineMemory, &lenMemory, fpMemory)) != -1)
    {        

        pchMemory = strtok(lineMemory, " ");                //necessário para começar a dividir tokens
        
        if(*pchMemory == '\n')
        {
            memory_list[nData].status = 0;
            nData++;
            continue;
        }

        memory_list[nData].content = (int)strtol(pchMemory, &pEndMemory, 10);
        memory_list[nData].status = 1;
        //printf("\nMemória posição %d: %d \n", nData, memory[nData]);
        nData++;
    }

    while(!end)
    {
        switch(stage)
        {
            case 'F':           //FETCH
                if(inst_pointer <= nInstructions)
                {
                    current_command = instruction_list[inst_pointer - 1];        //copia instrução para variável da inst atual
                    inst_pointer++;
                }
                else
                {
                    end = 1;
                }
                stage = 'D';
                break;

            case 'D':           //DECOD
                //operation = Decod(current_command);
                operation = Decod(current_command.instruction_part[0]);
                if(operation == 23)
                {
                    stage = 'F';
                }
                else{
                    stage = 'E';
                }
                break;

            case 'E':           //EXEC
                stage = Exec(current_command, operation, &inst_pointer);
                //stage = 'S';
                break; 

            case 'S':           //STORE
                fpMemory = fopen("memory.txt", "w");
                if (fpMemory == NULL)
                {
                    exit(EXIT_FAILURE);
                }

                for(int i = 0; i < 100; i++)                                        //Imprime toda a saída no arquivo txt de dados
                {
                    if(memory_list[i].status)
                    {
                        fprintf(fpMemory, "%d\n", memory_list[i].content);
                    }
                    else
                    {
                        fprintf(fpMemory, "\n");
                    }
                }
                end = 1;
                break;

            case 'I':           //INVALID
                return -1;
        }
    }

    printf("\nCacheHit = %d\tCacheMiss = %d\n", cacheHit, cacheMiss);

    fclose(fp);
    fclose(fpMemory);
    free(cache_memory);
    free(line);
    free(lineMemory);
    exit(EXIT_SUCCESS);

    return 0;
}