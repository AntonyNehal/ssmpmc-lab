#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    int locctr,start,length;
    char label[10],opcode[10],operand[10],code[10],mneumonic[10];
    FILE *f1,*f2,*f3,*f4,*f5;
    f1=fopen("input.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("inter.txt","w");
    f4=fopen("sys.txt","w");
    f5=fopen("len.txt","w");
    fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        locctr=(int)strtol(operand,NULL,16);
        start=locctr;
        fprintf(f3,"\t\t%s\t%s\t%s\n",label,opcode,operand);
    }
    else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0)
    {
        fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
        fprintf(f3,"%x\t%s\t%s\t\t%s\n",locctr,label,opcode,operand);
        if(strcmp(label,"**")!=0)
        {
            fprintf(f4,"%s\t%x\n",label,locctr);
        }
        fscanf(f2,"%s\t%s",code,mneumonic);
        while(strcmp(code,"END")!=0)
        {
            if(strcmp(opcode,code)==0)
             {
                    locctr+=3;
                   break;
             }
             fscanf(f2,"%s\t%s",code,mneumonic);
        }
        if(strcmp(opcode,"WORD")==0)
        {
            locctr+=3;
        }
        else if(strcmp(opcode,"RESW")==0)
        {
            locctr=locctr+3*(atoi(operand));
        }
        else if(strcmp(opcode,"RESB")==0)
        {
            locctr=locctr+atoi(operand);
        }
       else if(strcmp(opcode,"BYTE")==0)
        {
            locctr++;
        }
    }
    length=locctr-start;
    fprintf(f5,"%d\n",length);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
}