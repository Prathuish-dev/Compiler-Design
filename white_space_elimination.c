//elimination of white spaces

#include<stdio.h>

int main()
{
    FILE *fp1,*fp2;
    fp1 = fopen("your-.c file","r");
    fp2 = fopen("output.c","w");
    char ch;
    while((ch=fgetc(fp1))!=EOF)
    {
        switch(ch)
        {
            case ' ':
            case '\n':
            case '\t':
                break;
            case '/':
                ch = fgetc(fp1);
                if(ch=='/')
                {    
                    while((ch=fgetc(fp1))!='\n');
                }
                else if(ch=='*')
                {
                    char ch1=fgetc(fp1);
                    char ch2=fgetc(fp1);
                    while(ch1!='*'&& ch2!='/')
                    {
                        ch1=ch2;
                        ch2=fgetc(fp1);
                    }

                }
                else
                {
                    fputc('/',fp2);
                    ungetc(ch,fp1);    
                }
                break;
            default :
                fputc(ch,fp2);    
                break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}
