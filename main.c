#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARY_MAX 255

#define PARY_LENGTH 2


char input_char;

int pary_zgodne[PARY_MAX][PARY_LENGTH];


int main() {
    printf("Witaj! Podawaj pary zgodne :V\n");

    int while_loop_iterator = 0;

    char while_loop_buffor[PARY_MAX];

    while ((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
    {
        printf("Podaj %d pare zgodna (oddzielajac wartosci przecinkami): ", while_loop_iterator);

        fgets(while_loop_buffor, PARY_MAX, stdin);

        int test = strlen(while_loop_buffor);

        for (int i = 0, for_number_checker = 0; i < strlen(while_loop_buffor); ++i)
        {
            if ((while_loop_buffor[i]>=48)&&(while_loop_buffor[i]<=57))
            {
                if (for_number_checker>=PARY_LENGTH)
                {
                    puts("A Ty chujku!");
                    exit(1);
                }
                pary_zgodne[while_loop_iterator][for_number_checker] = while_loop_buffor[i];
                for_number_checker++;
            }
        }
        if((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
        {
            printf("%d. podana para zgodna to: %c %c \n", while_loop_iterator, pary_zgodne[while_loop_iterator][0],pary_zgodne[while_loop_iterator][1]);
            while_loop_iterator++;
        }

    }



    return 0;
}