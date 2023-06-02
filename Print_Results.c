#include "PokerISTars.h"

/* função que imprime o resultado final para uma mão de 5 cartas */
void print_result_c(bool royal_flush, bool straight, bool flush, bool four, bool three, int pairs) {
    if (royal_flush)
        printf("10\n");
    else if (straight && flush) // straight flush
        printf("9\n");
    else if (four) //four of a kind
        printf("8\n");
    else if (three && pairs == 1) // full house
        printf("7\n");
    else if (flush)
        printf("6\n");
    else if (straight)
        printf("5\n");
    else if (three) // three of a kind
        printf("4\n");
    else if (pairs == 2) // two pair
        printf("3\n");
    else if (pairs == 1) // pair
        printf("2\n");
    else // high hand
        printf("1\n");
}
void print_result_stdout(bool royal_flush, bool straight, bool flush, bool four, bool three, int pairs, int *hands_frequency) {
    if (royal_flush) {
        printf("10\n");
        hands_frequency[10]++;
    }
    else if (straight && flush) {
        printf("9\n");
        hands_frequency[9]++;
    }
    else if (four) {
        printf("8\n");
        hands_frequency[8]++;
    }
    else if (three && pairs == 1) {
        printf("7\n");
        hands_frequency[7]++;
    }
    else if (flush) {
        printf("6\n");
        hands_frequency[6]++;
    }
    else if (straight) {
        printf("5\n");
        hands_frequency[5]++;
    }
    else if (three) {
        printf("4\n");
        hands_frequency[4]++;
    }
    else if (pairs == 2) {
        printf("3\n");
        hands_frequency[3]++;
    }
    else if (pairs == 1) {
        printf("2\n");
        hands_frequency[2]++;
    }
    else {
        printf("1\n");
        hands_frequency[1]++;
    }
}
void print_result_file(bool royal_flush, bool straight, bool flush, bool four, bool three, int pairs, char *argv[], int *hands_frequency) {

    FILE *fp;
    fp = fopen(argv[4], "a");

    if (royal_flush) {
        fputs("10\n", fp);
        hands_frequency[10]++;
    }
    else if (straight && flush) {
        fputs("9\n", fp);
        hands_frequency[9]++;
    }
    else if (four) {
        fputs("8\n", fp);
        hands_frequency[8]++;
    }
    else if (three && pairs == 1) {
        fputs("7\n", fp);
        hands_frequency[7]++;
    }
    else if (flush) {
        fputs("6\n", fp);
        hands_frequency[6]++;
    }
    else if (straight) {
        fputs("5\n", fp);
        hands_frequency[5]++;
    }
    else if (three) {
        fputs("4\n", fp);
        hands_frequency[4]++;
    }
    else if (pairs == 2) {
        fputs("3\n", fp);
        hands_frequency[3]++;
    }
    else if (pairs == 1) {
        fputs("2\n", fp);
        hands_frequency[2]++;
    }
    else {
        fputs("1\n", fp);
        hands_frequency[1]++;
    }

    fclose(fp);
}
void print_stats_file(char *argv[], int *hands_frequency, int *victory, int n_of_sets, int cards_per_set) {

    double invalid_cards, royal_flush, straight_flush, four, full_house, flush, straight, three, two_pair, pair, high_card;
    int total_sets;

    if (cards_per_set == 5 || cards_per_set == 7)
        total_sets = n_of_sets - 1;
    else
        total_sets = (n_of_sets - 1) * 2;

    invalid_cards = (double) hands_frequency[0] / total_sets;
    high_card = (double) hands_frequency[1] / total_sets;
    pair = (double) hands_frequency[2] / total_sets;
    two_pair = (double) hands_frequency[3] / total_sets;
    three = (double) hands_frequency[4] / total_sets;
    straight = (double) hands_frequency[5] / total_sets;
    flush = (double) hands_frequency[6] / total_sets;
    full_house = (double) hands_frequency[7] / total_sets;
    four = (double) hands_frequency[8] / total_sets;
    straight_flush = (double) hands_frequency[9] / total_sets;
    royal_flush = (double) hands_frequency[10] / total_sets;


    FILE *fp;
    fp = fopen(argv[4], "a");

    fprintf(fp, "%d %.2E\n", -1, invalid_cards);
    fprintf(fp, "%d %.2E\n", 1, high_card);
    fprintf(fp, "%d %.2E\n", 2, pair);
    fprintf(fp, "%d %.2E\n", 3, two_pair);
    fprintf(fp, "%d %.2E\n", 4, three);
    fprintf(fp, "%d %.2E\n", 5, straight);
    fprintf(fp, "%d %.2E\n", 6, flush);
    fprintf(fp, "%d %.2E\n", 7, full_house);
    fprintf(fp, "%d %.2E\n", 8, four);
    fprintf(fp, "%d %.2E\n", 9, straight_flush);
    fprintf(fp, "%d %.2E\n", 10, royal_flush);

    if (cards_per_set == 9 || cards_per_set == 10) {
        fprintf(fp, "\n%d %d\n", 0, victory[0]);
        fprintf(fp, "%d %d\n", 1, victory[1]);
        fprintf(fp, "%d %d\n", 2, victory[2]);
    }

    fclose(fp);
}
void print_stats_stdout(int *hands_frequency, int *victory, int n_of_sets, int cards_per_set) {

    double invalid_cards, royal_flush, straight_flush, four, full_house, flush, straight, three, two_pair, pair, high_card;
    int total_sets;

    if (cards_per_set == 5 || cards_per_set == 7)
        total_sets = n_of_sets - 1;
    else
        total_sets = (n_of_sets - 1) * 2;

    invalid_cards = (double) hands_frequency[0] / total_sets;
    high_card = (double) hands_frequency[1] / total_sets;
    pair = (double) hands_frequency[2] / total_sets;
    two_pair = (double) hands_frequency[3] / total_sets;
    three = (double) hands_frequency[4] / total_sets;
    straight = (double) hands_frequency[5] / total_sets;
    flush = (double) hands_frequency[6] / total_sets;
    full_house = (double) hands_frequency[7] / total_sets;
    four = (double) hands_frequency[8] / total_sets;
    straight_flush = (double) hands_frequency[9] / total_sets;
    royal_flush = (double) hands_frequency[10] / total_sets;

    printf("-1 %.2E\n", invalid_cards);
    printf("1 %.2E\n", high_card);
    printf("2 %.2E\n", pair);
    printf("3 %.2E\n", two_pair);
    printf("4 %.2E\n", three);
    printf("5 %.2E\n", straight);
    printf("6 %.2E\n", flush);
    printf("7 %.2E\n", full_house);
    printf("8 %.2E\n", four);
    printf("9 %.2E\n", straight_flush);
    printf("10 %.2E\n", royal_flush);

    if (cards_per_set == 9 || cards_per_set == 10) {
        printf("\n0 %d", victory[0]);
        printf("\n1 %d", victory[1]);
        printf("\n2 %d\n", victory[2]);
    }

}
/* função que imprime o resultado final para uma mão de 7 cartas */
void print_result_7_c(int hand[][2], int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs) {

    char print_hand[5][2];
    int *hand_pointer, *aux_hand_pointer;
    hand_pointer = choose_5_out_of_7(hand, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    aux_hand_pointer = hand_pointer;

    /* repõe o conteúdo original das cartas */
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i) == 2)
            print_hand[i][RANK] = '2';
        else if (*(aux_hand_pointer + 2*i) == 3)
            print_hand[i][RANK] = '3';
        else if (*(aux_hand_pointer + 2*i) == 4)
            print_hand[i][RANK] = '4';
        else if (*(aux_hand_pointer + 2*i) == 5)
            print_hand[i][RANK] = '5';
        else if (*(aux_hand_pointer + 2*i) == 6)
            print_hand[i][RANK] = '6';
        else if (*(aux_hand_pointer + 2*i) == 7)
            print_hand[i][RANK] = '7';
        else if (*(aux_hand_pointer + 2*i) == 8)
            print_hand[i][RANK] = '8';
        else if (*(aux_hand_pointer + 2*i) == 9)
            print_hand[i][RANK] = '9';
        else if (*(aux_hand_pointer + 2*i) == 10)
            print_hand[i][RANK] = 'T';
        else if (*(aux_hand_pointer + 2*i) == 11)
            print_hand[i][RANK] = 'J';
        else if (*(aux_hand_pointer + 2*i) == 12)
            print_hand[i][RANK] = 'Q';
        else if (*(aux_hand_pointer + 2*i) == 13)
            print_hand[i][RANK] = 'K';
        else if (*(aux_hand_pointer + 2*i) == 14 || *(aux_hand_pointer + 2*i) == 1)
            print_hand[i][RANK] = 'A';
    }
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i + 1) == 1)
            print_hand[i][SUIT] = 'C';
        else if (*(aux_hand_pointer + 2*i + 1) == 2)
            print_hand[i][SUIT] = 'E';
        else if (*(aux_hand_pointer + 2*i + 1) == 3)
            print_hand[i][SUIT] = 'O';
        else if (*(aux_hand_pointer + 2*i + 1) == 4)
            print_hand[i][SUIT] = 'P';
    }
    /* dar print das 5 cartas que constituem a melhor mão */
    for (int i = 0; i < 5; i++) {
        printf("%c%c ", print_hand[i][RANK], print_hand[i][SUIT]);
    }

    if (*royal_flush_7) // royal flush
        printf("10");
    else if (*straight_flush_7) // straight flush
        printf("9");
    else if (*four_7) // four of a kind
        printf("8");
    else if (((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2))) // full house
        printf("7");
    else if (*flush_7) // flush
        printf("6");
    else if (*straight_7) // straight
        printf("5");
    else if (*three7) // three of a kind
        printf("4");
    else if (*pairs == 2 || *pairs == 3) // two pair
        printf("3");
    else if (*pairs == 1) // pair
        printf("2");
    else // high card
        printf("1");
}
void print_result_7_stdout(int hand[][2], int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs, int *hands_frequency) {

    char print_hand[5][2];
    int *hand_pointer, *aux_hand_pointer;
    hand_pointer = choose_5_out_of_7(hand, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    aux_hand_pointer = hand_pointer;

    /* repõe o conteúdo original das cartas */
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i) == 2)
            print_hand[i][RANK] = '2';
        else if (*(aux_hand_pointer + 2*i) == 3)
            print_hand[i][RANK] = '3';
        else if (*(aux_hand_pointer + 2*i) == 4)
            print_hand[i][RANK] = '4';
        else if (*(aux_hand_pointer + 2*i) == 5)
            print_hand[i][RANK] = '5';
        else if (*(aux_hand_pointer + 2*i) == 6)
            print_hand[i][RANK] = '6';
        else if (*(aux_hand_pointer + 2*i) == 7)
            print_hand[i][RANK] = '7';
        else if (*(aux_hand_pointer + 2*i) == 8)
            print_hand[i][RANK] = '8';
        else if (*(aux_hand_pointer + 2*i) == 9)
            print_hand[i][RANK] = '9';
        else if (*(aux_hand_pointer + 2*i) == 10)
            print_hand[i][RANK] = 'T';
        else if (*(aux_hand_pointer + 2*i) == 11)
            print_hand[i][RANK] = 'J';
        else if (*(aux_hand_pointer + 2*i) == 12)
            print_hand[i][RANK] = 'Q';
        else if (*(aux_hand_pointer + 2*i) == 13)
            print_hand[i][RANK] = 'K';
        else if (*(aux_hand_pointer + 2*i) == 14 || *(aux_hand_pointer + 2*i) == 1)
            print_hand[i][RANK] = 'A';
    }
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i + 1) == 1)
            print_hand[i][SUIT] = 'C';
        else if (*(aux_hand_pointer + 2*i + 1) == 2)
            print_hand[i][SUIT] = 'E';
        else if (*(aux_hand_pointer + 2*i + 1) == 3)
            print_hand[i][SUIT] = 'O';
        else if (*(aux_hand_pointer + 2*i + 1) == 4)
            print_hand[i][SUIT] = 'P';
    }
    /* dar print das 5 cartas que constituem a melhor mão */
    for (int i = 0; i < 5; i++) {
        printf("%c%c ", print_hand[i][RANK], print_hand[i][SUIT]);
    }

    if (*royal_flush_7) {
        printf("10");
        hands_frequency[10]++;
    }
    else if (*straight_flush_7) {
        printf("9");
        hands_frequency[9]++;
    }
    else if (*four_7) {
        printf("8");
        hands_frequency[8]++;
    }
    else if (((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2))) {
        printf("7");
        hands_frequency[7]++;
    }
    else if (*flush_7) {
        printf("6");
        hands_frequency[6]++;
    }
    else if (*straight_7) {
        printf("5");
        hands_frequency[5]++;
    }
    else if (*three7) {
        printf("4");
        hands_frequency[4]++;
    }
    else if (*pairs == 2 || *pairs == 3) {
        printf("3");
        hands_frequency[3]++;
    }
    else if (*pairs == 1) {
        printf("2");
        hands_frequency[2]++;
    }
    else {
        printf("1");
        hands_frequency[1]++;
    }
}
void print_result_7_file(int hand[][2], int *royal_flush_7, int *straight_flush_7, int *straight_7, int *flush_7, int *four_7, int *three7, int *pairs, char *argv[], int *hands_frequency) {

    char print_hand[5][2];
    int *hand_pointer, *aux_hand_pointer;
    hand_pointer = choose_5_out_of_7(hand, royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs);
    aux_hand_pointer = hand_pointer;

    /* repõe o conteúdo original das cartas */
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i) == 2)
            print_hand[i][RANK] = '2';
        else if (*(aux_hand_pointer + 2*i) == 3)
            print_hand[i][RANK] = '3';
        else if (*(aux_hand_pointer + 2*i) == 4)
            print_hand[i][RANK] = '4';
        else if (*(aux_hand_pointer + 2*i) == 5)
            print_hand[i][RANK] = '5';
        else if (*(aux_hand_pointer + 2*i) == 6)
            print_hand[i][RANK] = '6';
        else if (*(aux_hand_pointer + 2*i) == 7)
            print_hand[i][RANK] = '7';
        else if (*(aux_hand_pointer + 2*i) == 8)
            print_hand[i][RANK] = '8';
        else if (*(aux_hand_pointer + 2*i) == 9)
            print_hand[i][RANK] = '9';
        else if (*(aux_hand_pointer + 2*i) == 10)
            print_hand[i][RANK] = 'T';
        else if (*(aux_hand_pointer + 2*i) == 11)
            print_hand[i][RANK] = 'J';
        else if (*(aux_hand_pointer + 2*i) == 12)
            print_hand[i][RANK] = 'Q';
        else if (*(aux_hand_pointer + 2*i) == 13)
            print_hand[i][RANK] = 'K';
        else if (*(aux_hand_pointer + 2*i) == 14 || *(aux_hand_pointer + 2*i) == 1)
            print_hand[i][RANK] = 'A';
    }
    for (int i = 0; i < 5; i++) {
        if (*(aux_hand_pointer + 2*i + 1) == 1)
            print_hand[i][SUIT] = 'C';
        else if (*(aux_hand_pointer + 2*i + 1) == 2)
            print_hand[i][SUIT] = 'E';
        else if (*(aux_hand_pointer + 2*i + 1) == 3)
            print_hand[i][SUIT] = 'O';
        else if (*(aux_hand_pointer + 2*i + 1) == 4)
            print_hand[i][SUIT] = 'P';
    }

    FILE *fp;
    fp = fopen(argv[4], "a");

    /* dar print das 5 cartas que constituem a melhor mão */
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "%c%c ", print_hand[i][RANK], print_hand[i][SUIT]);
    }

    if (*royal_flush_7) {
        fputs("10", fp);
        hands_frequency[10]++;
    }
    else if (*straight_flush_7) {
        fputs("9", fp);
        hands_frequency[9]++;
    }
    else if (*four_7) {
        fputs("8", fp);
        hands_frequency[8]++;
    }
    else if (((*three7 == 1 && *pairs == 1) || (*three7 == 1 && *pairs == 2) || (*three7 == 2))) {
        fputs("7", fp);
        hands_frequency[7]++;
    }
    else if (*flush_7) {
        fputs("6", fp);
        hands_frequency[6]++;
    }
    else if (*straight_7) {
        fputs("5", fp);
        hands_frequency[5]++;
    }
    else if (*three7) {
        fputs("4", fp);
        hands_frequency[4]++;
    }
    else if (*pairs == 2 || *pairs == 3) {
        fputs("3", fp);
        hands_frequency[3]++;
    }
    else if (*pairs == 1) {
        fputs("2", fp);
        hands_frequency[2]++;
    }
    else {
        fputs("1", fp);
        hands_frequency[1]++;
    }

    fclose(fp);
}

