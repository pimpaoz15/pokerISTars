#include "PokerISTars.h"

/* função que analiza uma mão de 9 cartas */
void analyze_hand_9_c(int argc, int hand[][2], int n_of_cards, int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs, int *value_player1, int *value_player2) {

    int player1[7][2], player2[7][2];
    int *untie_pointer, *aux_untie_pointer;
    int untie_player1[5][2], untie_player2[5][2];
    int player1_straight_flush = 0, player2_straight_flush = 0, player1_straight = 0, player2_straight = 0, player1_flush = 0, player2_flush = 0;

    /* declarar a mão do jogador 1 */
    for (int i = 0; i < 2; i++) {
        player1[i][RANK] = hand[i][RANK];
        player1[i][SUIT] = hand[i][SUIT];
    }
    for (int i = 4; i < n_of_cards; i++) {
        player1[i-2][RANK] = hand[i][RANK];
        player1[i-2][SUIT] = hand[i][SUIT];
    }

    /* declarar a mão do jogador 2 */
    for (int j = 2; j < n_of_cards ; j++) {
        player2[j-2][RANK] = hand[j][RANK];
        player2[j-2][SUIT] = hand[j][SUIT];
    }

    /* determinar o valor da mão do jogador 1 */
    analyze_hand_7(player1, 7, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    if (*royal_flush_7)
        *value_player1 = 10;
    else if (*straight_flush_7) {
        *value_player1 = 9;
        player1_straight_flush = *straight_flush_7;
    }
    else if (*four_7) // four of a kind
        *value_player1 = 8;
    else if ((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2)) // full house
        *value_player1 = 7;
    else if (*flush_7) {
        *value_player1 = 6;
        player1_flush = *flush_7;
    }
    else if (*straight_7) {
        *value_player1 = 5;
        player1_straight = *straight_7;
    }
    else if (*three7 == 1) // three of a kind
        *value_player1 = 4;
    else if (*pairs == 2 || *pairs == 3) // two pair
        *value_player1 = 3;
    else if (*pairs == 1) // pair
        *value_player1 = 2;
    else // high hand
        *value_player1 = 1;

    /* print da mão do jogador 1 */
    print_result_7_c(player1, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);

    /* determinar o valor da mão do jogador 2 */
    analyze_hand_7(player2, 7, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    if (*royal_flush_7)
        *value_player2 = 10;
    else if (*straight_flush_7) {
        *value_player2 = 9;
        player2_straight_flush = *straight_flush_7;
    }
    else if (*four_7) // four of a kind
        *value_player2 = 8;
    else if (((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2))) // full house
        *value_player2 = 7;
    else if (*flush_7) {
        *value_player2 = 6;
        player2_flush = *flush_7;
    }
    else if (*straight_7) {
        *value_player2 = 5;
        player2_straight = *straight_7;
    }
    else if (*three7) // three of a kind
        *value_player2 = 4;
    else if (*pairs == 2 || *pairs == 3) // two pair
        *value_player2 = 3;
    else if (*pairs == 1) // pair
        *value_player2 = 2;
    else // hig hand
        *value_player2 = 1;

    /* print da mão do jogador 2 */
    printf(" ");
    print_result_7_c(player2, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    printf(" ");

    /* determinar qual é a mão vencedora */
    if (*value_player1 > *value_player2)
        printf("1\n"); // vitória jogador 1
    else if(*value_player1 < *value_player2)
        printf("2\n"); // vitória joagdor 2
    else if (*value_player1 == *value_player2){

        /* definir a mão do jogador 1 que vai a desempate */
        untie_pointer = choose_5_out_of_7(player1, royal_flush_7, &player1_straight_flush, &player1_straight, &player1_flush, four_7, three7, pairs);
        aux_untie_pointer = untie_pointer;
        for (int k = 0; k < 5; k++) {
            untie_player1[k][RANK] = *(aux_untie_pointer + 2*k);
            untie_player1[k][SUIT] = *(aux_untie_pointer + 2*k +1);
        }

        /* definir a mão do jogador 2 que vai a desempate */
        untie_pointer = choose_5_out_of_7(player2, royal_flush_7, &player2_straight_flush, &player2_straight, &player2_flush, four_7, three7, pairs);
        aux_untie_pointer = untie_pointer;
        for (int k = 0; k < 5; k++) {
            untie_player2[k][RANK] = *(aux_untie_pointer + 2*k);
            untie_player2[k][SUIT] = *(aux_untie_pointer + 2*k +1);
        }

        if (untie(untie_player1, untie_player2, *value_player1) == 0) {
            printf("0\n"); // empate
        }
        else if (untie(untie_player1, untie_player2, *value_player1) == 1) {
            printf("1\n"); // vitória jogador 1
        }
        else {
            printf("2\n"); // vitória jogador 2
        }
    }
}
void analyze_hand_9_di(int hand[][2], int cards_per_set, int  argc, char *argv[], int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs, int *value_player1, int *value_player2, int *hands_frequency, int *victory) {

    int player1[7][2], player2[7][2];
    int *untie_pointer, *aux_untie_pointer;
    int untie_player1[5][2], untie_player2[5][2];
    int player1_straight_flush = 0, player2_straight_flush = 0, player1_straight = 0, player2_straight = 0, player1_flush = 0, player2_flush = 0;

    FILE *print_file;

    /* declarar a mão do jogador 1 */
    for (int i = 0; i < 2; i++) {
        player1[i][RANK] = hand[i][RANK];
        player1[i][SUIT] = hand[i][SUIT];
    }
    for (int i = 4; i < cards_per_set; i++) {
        player1[i - 2][RANK] = hand[i][RANK];
        player1[i - 2][SUIT] = hand[i][SUIT];
    }

    /* declarar a mão do jogador 2 */
    for (int j = 2; j < cards_per_set; j++) {
        player2[j - 2][RANK] = hand[j][RANK];
        player2[j - 2][SUIT] = hand[j][SUIT];
    }

    /* determinar o valor da mão do jogador 1 */
    analyze_hand_7(player1, 7, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);

    if (*royal_flush_7)
        *value_player1 = 10;
    else if (*straight_flush_7) {
        *value_player1 = 9;
        player1_straight_flush = *straight_flush_7;
    }
    else if (*four_7)// four of a kind
        *value_player1 = 8;
    else if ((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2))// full house
        *value_player1 = 7;
    else if (*flush_7) {
        *value_player1 = 6;
        player1_flush = *flush_7;
    }
    else if (*straight_7) {
        *value_player1 = 5;
        player1_straight = *straight_7;
    }
    else if (*three7 == 1) // three of a kind
        *value_player1 = 4;
    else if (*pairs == 2 || *pairs == 3) // two pair
        *value_player1 = 3;
    else if (*pairs == 1) // pair
        *value_player1 = 2;
    else  // high hand
        *value_player1 = 1;

    /* print da mão do jogador 1 */
    if (argc == 3)
        print_result_7_stdout(player1, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs, hands_frequency);
    else
        print_result_7_file(player1, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs, argv, hands_frequency);

    /* determinar o valor da mão do jogador 2 */
    analyze_hand_7(player2, 7, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    if (*royal_flush_7)
        *value_player2 = 10;
     else if (*straight_flush_7) {
        *value_player2 = 9;
        player2_straight_flush = *straight_flush_7;
    } else if (*four_7)// four of a kind
        *value_player2 = 8;
    else if ((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2)) // full house
        *value_player2 = 7;
    else if (*flush_7) {
        *value_player2 = 6;
        player2_flush = *flush_7;
    } else if (*straight_7) {
        *value_player2 = 5;
        player2_straight = *straight_7;
    } else if (*three7 == 1) // three of a kind
        *value_player2 = 4;
    else if (*pairs == 2 || *pairs == 3)  // two pair
        *value_player2 = 3;
    else if (*pairs == 1) // pair
        *value_player2 = 2;
    else  // high hand
        *value_player2 = 1;

    /* print da mão do jogador 2 */
    if (argc == 3) {
        printf(" ");
        print_result_7_stdout(player2, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs, hands_frequency);
        printf(" ");

        /* determinar qual é a mão vencedora */
        if (*value_player1 > *value_player2) {
            printf("1\n"); // vitória jogador 1
            victory[1]++;
        } else if (*value_player1 < *value_player2) {
            printf("2\n"); // vitória joagdor 2
            victory[2]++;
        } else if (*value_player1 == *value_player2) {

            /* definir a mão do jogador 1 que vai a desempate */
            untie_pointer = choose_5_out_of_7(player1, royal_flush_7, &player1_straight_flush, &player1_straight, &player1_flush, four_7, three7, pairs);
            aux_untie_pointer = untie_pointer;
            for (int k = 0; k < 5; k++) {
                untie_player1[k][RANK] = *(aux_untie_pointer + 2 * k);
                untie_player1[k][SUIT] = *(aux_untie_pointer + 2 * k + 1);
            }

            /* definir a mão do jogador 2 que vai a desempate */
            untie_pointer = choose_5_out_of_7(player2, royal_flush_7, &player2_straight_flush, &player2_straight, &player2_flush, four_7, three7, pairs);
            aux_untie_pointer = untie_pointer;
            for (int k = 0; k < 5; k++) {
                untie_player2[k][RANK] = *(aux_untie_pointer + 2 * k);
                untie_player2[k][SUIT] = *(aux_untie_pointer + 2 * k + 1);
            }

            if (untie(untie_player1, untie_player2, *value_player1) == 0) {
                printf("0\n"); // empate
                victory[0]++;
            } else if (untie(untie_player1, untie_player2, *value_player1) == 1) {
                printf("1\n"); // vitória jogador 1
                victory[1]++;
            } else {
                printf("2\n"); // vitória jogador 2
                victory[2]++;
            }
        }
    }
    else {
        print_file = fopen(argv[4], "a");
        fprintf(print_file, " ");
        fclose(print_file);
        print_result_7_file(player2, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs, argv, hands_frequency);
        print_file = fopen(argv[4], "a");
        fprintf(print_file, " ");

        /* determinar qual é a mão vencedora */
        if (*value_player1 > *value_player2) {
            fprintf(print_file, "1\n"); // vitória jogador 1
            victory[1]++;
        } else if (*value_player1 < *value_player2) {
            fprintf(print_file, "2\n"); // vitória joagdor 2
            victory[2]++;
        } else if (*value_player1 == *value_player2) {

            /* definir a mão do jogador 1 que vai a desempate */
            untie_pointer = choose_5_out_of_7(player1, royal_flush_7, &player1_straight_flush, &player1_straight, &player1_flush, four_7, three7, pairs);
            aux_untie_pointer = untie_pointer;
            for (int k = 0; k < 5; k++) {
                untie_player1[k][RANK] = *(aux_untie_pointer + 2 * k);
                untie_player1[k][SUIT] = *(aux_untie_pointer + 2 * k + 1);
            }

            /* definir a mão do jogador 2 que vai a desempate */
            untie_pointer = choose_5_out_of_7(player2, royal_flush_7, &player2_straight_flush, &player2_straight, &player2_flush, four_7, three7, pairs);
            aux_untie_pointer = untie_pointer;
            for (int k = 0; k < 5; k++) {
                untie_player2[k][RANK] = *(aux_untie_pointer + 2 * k);
                untie_player2[k][SUIT] = *(aux_untie_pointer + 2 * k + 1);
            }

            if (untie(untie_player1, untie_player2, *value_player1) == 0) {
                fprintf(print_file, "0\n"); // empate
                victory[0]++;
            } else if (untie(untie_player1, untie_player2, *value_player1) == 1) {
                fprintf(print_file, "1\n"); // vitória jogador 1
                victory[1]++;
            } else {
                fprintf(print_file, "2\n"); // vitória jogador 2
                victory[2]++;
            }
        }
        fclose(print_file);
    }
}
