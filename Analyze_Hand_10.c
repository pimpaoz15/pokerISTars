#include "PokerISTars.h"

/* função que analiza uma mão de 10 cartas */
void analyze_hand_10_c(int hand[][2], bool *royal_flush, bool *straight, bool *flush, bool *four, bool *three, int *pairs, int *value_player1, int *value_player2) {

    int player1[5][2], player2[5][2];

    /* declarar a mão do jogador 1 */
    for (int i = 0; i < 5; i++) {
        player1[i][RANK] = hand[i][RANK];
        player1[i][SUIT] = hand[i][SUIT];
    }

    /* declarar a mão do jogador 2 */
    for (int j = 5; j < 10; j++) {
        player2[j - 5][RANK] = hand[j][RANK];
        player2[j - 5][SUIT] = hand[j][SUIT];
    }

    /* verificar se há cartas repetidas em cada uma das mãos */
    if (card_exists(player1, 5)) {
        printf("-1\n");
        exit(0);
    }
    if (card_exists(player2, 5)) {
        printf("-1\n");
        exit(0);
    }
    /* determinar o valor da mão do jogador 1 */
    analyze_hand_5(player1, 5, royal_flush, straight, flush, four, three, pairs);
    if (*royal_flush)
        *value_player1 = 10;
    else if (*straight && *flush)
        *value_player1 = 9;
    else if (*four)
        *value_player1 = 8;
    else if (*three && *pairs == 1)
        *value_player1 = 7;
    else if (*flush)
        *value_player1 = 6;
    else if (*straight)
        *value_player1 = 5;
    else if (*three)
        *value_player1 = 4;
    else if (*pairs == 2)
        *value_player1 = 3;
    else if (*pairs == 1)
        *value_player1 = 2;
    else
        *value_player1 = 1;

    /* determinar o valor da mão do jogador 2 */
    analyze_hand_5(player2, 5, royal_flush, straight, flush, four, three, pairs);
    if (*royal_flush)
        *value_player2 = 10;
    else if (*straight && *flush)
        *value_player2 = 9;
    else if (*four)
        *value_player2 = 8;
    else if (*three && *pairs == 1)
        *value_player2 = 7;
    else if (*flush)
        *value_player2 = 6;
    else if (*straight)
        *value_player2 = 5;
    else if (*three)
        *value_player2 = 4;
    else if (*pairs == 2)
        *value_player2 = 3;
    else if (*pairs == 1)
        *value_player2 = 2;
    else
        *value_player2 = 1;

    /* determinar qual é a mão vencedora */
    if (*value_player1 > *value_player2)
        printf("1\n"); // vitória joagaodr 1
    else if (*value_player1 < *value_player2)
        printf("2\n"); // vitória jogador 2
    else if (*value_player1 == *value_player2) {
        if (untie(player1, player2, *value_player1) == 0)
            printf("0\n"); // empate
        else if (untie(player1, player2, *value_player1) == 1)
            printf("1\n"); // vitória jogador 1
        else
            printf("2\n"); // vitória jogador 2
    }
}
void analyze_hand_10_di(int hand[][2], int argc, char *argv[],  bool *royal_flush, bool *straight, bool *flush, bool *four, bool *three, int *pairs, int *value_player1, int *value_player2, int *hands_frequency, int *victory){

    int player1[5][2], player2[5][2];
    FILE *print_file;

    /* declarar a mão do jogador 1 */
    for (int i = 0; i < 5; i++) {
        player1[i][RANK] = hand[i][RANK];
        player1[i][SUIT] = hand[i][SUIT];
    }

    /* declarar a mão do jogador 2 */
    for (int j = 5; j < 10; j++) {
        player2[j - 5][RANK] = hand[j][RANK];
        player2[j - 5][SUIT] = hand[j][SUIT];
    }

    /* verificar se há cartas repetidas em cada uma das mãos */
    if (card_exists(player1, 5)) {
        if (argc == 3) {
            printf("-1\n");

        } else {
            print_file = fopen(argv[4], "a");
            fprintf(print_file, "-1\n");
            fclose(print_file);
        }
        hands_frequency[0] += 2;
        victory[0]++;
        return;
    }
    if (card_exists(player2, 5)) {
        if (argc == 3) {
            printf("-1\n");

        } else {
            print_file = fopen(argv[4], "a");
            fprintf(print_file, "-1\n");
            fclose(print_file);
        }
        hands_frequency[0] += 2;
        victory[0]++;
        return;
    }

    /* determinar o valor da mão do jogador 1 */
    analyze_hand_5(player1, 5, royal_flush, straight, flush, four, three, pairs);
    if (*royal_flush) {
        *value_player1 = 10;
        hands_frequency[10]++;
    } else if (*straight && *flush) {
        *value_player1 = 9;
        hands_frequency[9]++;
    } else if (*four) {
        *value_player1 = 8;
        hands_frequency[8]++;
    } else if (*three && *pairs == 1) {
        *value_player1 = 7;
        hands_frequency[7]++;
    } else if (*flush) {
        *value_player1 = 6;
        hands_frequency[6]++;
    } else if (*straight) {
        *value_player1 = 5;
        hands_frequency[5]++;
    } else if (*three) {
        *value_player1 = 4;
        hands_frequency[4]++;
    } else if (*pairs == 2) {
        *value_player1 = 3;
        hands_frequency[3]++;
    } else if (*pairs == 1) {
        *value_player1 = 2;
        hands_frequency[2]++;
    } else {
        *value_player1 = 1;
        hands_frequency[1]++;
    }

    /* determinar o valor da mão do jogador 2 */
    analyze_hand_5(player2, 5, royal_flush, straight, flush, four, three, pairs);
    if (*royal_flush) {
        *value_player2 = 10;
        hands_frequency[10]++;
    } else if (*straight && *flush) {
        *value_player2 = 9;
        hands_frequency[9]++;
    } else if (*four) {
        *value_player2 = 8;
        hands_frequency[8]++;
    } else if (*three && *pairs == 1) {
        *value_player2 = 7;
        hands_frequency[7]++;
    } else if (*flush) {
        *value_player2 = 6;
        hands_frequency[6]++;
    } else if (*straight) {
        *value_player2 = 5;
        hands_frequency[5]++;
    } else if (*three) {
        *value_player2 = 4;
        hands_frequency[4]++;
    } else if (*pairs == 2) {
        *value_player2 = 3;
        hands_frequency[3]++;
    } else if (*pairs == 1) {
        *value_player2 = 2;
        hands_frequency[2]++;
    } else {
        *value_player2 = 1;
        hands_frequency[1]++;
    }


    if (argc == 3) {
        /* determinar qual é a mão vencedora */
        if (*value_player1 > *value_player2) {
            printf("1\n"); // vitória joagaodr 1
            victory[1]++;
        } else if (*value_player1 < *value_player2) {
            printf("2\n"); // vitória jogador 2
            victory[2]++;
        } else if (*value_player1 == *value_player2) {
            if (untie(player1, player2, *value_player1) == 0) {
                printf("0\n"); // empate
                victory[0]++;
            } else if (untie(player1, player2, *value_player1) == 1) {
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
        if (*value_player1 > *value_player2) {
            fprintf(print_file, "1\n"); // vitória joagaodr 1
            victory[1]++;
        } else if (*value_player1 < *value_player2) {
            fprintf(print_file, "2\n"); // vitória jogador 2
            victory[2]++;
        } else if (*value_player1 == *value_player2) {
            if (untie(player1, player2, *value_player1) == 0) {
                fprintf(print_file, "0\n"); // empate
                victory[0]++;
            } else if (untie(player1, player2, *value_player1) == 1) {
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