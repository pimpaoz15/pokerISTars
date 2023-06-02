#include "PokerISTars.h"

/* função que analiza uma mão de 7 cartas */
void analyze_hand_7(int hand[][2], int n_of_cards, int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs) {

    int hash_pair;
    int ranks_in_hand[n_of_cards][2];

    *royal_flush_7 = *straight_flush_7 = *flush_7 = *straight_7 = *four_7 = *three7 = *pairs = 0;

    is_straight_flush_7(hand, royal_flush_7, straight_flush_7);

    if (*royal_flush_7 == 1 || (*straight_flush_7 >= 1 && *straight_flush_7 <= 9))
        return;

    is_flush_7(hand, n_of_cards, flush_7);

    if (*flush_7 >= 1 && *flush_7 <= 3)
        return;

    is_straight_7(hand, straight_7);

    if (*straight_7 >= 1 && *straight_7 <= 6)
        return;

    /* verifica a existência de four of a kind, three of a kind e pares */
    count_ranks_in_hand(n_of_cards, hand, ranks_in_hand);
    for (hash_pair = 0; hash_pair < n_of_cards && ranks_in_hand[hash_pair][KEY] != 0; hash_pair++) {
        if (ranks_in_hand[hash_pair][VALUE] == 4) *four_7 = 1;
        if (ranks_in_hand[hash_pair][VALUE] == 3) (*three7)++;
        if (ranks_in_hand[hash_pair][VALUE] == 2) (*pairs)++;
    }
}
/* função que organiza as cartas para determinar se existe straight flush */
int *organize_straight_flush_7 (int hand[][2], int n_of_cards) {

    static int org_hand[7][2];
    int swap_rank = 0, swap_suit = 0;

    for (int k = 0; k < 7; k++) {
        org_hand[k][RANK] = hand[k][RANK];
        org_hand[k][SUIT] = hand[k][SUIT];
    }
    /* organizar as cartas por naipe (P/O/E/C)*/
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (org_hand[j][SUIT] < org_hand[j + 1][SUIT]) {
                swap_suit = org_hand[j][SUIT];
                org_hand[j][SUIT] = org_hand[j + 1][SUIT];
                org_hand[j + 1][SUIT] = swap_suit;
                swap_rank = org_hand[j][RANK];
                org_hand[j][RANK] = org_hand[j + 1][RANK];
                org_hand[j + 1][RANK] = swap_rank;
            }
        }
    }
    /* caso existam cartas com o mesmo naipe, ordenar por ordem decrescente, de acordo com o seu valor */
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (org_hand[j][SUIT] == org_hand[j + 1][SUIT]) {
                if (org_hand[j][RANK] < org_hand[j + 1][RANK]) {
                    swap_rank = org_hand[j][RANK];
                    org_hand[j][RANK] = org_hand[j + 1][RANK];
                    org_hand[j + 1][RANK] = swap_rank;
                }
            }
        }
    }
    return *org_hand;
}
/* função que determina a existênica de straight flush para uma mão de 7 cartas */
void is_straight_flush_7(int hand[][2], int *royal_flush_7, int *straight_flush_7) {

    int *sf7_pointer, *aux_sf7_pointer;
    int sf7_hand[7][2];
    sf7_pointer = organize_straight_flush_7(hand, 7);
    aux_sf7_pointer = sf7_pointer;

    for (int i = 0; i < 7; i++) {
        sf7_hand[i][RANK] = *(aux_sf7_pointer + 2*i);
        sf7_hand[i][SUIT] = *(aux_sf7_pointer + 2*i + 1);
    }

    if (sf7_hand[0][RANK] - sf7_hand[4][RANK] == 4) {
        if (sf7_hand[0][SUIT] == sf7_hand[4][SUIT]) {
            if (sf7_hand[0][RANK] == 14 && sf7_hand[4][RANK] == 10)
                *royal_flush_7 = 1; // royal flush
            else
                *straight_flush_7 = 1; // straight flush
            return;
        }
    }
    if (sf7_hand[1][RANK] - sf7_hand[5][RANK] == 4) {
        if (sf7_hand[1][SUIT] == sf7_hand[5][SUIT]) {
            if (sf7_hand[1][RANK] == 14 && sf7_hand[5][RANK] == 10)
                *royal_flush_7 = 1; // royal flush
            else
                *straight_flush_7 = 2; // straight flush
            return;
        }
    }
    if (sf7_hand[2][RANK] - sf7_hand[6][RANK] == 4) {
        if (sf7_hand[2][SUIT] == sf7_hand[6][SUIT]) {
            if (sf7_hand[2][RANK] == 14 && sf7_hand[6][RANK] == 10)
                *royal_flush_7 = 1; // royal flush
            else
                *straight_flush_7 = 3; // straight flush
            return;
        }
    }
    /* casos para a sequência 5 4 3 2 A (com o mesmo naipe) */
    if (sf7_hand[0][RANK] == 14 && sf7_hand[1][RANK] == 5 && sf7_hand[2][RANK] == 4 && sf7_hand[3][RANK] == 3 && sf7_hand[4][RANK] == 2) {
        if (sf7_hand[0][SUIT] == sf7_hand[4][SUIT]) {
            *straight_flush_7 = 4;
            return; }
    }
    if (sf7_hand[1][RANK] == 14 && sf7_hand[2][RANK] == 5 && sf7_hand[3][RANK] == 4 && sf7_hand[4][RANK] == 3 && sf7_hand[5][RANK] == 2) {
        if (sf7_hand[1][SUIT] == sf7_hand[5][SUIT]) {
            *straight_flush_7 = 5;
            return; }
    }
    if (sf7_hand[2][RANK] == 14 && sf7_hand[3][RANK] == 5 && sf7_hand[4][RANK] == 4 && sf7_hand[5][RANK] == 3 && sf7_hand[6][RANK] == 2) {
        if ( sf7_hand[2][SUIT] == sf7_hand[6][SUIT]) {
            *straight_flush_7 = 6;
            return; }
    }
    if (sf7_hand[0][SUIT] == sf7_hand[5][SUIT]) {
        if (sf7_hand[0][RANK] == 14 && sf7_hand[2][RANK] == 5 && sf7_hand[3][RANK] == 4 && sf7_hand[4][RANK] == 3 && sf7_hand[5][RANK] == 2) {
            *straight_flush_7 = 7;
            return; }
    }
    if (sf7_hand[0][SUIT] == sf7_hand[6][SUIT]) {
        if (sf7_hand[0][RANK] == 14 && sf7_hand[3][RANK] == 5 && sf7_hand[4][RANK] == 4 && sf7_hand[5][RANK] == 3 && sf7_hand[6][RANK] == 2) {
            *straight_flush_7 = 8;
            return; }
    }
    if (sf7_hand[1][SUIT] == sf7_hand[6][SUIT]) {
        if (sf7_hand[1][RANK] == 14 && sf7_hand[3][RANK] == 5 && sf7_hand[4][RANK] == 4 && sf7_hand[5][RANK] == 3 && sf7_hand[6][RANK] == 2) {
            *straight_flush_7 = 9;
            return; }
    }
}
/* função que determina a existênica de flush para uma mão de 7 cartas */
void is_flush_7(int hand[][2], int n_of_cards, int *flush_7) {

    int aux_hand[7][2];
    int swap_rank, swap_suit;

    for (int k = 0; k < 7; k++) {
        aux_hand[k][RANK] = hand[k][RANK];
        aux_hand[k][SUIT] = hand[k][SUIT];
    }
    /* ordena as cartas de acordo com o seu naipe, por ordem alfabética */
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (aux_hand[j][SUIT] > aux_hand[j + 1][SUIT]) {
                swap_suit = aux_hand[j][SUIT];
                aux_hand[j][SUIT] = aux_hand[j + 1][SUIT];
                aux_hand[j + 1][SUIT] = swap_suit;
                swap_rank = aux_hand[j][RANK];
                aux_hand[j][RANK] = aux_hand[j + 1][RANK];
                aux_hand[j + 1][RANK] = swap_rank;
            }
        }
    }
    /* verificar se os naipes são iguais 5 a 5 = flush */
    if (aux_hand[0][SUIT] == aux_hand[4][SUIT])
        *flush_7 = 1;
    else if (aux_hand[1][SUIT] == aux_hand[5][SUIT])
        *flush_7 = 2;
    else if (aux_hand[2][SUIT] == aux_hand[6][SUIT])
        *flush_7 = 3;
}
/* função que organiza as cartas para determinar se existe sequência */
int *organize_straight_7(int hand[][2]) {

    static int org_hand[7][2];
    int swap_rank = 0, swap_suit = 0;

    for (int i = 0; i < 7; i++) {
        org_hand[i][RANK] = hand[i][RANK];
        org_hand[i][SUIT] = hand[i][SUIT];
    }
    /* organizar as cartas, por ordem decresecente, de acordo com o seu valor */
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (7 - i - 1); j++) {
            if (org_hand[j][RANK] < org_hand[j + 1][RANK]) {
                swap_rank = org_hand[j][RANK];
                org_hand[j][RANK] = org_hand[j + 1][RANK];
                org_hand[j + 1][RANK] = swap_rank;
                swap_suit = org_hand[j][SUIT];
                org_hand[j][SUIT] = org_hand[j + 1][SUIT];
                org_hand[j + 1][SUIT] = swap_suit;
            }
        }
    }
    /* no caso de haver cartas com o mesmo valor, organizá-las por ordem alfabética */
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (7 - i - 1); j++) {
            if (org_hand[j][RANK] == org_hand[j + 1][RANK]) {
                if (org_hand[j][SUIT] > org_hand[j + 1][SUIT]) {
                    swap_suit = org_hand[j][SUIT];
                    org_hand[j][SUIT] = org_hand[j + 1][SUIT];
                    org_hand[j + 1][SUIT] = swap_suit;
                }
            }
        }
    }
    /* conta o número de valores diferentes que existem entre as 7 cartas */
    int ranks_in_hand = 1;
    for (int i = 0; i < 6; i++) {
        if (hand[i][RANK] != hand[i+1][RANK])
            ranks_in_hand++;
    }
    /* colocar as cartas que têm valores iguais no fim do array */
    if (ranks_in_hand == 5 || ranks_in_hand == 6) {
        for (int i = 0; i < ranks_in_hand; i++) {
            for (int j = i + 1; j < ranks_in_hand && org_hand[j][RANK] == org_hand[i][RANK]; j++) {
                if (ranks_in_hand == 5) {
                    if (i == 0 && j == 1)
                        i = 0;
                    else i--;
                }
                int rank = org_hand[j][RANK];
                int suit = org_hand[j][SUIT];

                for (int k = j; k < 6; k++) {
                    org_hand[k][RANK] = org_hand[k + 1][RANK];
                    org_hand[k][SUIT] = org_hand[k + 1][SUIT];
                }
                org_hand[6][RANK] = rank;
                org_hand[6][SUIT] = suit;

                if (ranks_in_hand == 5)
                    if (i == 0 && j == 1)
                        j = 0;
            }
        }
    }

    return *org_hand;
}
/* função que determina a existênica de sequência para uma mão de 7 cartas */
void is_straight_7(int hand[][2], int *straight_7) {

    int ranks_in_hand = 1;
    int swap_rank, swap_suit;

    /* organiza as cartas por ordem decrescente, de acordo com o seu 'valor' */
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (7 - i - 1); j++) {
            if (hand[j][RANK] < hand[j + 1][RANK]) {
                swap_rank = hand[j][RANK];
                hand[j][RANK] = hand[j + 1][RANK];
                hand[j + 1][RANK] = swap_rank;
                swap_suit = hand[j][SUIT];
                hand[j][SUIT] = hand[j + 1][SUIT];
                hand[j + 1][SUIT] = swap_suit;
            }
        }
    }
    /* conta o número de 'valores' diferentes que existem entre as 7 cartas*/
    for (int i = 0; i < 6; i++) {
        if (hand[i][RANK] != hand[i+1][RANK])
            ranks_in_hand++;
    }
    if (ranks_in_hand < 5) // caso haja menos de 5 valores diferentes, não é possível existir sequêcia
        return;

    /* vai buscar a mão organizada para determinar se existe sequência */
    int *st7_pointer, *aux_st7_pointer;
    int st7_hand[ranks_in_hand][2];
    st7_pointer = organize_straight_7(hand);
    aux_st7_pointer = st7_pointer;

    for (int i = 0; i < ranks_in_hand; i++) {
        st7_hand[i][RANK] = *(aux_st7_pointer + 2*i);
        st7_hand[i][SUIT] = *(aux_st7_pointer + 2*i + 1);
    }

    if (ranks_in_hand == 7) {
        if (st7_hand[0][RANK] - st7_hand[4][RANK] == 4)
            *straight_7 = 1;
        else if (st7_hand[1][RANK] - st7_hand[5][RANK] == 4)
            *straight_7 = 2;
        else if (st7_hand[2][RANK] - st7_hand[6][RANK] == 4)
            *straight_7 = 3;
        else if (st7_hand[0][RANK] == 14 && st7_hand[3][RANK] == 5 && st7_hand[4][RANK] == 4 && st7_hand[5][RANK] == 3 && st7_hand[6][RANK] == 2)
            *straight_7 = 4;
    }  else if (ranks_in_hand == 6) {
        if (st7_hand[0][RANK] - st7_hand[4][RANK] == 4)
            *straight_7 = 1;
        else if (st7_hand[1][RANK] - st7_hand[5][RANK] == 4)
            *straight_7 = 2;
        else if (st7_hand[0][RANK] == 14 && st7_hand[2][RANK] == 5 && st7_hand[3][RANK] == 4 && st7_hand[4][RANK] == 3 && st7_hand[5][RANK] == 2)
            *straight_7 = 5;
    } else if (ranks_in_hand == 5) {
        if (st7_hand[0][RANK] - st7_hand[4][RANK] == 4)
            *straight_7 = 1;
        else if (st7_hand[0][RANK] == 14 && st7_hand[1][RANK] == 5 && st7_hand[2][RANK] == 4 && st7_hand[3][RANK] == 3 && st7_hand[4][RANK] == 2)
            *straight_7 = 6;
    }
}
/* função que escolhe a melhor mão que é possível formar com 7 cartas */
int *choose_5_out_of_7 (int hand[][2], int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs) {

    int swap_rank, swap_suit;
    static int org_hand[5][2];
    int *sf7_pointer, *aux_sf7_pointer;
    int *st7_pointer, *aux_st7_pointer;

    /* organizar as cartas, por ordem decresecente, de acordo com o seu valor */
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (7 - i - 1); j++) {
            if (hand[j][RANK] < hand[j + 1][RANK]) {
                swap_rank = hand[j][RANK];
                hand[j][RANK] = hand[j + 1][RANK];
                hand[j + 1][RANK] = swap_rank;
                swap_suit = hand[j][SUIT];
                hand[j][SUIT] = hand[j + 1][SUIT];
                hand[j + 1][SUIT] = swap_suit;
            }
        }
    }
    /* no caso de haver cartas com o mesmo valor, organizá-las por ordem alfabética */
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < (7 - i - 1); j++)
            if (hand[j][RANK] == hand[j + 1][RANK])
                if (hand[j][SUIT] > hand[j + 1][SUIT]) {
                    swap_suit = hand[j][SUIT];
                    hand[j][SUIT] = hand[j + 1][SUIT];
                    hand[j + 1][SUIT] = swap_suit;
                }
    }

    if (*royal_flush_7) {
        /* declarar uma mão especial para o caso de royal flush*/
        sf7_pointer = organize_straight_flush_7(hand, 7);
        aux_sf7_pointer = sf7_pointer;

        if (*(aux_sf7_pointer + 8) == 10) { // carta '10' na 5ª posição (carta [4])
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        } else if (*(aux_sf7_pointer + 10) == 10) { // carta '10' na 6ª posição (carta [5])
            for (int i = 1; i < 6; i++) {
                org_hand[i - 1][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 1][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        } else if (*(aux_sf7_pointer + 12) == 10) { // carta '10' na 7ª posição (carta [6])
            for (int i = 2; i < 7; i++) {
                org_hand[i - 2][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        }
    }
    else if (*straight_flush_7) {
        /* declarar uma mão especial para o caso de straight flush*/
        sf7_pointer = organize_straight_flush_7(hand, 7);
        aux_sf7_pointer = sf7_pointer;

        if (*straight_flush_7 == 1) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        } else if (*straight_flush_7 == 2) {
            for (int i = 1; i < 6; i++) {
                org_hand[i - 1][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 1][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        } else if (*straight_flush_7 == 3) {
            for (int i = 2; i < 7; i++) {
                org_hand[i - 2][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
        } else if (*straight_flush_7 == 4) {
            for (int i = 1; i < 5; i++) {
                org_hand[i - 1][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 1][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 1);

        } else if (*straight_flush_7 == 5) {
            for (int i = 2; i < 6; i++) {
                org_hand[i - 2][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 3);

        } else if (*straight_flush_7 == 6) {
            for (int i = 3; i < 7; i++) {
                org_hand[i - 3][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 3][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 5);

        } else if (*straight_flush_7 == 7) {
            for (int i = 2; i < 6; i++) {
                org_hand[i - 2][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 1);

        } else if (*straight_flush_7 == 8) {
            for (int i = 3; i < 7; i++) {
                org_hand[i - 3][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 3][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 1);

        } else if (*straight_flush_7 == 9) {
            for (int i = 3; i < 7; i++) {
                org_hand[i - 3][RANK] = *(aux_sf7_pointer + 2 * i);
                org_hand[i - 3][SUIT] = *(aux_sf7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_sf7_pointer + 3);
        }
    }
    else if (*four_7) {
        if (hand[1][RANK] == hand[2][RANK] && hand[2][RANK] == hand[3][RANK]) { // poker da 1ª à 4ª ou da 2ª à 5ª cartas
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        }
        else if (hand[2][RANK] == hand[3][RANK] && hand[3][RANK] == hand[4][RANK] && hand[4][RANK] == hand[5][RANK]) {
            org_hand[0][RANK] = hand[0][RANK];
            org_hand[0][SUIT] = hand[0][SUIT];
            for (int i = 2; i < 6; i++) {
                org_hand[i - 1][RANK] = hand[i][RANK];
                org_hand[i - 1][SUIT] = hand[i][SUIT];
            }
        }
        else if (hand[3][RANK] == hand[4][RANK] && hand[4][RANK] == hand[5][RANK] && hand[5][RANK] == hand[6][RANK]) {
            org_hand[0][RANK] = hand[0][RANK];
            org_hand[0][SUIT] = hand[0][SUIT];
            for (int i = 3; i < 7; i++) {
                org_hand[i - 2][RANK] = hand[i][RANK];
                org_hand[i - 2][SUIT] = hand[i][SUIT];
            }
        }
    }
    else if ((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2)) {
        if (hand[0][RANK] == hand[1][RANK] && hand[1][RANK] == hand[2][RANK]) {
            if (hand[3][RANK] == hand[4][RANK]) {
                for (int i = 0; i < 5; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
            } else if (hand[4][RANK] == hand[5][RANK]){
                for (int i = 0; i < 3; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
                for (int i = 4; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            } else {
                for (int i = 0; i < 3; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
                for (int i = 5; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[1][RANK] == hand[2][RANK] && hand[2][RANK] == hand[3][RANK]) {
            if (hand[4][RANK] == hand[5][RANK]) {
                for (int i = 1; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            } else {
                for (int i = 1; i < 4; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
                for (int i = 5; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[2][RANK] == hand[3][RANK] && hand[3][RANK] == hand[4][RANK]) {
            if (hand[0][RANK] == hand[1][RANK]) {
                for (int i = 0; i < 5; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
            } else {
                for (int i = 2; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[3][RANK] == hand[4][RANK] && hand[4][RANK] == hand[5][RANK]) {
            if (hand[0][RANK] == hand[1][RANK]) {
                for (int i = 0; i < 2; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
                for (int i = 3; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            } else {
                for (int i = 1; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[4][RANK] == hand[5][RANK] && hand[5][RANK] == hand[6][RANK]) {
            if (hand[0][RANK] == hand[1][RANK]) {
                for (int i = 0; i < 2; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
                for (int i = 4; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            } else if(hand[1][RANK] == hand[2][RANK]) {
                for (int i = 1; i < 3; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
                for (int i = 4; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            } else {
                for (int i = 2; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
    } // full house
    else if (*flush_7) {
        /* organizar as cartas por 'naipe' (C/E/O/P) */
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < (7 - i - 1); j++) {
                if (hand[j][SUIT] > hand[j + 1][SUIT]) {
                    swap_suit = hand[j][SUIT];
                    hand[j][SUIT] = hand[j + 1][SUIT];
                    hand[j + 1][SUIT] = swap_suit;
                    swap_rank = hand[j][RANK];
                    hand[j][RANK] = hand[j + 1][RANK];
                    hand[j + 1][RANK] = swap_rank;
                }
            }
        }
        /* caso o 'naipe' seja igual, organizar as cartas por ordem decrescente do seu 'valor' */
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < (7 - i - 1); j++) {
                if (hand[j][SUIT] == hand[j + 1][SUIT]) {
                    if (hand[j][RANK] < hand[j + 1][RANK]) {
                        swap_rank = hand[j][RANK];
                        hand[j][RANK] = hand[j + 1][RANK];
                        hand[j + 1][RANK] = swap_rank;
                    }
                }
            }
        }
        if (*flush_7 == 1) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        } else if (*flush_7 == 2) {
            for (int i = 1; i < 6; i++) {
                org_hand[i - 1][RANK] = hand[i][RANK];
                org_hand[i - 1][SUIT] = hand[i][SUIT];
            }
        } else if (*flush_7 == 3) {
            for (int i = 2; i < 7; i++) {
                org_hand[i - 2][RANK] = hand[i][RANK];
                org_hand[i - 2][SUIT] = hand[i][SUIT];
            }
        }
    }
    else if (*straight_7) {
        /* declarar uma mão especial para o caso de straight */
        st7_pointer = organize_straight_7(hand);
        aux_st7_pointer = st7_pointer;

        if (*straight_7 == 1) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
        } else if (*straight_7 == 2) {
            for (int i = 1; i < 6; i++) {
                org_hand[i - 1][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i - 1][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
        } else if (*straight_7 == 3) {
            for (int i = 2; i < 7; i++) {
                org_hand[i - 2][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
        } else if (*straight_7 == 4) {
            for (int i = 3; i < 7; i++) {
                org_hand[i - 3][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i - 3][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_st7_pointer + 1);

        } else if (*straight_7 == 5) {
            for (int i = 2; i < 6; i++) {
                org_hand[i - 2][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i - 2][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_st7_pointer + 1);

        } else if (*straight_7 == 6) {
            for (int i = 1; i < 5; i++) {
                org_hand[i - 1][RANK] = *(aux_st7_pointer + 2 * i);
                org_hand[i - 1][SUIT] = *(aux_st7_pointer + 2 * i + 1);
            }
            org_hand[4][RANK] = 1;
            org_hand[4][SUIT] = *(aux_st7_pointer + 1);
        }
    }
    else if (*three7 == 1) {
        if (hand[0][RANK] == hand[1][RANK] && hand[1][RANK] == hand[2][RANK]) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        } else if (hand[1][RANK] == hand[2][RANK] && hand[2][RANK] == hand[3][RANK]) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        } else if (hand[2][RANK] == hand[3][RANK] && hand[3][RANK] == hand[4][RANK]) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        } else if (hand[3][RANK] == hand[4][RANK] && hand[4][RANK] == hand[5][RANK]) {
            for (int i = 0; i < 2; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            for (int i = 3; i < 6; i++) {
                org_hand[i - 1][RANK] = hand[i][RANK];
                org_hand[i - 1][SUIT] = hand[i][SUIT];
            }
        } else if (hand[4][RANK] == hand[5][RANK] && hand[5][RANK] == hand[6][RANK]) {
            for (int i = 0; i < 2; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            for (int i = 4; i < 7; i++) {
                org_hand[i - 2][RANK] = hand[i][RANK];
                org_hand[i - 2][SUIT] = hand[i][SUIT];
            }
        }
    }
    else if (*pairs == 2 || *pairs == 3) {
        if (hand[0][RANK] == hand[1][RANK]) {
            for (int i = 0; i < 2; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            if (hand[2][RANK] == hand[3][RANK] || hand[3][RANK] == hand[4][RANK]) {
                for (int i = 2; i < 5; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
            } else if (hand[4][RANK] == hand[5][RANK]) {
                org_hand[2][RANK] = hand[2][RANK];
                org_hand[2][SUIT] = hand[2][SUIT];
                for (int i = 4; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            }
            else if (hand[5][RANK] == hand[6][RANK]) {
                org_hand[2][RANK] = hand[2][RANK];
                org_hand[2][SUIT] = hand[2][SUIT];
                for (int i = 5; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[1][RANK] == hand[2][RANK]) {
            for (int i = 0; i < 3; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            if (hand[3][RANK] == hand[4][RANK]) {
                for (int i = 3; i < 5; i++) {
                    org_hand[i][RANK] = hand[i][RANK];
                    org_hand[i][SUIT] = hand[i][SUIT];
                }
            } else if (hand[4][RANK] == hand[5][RANK]) {
                for (int i = 4; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            } else if (hand[5][RANK] == hand[6][RANK]) {
                for (int i = 5; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[2][RANK] == hand[3][RANK]) {
            org_hand[0][RANK] = hand[0][RANK];
            org_hand[0][SUIT] = hand[0][SUIT];
            for (int i = 2; i < 4; i++) {
                org_hand[i - 1][RANK] = hand[i][RANK];
                org_hand[i - 1][SUIT] = hand[i][SUIT];
            }
            if (hand[4][RANK] == hand[5][RANK]) {
                for (int i = 4; i < 6; i++) {
                    org_hand[i - 1][RANK] = hand[i][RANK];
                    org_hand[i - 1][SUIT] = hand[i][SUIT];
                }
            }
            else if (hand[5][RANK] == hand[6][RANK]) {
                for (int i = 5; i < 7; i++) {
                    org_hand[i - 2][RANK] = hand[i][RANK];
                    org_hand[i - 2][SUIT] = hand[i][SUIT];
                }
            }
        }
        else if (hand[3][RANK] == hand[4][RANK]) {
            org_hand[0][RANK] = hand[0][RANK];
            org_hand[0][SUIT] = hand[0][SUIT];
            for (int i = 3; i < 7; i++) {
                org_hand[i - 2][RANK] = hand[i][RANK];
                org_hand[i - 2][SUIT] = hand[i][SUIT];
            }
        }
    } // two pair
    else if (*pairs == 1) {
        if ((hand[0][RANK] == hand[1][RANK]) || (hand[1][RANK] == hand[2][RANK]) || (hand[2][RANK] == hand[3][RANK]) || (hand[3][RANK] == hand[4][RANK])) {
            for (int i = 0; i < 5; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
        } else if (hand[4][RANK] == hand[5][RANK]) {
            for (int i = 0; i < 3; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            for (int i = 4; i < 6; i++) {
                org_hand[i - 1][RANK] = hand[i][RANK];
                org_hand[i - 1][SUIT] = hand[i][SUIT];
            }
        } else if (hand[5][RANK] == hand[6][RANK]) {
            for (int i = 0; i < 3; i++) {
                org_hand[i][RANK] = hand[i][RANK];
                org_hand[i][SUIT] = hand[i][SUIT];
            }
            for (int i = 5; i < 7; i++) {
                org_hand[i - 2][RANK] = hand[i][RANK];
                org_hand[i - 2][SUIT] = hand[i][SUIT];
            }
        }
    }
    else { // high card
        for (int i = 0; i < 5; i++) {
            org_hand[i][RANK] = hand[i][RANK];
            org_hand[i][SUIT] = hand[i][SUIT];
        }
    }
    return *org_hand;
}
