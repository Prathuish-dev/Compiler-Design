#include<stdio.h>

int main()
{
    int num_state,num_input,current_state=0;
    printf("Enter the number of states: ");
    scanf("%d", &num_state);
    printf("Enter the number of input characters: ");
    scanf("%d", &num_input);

    char input[num_input];
    printf("Enter the characters: ");

    for(int i = 0; i < num_input; i++) {
        scanf(" %c", &input[i]);  // Space before %c fixes the issue
    }
    int tran[num_state][num_input];
    printf("enter the tansistions\n");
    for(int i=0;i<num_state;i++)
    {
        for(int j=0;j<num_input;j++)
        {
            printf("enter the transition for Q%d--%c-->",i,input[j]);
            scanf("%d",&tran[i][j]);
        }
    }
    int num_final;
    printf("enter the number of final states: ");
    scanf("%d",&num_final);
    int final[num_final];
    printf("enter the final states\n");
    for(int i=0;i<num_final;i++)
    {
        scanf("%d",&final[i]);
    }
    while(1)
    {
        current_state=0; //makeing sure the start state is Q0 
        int num_string;
        printf("enter the size of the test string: ");
        scanf("%d",&num_string);
        char string[num_string];
        printf("enter the test string: ");
        scanf("%s",string);
    
        for(int i=0;i<num_string;i++)
        {
            char ch=string[i];
            int string_index;
            for(int j=0;j<num_input;j++)
            {
                if(ch==input[j])
                {
                    string_index=j;
                    break;
                }
                else continue;    
            }
            current_state=tran[current_state][string_index];
        }
        //check if the current state is in final state
        int flag=0;
        for(int i=0;i<num_final;i++)
        {
            if(current_state==final[i])
            {
                printf("string is accepted\n");
                flag=1;
            }    
        }
        if(flag==0)
            printf("string is rejected\n");
    }  

    return 0;    

    
}
