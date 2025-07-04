//elimination of white spaces

#include<stdio.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("usage: %s <input file> <output file>\n", argv[0]);
        returnn 1;
    }
    FILE *fp1,*fp2;
    fp1 = fopen(argv[1],"r");
    fp2 = fopen(argv[2],"w");
    char ch;
    while((ch=fgetc(fp1))!=EOF)
    {
        switch(ch)
        {
            //elimination of white space, new line and tab
            case ' ':
            case '\n':
            case '\t':
                break;
            case '/':
                ch = fgetc(fp1);
                if(ch=='/')//elimination of single line commend
                {    
                    while((ch=fgetc(fp1))!='\n');
                }
                else if(ch=='*')//elimination of multi line comment
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
