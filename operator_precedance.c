#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

// Terminals in fixed order
char Tr[] = { '+', '*', '(', ')', 'i', '$' };
int N = 6;

// Precedence table for grammar: E -> E+E | E*E | (E) | i
char pt[6][6] = {
    // +     *     (     )     i     $
    { '>',  '<',  '<',  '>',  '<',  '>' }, // +
    { '>',  '>',  '<',  '>',  '<',  '>' }, // *
    { '<',  '<',  '<',  '=',  '<',  '-' }, // (
    { '>',  '>',  '-',  '>',  '>',  '>' }, // )
    { '>',  '>',  '-',  '>',  '>',  '>' }, // i
    { '<',  '<',  '<',  '-',  '<',  '=' }  // $
};

int findPos(char symbol) {
    for (int i = 0; i < N; i++) {
        if (Tr[i] == symbol) return i;
    }
    return -1; // not found
}

int main() {
    while (1) {
        char input[100];
        printf("\nEnter the input string (end with $): ");
        scanf("%s", input);

        top = -1;
        stack[++top] = '$';

        int ip = 0, flag = 0;

        while (!(stack[top] == '$' && input[ip] == '$')) {
            char a = stack[top];
            char b = input[ip];

            int pos_a = findPos(a);
            int pos_b = findPos(b);

            if (pos_a == -1 || pos_b == -1) {
                printf("Rejected (invalid symbol)\n");
                flag = 1;
                break;
            }

            char relation = pt[pos_a][pos_b];

            if (relation == '<' || relation == '=') {
                stack[++top] = input[ip++];
            }
            else if (relation == '>') {
                char ch1;
                do {
                    char x = stack[top--];
                    char y = stack[top];
                    int pos_x = findPos(x);
                    int pos_y = findPos(y);
                    if (pos_x == -1 || pos_y == -1) {
                        flag = 1;
                        break;
                    }
                    ch1 = pt[pos_y][pos_x];
                } while (ch1 != '<' && top > 0);
            }
            else {
                flag = 1;
                break;
            }
        }

        if (flag == 0) printf("Accepted \n");
        else printf("Rejected \n");
    }

    return 0;
}
