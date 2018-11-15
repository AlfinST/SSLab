#include<stdio.h>
#include<string.h>

void main()
{
	FILE *f1,*f2,*f3,*f4,*f5;
	
	int locctr, startAddr, opcode1, o, length;
	char mcode[20], label[20], opcode[20], otp[20];
	system("clear");
	
	f1 = fopen("input.txt", "r");
	f3 = fopen("symtab.txt", "w");
	f4 = fopen("output.txt", "w+");	

	fscanf(f1,"%s %s %d", label, mcode, &opcode1);
	
	if(strcmp(mcode,"START")==0) 
	{
		startAddr=opcode1;
		locctr=startAddr;
		printf("-\t%s\t%s\t%d\n", label, mcode, opcode1);
		fprintf(f4, "-\t%s\t%s\t%d\n", label, mcode, opcode1);
	} 
	else
		locctr=0;
	
	fscanf(f1,"%s %s",label,mcode);
	while(!feof(f1))
	{
		fscanf(f1,"%s",opcode);
		printf("\n%d\t%s\t%s\t%s\n", locctr, label, mcode, opcode);
		fprintf(f4, "\n%d\t%s\t%s\t%s\n", locctr, label, mcode, opcode);
		
		if(strcmp(label,"-")!=0)
		{
			fprintf(f3,"\n%d\t%s\n",locctr,label);
		}
		f2=fopen("optab.txt","r");
		fscanf(f2,"%s %d",otp, &o);
	
		while(!feof(f2))
		{
			if(strcmp(mcode,otp)==0)
			{
				locctr=locctr+3;
				break;
			}
			fscanf(f2,"%s %d", otp, &o);
		}
		fclose(f2);
	
		if(strcmp(mcode,"WORD")==0) 
		{
			locctr=locctr+3;
		}
		else if(strcmp(mcode,"RESW")==0)
		{
		opcode1=atoi(opcode);
		locctr=locctr+(3*opcode1);
		}
		else if(strcmp(mcode,"BYTE")==0)
		{
			if(opcode[0]=='X')
				locctr=locctr+1;
			else
			{
				length=strlen(opcode)-2;
				locctr=locctr+length;
			}
		}
		else if(strcmp(mcode,"RESB")==0)
		{
			opcode1=atoi(opcode);
			locctr=locctr+opcode1;
		}
	
		fscanf(f1,"%s%s",label,mcode);
	}
	
	if(strcmp(mcode,"END")==0)
	{
		printf("Program length =%d\n",locctr-startAddr);

		f5 = fopen("length.txt", "w");
	
		fprintf(f5, "%d", locctr - startAddr);
		fclose(f5);	
	}

	fclose(f1);
	fclose(f3);
	fclose(f4);
}
