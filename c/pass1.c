#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int start,locctr,length;
	char label[10],opcode[10],operand[10],code[10],mnemonic[10];
	FILE *fd1,*fd2,*fd3,*fd4,*fd5;
	fd1=fopen("input.txt","r");
	fd2=fopen("optab.txt","r");
	fd3=fopen("intermediate.txt","w");
	fd4=fopen("symtab.txt","w");
	fd5=fopen("length.txt","w");
	fscanf(fd1,"%s\t%s\t%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start=(int)strtol(operand, NULL, 16);
		locctr=start;
		fprintf(fd3,"\t%s\t%s\t%s\n",label,opcode,operand);
	}
	else
	{
		locctr=0;
	}
	while(strcmp(opcode,"END")!=0)
	{
		fscanf(fd1,"%s\t%s\t%s",label,opcode,operand);
		fprintf(fd3,"%x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		if(strcmp(label,"**")!=0)
		{
			fprintf(fd4,"%s\t%x\n",label,locctr);
		}
		fscanf(fd2,"%s\t%s",code,mnemonic);
		while(strcmp(code,"END")!=0)
		{
			if(strcmp(opcode,code)==0)
			{
				locctr=locctr+3;
				break;
			}
			fscanf(fd2,"%s\t%s",code,mnemonic);
		}
		if(strcmp(opcode,"WORD")==0)
			locctr=locctr+3;
		else if(strcmp(opcode,"RESW")==0)
			locctr=locctr+3*(atoi(operand));
		else if(strcmp(opcode,"BYTE")==0)
			locctr++;
		else if(strcmp(opcode,"RESB")==0)
			locctr=locctr+ atoi(operand);
	}
	length=locctr-start;
	fprintf(fd5,"%d\n",length);
	fclose(fd1);
	fclose(fd2);
	fclose(fd3);
	fclose(fd4);
	fclose(fd5);

}
