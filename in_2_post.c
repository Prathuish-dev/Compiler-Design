#include<stdio.h>
#include<ctype.h>

int stack[100];
int top=-1;

void postfix(char *input);
int precedance(char ch);

int main()
{
    char input[100];
    while(1)
    {
        printf("Enter the input expression:");
        scanf("%s",input);
        postfix(input);
        printf("\n");
    }    
}

void postfix(char *input)
{
    int i=0;
    char ch;
    while(ch!='\0')
    {
        ch=input[i];
        if(ch=='(')
        {
            stack[++top]=ch;
        }
        else if(ch==')')
        {
            while(ch!='(')
            {
                ch=stack[top--];
                printf("%c",ch);
            }
            top--;
        }
        else if(isalpha(ch))
        {
            printf("%c",ch);
        }
        else{
            int x,y;
            x=precedance(ch);
            y=precedance(stack[top]);
            if(x<y)
            {
                stack[++top]=ch;
            }else{
                while(y<x)
                {
                    printf("%c",stack[top--]);
                    x=precedance(ch);
                    y=precedance(stack[top]);
                }
            }
        }
        i++;
    }
}

int precedance(char ch)
{
    if(ch=='*'||ch=='/'||ch=='%'||ch=='^') return 1;
    else if(ch=='+'||ch=='-') return 2;
    else return 3;
}
