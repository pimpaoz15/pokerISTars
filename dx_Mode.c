#include "PokerISTars.h"

void analyze_dx_mode(int argc, char *argv[]) {

    player player1, player2, player3, player4, player5, player6, player7, player8;
    char arr[3];
    int table_hand[5][2];
    int n_of_cards = 7;
    int active_players = 0, decks_read = 0, cards_read = 0, cards_to_skip = 52;
    int hands_frequency[11];
    int winner[8];
    double win[8];
    check_winner *list_head = NULL;
    int n_of_players_tied, players_tied[8];

    for (int m = 0; m < 8; m++) {
        win[m] = 0;
    }
    for (int j = 0; j < 11; j++) {
        hands_frequency[j] = 0;
    }

    player1.rounds_played = player2.rounds_played = player3.rounds_played = player4.rounds_played = 0;
    player5.rounds_played = player6.rounds_played = player7.rounds_played = player8.rounds_played = 0;

    player1.fold = player2.fold = player3.fold = player4.fold = player5.fold = player6.fold = player7.fold = player8.fold = 0;

    player1.inactive = player2.inactive = player3.inactive = player4.inactive = 0;
    player5.inactive = player6.inactive = player7.inactive = player8.inactive = 0;

    int *hand_pointer, *aux_hand_pointer;

    FILE *fp;
    fp = fopen(argv[2], "r");

    while (1) {

        player1.royal_flush = player1.straight_flush = player1.flush = player1.straight = player1.four = player1.three = player1.pairs = 0;
        player2.royal_flush = player2.straight_flush = player2.flush = player2.straight = player2.four = player2.three = player2.pairs = 0;
        player3.royal_flush = player3.straight_flush = player3.flush = player3.straight = player3.four = player3.three = player3.pairs = 0;
        player4.royal_flush = player4.straight_flush = player4.flush = player4.straight = player4.four = player4.three = player4.pairs = 0;
        player5.royal_flush = player5.straight_flush = player5.flush = player5.straight = player5.four = player5.three = player5.pairs = 0;
        player6.royal_flush = player6.straight_flush = player6.flush = player6.straight = player6.four = player6.three = player6.pairs = 0;
        player7.royal_flush = player7.straight_flush = player7.flush = player7.straight = player7.four = player7.three = player7.pairs = 0;
        player8.royal_flush = player8.straight_flush = player8.flush = player8.straight = player8.four = player8.three = player8.pairs = 0;

        player1.hand_value = player2.hand_value = player3.hand_value = player4.hand_value = 0;
        player5.hand_value = player6.hand_value = player7.hand_value = player8.hand_value = 0;

        if (feof(fp))
            break;
        if (player1.rounds_played == 2)
            player1.inactive = 1;
        if (player2.rounds_played == 2)
            player2.inactive = 1;
        if (player3.rounds_played == 2)
            player3.inactive = 1;
        if (player4.rounds_played == 2)
            player4.inactive = 1;
        if (player5.rounds_played == 2)
            player5.inactive = 1;
        if (player6.rounds_played == 2)
            player6.inactive = 1;
        if (player7.rounds_played == 2)
            player7.inactive = 1;
        if (player8.rounds_played == 2)
            player8.inactive = 1;

        if (!player1.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player1.hand[i][RANK] = arr[0];
                player1.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (feof(fp))
            break;
        if (!player2.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player2.hand[i][RANK] = arr[0];
                player2.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player3.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player3.hand[i][RANK] = arr[0];
                player3.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player4.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player4.hand[i][RANK] = arr[0];
                player4.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player5.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player5.hand[i][RANK] = arr[0];
                player5.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player6.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player6.hand[i][RANK] = arr[0];
                player6.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player7.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player7.hand[i][RANK] = arr[0];
                player7.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }
        if (!player8.inactive) {
            for (int i = 0; i < 2; i++) {
                fscanf(fp, " %s", arr);
                player8.hand[i][RANK] = arr[0];
                player8.hand[i][SUIT] = arr[1];
            }
            cards_read += 2;
        }

        if (cards_read != 0) {
            for (int i = 0; i < 5; i++) {
                fscanf(fp, " %s", arr);
                table_hand[i][RANK] = arr[0];
                table_hand[i][SUIT] = arr[1];
            }
            cards_read += 5;
        }
        cards_to_skip = cards_to_skip - cards_read;

        if (!player1.inactive) {
            for (int i = 0; i < 5; i++) {
                player1.hand[i + 2][RANK] = table_hand[i][RANK];
                player1.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player1.hand);
            analyze_hand_7(player1.hand, n_of_cards, &player1.royal_flush, &player1.straight_flush, &player1.straight,
                           &player1.flush, &player1.four, &player1.three, &player1.pairs);
            if (player1.royal_flush)
                player1.hand_value = 10;
            else if (player1.straight_flush)
                player1.hand_value = 9;
            else if (player1.four)
                player1.hand_value = 8;
            else if ((player1.three == 1 && player1.pairs == 1) || (player1.three == 1 && player1.pairs == 2) ||
                     (player1.three == 2))
                player1.hand_value = 7;
            else if (player1.flush)
                player1.hand_value = 6;
            else if (player1.straight)
                player1.hand_value = 5;
            else if (player1.three == 1)
                player1.hand_value = 4;
            else if (player1.pairs == 2 || player1.pairs == 3)
                player1.hand_value = 3;
            else if (player1.pairs == 1)
                player1.hand_value = 2;
            else
                player1.hand_value = 1;

            if (player1.hand_value >= 1 || player1.fold == 4) {
                player1.rounds_played++;
                player1.fold = 0;
                active_players++;
                printf("1 ");
                print_result_7_c(player1.hand, &player1.royal_flush, &player1.straight_flush, &player1.straight,
                                 &player1.flush, &player1.four, &player1.three, &player1.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player1.hand, &player1.royal_flush, &player1.straight_flush,
                                                 &player1.straight, &player1.flush, &player1.four, &player1.three,
                                                 &player1.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player1.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player1.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(1, player1.hand_value, player1.untie_hand));
            } else {
                player1.fold++;
                player1.rounds_played = 0;
            }
        }
        if (!player2.inactive) {
            for (int i = 0; i < 5; i++) {
                player2.hand[i + 2][RANK] = table_hand[i][RANK];
                player2.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player2.hand);
            analyze_hand_7(player2.hand, n_of_cards, &player2.royal_flush, &player2.straight_flush, &player2.straight,
                           &player2.flush, &player2.four, &player2.three, &player2.pairs);
            if (player2.royal_flush)
                player2.hand_value = 10;
            else if (player2.straight_flush)
                player2.hand_value = 9;
            else if (player2.four)
                player2.hand_value = 8;
            else if ((player2.three == 1 && player2.pairs == 1) || (player2.three == 1 && player2.pairs == 2) ||
                     (player2.three == 2))
                player2.hand_value = 7;
            else if (player2.flush)
                player2.hand_value = 6;
            else if (player2.straight)
                player2.hand_value = 5;
            else if (player2.three == 1)
                player2.hand_value = 4;
            else if (player2.pairs == 2 || player2.pairs == 3)
                player2.hand_value = 3;
            else if (player2.pairs == 1)
                player2.hand_value = 2;
            else
                player2.hand_value = 1;

            if (player2.hand_value >= 2 || player2.fold == 4) {
                player2.rounds_played++;
                player2.fold = 0;
                active_players++;
                printf("2 ");
                print_result_7_c(player2.hand, &player2.royal_flush, &player2.straight_flush, &player2.straight,
                                 &player2.flush, &player2.four, &player2.three, &player2.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player2.hand, &player2.royal_flush, &player2.straight_flush,
                                                 &player2.straight, &player2.flush, &player2.four, &player2.three,
                                                 &player2.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player2.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player2.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(2, player2.hand_value, player2.untie_hand));
            } else {
                player2.fold++;
                player2.rounds_played = 0;
            }
        }
        if (!player3.inactive) {
            for (int i = 0; i < 5; i++) {
                player3.hand[i + 2][RANK] = table_hand[i][RANK];
                player3.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player3.hand);
            analyze_hand_7(player3.hand, n_of_cards, &player3.royal_flush, &player3.straight_flush, &player3.straight,
                           &player3.flush, &player3.four, &player3.three, &player3.pairs);
            if (player3.royal_flush)
                player3.hand_value = 10;
            else if (player3.straight_flush)
                player3.hand_value = 9;
            else if (player3.four)
                player3.hand_value = 8;
            else if ((player3.three == 1 && player3.pairs == 1) || (player3.three == 1 && player3.pairs == 2) ||
                     (player3.three == 2))
                player3.hand_value = 7;
            else if (player3.flush)
                player3.hand_value = 6;
            else if (player3.straight)
                player3.hand_value = 5;
            else if (player3.three == 1)
                player3.hand_value = 4;
            else if (player3.pairs == 2 || player3.pairs == 3)
                player3.hand_value = 3;
            else if (player3.pairs == 1)
                player3.hand_value = 2;
            else
                player3.hand_value = 1;

            if (player3.hand_value >= 3 || player3.fold == 4) {
                player3.rounds_played++;
                player3.fold = 0;
                active_players++;
                printf("3 ");
                print_result_7_c(player3.hand, &player3.royal_flush, &player3.straight_flush, &player3.straight,
                                 &player3.flush, &player3.four, &player3.three, &player3.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player3.hand, &player3.royal_flush, &player3.straight_flush,
                                                 &player3.straight, &player3.flush, &player3.four, &player3.three,
                                                 &player3.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player3.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player3.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(3, player3.hand_value, player3.untie_hand));
            } else {
                player3.fold++;
                player3.rounds_played = 0;
            }
        }
        if (!player4.inactive) {
            for (int i = 0; i < 5; i++) {
                player4.hand[i + 2][RANK] = table_hand[i][RANK];
                player4.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player4.hand);
            analyze_hand_7(player4.hand, n_of_cards, &player4.royal_flush, &player4.straight_flush, &player4.straight,
                           &player4.flush, &player4.four, &player4.three, &player4.pairs);
            if (player4.royal_flush)
                player4.hand_value = 10;
            else if (player4.straight_flush)
                player4.hand_value = 9;
            else if (player4.four)
                player4.hand_value = 8;
            else if ((player4.three == 1 && player4.pairs == 1) || (player4.three == 1 && player4.pairs == 2) ||
                     (player4.three == 2))
                player4.hand_value = 7;
            else if (player4.flush)
                player4.hand_value = 6;
            else if (player4.straight)
                player4.hand_value = 5;
            else if (player4.three == 1)
                player4.hand_value = 4;
            else if (player4.pairs == 2 || player4.pairs == 3)
                player4.hand_value = 3;
            else if (player4.pairs == 1)
                player4.hand_value = 2;
            else
                player4.hand_value = 1;

            if (player4.hand_value >= 4 || player4.fold == 4) {
                player4.rounds_played++;
                player4.fold = 0;
                active_players++;
                printf("4 ");
                print_result_7_c(player4.hand, &player4.royal_flush, &player4.straight_flush, &player4.straight,
                                 &player4.flush, &player4.four, &player4.three, &player4.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player4.hand, &player4.royal_flush, &player4.straight_flush,
                                                 &player4.straight, &player4.flush, &player4.four, &player4.three,
                                                 &player4.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player4.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player4.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(4, player4.hand_value, player4.untie_hand));
            } else {
                player4.fold++;
                player4.rounds_played = 0;
            }
        }
        if (!player5.inactive) {
            for (int i = 0; i < 5; i++) {
                player5.hand[i + 2][RANK] = table_hand[i][RANK];
                player5.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player5.hand);
            analyze_hand_7(player5.hand, n_of_cards, &player5.royal_flush, &player5.straight_flush, &player5.straight,
                           &player5.flush, &player5.four, &player5.three, &player5.pairs);
            if (player5.royal_flush)
                player5.hand_value = 10;
            else if (player5.straight_flush)
                player5.hand_value = 9;
            else if (player5.four)
                player5.hand_value = 8;
            else if ((player5.three == 1 && player5.pairs == 1) || (player5.three == 1 && player5.pairs == 2) ||
                     (player5.three == 2))
                player5.hand_value = 7;
            else if (player5.flush)
                player5.hand_value = 6;
            else if (player5.straight)
                player5.hand_value = 5;
            else if (player5.three == 1)
                player5.hand_value = 4;
            else if (player5.pairs == 2 || player5.pairs == 3)
                player5.hand_value = 3;
            else if (player5.pairs == 1)
                player5.hand_value = 2;
            else
                player5.hand_value = 1;

            if (player5.hand_value >= 5 || player5.fold == 4) {
                player5.rounds_played++;
                player5.fold = 0;
                active_players++;
                printf("5 ");
                print_result_7_c(player5.hand, &player5.royal_flush, &player5.straight_flush, &player5.straight,
                                 &player5.flush, &player5.four, &player5.three, &player5.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player5.hand, &player5.royal_flush, &player5.straight_flush,
                                                 &player5.straight, &player5.flush, &player5.four, &player5.three,
                                                 &player5.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player5.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player5.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(5, player5.hand_value, player5.untie_hand));
            } else {
                player5.fold++;
                player5.rounds_played = 0;
            }
        }
        if (!player6.inactive) {
            for (int i = 0; i < 5; i++) {
                player6.hand[i + 2][RANK] = table_hand[i][RANK];
                player6.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player6.hand);
            analyze_hand_7(player6.hand, n_of_cards, &player6.royal_flush, &player6.straight_flush, &player6.straight,
                           &player6.flush, &player6.four, &player6.three, &player6.pairs);
            if (player6.royal_flush)
                player6.hand_value = 10;
            else if (player6.straight_flush)
                player6.hand_value = 9;
            else if (player6.four)
                player6.hand_value = 8;
            else if ((player6.three == 1 && player6.pairs == 1) || (player6.three == 1 && player6.pairs == 2) ||
                     (player6.three == 2))
                player6.hand_value = 7;
            else if (player6.flush)
                player6.hand_value = 6;
            else if (player6.straight)
                player6.hand_value = 5;
            else if (player6.three == 1)
                player6.hand_value = 4;
            else if (player6.pairs == 2 || player6.pairs == 3)
                player6.hand_value = 3;
            else if (player6.pairs == 1)
                player6.hand_value = 2;
            else
                player6.hand_value = 1;

            if (player6.hand_value >= 6 || player6.fold == 4) {
                player6.rounds_played++;
                player6.fold = 0;
                active_players++;
                printf("6 ");
                print_result_7_c(player6.hand, &player6.royal_flush, &player6.straight_flush, &player6.straight,
                                 &player6.flush, &player6.four, &player6.three, &player6.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player6.hand, &player6.royal_flush, &player6.straight_flush,
                                                 &player6.straight, &player6.flush, &player6.four, &player6.three,
                                                 &player6.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player6.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player6.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(6, player6.hand_value, player6.untie_hand));
            } else {
                player6.fold++;
                player6.rounds_played = 0;
            }
        }
        if (!player7.inactive) {
            for (int i = 0; i < 5; i++) {
                player7.hand[i + 2][RANK] = table_hand[i][RANK];
                player7.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player7.hand);
            analyze_hand_7(player7.hand, n_of_cards, &player7.royal_flush, &player7.straight_flush, &player7.straight,
                           &player7.flush, &player7.four, &player7.three, &player7.pairs);
            if (player7.royal_flush)
                player7.hand_value = 10;
            else if (player7.straight_flush)
                player7.hand_value = 9;
            else if (player7.four)
                player7.hand_value = 8;
            else if ((player7.three == 1 && player7.pairs == 1) || (player7.three == 1 && player7.pairs == 2) ||
                     (player7.three == 2))
                player7.hand_value = 7;
            else if (player7.flush)
                player7.hand_value = 6;
            else if (player7.straight)
                player7.hand_value = 5;
            else if (player7.three == 1)
                player7.hand_value = 4;
            else if (player7.pairs == 2 || player7.pairs == 3)
                player7.hand_value = 3;
            else if (player7.pairs == 1)
                player7.hand_value = 2;
            else
                player7.hand_value = 1;

            if (player7.hand_value >= 7 || player7.fold == 4) {
                player7.rounds_played++;
                player7.fold = 0;
                active_players++;
                printf("7 ");
                print_result_7_c(player7.hand, &player7.royal_flush, &player7.straight_flush, &player7.straight,
                                 &player7.flush, &player7.four, &player7.three, &player7.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player7.hand, &player7.royal_flush, &player7.straight_flush,
                                                 &player7.straight, &player7.flush, &player7.four, &player7.three,
                                                 &player7.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player7.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player7.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(7, player7.hand_value, player7.untie_hand));
            } else {
                player7.fold++;
                player7.rounds_played = 0;
            }
        }
        if (!player8.inactive) {
            for (int i = 0; i < 5; i++) {
                player8.hand[i + 2][RANK] = table_hand[i][RANK];
                player8.hand[i + 2][SUIT] = table_hand[i][SUIT];
            }
            convert_input(n_of_cards, argv, player8.hand);
            analyze_hand_7(player8.hand, n_of_cards, &player8.royal_flush, &player8.straight_flush, &player8.straight,
                           &player8.flush, &player8.four, &player8.three, &player8.pairs);
            if (player8.royal_flush)
                player8.hand_value = 10;
            else if (player8.straight_flush)
                player8.hand_value = 9;
            else if (player8.four)
                player8.hand_value = 8;
            else if ((player8.three == 1 && player8.pairs == 1) || (player8.three == 1 && player8.pairs == 2) ||
                     (player8.three == 2))
                player8.hand_value = 7;
            else if (player8.flush)
                player8.hand_value = 6;
            else if (player8.straight)
                player8.hand_value = 5;
            else if (player8.three == 1)
                player8.hand_value = 4;
            else if (player8.pairs == 2 || player8.pairs == 3)
                player8.hand_value = 3;
            else if (player8.pairs == 1)
                player8.hand_value = 2;
            else
                player8.hand_value = 1;

            if (player8.hand_value >= 8 || player8.fold == 4) {
                player8.rounds_played++;
                player8.fold = 0;
                active_players++;
                printf("8 ");
                print_result_7_c(player8.hand, &player8.royal_flush, &player8.straight_flush, &player8.straight,
                                 &player8.flush, &player8.four, &player8.three, &player8.pairs);
                printf("\n");
                hand_pointer = choose_5_out_of_7(player8.hand, &player8.royal_flush, &player8.straight_flush,
                                                 &player8.straight, &player8.flush, &player8.four, &player8.three,
                                                 &player8.pairs);
                aux_hand_pointer = hand_pointer;
                for (int i = 0; i < 5; i++) {
                    player8.untie_hand[i][RANK] = *(aux_hand_pointer + 2 * i);
                    player8.untie_hand[i][SUIT] = *(aux_hand_pointer + 2 * i + 1);
                }
                list_head = insert_player_end(list_head, create_player(8, player8.hand_value, player8.untie_hand));
            } else {
                player8.fold++;
                player8.rounds_played = 0;
            }
        }

        if (active_players != 0) {
            for (int l = 0; l < 8; l++) {
                players_tied[l] = 0;
            }
            for (int k = 0; k < 8; k++) {
                winner[k] = 0;
            }
            decks_read++;
            bubble_sort(list_head);
            printf("W ");
            n_of_players_tied = count(list_head, list_head->value_player_number);
            check_winner *winner_after_untie = untie_dx(list_head, n_of_players_tied, players_tied);
            hands_frequency[winner_after_untie->value_player_number]++;
            winner[(winner_after_untie->player_number) - 1]++;
            print_untie_dx(winner_after_untie->player_hand, winner_after_untie->value_player_number,
                           winner_after_untie->player_number, players_tied);
            counnt_stats_dx(winner, players_tied, win);
        }
        for (int i = 0; i < cards_to_skip; i++) {
            fscanf(fp, " %s", arr);
        }

        if (player1.inactive)
            player1.inactive = 0;
        if (player2.inactive)
            player2.inactive = 0;
        if (player3.inactive)
            player3.inactive = 0;
        if (player4.inactive)
            player4.inactive = 0;
        if (player5.inactive)
            player5.inactive = 0;
        if (player6.inactive)
            player6.inactive = 0;
        if (player7.inactive)
            player7.inactive = 0;
        if (player8.inactive)
            player8.inactive = 0;

        free_list_dx(list_head);

        if (feof(fp))
            break;
    }

    fclose(fp);
    printf("\n");
    print_stats_stdout_dx(hands_frequency, decks_read);
    printf("\n");
    print_winners_dx(win);

}

check_winner *create_player(int player_nbr, int value_player_nbr, int hand[][2]) {

    check_winner *new_player;
    if ((new_player = (check_winner *) malloc(sizeof(check_winner))) == NULL) {
        printf("Error: unable to allocate memory block.\n");
        exit(EXIT_FAILURE);
    }

    new_player -> player_number = player_nbr;
    new_player -> value_player_number = value_player_nbr;
    for (int i = 0; i < 5; i++) {
        new_player -> player_hand[i][RANK] = hand[i][RANK];
        new_player -> player_hand[i][SUIT] = hand[i][SUIT];
    }
    new_player -> next = NULL;

    return new_player;
}
check_winner *insert_player_end(check_winner *list_head, check_winner *new_player) {

    if (list_head == NULL)
        return new_player;

    check_winner *aux = list_head;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new_player;

    return list_head;
}
void bubble_sort(check_winner *list_head) {

    int swapped;
    if (list_head == NULL)
        return;
    check_winner *lptr = NULL;
    do {
        swapped = 0;
        check_winner *ptr1 = list_head;

        while (ptr1->next != lptr) {
            if (ptr1->value_player_number < ptr1->next->value_player_number) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void swap(check_winner *a, check_winner *b) {
    int temp = a->player_number;
    int aux = a->value_player_number;
    int aux_hand[5][2];
    for (int i = 0; i < 5; i++) {
        aux_hand[i][RANK] = a->player_hand[i][RANK];
        aux_hand[i][SUIT] = a->player_hand[i][SUIT];
    }
    a->player_number = b->player_number;
    b->player_number = temp;
    a->value_player_number = b->value_player_number;
    b->value_player_number = aux;
    for (int i = 0; i < 5; i++) {
        a->player_hand[i][RANK] = b->player_hand[i][RANK];
        a->player_hand[i][SUIT] = b->player_hand[i][SUIT];
    }
    for (int i = 0; i < 5; i++) {
        b->player_hand[i][RANK] = aux_hand[i][RANK];
        b->player_hand[i][SUIT] = aux_hand[i][SUIT];
    }
}
int count(check_winner *list_head, int search_for) {

    check_winner *current = list_head;
    int count = 0;
    while (current != NULL) {
        if (current->value_player_number == search_for)
            count++;
        current = current->next;
    }
    return count;
}
void free_list_dx(check_winner *list_head) {
    while (list_head != NULL) {
        check_winner *aux = list_head;
        list_head = list_head->next;
        free(aux);
    }
}
void counnt_stats_dx(int *winner, int *players_tied, double *win) {

    int n_of_players_tied = 0;

    if (players_tied[0])
        n_of_players_tied++;
    if (players_tied[1]) {
        n_of_players_tied++;
        winner[1]++;
    }
    if (players_tied[2]) {
        n_of_players_tied++;
        winner[2]++;
    }
    if (players_tied[3]) {
        n_of_players_tied++;
        winner[3]++;
    }
    if (players_tied[4]) {
        n_of_players_tied++;
        winner[4]++;
    }
    if (players_tied[5]) {
        n_of_players_tied++;
        winner[5]++;
    }
    if (players_tied[6]) {
        n_of_players_tied++;
        winner[6]++;
    }
    if (players_tied[7]) {
        n_of_players_tied++;
        winner[7]++;
    }

    if (n_of_players_tied == 0)
        n_of_players_tied = 1;

    win[0] += (double) winner[0]/n_of_players_tied;
    win[1] += (double) winner[1]/n_of_players_tied;
    win[2] += (double) winner[2]/n_of_players_tied;
    win[3] += (double) winner[3]/n_of_players_tied;
    win[4] += (double) winner[4]/n_of_players_tied;
    win[5] += (double) winner[5]/n_of_players_tied;
    win[6] += (double) winner[6]/n_of_players_tied;
    win[7] += (double) winner[7]/n_of_players_tied;
}