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

int while_loop_iterator = 0;


typedef struct para_s para_t;
struct para_s{
    int para_a[PARY_LENGTH];
    para_t *nast;
};

para_t *para_first = NULL;
para_t *para_last = NULL;
para_t *para_one_time_use;


int main() {

    /*
     *
     *  REALIZACJA KOLEJKI
     *
     */



    void dodaj_pare(char *buffor, int buffor_len)
    {
        para_t *nowa_para = malloc(sizeof(para_t));
        nowa_para->nast = NULL;

        for (int i = 0, for_number_checker = 0; i < buffor_len; ++i)
        {
            if ((buffor[i]>=48)&&(buffor[i]<=57))
            {
                if (for_number_checker>=PARY_LENGTH)
                {
                    printf("Mozesz podac pare o dlugosci %d!\n",PARY_LENGTH);
                    exit(1);
                }
                nowa_para->para_a[for_number_checker] = atoi(&buffor[i]);
                for_number_checker++;
            }
        }

        para_t *stara_para;
        stara_para = para_last;


        if (para_first == NULL)
        {
            para_first = nowa_para;
            para_last = nowa_para;
        }
        else
        {
            stara_para->nast = nowa_para;
            para_last = nowa_para;
        }

    }


    void printhe()
    {
        para_t *para_print = para_first;

        while(para_print!=NULL)
        {
            printf("Para to: %d %d\n", para_print->para_a[0], para_print->para_a[1]);
            para_print = para_print->nast;
        }
    }

    /*
     *
     *
     * PODAWANIE PAR ZGODNYCH
     *
     *
     *
     */


    printf("Witaj! Podawaj pary zgodne :V\n");


    char while_loop_buffor[PARY_MAX];

    while ((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
    {
        printf("Podaj %d pare zgodna (oddzielajac spacja, przecinkiem lub innym znakiem): ", while_loop_iterator+1);

        fgets(while_loop_buffor, PARY_MAX, stdin);


        if((while_loop_buffor[0] != 'q')&&(while_loop_buffor[1] != 'q'))
        {
            dodaj_pare(while_loop_buffor, strlen(while_loop_buffor));
            printf("%d. podana para zgodna to: %d %d \n", while_loop_iterator+1, para_last->para_a[0],para_last->para_a[1]);
            while_loop_iterator++;
        }
    }

    printf("Podano %d par zgodnych\n", while_loop_iterator);


    /*
     *
     * Znajdz najwiekszy i najmniejszy element ze zbioru
     *
     */

    int greatest_element = 0;
    int smallest_element = INT_MAX;

    para_one_time_use = para_first;
    for (int i = 0; i < while_loop_iterator; ++i)
    {
        while(para_one_time_use!=NULL)
        {
            for (int j = 0; j < PARY_LENGTH; ++j)
            {
                if ((para_one_time_use->para_a[j]>=greatest_element)&&(para_one_time_use->para_a[j] != 'q'))
                    greatest_element = para_one_time_use->para_a[j];

                if ((para_one_time_use->para_a[j]<=smallest_element)&&(para_one_time_use->para_a[j] != 'q'))
                    smallest_element = para_one_time_use->para_a[j];
            }

            para_one_time_use = para_one_time_use->nast;
        }
    }

    printf("Najwiekszy element to: %d\n", greatest_element);

    printf("Najmniejszy element to: %d\n", smallest_element);


    /*
     *
     * Znajdz wszystkie elementy
     *
     */
    int number_of_non_repeat_elements = 0;


    bool found_in_this_iteration = false;

    for (int m = 0; m < PARY_MAX ; ++m)
    {
        para_one_time_use = para_first;
        while(para_one_time_use!=NULL)
        {
            for (int j = 0; j < PARY_LENGTH; ++j) {
                if (para_one_time_use->para_a[j] == m)
                {
                    all_elements[number_of_non_repeat_elements] = m;
                    number_of_non_repeat_elements++;
                    found_in_this_iteration = true;
                }
            }
            if (found_in_this_iteration)
                break;

            para_one_time_use = para_one_time_use->nast;
        }
        found_in_this_iteration=false;
    }


    for (int n = 0; n < number_of_non_repeat_elements; ++n)
    {
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
        for (int i = 0, number_of_found_elements = 0, position_of_current_element = 0, position_of_current_pair_element = 0; i < number_of_non_repeat_elements; ++i)
        {
            number_of_found_elements = 0;

            para_one_time_use = para_first;
            while(para_one_time_use!=NULL)
            {
                position_of_current_element = 0;
                position_of_current_pair_element = 0;
                if ((para_one_time_use->para_a[0] == all_elements[i]))
                {
                    position_of_current_element = 0;
                    position_of_current_pair_element = 1;
                }
                if ((para_one_time_use->para_a[1] == all_elements[i]))
                {
                    position_of_current_element = 1;
                    position_of_current_pair_element = 0;
                }

                if ((position_of_current_element != position_of_current_pair_element) && (para_one_time_use->para_a[position_of_current_element] > para_one_time_use->para_a[position_of_current_pair_element]))
                {
                    pairs_table_elements[i][number_of_found_elements] = para_one_time_use->para_a[position_of_current_pair_element];
                }
                number_of_found_elements++;
                // /////////////////////////////////////////////
                para_one_time_use = para_one_time_use->nast;
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




    int pairs_table_elements_right[number_of_non_repeat_elements][PARY_MAX];
    void create_right_column()
    {
        for (int i = 0; i < number_of_non_repeat_elements; ++i)
        {
            printf("S[%d] = ", all_elements[i]);
            for (int j = 0; j < PARY_MAX; ++j) {


            }

        }
    }




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


                    para_one_time_use = para_first;
                    while(para_one_time_use!=NULL)
                    {
                        int position_of_current_element = 0;
                        int position_of_current_pair_element = 0;
                        if ((para_one_time_use->para_a[0]==current_element))
                        {
                            position_of_current_element = 0;
                            position_of_current_pair_element = 1;
                        }
                        else if ((para_one_time_use->para_a[1]==current_element))
                        {
                            position_of_current_element = 1;
                            position_of_current_pair_element = 0;
                        }
                        else
                        {
                            // position_of_current_element = INT_MAX;
                            break;
                        }
                        if (para_one_time_use->para_a[position_of_current_element] > para_one_time_use->para_a[position_of_current_pair_element])
                        {
                            pairs_table_elements[k][j];
                        }
                        // /////////////////////////////////////////////
                        para_one_time_use = para_one_time_use->nast;
                    }
/*
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



                    }*/



                }

                if (1)
                    break;


            }

            current_element++;
        }
    }



    void create_table()
    {


    }


    return 0;
}