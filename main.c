#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <limits.h>

#define PARY_MAX 255

#define PARY_LENGTH 2


char input_char;

int pary_zgodne[PARY_MAX][PARY_LENGTH] = {0};

int all_elements[PARY_MAX] = {0};


int main() {


    /*
     *
     *
     * PODAWANIE PAR ZGODNYCH
     *
     *
     *
     */


    printf("Witaj! Podawaj pary zgodne :V\n");

    int while_loop_iterator = 0;

    char while_loop_buffor[PARY_MAX];

    while ((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
    {
        printf("Podaj %d pare zgodna (oddzielajac spacja, przecinkiem lub innym znakiem): ", while_loop_iterator);

        fgets(while_loop_buffor, PARY_MAX, stdin);

        int test = strlen(while_loop_buffor);

        for (int i = 0, for_number_checker = 0; i < strlen(while_loop_buffor); ++i)
        {
            if ((while_loop_buffor[i]>=48)&&(while_loop_buffor[i]<=57))
            {
                if (for_number_checker>=PARY_LENGTH)
                {
                    printf("Mozesz podac pare o dlugosci %d!\n",PARY_LENGTH);
                    exit(1);
                }
                pary_zgodne[while_loop_iterator][for_number_checker] = atoi(&while_loop_buffor[i]);
                for_number_checker++;
            }
        }
        if((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
        {
            printf("%d. podana para zgodna to: %d %d \n", while_loop_iterator, pary_zgodne[while_loop_iterator][0],pary_zgodne[while_loop_iterator][1]);
            while_loop_iterator++;
        }
    }

    printf("Podano %d par zgodnych\n", while_loop_iterator);


    /*
     *
     * Znajdz najwiekszy element ze zbioru
     *
     */

    int greatest_element = 0;

    for (int i = 0; i < while_loop_iterator; ++i)
    {
        for (int j = 0; j < PARY_LENGTH; ++j)
        {
            if ((pary_zgodne[i][j]>=greatest_element)&&(pary_zgodne[i][j] != 'q'))
                greatest_element = pary_zgodne[i][j];
        }
    }

    printf("Najwiekszy element to: %d\n", greatest_element);

    /*
     *
     * Znajdz najmniejszy element ze zbioru
     *
     */

    int smallest_element = INT_MAX;

    for (int i = 0; i < while_loop_iterator; ++i)
    {
        for (int j = 0; j < PARY_LENGTH; ++j)
        {
            if ((pary_zgodne[i][j]<=smallest_element)&&(pary_zgodne[i][j] != 'q'))
                smallest_element = pary_zgodne[i][j];
        }
    }

    printf("Najmniejszy element to: %d\n", smallest_element);


    /*
     *
     * Znajdz wszystkie elementy
     *
     */
    int number_of_non_repeat_elements = 0;


    bool found_in_this_iteration = false;
    for (int m = 0; m < PARY_MAX ; ++m) {
        for (int i = 0; i < while_loop_iterator; ++i) {
            for (int j = 0; j < PARY_LENGTH; ++j) {
                if (pary_zgodne[i][j] == m)
                {
                    all_elements[number_of_non_repeat_elements] = m;
                    number_of_non_repeat_elements++;
                    found_in_this_iteration = true;
                }
            }
            if (found_in_this_iteration)
                break;

        }
        found_in_this_iteration=false;

    }
    for (int n = 0; n < number_of_non_repeat_elements; ++n) {
        if (n==0)
            printf("Podano nastepujace elementy: ");
        printf("%d", all_elements[n]);
        if (n+1 == number_of_non_repeat_elements)
            printf("\n");
    }







    int pairs_table_elements[number_of_non_repeat_elements][PARY_MAX];

    for (int j1 = 0; j1 < number_of_non_repeat_elements; ++j1) {
        for (int i = 0; i < PARY_MAX; ++i) {
            pairs_table_elements[j1][i] = INT_MAX;

        }

    }



    void new_create_left_column()
    {
        for (int i = 0, number_of_found_elements = 0; i < number_of_non_repeat_elements; ++i)
        {
            number_of_found_elements = 0;

            for (int k = 0, position_of_current_element = 0, position_of_current_pair_element = 0; k < while_loop_iterator; ++k)
            {
                    position_of_current_element = 0;
                    position_of_current_pair_element = 0;
                    if ((pary_zgodne[k][0] == all_elements[i]))
                    {
                        position_of_current_element = 0;
                        position_of_current_pair_element = 1;
                    }
                    if ((pary_zgodne[k][1] == all_elements[i]))
                    {
                        position_of_current_element = 1;
                        position_of_current_pair_element = 0;
                    }

                    if ((position_of_current_element != position_of_current_pair_element) && (pary_zgodne[k][position_of_current_element] > pary_zgodne[k][position_of_current_pair_element]))
                    {
                        pairs_table_elements[i][number_of_found_elements] = pary_zgodne[k][position_of_current_pair_element];
                    }
                    number_of_found_elements++;


            }

        }



        printf("Lewa kolumna: \n");
        for (int i1 = 0; i1 < number_of_non_repeat_elements; ++i1) {
            printf("S[%d] = ", all_elements[i1]);
            for (int i = 0; i < PARY_MAX; ++i) {
                if ( (pairs_table_elements[i1][i] != INT_MAX) && ((pairs_table_elements[i1][i+1] != INT_MAX)) )
                    printf("%d, ", pairs_table_elements[i1][i]);
                else if( (pairs_table_elements[i1][i] != INT_MAX) && ((pairs_table_elements[i1][i+1] == INT_MAX)) )
                    printf("%d", pairs_table_elements[i1][i]);
            }
            printf("\n");

        }

    }

    new_create_left_column();





    void create_left_column()
    {
        int current_element = smallest_element;
        for (int k = 0; k < greatest_element-smallest_element; ++k) {
            if (k==0)
                pairs_table_elements[k][0] = 'N';
            else
            for (int i = 0; i < while_loop_iterator; ++i)
            {
                for (int j = 0; j < PARY_MAX; ++j) {

                    for (int l = 0; l < while_loop_iterator; ++l)
                    {
                        int position_of_current_element = 0;
                        int position_of_current_pair_element = 0;
                            if ((pary_zgodne[l][0]==current_element))
                            {
                                position_of_current_element = 0;
                                position_of_current_pair_element = 1;
                            }
                            else if ((pary_zgodne[l][1]==current_element))
                            {
                                position_of_current_element = 1;
                                position_of_current_pair_element = 0;
                            }
                            else
                            {
                               // position_of_current_element = INT_MAX;
                                break;
                            }
                        if (pary_zgodne[l][position_of_current_element] > pary_zgodne[l][position_of_current_pair_element])
                        {
                            pairs_table_elements[k][j];
                        }



                    }



                }

                if (1)
                    break;


            }

            current_element++;
        }
    }

    void create_right_column()
    {

    }


    void create_table()
    {


    }


    return 0;
}