void print_stats_stdout_dx(int *hands_frequency, int decks_read) {

    double royal_flush, straight_flush, four, full_house, flush, straight, three, two_pair, pair, high_card;

    high_card = (double) hands_frequency[1]/decks_read;
    pair = (double) hands_frequency[2]/decks_read;
    two_pair = (double) hands_frequency[3]/decks_read;
    three = (double) hands_frequency[4]/decks_read;
    straight = (double) hands_frequency[5]/decks_read;
    flush = (double) hands_frequency[6]/decks_read;
    full_house = (double) hands_frequency[7]/decks_read;
    four = (double) hands_frequency[8]/decks_read;
    straight_flush = (double) hands_frequency[9]/decks_read;
    royal_flush = (double) hands_frequency[10]/decks_read;

    printf("1 %.2E\n", high_card);
    printf("2 %.2E\n", pair);
    printf("3 %.2E\n", two_pair);
    printf("4 %.2E\n", three);
    printf("5 %.2E\n", straight);
    printf("6 %.2E\n", flush);
    printf("7 %.2E\n", full_house);
    printf("8 %.2E\n", four);
    printf("9 %.2E\n", straight_flush);
    printf("10 %.2E\n", royal_flush);
}
void print_winners_dx(double *win) {

    double swap_player;
    int swap_number;
    int winner_number[8];

    for (int k = 0; k < 8; k++) {
        winner_number[k] = k+1;
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < (8 - i - 1); j++) {
            if (win[j] < win[j+1]) {
                swap_player = win[j];
                win[j] = win[j+1];
                win[j+1] = swap_player;
                swap_number = winner_number[j];
                winner_number[j] = winner_number[j+1];
                winner_number[j+1] = swap_number;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        printf("%d %.2f\n", winner_number[i], win[i]);
    }

}
void print_untie_dx(int hand[][2], int hand_value, int player_number, int *players_tied) {

    int print_hand[5][2];

    for (int i = 0; i < 5; i++) {
        if (hand[i][RANK] == 2)
            print_hand[i][RANK] = '2';
        else if (hand[i][RANK] == 3)
            print_hand[i][RANK] = '3';
        else if (hand[i][RANK] == 4)
            print_hand[i][RANK] = '4';
        else if (hand[i][RANK] == 5)
            print_hand[i][RANK] = '5';
        else if (hand[i][RANK] == 6)
            print_hand[i][RANK] = '6';
        else if (hand[i][RANK] == 7)
            print_hand[i][RANK] = '7';
        else if (hand[i][RANK] == 8)
            print_hand[i][RANK] = '8';
        else if (hand[i][RANK] == 9)
            print_hand[i][RANK] = '9';
        else if (hand[i][RANK] == 10)
            print_hand[i][RANK] = 'T';
        else if (hand[i][RANK] == 11)
            print_hand[i][RANK] = 'J';
        else if (hand[i][RANK] == 12)
            print_hand[i][RANK] = 'Q';
        else if (hand[i][RANK] == 13)
            print_hand[i][RANK] = 'K';
        else if (hand[i][RANK] == 14 || hand[i][RANK] == 1)
            print_hand[i][RANK] = 'A';
    }
    for (int i = 0; i < 5; i++) {
        if (hand[i][SUIT] == 1)
            print_hand[i][SUIT] = 'C';
        else if (hand[i][SUIT] == 2)
            print_hand[i][SUIT] = 'E';
        else if (hand[i][SUIT] == 3)
            print_hand[i][SUIT] = 'O';
        else if (hand[i][SUIT] == 4)
            print_hand[i][SUIT] = 'P';
    }
    /* dar print das 5 cartas que constituem a melhor mão */
    for (int i = 0; i < 5; i++) {
        printf("%c%c ", print_hand[i][RANK], print_hand[i][SUIT]);
    }

    printf("%d %d ", hand_value, player_number);
    if (players_tied[1] && player_number != 2)
        printf("2 ");
    if (players_tied[2] && player_number != 3)
        printf("3 ");
    if (players_tied[3] && player_number != 4)
        printf("4 ");
    if (players_tied[4] && player_number != 5)
        printf("5 ");
    if (players_tied[5] && player_number != 6)
        printf("6 ");
    if (players_tied[6] && player_number != 7)
        printf("7 ");
    if (players_tied[7] && player_number != 8)
        printf("8 ");
    printf("\n\n");
}
