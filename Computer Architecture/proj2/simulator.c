/******************************************************
 * *
 * Name: James Bach *
 * Class: CDA 3101 *
 * Assignment: Asg 3 (a simulator of a subset of the *
 * MIPS assembly language) *
 * Compile: "c99 simulator.c" *
 * *
******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define USHRT_MIN -65536
#define SUBU_REGCONFLICT 999

int ProcessRType(const unsigned int, int*);
int ProcessIType(const int, int*, int*);

void PrintOper(const int);
void PrintInstruction(char*);
void PrintData(int*);
void PrintRegs(int*);

const int MAXASSEMBLY = 32768 * 2 + 1;
const int MAXINSTR = 32768;
const int MAXINLINE = 9;
const int MAXOUTLINE = 81;

const char* const instrName[] =
    {"addiu","addu","and","beq","bne","div","j","lw",
     "mfhi","mflo", "mult","or","slt","subu","sw","syscall"};

const char* const regName[] =
    {"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3",
     "$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7",
     "$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7",
     "$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra",
     "$lo","$hi"};

const int opcode[] =
    {9, 33, 36, 4, 5, 26, 2, 35,
     16, 18, 24, 37, 42, 999, 43, 12};
 
unsigned int wordCnt, PC = 0; 
FILE* output;

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <name>.obj\n",argv[0]);
        exit(1);
    }
    output = fopen("log.txt", "w");
    int registers[34] = {0}; //[32] = mflo [33] = mfhi
    unsigned hexConvert;
    char instructions[MAXINSTR][MAXINLINE];
    int datamemory[MAXINSTR];
    char* temp;
    FILE* input = fopen(argv[1],"r");
    if (input == NULL)
    {
        fprintf(stderr, "file %s cannot be opened\n",argv[1]);
        exit(1);
    }
    char wordline[MAXINLINE];
    if (!(fscanf(input," %d %d", &registers[28], &wordCnt) == 2))
    {
        fprintf(stderr,
                "could not read machine code header information\n");
        fclose(input);
        fclose(output);
        exit(1);
    }
    int gpAddress = registers[28];
    fprintf(output, "insts:\n");
    for (int i = 0; i < registers[28]; i++)
    {
        fprintf(output, "%4d: ", i);
        fscanf(input, "%s", instructions[i]);
        PrintInstruction(instructions[i]);
    }
    fprintf(output, "\ndata:\n");
    for (int i = 0; i < wordCnt; i++)
    {
        fscanf(input, "%s", wordline);
        
        hexConvert = strtol(wordline, &temp, 16);
        fprintf(output, "%4d: %d\n", registers[28] + i, hexConvert);
        datamemory[i] = hexConvert;
    }
    fclose(input);
    fprintf(output,"\n");
    while (PC >= 0 && PC < registers[28])
    {
        fprintf(output, "PC: %d\n",PC);
        hexConvert = strtol(instructions[PC], &temp, 16);
        fprintf(output, "inst: ");
        PrintInstruction(instructions[PC]);
        switch (hexConvert >> 26)
        {
        case 0://r type
            if (hexConvert == 12)//syscall
            {
                if (registers[2] == 1) //display what is a0
                {
                    int tempout = registers[4];
                    if (tempout >> 15 == 1)
                    {
                        tempout |= USHRT_MIN;
                    }
                    printf("%d\n",tempout);
                }
                else if (registers[2] == 5)  //read next input
                {
                    scanf("%d",&registers[2]);
                }
                else if (registers[2] == 10)
                {
                    fprintf(output, "exiting simulator\n");
                    fclose(output);
                    exit(0);
                }
                else 
                {
                    //error on syscall
                }
                PC++;
            }
            else
            {
                PC += ProcessRType(hexConvert, registers);
            }
            break;
        case 9: case 4: case 5: case 43: case 35://i type
            PC += ProcessIType(hexConvert, registers, datamemory); 
            break;
        case 2: //jump
            PC = hexConvert & 67108863;
            break;
        default:
            fprintf(stderr,
                    "could not find inst with opcode %d and funct %d\n",
                    hexConvert >> 26, hexConvert & 63); 
            fclose(output);
            exit(1);
        }
        if (registers[28] != gpAddress)
        {
            fprintf(stderr,"$gp access violation at address %d\n", PC);
            fclose(output);
            exit(1);
        }
        PrintRegs(registers);
        PrintData(datamemory);
    }
    fprintf(stderr,"PC is accessing data memory at address %d\n", PC);
    fclose(output);
    return 0;
}

void PrintRegs(int* regs)
{
    fprintf(output, "\nregs:\n");
    for (int i = 0; i < 34; i++)
    {
        fprintf(output, "%8s = %5d",regName[i],regs[i]);
        if (i % 4 == 3)
        {
            fprintf(output, "\n");
        }
    }
    fprintf(output, "\n\n");
}

void PrintData(int* data)
{
    fprintf(output, "data memory:\n");
    for (int i = 0; i < wordCnt; i++)
    {
        
        fprintf(output, "   data[%3d] = %5d", i, data[i]);
        if (i % 3 == 2)
        {
            fprintf(output, "\n");
        }
    }
    fprintf(output, "\n\n\n");
}

int ProcessRType(const unsigned int num, int* regs)
{
    unsigned int rs, rt, rd;
    rs = (num & (31 << 21)) >> 21; 
    rt = (num & (31 << 16)) >> 16;
    rd = (num & (31 << 11)) >> 11;

    switch (num & 63)
    {
    case 33: //addu
        regs[rd] = regs[rs] + regs[rt];
        break;
    case 36: //and
        regs[rd] = regs[rs] & regs[rt];
        break;
    case 26: //div
        if (regs[rt] == 0)
        {
            fprintf(stderr, 
                    "divide by zero for instruction at %d\n",
                    PC);
            fclose(output);
            exit(1);
        }
        regs[32] = (regs[rs] / regs[rt]) & UINT_MAX;
        regs[33] = (regs[rs] % regs[rt]) >> 16;
        break;
    case 16: //mfhi
        regs[rd] = regs[33];
        break;
    case 18: //mflo
        regs[rd] = regs[32];
        break;
    case 24: //mult
        ;
        signed long long int multitemp;
        multitemp = regs[rs] * regs[rt];
        if (multitemp > LONG_MAX || multitemp < LONG_MIN)
        {
            regs[32] = multitemp & ULONG_MAX;
            regs[33] = multitemp >> 32; 
        }
        else 
        {
            regs[32] = multitemp;
        }
        break;
    case 37: //or
        regs[rd] = regs[rs] | regs[rt];
        break;
    case 42: //slt
        regs[rs] < regs[rt] ? (regs[rd] = 1) : (regs[rd] = 0);
        break;
    case 35: //subu
        regs[rd] = regs[rs] - regs[rt];
        break;
    default:
        fprintf(stderr,
                "could not find inst with opcode 0 and funct %d\n", 
                num & 63); 
        fclose(output);
        exit(1);
     break;
    }
    regs[0] = 0;
    return 1;
}
int ProcessIType(const int num, int* regs, int* data)
{
    unsigned int rs, rt, oper = num;
    int offset;
    oper >>= 26;
    rs = (num & (31 << 21)) >> 21; 
    rt = (num & (31 << 16)) >> 16;
    offset = num & USHRT_MAX;
    if (offset >> 15 == 1)
    {
        offset |= USHRT_MIN;
    }
    switch (oper)
    {
    case 9: //addiu
        regs[rt] = regs[rs] + offset;
        break;
    case 4: //beq
        if (regs[rs] == regs[rt])
        {
            return offset;
        }
        break;
    case 43://sw
        if (offset > wordCnt)
        {
            fprintf(stderr,
                    "store to instruction memory at address %d\n",
                    regs[28] + offset);
            fclose(output);
            exit(1);
        } 
        data[offset] = regs[rt];
        break;
    case 35://lw
        if (offset > wordCnt)
        {
            fprintf(stderr,
                    "load from instruction memory at address %d\n",
                    regs[28] + offset);
            fclose(output);
            exit(1);
        }
        regs[rt] = data[offset];
        break;
    case 5: //bne
        if (regs[rs] != regs[rt])
        {
            return offset;
        }
        break;
    default:
        fprintf(stderr,
                "could not find inst with opcode %d and funct %d\n", 
                oper, num & 63); 
        fclose(output);
        exit(1);
        break;
    }
    regs[0] = 0;
    return 1;
}
 
void PrintInstruction(char* hexstr)
{
    char* temp;
    unsigned int hexConvert = strtol(hexstr, &temp, 16);
    unsigned int rd, rs, rt, oper = hexConvert >> 26;
    int offset;
    rs = (hexConvert & (31 << 21)) >> 21; 
    rt = (hexConvert & (31 << 16)) >> 16;
    rd = (hexConvert & (31 << 11)) >> 11;
    offset = hexConvert & USHRT_MAX; //65535
    if (offset >> 15 == 1)
    {
        offset |= USHRT_MIN; //65536
    }
    if (oper == 0)
    {
        oper = hexConvert & 63;
        if (oper == 35)
        {
            oper = SUBU_REGCONFLICT; // special case for subu and lw having identical op/func
        }
    }
    PrintOper(oper);
    switch (oper)
    {
    case 33: case 36: case 37: case 42: case SUBU_REGCONFLICT://3 register format
        fprintf(output, "%s,%s,%s\n", regName[rd], regName[rs], regName[rt]);
        break;
    case 26: case 24: //2 register format
        fprintf(output, "%s,%s\n", regName[rs], regName[rt]);
        break;
    case 16: case 18: //1 register format
        fprintf(output, "%s\n", regName[rd]);
        break;
    case 12://syscall
        fprintf(output, "\n");
        break;
    case 9: //addiu
        fprintf(output, "%s,%s,%d\n", regName[rt], regName[rs], offset);
        break;
    case 4: case 5://beq/bne
        fprintf(output, "%s,%s,%d\n", regName[rs], regName[rt], offset);
        break;
    case 43: case 35://lw/sw
        fprintf(output, "%s,%d(%s)\n", regName[rt], offset, regName[rs]);
        break;
    case 2: //jump
        fprintf(output, "%d\n",offset);
        break;
    default:
        fprintf(stderr,"could not find inst with opcode %d and funct %d\n",
                hexConvert >> 26, hexConvert & 63); 
        fclose(output);
        exit(1);
        break;;
    }
    return;
}

void PrintOper(const int n)
{
    for (int i = 0; i < 16; i++)
    {
        if (n == opcode[i])
        {
            if (n == 2) // jump formatting to match
            {
                fprintf(output, "j\t");
            }
            else if (n == 12) //syscall formatting to match
            {
                fprintf(output, "%s", instrName[i]);
            }
            else
            {
                fprintf(output, "%s\t", instrName[i]);
            }
            break;
        }
    }
    return;
}
