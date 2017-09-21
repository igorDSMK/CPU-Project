/*
*   O primeiro argumento sempre é o destino
*
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//registradores globais
int r[10];
//int a, b, c, d, operation;

//flags
int flag_z,     //zero
    flag_g,     //greater
    flag_l,     //lesser
    flag_ge,    //greater-equals
    flag_le,    //lesser-equals
    flag_e,     //equals    
    flag_d;     //different

//resto
int resto;    

//struct para instruções
struct command{
    char instruction_part[3][30];           //cada instrução tem 3 partes(strings de tamanho 10)
};

struct memory
{
    int status;
    int content;
};

//array de instruções
struct command instruction_list[100];
struct memory memory_list[100];

int Decod(struct command current_command)
{

    if(strcmp(current_command.instruction_part[0], "MOVE") == 0)                //coloca inteiro no registrador
    {            
        return 1;
    }
    else if(strcmp(current_command.instruction_part[0], "LOAD") == 0)           //coloca valor da memória no registrador;
    {
        return 2;
    }
    else if(strcmp(current_command.instruction_part[0], "STORE") == 0)          //coloca valor do registrador na memoria;
    {
        return 3;
    }
    else if(strcmp(current_command.instruction_part[0], "COPY") == 0)           //copia valor do registrador 2 no registrador 1
    {
        return 4;         
    }
    else if(strcmp(current_command.instruction_part[0], "ADD") == 0)
    {
        return 5;
    }
    else if(strcmp(current_command.instruction_part[0], "SUB") == 0)
    {
        return 6;
    }
    else if(strcmp(current_command.instruction_part[0], "MUL") == 0)
    {
        return 7;
    }
    else if(strcmp(current_command.instruction_part[0], "DIV") == 0)
    {
        return 8;
    }
    else if(strcmp(current_command.instruction_part[0], "COMP") == 0)
    {   
        return 9;
    }
    else if(strcmp(current_command.instruction_part[0], "JUMP") == 0)
    {            
        return 10;              
    }
    else if(strcmp(current_command.instruction_part[0], "JZ") == 0)
    {
        return 11;
    }
    else if(strcmp(current_command.instruction_part[0], "JG") == 0)
    {
        return 12;
    }
    else if(strcmp(current_command.instruction_part[0], "JGE") == 0)
    {
        return 13;
    }
    else if(strcmp(current_command.instruction_part[0], "JL") == 0)
    {
        return 14;
    }
    else if(strcmp(current_command.instruction_part[0], "JLE") == 0)
    {
        return 15;
    }
    else if(strcmp(current_command.instruction_part[0], "JE") == 0)
    {
        return 16;
    }
    else if(strcmp(current_command.instruction_part[0], "JD") == 0)
    {
        return 17;
    }
    else if(strcmp(current_command.instruction_part[0], "GETINT") == 0)     //recebe valor inteiro do usuário e coloca num reg
    {
        return 18;
    }
    else if(strcmp(current_command.instruction_part[0], "ESCREVAL") == 0)   //imprime valor de reg na tela
    {
        return 19;
    }
    else if(strcmp(current_command.instruction_part[0], "PRINT") == 0)   //imprime valor de reg na tela
    {
        return 20;
    }
    else if(strcmp(current_command.instruction_part[0], "RET") == 0)        //sai do programa
    {
        return 21;
    }
    else if(strcmp(current_command.instruction_part[0], "ESCREVA") == 0)   //imprime valor de reg na tela
    {
        return 22;
    }
    else
    {
        return 23;                                                         //Comando vazio
    }
}


char Exec(struct command current_command, int op, int* inst_pointer)
{
    char *pEnd;
    int reg_id, reg_id1, reg_id2, value, adress, arg1, arg2, status, inst_adress;
    //printf("\nInstruction : %s\n", current_command.instruction_part[0]);

    switch(op)
    {
        case 1:
            reg_id = current_command.instruction_part[1][1] - 48;               //pega o número depois do r no arquivo de texto e converte para int
            value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);//converte o segundo argumento para int 

            r[reg_id] = value; 
            return 'F';

        case 2:
             reg_id = current_command.instruction_part[1][1] - 48;               //pega o número depois do r no arquivo de texto e converte para int
            //int adress = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;
                adress = r[reg_id2];                
            }
            else{
                adress = (int)strtol(current_command.instruction_part[2], &pEnd, 10);
                //r[reg_id] += value;
            }
            
            if(memory_list[adress-1].status)
            {
                r[reg_id] = memory_list[adress-1].content;
            }
            else
            {
                printf("\nInvalid memory access\n");
                //printf("\nLOAD__Valor : %d, Status: %d\n\n",adress-1, memory_list[adress-1].status);
                return 'I';
            }
            return 'F';

        case 3:
            reg_id = current_command.instruction_part[1][1] - 48;               //pega o número depois do r no arquivo de texto e converte para int
            //int adress = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;
                adress = r[reg_id2];                
            }
            else{
                adress = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

                //r[reg_id] += value;
            }
            
            memory_list[adress-1].content = r[reg_id];
            memory_list[adress-1].status = 1;
            return 'F';

        case 4:
            reg_id1 = current_command.instruction_part[1][1] - 48;
            reg_id2 = current_command.instruction_part[2][1] - 48;                
            
            r[reg_id1] = r[reg_id2];
            return 'F';

        case 5:
            reg_id = current_command.instruction_part[1][1] - 48;
            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;

                r[reg_id] += r[reg_id2];
            }
            else{
                value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

                r[reg_id] += value;
            }
            return 'F';

        case 6:
            reg_id = current_command.instruction_part[1][1] - 48;
            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;

                r[reg_id] -= r[reg_id2];
            }
            else{
                value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

                r[reg_id] -= value;
            }
            return 'F';

        case 7:
            reg_id = current_command.instruction_part[1][1] - 48;
            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;

                r[reg_id] *= r[reg_id2];
            }
            else{
                value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);

                r[reg_id] *= value;
            }
            return 'F';

        case 8:
            reg_id = current_command.instruction_part[1][1] - 48;
            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;
                
                resto = r[reg_id] % r[reg_id2];
                r[reg_id] /= r[reg_id2];
            }
            else{
                value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);
                
                resto = r[reg_id] % value;
                r[reg_id] /= value;                
            }
            return 'F';

        case 9:
            //flags zeradas para facilitar
            flag_z = 0;     //zero
            flag_g = 0;     //greater
            flag_ge = 0;     
            flag_l = 0;     //lesser
            flag_le = 0;     
            flag_e = 0;     //equals    
            flag_d = 0;     //different

            reg_id1 = current_command.instruction_part[1][1] - 48;
            arg1 = r[reg_id1];

            if(current_command.instruction_part[2][0] == 'r')
            {
                reg_id2 = current_command.instruction_part[2][1] - 48;
                arg2 = r[reg_id2];               
            }
            else{
                value = (int)strtol(current_command.instruction_part[2], &pEnd, 10);
                arg2 = value;                             
            }

            //comparações começam aqui
            if(arg1 == 0) flag_z = 1;
            if(arg1 > arg2) flag_g = 1;
            if(arg1 >= arg2) flag_ge = 1;
            if(arg1 < arg2) flag_l = 1;
            if(arg1 <= arg2) flag_le = 1;
            if(arg1 == arg2) flag_e = 1;
            if(arg1 != arg2) flag_d = 1;
            return 'F';

        case 10:
            inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
            *inst_pointer = inst_adress ;         //subtrai 1 para compensar o incremento da variável de controle inst_pointer 
            return 'F';

        case 11: 
            if(flag_z == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;         //subtrai 1 para compensar o incremento da variável de controle inst_pointer                
            }
            return 'F';

        case 12:
            if(flag_g == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 13:
            if(flag_ge == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 14:
            if(flag_l == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 15:
            if(flag_le == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 16:
            if(flag_e == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 17:
            if(flag_d == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                
            }
            return 'F';

        case 18:
            reg_id = current_command.instruction_part[1][1] - 48;
            scanf("%d", &r[reg_id]);
            return 'F';

        case 19:
            reg_id = current_command.instruction_part[1][1] - 48;
            printf("%d\n", r[reg_id]);
            return 'F';

        case 20:
            //int reg_id = current_command.instruction_part[1][1] - 48;
            printf("%s\n", current_command.instruction_part[1]);
            return 'F';

        case 21:
            status = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
            printf("Program ended with status %d\n", status);
            return 'S';

        case 22:
            reg_id = current_command.instruction_part[1][1] - 48;
            printf("%d", r[reg_id]);
            return 'F';

    }
}


int main(void)
{
    //getline
    FILE *fp, *fpMemory;
    char *line = NULL, *lineMemory = NULL;
    size_t len = 0, lenMemory = 0;
    ssize_t read, readMemory;

    //strtok
    char *pch, *pchMemory, stage='F';
    
    //strtol
    char *pEndMemory;

    //instruction pointer
    int inst_pointer = 1, end = 0, operation;

    struct command current_command;    

    fp = fopen("telefones.txt", "r");
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
                operation = Decod(current_command);
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

    fclose(fp);
    fclose(fpMemory);
    free(line);
    free(lineMemory);
    exit(EXIT_SUCCESS);
}