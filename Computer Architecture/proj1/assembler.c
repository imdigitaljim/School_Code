/******************************************************
 * *
 * Name: James Bach *
 * Class: CDA 3101 *
 * Assignment: Asg 2 (an assembler of a subset of the *
 * MIPS assembly language) *
 * Compile: "c99 assembler.c" *
 * *
 ******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAXINSTR = 32768;
const int MAXASSEMBLY = 32768 * 2 + 2; // per write up
const int MAXLINE = 81;
const int MAXREG = 8;
const int MAXLBL = 11;
const char* const reg[] = 
        {"zero","at","v0","v1","a0","a1","a2","a3",
         "t0","t1","t2","t3","t4","t5","t6","t7",
         "s0","s1","s2","s3","s4","s5","s6","s7",
         "t8","t9","k0","k1","gp","sp","fp","ra"};
const char* const instr[] = 
    {"addiu","addu","and","beq","bne","div","j","lw",
     "mfhi","mflo", "mult","or","slt","subu","sw","syscall"};

const int opcode[] = 
    {9, 33, 36, 4, 5, 26, 2, 35,
     16, 18, 24, 37, 42, 35, 43, 12};

int GetRegIndex(const char*);
int GetOpCode(const char*);
int ValidateInstr(const char*);
void ValidateReg(const char*);

int lineCnt = 0; 

int main(int argc, char** argv)
{
    int instrCnt = 0, wordCnt = 0, totalCnt = 0, wordIndex = 0;
    bool isData = false, isText = false, isFound = false;
    char oper[8], rs[MAXREG], rt[MAXREG], rd[MAXREG];
    char line[MAXLINE], targaddr[MAXLBL], immed[MAXLBL];
    int wordsPerLine[MAXINSTR], inword[MAXINSTR];
    char intake[MAXASSEMBLY][MAXLINE]; 
    char labelLoc[MAXASSEMBLY][MAXLBL];
    char labelFound[MAXASSEMBLY][MAXLBL];
    int nspace, binary, offset;
    int a = 0;
    char comment;
    char* token; 
    

    //first pass to get labels for offsets from stdin saving to array
    while(fgets(intake[a], MAXLINE, stdin))
    {
        //remove comments
        if (instrCnt == 0 && sscanf(intake[a], " %s", line) && strcmp(line, ".text") == 0)
        {
            isText = true;
            continue;
        }
        else if (!isText && !isData)
        {
            //his program does not catch comments pre-.text directive, i copied
            //this functionality
            fprintf(stderr,
                    "The following line is not a .text directive:\n   %s\n",
                    intake[a]);
            exit(1);
        }
        //remove all comment-only lines
        if (sscanf(intake[a]," %c", &comment) == 1)
        {
            if (comment == '#')
            {
                continue;
            }
        } 
        //remove all eol comments
        sscanf(intake[a], "%[^#\n]", intake[a]);
      
        //extract labels
        if (sscanf(intake[a], "%[^:]:%[^\n]", labelLoc[lineCnt], intake[a]) != 2)
        {
            strcpy(labelLoc[lineCnt],"");
        }
        //scan by line variable
        strcpy(line, intake[a]);
        sscanf(line, "%s", oper);
        
        //start instructions
        if (isText)
        {
            lineCnt += ValidateInstr(oper);
            instrCnt = lineCnt; 
            //this is to extract all the labels that were found to ensure 
            //the labels and registers are valid
            if (sscanf(line, "%*s $%[^,],%d($%[^)]", rt, &offset, rs) == 3)
            {
                ValidateReg(rt);
                ValidateReg(rs);
            }
            else if (sscanf(line, "%*s $%[^,],%[^(]($%[^)]", rt, immed, rs) == 3)
            {
                strcpy(labelFound[lineCnt],immed);
                ValidateReg(rt);
                ValidateReg(rs);
            }
            else if (sscanf(line, "%*s $%[^,],($%[^)]", rt, rs) == 2)
            {
                ValidateReg(rt);
                ValidateReg(rs);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],$%s", rd, rs, rt) == 3) 
            {
                ValidateReg(rt);
                ValidateReg(rs);
                ValidateReg(rd);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],%d", rs, rt, &offset) == 3) 
            {
                ValidateReg(rt);
                ValidateReg(rs);
            }
            else if (sscanf(line, "%*s $%[^,],$%[^,],%s", rs, rt, immed) == 3) 
            {
                ValidateReg(rt);
                ValidateReg(rs);
                strcpy(labelFound[lineCnt],immed);
            }
            else if (sscanf(line, "%*s $%[^,],$%s", rs, rt) == 2) 
            {
                ValidateReg(rt);
                ValidateReg(rs);
            }
            else if (sscanf(line, "%*s $%s", rd) == 1) 
            {
                ValidateReg(rd);
            }
            else if (strcmp(oper, "j") == 0 && sscanf(line, "%*s %s", targaddr) == 1)
            {
                strcpy(labelFound[lineCnt],targaddr);
            }
            if (strcmp(oper, ".data") == 0)
            {
                a--;
                isText = false;
                isData = true;
            }
        }
        //runs .data segment
        else if (isData)
        {
            if (sscanf(intake[a], "%[^:]:%s", targaddr, line) == 2)
            {
                strcpy(labelFound[lineCnt],targaddr);
            }
            lineCnt++;
            if (strcmp(oper, ".word") == 0)
            {
                int temp = wordCnt;
                token = strtok(line, ",");
                while (token != NULL)
                {
                    inword[wordCnt] = atoi(token);    
                    token  = strtok(NULL, ",");
                    wordCnt++;  
                }
                wordsPerLine[wordIndex]= wordCnt - temp;
                wordIndex++;
            }
            else if (strcmp(oper, ".space") == 0)
            {
                sscanf(line, "%*s %d", &nspace);
                wordCnt+= nspace;
                wordsPerLine[wordIndex] = nspace;
                wordIndex++;
            }
            else 
            {
                fprintf(stderr,".word or .space directive expected after .data\n");
                exit(1);
            }
        }
        ++a;
    }

    //print out first line
    printf("%d %d\n",instrCnt,wordCnt);
    //reset iterator
    totalCnt = lineCnt;
    for (int i = 0; i < totalCnt + 2; i++)
    {
        if (strlen(labelFound[i]) > 0)
        {
            for (int j = 0; j < totalCnt + 2; j++)
            {
                if (strcmp(labelLoc[j], labelFound[i]) == 0)
                {
                    isFound = true;
                }
            }
            if (!isFound)
            {
                fprintf(stderr,"could not find label %s\n", labelFound[i]);
                exit(1);
            }
            isFound = false;
        }

    }
    lineCnt = 0;

    for (int z = 0; z < totalCnt; z++) //while (intake[a][b] != 0) 
    {
        //save to read by line
        strcpy(line,intake[z]);

        //reset integer binary builder (will later convert int to hex)
        binary = 0;

        //set to something guaranteed not to be found as a label
        strcpy(immed, "!"); 
        
        //if there is a number in $,$,#($)
        offset = 0;
        if (sscanf(line, "%s $%[^,],%d($%[^)]", oper, rt, &offset, rs) == 4)
        {
            binary = GetOpCode(oper) << 5;
            binary = (binary + GetRegIndex(rs)) << 5;
            binary = (binary + GetRegIndex(rt)) << 16;
            binary += offset;
        }

        //$,$,n($)) type
        else if (sscanf(line, "%s $%[^,],($%[^)]", oper, rt, rs) == 3 || 
            sscanf(line, "%s $%[^,],%[^(]($%[^)]", oper, rt, immed, rs) == 4)
        {
            binary = GetOpCode(oper) << 5;
            binary = (binary + GetRegIndex(rs)) << 5;
            binary = (binary + GetRegIndex(rt)) << 16;
                          
            for (int i = 0; i < totalCnt; i++)
            {
                if (strcmp(immed,labelLoc[i]) == 0)
                {
                    if (i > instrCnt)
                    {
                        int temp = 0;
                        for (int x = 0; x < i - instrCnt; x++)
                        {
                            temp += wordsPerLine[x];
                        }
                        binary += temp;
                        break;
                    }
                    else 
                    {
                        binary += (i - instrCnt) & 65535;
                        break;
                    }
                } 
            }  
        }

        //$,$,$ type
        else if (sscanf(line, "%s $%[^,],$%[^,],$%s", oper, rd, rs, rt) == 4) 
        {
            binary = GetRegIndex(rs) << 5;
            binary = (binary + GetRegIndex(rt)) << 5;
            binary = (binary + GetRegIndex(rd)) << 11; 
            binary += GetOpCode(oper);
        }
        //$,$,imme/label type
        else if (sscanf(line, "%s $%[^,],$%[^,],%s", oper, rs, rt, immed) == 4) 
        {
            binary = GetOpCode(oper) << 5;
            if(strcmp(oper,"beq") == 0 || strcmp(oper,"bne") == 0)
            {
                binary = (binary + GetRegIndex(rs)) << 5;
                binary = (binary + GetRegIndex(rt)) << 16;
                for (int i = 0; i < totalCnt; i++)
                {
                    if (strcmp(immed,labelLoc[i]) == 0)
                    {
                        binary += (i - lineCnt) & 65535;
                        break;
                    } 
                }  
            }
            else
            {
                // mask negative overflow
                binary = (binary + GetRegIndex(rt)) << 5;
                binary = (binary + GetRegIndex(rs)) << 16;
                binary += atoi(immed) & 65535;
            }
        }
        //$,$
        else if (sscanf(line, "%s $%[^,],$%s", oper, rs, rt) == 3) 
        {
            binary = GetRegIndex(rs) << 5;
            binary = (binary + GetRegIndex(rt)) << 16;
            binary += GetOpCode(oper);
        }
        //$
        else if (sscanf(line, "%s $%s", oper, rd) == 2) 
        {
            binary = (binary + GetRegIndex(rd)) << 11;
            binary += GetOpCode(oper);
        }
        else 
        {
            binary = GetOpCode(oper);
            //j instruction
            if (binary == 2)
            {
                sscanf(line, "%s %s", oper, targaddr);
                binary = 2 << 26; 
                for (int i = 0; i < totalCnt; i++)
                {
                    if (strcmp(targaddr,labelLoc[i]) == 0)
                    {
                        binary += i;
                        break;
                    } 
                } 
            }
            //syscall and others
            else if (binary < 0)
            {
                if (strcmp(oper, ".word") == 0)
                {
                    lineCnt++;
                    sscanf(line, "%s %s", oper, line); 
                    token = strtok(line, ",");
                    while (token != NULL)
                    {
                        printf("%08x\n",atoi(token));    
                        token = strtok(NULL, ",");
                    }
                } 
                else if (strcmp(oper, ".space") == 0)
                {
                    lineCnt++;
                    sscanf(line, "%*s %d", &nspace);
                    for (int i = 0; i < nspace; i++)
                    {
                        printf("%08x\n", 0);
                    }
                }
                continue;
            }
        }
        lineCnt++;
        printf("%08x\n", binary);
    }
    return 0;
}

int GetRegIndex(const char* currReg)
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(currReg, reg[i]) == 0)
        {
            return i;
        }
    }
    return -1; //already checked for good
}

int GetOpCode(const char* code)
{
    for (int i = 0; i < 16; i++)
    {
        if (strcmp(code, instr[i]) == 0)
        {
            return opcode[i];
        }
    } 
    return -1; //already checked for good
}

int ValidateInstr(const char* op)
{
    if (strcmp(op, ".data") == 0)
    {
        return 0;
    }
    for (int i = 0; i < 16; i++)
    {
        if (strcmp(op, instr[i]) == 0)    //find if instructions valid
        {
            return 1;
        }
    }
    fprintf(stderr,
            "invalid instruction operation %s at line %d\n",
            op, lineCnt + 2);//.text and 0 index
    exit(1);
    return 0;
}

void ValidateReg(const char* currReg)
{
    for (int i = 0; i < 32; i++)
    {
        if (strcmp(currReg, reg[i]) == 0)
        {
            return;
        }
    }
    fprintf(stderr, 
            "invalid register: %s at line %d\n", 
            currReg, lineCnt + 1); //including .text
    exit(1);
}
