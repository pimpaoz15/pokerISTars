#include "PokerISTars.h"

/* função que valida os argumentos introduzidos (input) */
int analyze_input(int argc, char *argv[]) {

    const int n_of_cards = argc - 2;
    /* verifica o número de cartas introduzidas */
    if (n_of_cards != 5 && n_of_cards != 7 && n_of_cards != 9 && n_of_cards != 10) {
        printf("-1\n");
        exit(0);
    }
    /* verifica se o comprimento de todos os argumentos é igual a 2 */
    for (int i = 1; i < argc; i++) {
        if (strlen(argv[i]) != 2) {
            printf("-1\n");
            exit(0);
        }
    }
    return n_of_cards;
}
/* função que valida e converte os argumentos introduzidos */
void convert_input(int n_of_cards, char *argv[], int hand[n_of_cards][2]) {

    int rank, suit;
    /* guarda os inputs das cartas num array bidimensional */
    if (strncmp(argv[1], "-c", 2) == 0) {
        for (int i = 0; i < n_of_cards; i++) {
            hand[i][RANK] = argv[i + 2][0];
            hand[i][SUIT] = argv[i + 2][1];
        }
    }
    /* verifica se as cartas são válidas e classifica-as de acordo com o seu valor e naipe */
    for (int i = 0; i < n_of_cards; i++) {
        switch (hand[i][RANK]) {
            case '2': rank = 2; break;
            case '3': rank = 3; break;
            case '4': rank = 4; break;
            case '5': rank = 5; break;
            case '6': rank = 6; break;
            case '7': rank = 7; break;
            case '8': rank = 8; break;
            case '9': rank = 9; break;
            case 'T': rank = 10; break;
            case 'J': rank = 11; break;
            case 'Q': rank = 12; break;
            case 'K': rank = 13; break;
            case 'A': rank = 14; break;
            default:
                printf("-1\n");
                exit(0);
        }
        switch (hand[i][SUIT]) {
            case 'C': suit = 1; break;
            case 'E': suit = 2; break;
            case 'O': suit = 3; break;
            case 'P': suit = 4; break;
            default:
                printf("-1\n");
                exit(0);
        }
        hand[i][RANK] = rank;
        hand[i][SUIT] = suit;
    }
}
/* função que determina a existência de cartas duplicadas */
int card_exists(int hand[][2], int n_of_cards) {

    int duplicated_card[n_of_cards][2];
    int swap_rank = 0, swap_suit = 0;

    for (int i = 0; i < n_of_cards; i++) {
        duplicated_card[i][RANK] = hand[i][RANK];
        duplicated_card[i][SUIT] = hand[i][SUIT];
    }
    /* ordena as cartas, da maior para a menor, de acordo com o seu valor*/
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (duplicated_card[j][RANK] < duplicated_card[j + 1][RANK]) {
                swap_rank = duplicated_card[j][RANK];
                duplicated_card[j][RANK] = duplicated_card[j + 1][RANK];
                duplicated_card[j + 1][RANK] = swap_rank;
                swap_suit = duplicated_card[j][SUIT];
                duplicated_card[j][SUIT] = duplicated_card[j + 1][SUIT];
                duplicated_card[j + 1][SUIT] = swap_suit;
            }
        }
    }
    /* caso haja cartas com o mesmo 'valor', organiza-as por ordem alfabética dos naipes */
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (duplicated_card[j][RANK] == duplicated_card[j + 1][RANK]) {
                if (duplicated_card[j][SUIT] > duplicated_card[j + 1][SUIT]) {
                    swap_suit = duplicated_card[j][SUIT];
                    duplicated_card[j][SUIT] = duplicated_card[j + 1][SUIT];
                    duplicated_card[j + 1][SUIT] = swap_suit;
                }
            }
        }
    }
    /* verifica se existem cartas duplicadas */
    for (int k = 0; k < n_of_cards; k++) {
        if(duplicated_card[k][RANK] == duplicated_card[k+1][RANK] && duplicated_card[k][SUIT] == duplicated_card[k+1][SUIT])
            return 1;
    }
    return 0;
}