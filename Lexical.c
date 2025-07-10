#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s <input file name> <out file name>\n",argv[0]);
		exit(0);
	}
	FILE *fp1,*fp2;
	fp1=fopen(argv[1],"r");
	fp2=fopen(argv[2],"w");	
	int srno=1,line=1,i=0,flag=0;
	char lex[50],ch,ch1;
	char key[15][50]={"void","main","int","float","if","else","for","while","continue","break","do","char","printf","scanf","switch"};
	fprintf(fp2,"sl\t lexem\t token\t lno\n");
	while((ch=fgetc(fp1))!=EOF)
	{
		if(ch==' '|| ch=='\t');
		else if(ch=='\n')
			line++;
		else if(ch=='('||ch=='{'||ch=='[')
		{
			fprintf(fp2,"%d\t %c\t open_brac\t %d\n", srno,ch,line);
			srno++;
		}
		else if(ch==')'||ch=='}'||ch==']')
		{
			fprintf(fp2,"%d\t %c\t close_brac\t %d\n", srno,ch,line);
			srno++;
		}
		else if(ch == ';')
		{
			fprintf(fp2,"%d\t %c\t semicollon\t %d\n", srno,ch,line);
			srno++;
		}
		else if(ch =='+'||ch=='-'||ch=='*'||ch=='/')
		{
			fprintf(fp2,"%d\t %c\t arithm_op\t %d\n", srno,ch,line);
			srno++;
		}
		else if(ch ==',')
		{
			fprintf(fp2,"%d\t %c\t specl_char\t %d\n", srno,ch,line);
			srno++;
		}
		else if(ch =='&')
		{
			ch1=fgetc(fp1);
			if(ch1=='&')
			{
				fprintf(fp2,"%d\t &&\t log_op\t %d\n", srno,line);
			srno++;
			}
			else
			{
				fprintf(fp2,"%d\t %c\t specl_op\t %d\n", srno,ch,line);
			srno++;
			ungetc(ch1,fp1);
			}
		}
		else if(ch == '|')
		{
			ch1=fgetc(fp1);
			if(ch1=='|')
			{
				fprintf(fp2,"%d\t ||\t log_op\t %d\n", srno,line);
			srno++;
			}
			else
			{
				fprintf(fp2,"%d\t %c\t specl_op\t %d\n", srno,ch,line);
			srno++;
			ungetc(ch1,fp1);
			}
		}
		else if(ch=='=')
		{
			ch1=fgetc(fp1);
			if(ch1=='=')
			{
				fprintf(fp2,"%d\t ==\t rel_op\t %d\n", srno,line);
			srno++;
			}
			else
			{
				fprintf(fp2,"%d\t %c\t ass_op\t %d\n", srno,ch,line);
			srno++;
			ungetc(ch1,fp1);
			}
		}
		else if(ch=='>'||ch=='<'||ch=='!')
		{
			ch1=fgetc(fp1);
			if(ch1=='=')
			{
				fprintf(fp2,"%d\t %c%c\t rel_op\t %d\n", srno,ch,ch1,line);
			srno++;
			}
			else
			{
				fprintf(fp2,"%d\t %c\t rel_op\t %d\n", srno,ch,line);
			srno++;
			ungetc(ch1,fp1);
			}
		}
		else if(isdigit(ch))
		{
			i=0;
			lex[i++]=ch;
			do{
				ch1=fgetc(fp1);
				lex[i++]=ch1;
				if(ch1=='.')
					flag=1;	
			}while(isdigit(ch1)||ch1=='.');
			lex[--i]='\0';
			ungetc(ch1,fp1);
			if(flag==0)
			{
				fprintf(fp2,"%d\t %s\t num\t %d\n", srno,lex,line);
				srno++;
			}
			else
			{
				fprintf(fp2,"%d\t %s\t float\t %d\n", srno,lex,line);
				srno++;
			}
			flag=0;
			i=0;
		}
		else if(isalpha(ch))
		{
			i=0;
			lex[i++]=ch;
			do{
				ch1=fgetc(fp1);
				lex[i++]=ch1;
			}while(isalpha(ch1)||isdigit(ch1));
			lex[--i]='\0';
			ungetc(ch1,fp1);
			for(int j=0;j<12;j++)
			{
				if(strcmp(key[j],lex)==0)
				{
					fprintf(fp2,"%d\t %s\t keywrd\t %d\n", srno,lex,line);
				srno++;
				flag=1;
				break;
				}
			}
			if(flag==0)
			{
				fprintf(fp2,"%d\t %s\t identifer\t %d\n", srno,lex,line);
				srno++;
			}
			flag=0;
			i=0;
		}	
		else 
		{
			fprintf(fp2,"%d\t %c\t unrecognized\t %d\n", srno,ch,line);
			srno++;
		} 	
	}
	
	
	fclose(fp1);
	fclose(fp2);
}
