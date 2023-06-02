#include "PokerISTars.h"

int analyze_c_mode (int argc, char *argv[]) {

    bool royal_flush, straight, flush, four, three;
    int royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs;
    int value_player1 = 0, value_player2 = 0;
    int n_of_cards = analyze_input(argc, argv);
    int hand[n_of_cards][2];

    royal_flush = straight = flush = four = three = false;
    royal_flush_7 = straight_flush_7 = straight_7 = flush_7 = four_7 = three7 = pairs = 0;

    if (n_of_cards == 5) { // jogo de 5 cartas
        convert_input(n_of_cards, argv, hand);
        if (card_exists(hand, n_of_cards)) {
            printf("-1\n");
            exit(0);
        }
        analyze_hand_5(hand, n_of_cards, &royal_flush, &straight, &flush, &four, &three, &pairs);
        print_result_c(royal_flush, straight, flush, four, three, pairs);

    } else if (n_of_cards == 7) { // jogo de 7 cartas
        convert_input(n_of_cards, argv, hand);
        if (card_exists(hand, n_of_cards)) {
            printf("-1\n");
            exit(0);
        }
        analyze_hand_7(hand, n_of_cards, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs);
        print_result_7_c(hand, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs);
        printf("\n");

    } else if (n_of_cards == 9) { // jogo de 9 cartas
        convert_input(n_of_cards, argv, hand);
        if (card_exists(hand, n_of_cards)) {
            printf("-1\n");
            exit(0);
        }
        analyze_hand_9_c(argc, hand, n_of_cards, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs, &value_player1, &value_player2);

    } else if (n_of_cards == 10) { // jogo de 10 cartas
        convert_input(n_of_cards, argv, hand);
        analyze_hand_10_c(hand, &royal_flush, &straight, &flush, &four, &three, &pairs, &value_player1, &value_player2);
    }
    return 0;
}