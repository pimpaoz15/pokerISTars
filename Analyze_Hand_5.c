#include "PokerISTars.h"

/* função que analiza uma mão de 5 cartas */
void analyze_hand_5(int hand[][2], int n_of_cards, bool *royal_flush, bool *straight, bool *flush, bool *four, bool *three, int *pairs) {

    int min_rank;
    int hash_pair;
    int ranks_in_hand[n_of_cards][2];

    *royal_flush = *straight = *flush = *four = *three = false;
    *pairs = 0;

    *flush = is_flush(hand, n_of_cards);
    *straight = is_straight(hand, n_of_cards);

    /* determina o carta mais baixa */
    min_rank = hand[0][RANK];
    for (int card = 1; card < n_of_cards; card++) {
        if (hand[card][RANK] < min_rank)
            min_rank = hand[card][RANK];
    }

    *royal_flush = *flush && *straight && min_rank == 10;

    /* caso se verifique uma destas 3 condições o programa retorna logo um valor, uma vez que já não há qualquer outra possibilidade */
    if (*flush || *straight || *royal_flush)
        return;

    /* verifica a existência de four of a kind, three of a kind e pares */
    count_ranks_in_hand(n_of_cards, hand, ranks_in_hand);
    for (hash_pair = 0; hash_pair < n_of_cards && ranks_in_hand[hash_pair][KEY] != 0; hash_pair++) {
        if (ranks_in_hand[hash_pair][VALUE] == 4) *four = true;
        if (ranks_in_hand[hash_pair][VALUE] == 3) *three = true;
        if (ranks_in_hand[hash_pair][VALUE] == 2) (*pairs)++;
    }
}
/* função que determina a existênica de flush para uma mão de 5 cartas */
bool is_flush(int hand[][2], int n_of_cards) {
    /* flush - todas as cartas do mesmo naipe */
    for (int card = 1; card < n_of_cards; card++)
        if (hand[0][SUIT] != hand[card][SUIT])
            return false;
    return true;
}
/* função que determina a existênica de sequência para uma mão de 5 cartas */
bool is_straight(int hand[][2], int n_of_cards) {

    int swap_rank;
    /* organiza as cartas por ordem decrescente, de acordo com o seu valor */
    for (int i = 0; i < n_of_cards; i++) {
        for (int j = 0; j < (n_of_cards - i - 1); j++) {
            if (hand[j][RANK] < hand[j+1][RANK]) {
                swap_rank = hand[j][RANK];
                hand[j][RANK] = hand[j+1][RANK];
                hand[j+1][RANK] = swap_rank;
            }
        }
    }
    if (hand[0][RANK] == 14 && hand[1][RANK] == 5 && hand[2][RANK] == 4 && hand[3][RANK] == 3 && hand[4][RANK] == 2) {
        hand[0][RANK] = 1; // caso da sequência 5 4 3 2 A, em que o ás vale '1'
        return true;
    }
    if ((hand[0][RANK] - hand[1][RANK] != 1) || (hand[1][RANK] - hand[2][RANK] != 1) || (hand[2][RANK] - hand[3][RANK] != 1) || (hand[3][RANK] - hand[4][RANK] != 1))
        return false;
    return true;
}
/* função que determina o número de valores iguais presentes numa mão de 5 cartas */
void count_ranks_in_hand(int n_of_cards, int hand[][2], int ranks_in_hand[][2]) {

    int card, hash_pair;

    for (hash_pair = 0; hash_pair < n_of_cards; hash_pair++)
        ranks_in_hand[hash_pair][KEY] = ranks_in_hand[hash_pair][VALUE] = 0;

    /* começamos com o 'valor' da primeira carta na mão, como a nossa primeira 'hash key' */
    ranks_in_hand[0][KEY] = hand[0][RANK];
    ranks_in_hand[0][VALUE] = 1;

    for (card = 1; card < n_of_cards; card++) {
        hash_pair = 0;
        /* encontra o 'valor' atual da mão ou o próximo elemento vazio, que será a nossa próxima 'hash key'  */
        while (ranks_in_hand[hash_pair][KEY] != hand[card][RANK] && ranks_in_hand[hash_pair][KEY] != 0)
            hash_pair++;

        /* nova 'hash key': o 'valor' atual da mão não foi encontrado */
        if (ranks_in_hand[hash_pair][KEY] == 0)
            ranks_in_hand[hash_pair][KEY] = hand[card][RANK];

        ranks_in_hand[hash_pair][VALUE]++;
    }
}

