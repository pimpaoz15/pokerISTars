#include "PokerISTars.h"

int analyze_di_mode(int argc, char *argv[]) {

    bool royal_flush, straight, flush, four, three;
    int royal_flush_7, straight_flush_7, straight_7, flush_7, four_7, three7, pairs;
    int value_player1 = 0, value_player2 = 0;
    char arr[3];
    int sets_per_deck = 0, cards_per_set = 0, cards_to_skip = 0;
    int n_of_sets = 1;
    int hands_frequency[11], victory[3];
    int len;
    char ex_argv[6], deck[] = ".deck";

    len = strlen(argv[2]);
    if (argc != 3 && argc != 5) {
        printf("-1\n");
        exit(0);
    }
    for (int m = 0; m < 6; m++) {
        ex_argv[m] = argv[2][len + m - 5];
    }
    if (strcmp(ex_argv, deck) != 0) {
        printf("-1\n");
        exit(0);
    }
    if (argc == 5) {
        if (strncmp(argv[3], "-o", 2) != 0) {
            printf("-1\n");
            exit(0);
        }
    }

    for (int l = 0; l < 11; l++)
        hands_frequency[l] = 0;
    for (int n = 0; n < 3; n++)
        victory[n] = 0;

    royal_flush = straight = flush = four = three = false;
    royal_flush_7 = straight_flush_7 = straight_7 = flush_7 = four_7 = three7 = pairs = 0;

    if (strncmp(argv[1], "-d1", 3) == 0) {
        cards_per_set = 5;
        sets_per_deck = 10;
        cards_to_skip = 2;
    }
    else if (strncmp(argv[1], "-d2", 3) == 0) {
        cards_per_set = 7;
        sets_per_deck = 7;
        cards_to_skip = 3;
    }
    else if (strncmp(argv[1], "-d3", 3) == 0) {
        cards_per_set = 9;
        sets_per_deck = 5;
        cards_to_skip = 7;
    }
    else if (strncmp(argv[1], "-d4", 3) == 0) {
        cards_per_set = 10;
        sets_per_deck = 5;
        cards_to_skip = 2;
    }

    int hand[cards_per_set][2];

    FILE *fp, *print_file;
    fp = fopen(argv[2], "r");

    while (1) {
        if (feof(fp))
            break;
        for (int k = 0; k < sets_per_deck; k++) {
            for (int i = 0; i < cards_per_set; i++) {
                fscanf(fp, " %s", arr);
                hand[i][RANK] = arr[0];
                hand[i][SUIT] = arr[1];
            }
            if (feof(fp))
                break;
            if (k == sets_per_deck - 1) {
                for (int j = 0; j < cards_to_skip; j++) {
                    fscanf(fp, " %s", arr);
                }
            }

            convert_input(cards_per_set, argv, hand);

            if (card_exists(hand, cards_per_set) == 0 && cards_per_set != 10) {
                if (argc == 3) {
                    if (cards_per_set == 5) {
                        analyze_hand_5(hand, cards_per_set, &royal_flush, &straight, &flush, &four, &three, &pairs);
                        print_result_stdout(royal_flush, straight, flush, four, three, pairs, hands_frequency);
                        if (n_of_sets % 10 == 0)
                            printf("\n");
                    }
                    else if (cards_per_set == 7) {
                        analyze_hand_7(hand, cards_per_set, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs);
                        print_result_7_stdout(hand, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs, hands_frequency);
                        printf("\n");
                        if (n_of_sets % 7 == 0)
                            printf("\n");
                    }
                    else if (cards_per_set == 9) {
                        analyze_hand_9_di(hand, cards_per_set, argc, argv, &royal_flush_7, &straight_flush_7,
                                          &straight_7, &flush_7, &four_7, &three7, &pairs, &value_player1,
                                          &value_player2, hands_frequency, victory);
                        if (n_of_sets % 5 == 0)
                            printf("\n");
                    }
                }
                else if (argc == 5) {
                    if (cards_per_set == 5) {
                        analyze_hand_5(hand, cards_per_set, &royal_flush, &straight, &flush, &four, &three, &pairs);
                        print_result_file(royal_flush, straight, flush, four, three, pairs, argv, hands_frequency);
                        if (n_of_sets % 10 == 0) {
                            print_file = fopen(argv[4], "a");
                            fprintf(print_file, "\n");
                            fclose(print_file);
                        }
                    }
                    else if (cards_per_set == 7) {
                        analyze_hand_7(hand, cards_per_set, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs);
                        print_result_7_file(hand, &royal_flush_7, &straight_flush_7, &straight_7, &flush_7, &four_7, &three7, &pairs, argv, hands_frequency);

                        print_file = fopen(argv[4], "a");
                        fprintf(print_file, "\n");
                        fclose(print_file);

                        if (n_of_sets % 7 == 0) {
                            print_file = fopen(argv[4], "a");
                            fprintf(print_file, "\n");
                            fclose(print_file);
                        }
                    }
                    else if (cards_per_set == 9) {
                        analyze_hand_9_di(hand, cards_per_set, argc, argv, &royal_flush_7, &straight_flush_7,
                                          &straight_7, &flush_7, &four_7, &three7, &pairs, &value_player1,
                                          &value_player2, hands_frequency, victory);
                        if (n_of_sets % 5 == 0) {
                            print_file = fopen(argv[4], "a");
                            fprintf(print_file, "\n");
                            fclose(print_file);
                        }
                    }
                }
            }
            else if (cards_per_set == 10) {
                analyze_hand_10_di(hand, argc, argv, &royal_flush, &straight, &flush, &four, &three, &pairs, &value_player1, &value_player2, hands_frequency, victory);
                if (n_of_sets % 5 == 0) {
                    if (argc == 3)
                        printf("\n");
                    else {
                        print_file = fopen(argv[4], "a");
                        fprintf(print_file, "\n");
                        fclose(print_file);
                    }
                }
            }
            else {
                if (argc == 3)
                    printf("-1\n");
                else {
                    print_file = fopen(argv[4], "a");
                    fprintf(print_file, "-1\n");
                    if (cards_per_set == 5) {
                        if (n_of_sets % 10 == 0)
                            fprintf(print_file, "\n");
                    }
                    else if (cards_per_set == 7) {
                        if (n_of_sets % 7 == 0)
                            fprintf(print_file, "\n");
                    }
                    else if (cards_per_set == 9) {
                        if (n_of_sets % 5 == 0)
                            fprintf(print_file, "\n");
                    }
                    fclose(print_file);
                }
                if (cards_per_set == 5 || cards_per_set == 7)
                    hands_frequency[0]++;
                else if (cards_per_set == 9)
                    hands_frequency[0] += 2;
                victory[0]++;
            }
            n_of_sets++;
        }
    }

    if (argc == 3)
        print_stats_stdout(hands_frequency, victory, n_of_sets, cards_per_set);
    else
        print_stats_file(argv, hands_frequency, victory, n_of_sets, cards_per_set);

    fclose(fp);
    return 0;
}