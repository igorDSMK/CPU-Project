#include "cpu.h"

//registradores globais
int r[10];

//endereço da memória cache
char adress_cache;

//flags
char flag_z,     //zero
    flag_g,     //greater
    flag_l,     //lesser
    flag_ge,    //greater-equals
    flag_le,    //lesser-equals
    flag_e,     //equals    
    flag_d;     //different

//resto
int resto;    

char direct_access(char reg_id, char adress)
{
    adress_cache = adress % size_cache;

    if((cache_memory[adress_cache].status == 1) && (cache_memory[adress_cache].tag == (adress-1)))
    {   
        r[reg_id] = cache_memory[adress_cache].content;
        cacheHit++;

        return 'F';
    }
    else
    {
        cacheMiss++;
        if(memory_list[adress-1].status)
        {
            cache_memory[adress_cache].content = memory_list[adress-1].content;
            cache_memory[adress_cache].status = 1;
            cache_memory[adress_cache].tag = (adress-1);

            //printf("Cache: %d \tMemory: %d\n\n", cache_memory[adress_cache].tag, memory_list[adress-1].content);

            r[reg_id] = cache_memory[adress_cache].content;
        }
        else
        {
            printf("\nInvalid memory access\n");
            //printf("\nLOAD__Valor : %d, Status: %d\n\n",adress-1, memory_list[adress-1].status);
            return 'I';
        }
        return 'F';
    }
}



char associativity_acess()
{
    return 'I';
}

char Decod(const char * current_command)
{
    if(strcmp(current_command, "MOVE") == 0)                //coloca inteiro no registrador
    {            
        return 1;
    }
    else if(strcmp(current_command, "LOAD") == 0)           //coloca valor da memória no registrador;
    {
        return 2;
    }
    else if(strcmp(current_command, "STORE") == 0)          //coloca valor do registrador na memoria;
    {
        return 3;
    }
    else if(strcmp(current_command, "COPY") == 0)           //copia valor do registrador 2 no registrador 1
    {
        return 4;         
    }
    else if(strcmp(current_command, "ADD") == 0)
    {
        return 5;
    }
    else if(strcmp(current_command, "SUB") == 0)
    {
        return 6;
    }
    else if(strcmp(current_command, "MUL") == 0)
    {
        return 7;
    }
    else if(strcmp(current_command, "DIV") == 0)
    {
        return 8;
    }
    else if(strcmp(current_command, "COMP") == 0)
    {   
        return 9;
    }
    else if(strcmp(current_command, "JUMP") == 0)
    {            
        return 10;              
    }
    else if(strcmp(current_command, "JZ") == 0)
    {
        return 11;
    }
    else if(strcmp(current_command, "JG") == 0)
    {
        return 12;
    }
    else if(strcmp(current_command, "JGE") == 0)
    {
        return 13;
    }
    else if(strcmp(current_command, "JL") == 0)
    {
        return 14;
    }
    else if(strcmp(current_command, "JLE") == 0)
    {
        return 15;
    }
    else if(strcmp(current_command, "JE") == 0)
    {
        return 16;
    }
    else if(strcmp(current_command, "JD") == 0)
    {
        return 17;
    }
    else if(strcmp(current_command, "GETINT") == 0)     //recebe valor inteiro do usuário e coloca num reg
    {
        return 18;
    }
    else if(strcmp(current_command, "ESCREVAL") == 0)   //imprime valor de reg na tela
    {
        return 19;
    }
    else if(strcmp(current_command, "PRINT") == 0)   //imprime valor de reg na tela
    {
        return 20;
    }
    else if(strcmp(current_command, "RET") == 0)        //sai do programa
    {
        return 21;
    }
    else if(strcmp(current_command, "ESCREVA") == 0)   //imprime valor de reg na tela
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

        case 2:     //LOAD
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

            if(associativity == 0)
            {
                return direct_access(reg_id, adress);
            }
            else
            {
                return associativity_acess();
            }
            
        case 3:     //STORE
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

            if(associativity == 0)
            {
                adress_cache = adress % size_cache;
                cache_memory[adress_cache].status = 1;
                cache_memory[adress_cache].tag = (adress-1);
                cache_memory[adress_cache].content = r[reg_id];
            }
            else
            {
                ;
            }

            memory_list[adress-1].content = cache_memory[adress_cache].content;
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
            *inst_pointer = inst_adress ;         
            return 'F';

        case 11: 
            if(flag_z == 1)
            {
                inst_adress = (int)strtol(current_command.instruction_part[1], &pEnd, 10);
                *inst_pointer = inst_adress ;                    
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

