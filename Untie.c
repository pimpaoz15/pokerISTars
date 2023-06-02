#include "PokerISTars.h"

/* função que desempata, no caso de os dois jogador terem uma mão com o mesmo valor */
int untie(int player1[][2], int player2[][2], int value_player1) {

    int three1 = 0, three2 = 0, two1 = 0, two2 = 0;
    int pair11 = 0, pair12 = 0, pair21 = 0, pair22 = 0;
    int sum_player1, sum_player2;

    sum_player1 = player1[0][RANK] + player1[1][RANK] + player1[2][RANK] + player1[3][RANK] + player1[4][RANK];
    sum_player2 = player2[0][RANK] + player2[1][RANK] + player2[2][RANK] + player2[3][RANK] + player2[4][RANK];

    if (value_player1 == 1) {   // HIGH CARD
        for (int i = 0; i < 5; i++) {
            if (player1[i][RANK] > player2[i][RANK])
                return 1;
            else if (player1[i][RANK] < player2[i][RANK])
                return 2;
        }
        return 0;
    }
    else if (value_player1 == 2) {    // PAIR
        if (player1[0][RANK] == player1[1][RANK])
            two1 = player1[0][RANK];
        else if (player1[1][RANK] == player1[2][RANK])
            two1 = player1[1][RANK];
        else if (player1[2][RANK] == player1[3][RANK])
            two1 = player1[2][RANK];
        else // if (player1[3][RANK] == player1[4][RANK])
            two1 = player1[3][RANK];
        if (player2[0][RANK] == player2[1][RANK])
            two2 = player2[0][RANK];
        else if (player2[1][RANK] == player2[2][RANK])
            two2 = player2[1][RANK];
        else if (player2[2][RANK] == player2[3][RANK])
            two2 = player2[2][RANK];
        else // if (player2[3][RANK] == player2[4][RANK])
            two2 = player2[3][RANK];

        if (two1 > two2)
            return 1;
        else if (two1 < two2)
            return 2;
        else { // if (two1 == two2)
            for (int i = 0; i < 5; i++) {
                if (player1[i][RANK] > player2[i][RANK])
                    return 1;
                if (player1[i][RANK] < player2[i][RANK])
                    return 2;
            }
            return 0;
        }
    }
    else if (value_player1 == 3) {   // TWO PAIR
        if (player1[0][RANK] == player1[1][RANK]) {
            pair11 = player1[0][RANK];
            if (player1[2][RANK] == player1[3][RANK])
                pair12 = player1[2][RANK];
            else // if (player1[3][RANK] == player1[4][RANK])
                pair12 = player1[3][RANK];
        } else { // if (player1[1][RANK] == player1[2][RANK]) {
            pair11 = player1[1][RANK];
            pair12 = player1[3][RANK];
        }

        if (player2[0][RANK] == player2[1][RANK]) {
            pair21 = player2[0][RANK];
            if (player2[2][RANK] == player2[3][RANK])
                pair22 = player2[2][RANK];
            else if (player2[3][RANK] == player2[4][RANK])
                pair22 = player2[3][RANK];
            else
                return 0;
        } else if (player2[1][RANK] == player2[2][RANK]) {
            pair21 = player2[1][RANK];
            pair22 = player2[3][RANK];
        } else
            return 0;
        if (pair11 > pair21)
            return 1;
        else if (pair11 < pair21)
            return 2;
        else {
            if (pair12 > pair22)
                return 1;
            else if (pair12 < pair22)
                return 2;
            else {
                if (sum_player1 > sum_player2)
                    return 1;
                else if (sum_player1 < sum_player2)
                    return 2;
                else
                    return 0;
            }
        }
    }
    else if (value_player1 == 4) {   // THREE OF A KIND
        if (player1[0][RANK] == player1[1][RANK] && player1[1][RANK] == player1[2][RANK])
            three1 = player1[0][RANK];
        else if (player1[1][RANK] == player1[2][RANK] && player1[2][RANK] == player1[3][RANK])
            three1 = player1[1][RANK];
        else if (player1[2][RANK] == player1[3][RANK] && player1[3][RANK] == player1[4][RANK])
            three1 = player1[2][RANK];
        if (player2[0][RANK] == player2[1][RANK] && player2[1][RANK] == player2[2][RANK])
            three2 = player2[0][RANK];
        else if (player2[1][RANK] == player2[2][RANK] && player2[2][RANK] == player2[3][RANK])
            three2 = player2[1][RANK];
        else if (player2[2][RANK] == player2[3][RANK] && player2[3][RANK] == player2[4][RANK])
            three2 = player2[2][RANK];
        else
            return 0;

        if (three1 > three2)
            return 1;
        else if (three1 < three2)
            return 2;
        else if (three1 == three2) {
            for (int i = 0; i < 5; i++) {
                if (player1[i][RANK] > player2[i][RANK])
                    return 1;
                if (player1[i][RANK] < player2[i][RANK])
                    return 2;
            }
            return 0;
        }
        else
            return 0;
    }
    else if (value_player1 == 5) {   // STRAIGHT
        if (player1[0][RANK] > player2[0][RANK])
            return 1;
        else if (player1[0][RANK] < player2[0][RANK])
            return 2;
        else
            return 0;
    }
    else if (value_player1 == 6) {   // FLUSH
        for (int i = 0; i < 5; i++) {
            if (player1[i][RANK] > player2[i][RANK])
                return 1;
            else if (player1[i][RANK] < player2[i][RANK])
                return 2;
        }
        return 0;
    }
    else if (value_player1 == 7) {   // FULL HOUSE
        if ((player1[0][RANK] == player1[1][RANK] && player1[1][RANK] == player1[2][RANK]) &&
            (player2[0][RANK] == player2[1][RANK] && player2[1][RANK] == player2[2][RANK])) {
            if (player1[0][RANK] > player2[0][RANK])
                return 1;
            else if (player1[0][RANK] < player2[0][RANK])
                return 2;
            else if (player1[0][RANK] == player2[0][RANK]) {
                if ((player1[3][RANK] > player2[3][RANK]))
                    return 1;
                else if ((player1[3][RANK] < player2[3][RANK]))
                    return 2;
                else
                    return 0;
            }
        }
        if ((player1[0][RANK] == player1[1][RANK] && player1[1][RANK] == player1[2][RANK]) &&
            (player2[2][RANK] == player2[3][RANK] && player2[3][RANK] == player2[4][RANK])) {
            if (player1[0][RANK] > player2[2][RANK])
                return 1;
            else if (player1[0][RANK] < player2[2][RANK])
                return 2;
            else
                return 2;
        }
        if ((player1[2][RANK] == player1[3][RANK] && player1[3][RANK] == player1[4][RANK]) &&
            (player2[0][RANK] == player2[1][RANK] && player2[1][RANK] == player2[2][RANK])) {
            if (player1[2][RANK] > player2[0][RANK])
                return 1;
            else if (player1[2][RANK] < player2[0][RANK])
                return 2;
            else
                return 1;
        }
        if ((player1[2][RANK] == player1[3][RANK] && player1[3][RANK] == player1[4][RANK]) &&
            (player2[2][RANK] == player2[3][RANK] && player2[3][RANK] == player2[4][RANK])) {
            if (player1[2][RANK] > player2[2][RANK])
                return 1;
            else if (player1[2][RANK] < player2[2][RANK])
                return 2;
            else if (player1[2][RANK] == player2[2][RANK]) {
                if ((player1[0][RANK] > player2[0][RANK]))
                    return 1;
                else if ((player1[0][RANK] < player2[0][RANK]))
                    return 2;
                else
                    return 0;
            }
        }
    }
    else if (value_player1 == 8) {   // FOUR OF A KIND
        if (player1[0][RANK] == player1[1][RANK] && player2[0][RANK] == player2[1][RANK]) {
            if (player1[0][RANK] > player2[0][RANK])
                return 1;
            else if (player1[0][RANK] < player2[0][RANK])
                return 2;
            else if (player1[0][RANK] == player2[0][RANK]) {
                if (player1[4][RANK] > player2[4][RANK])
                    return 1;
                else if (player1[4][RANK] < player2[4][RANK])
                    return 2;
                else
                    return 0;
            }
        }
        if (player1[0][RANK] == player1[1][RANK] && player2[1][RANK] == player2[2][RANK]) {
            if (player1[0][RANK] > player2[1][RANK])
                return 1;
            else if (player1[0][RANK] < player2[1][RANK])
                return 2;
            else if (player1[0][RANK] == player2[1][RANK]) {
                return 2;
            }
        }
        if (player1[1][RANK] == player1[2][RANK] && player2[0][RANK] == player2[1][RANK]) {
            if (player1[1][RANK] > player2[0][RANK])
                return 1;
            else if (player1[1][RANK] < player2[2][RANK])
                return 2;
            else if (player1[0][RANK] == player2[1][RANK]) {
                return 1;
            }
        }
        if (player1[1][RANK] == player1[2][RANK] && player2[1][RANK] == player2[2][RANK]) {
            if (player1[1][RANK] > player2[1][RANK])
                return 1;
            else if (player1[1][RANK] < player2[1][RANK])
                return 2;
            else if (player1[1][RANK] == player2[1][RANK]) {
                if (player1[0][RANK] > player2[0][RANK])
                    return 1;
                else if (player1[0][RANK] < player2[0][RANK])
                    return 2;
                else
                    return 0;
            }
        }
    }
    else if (value_player1 == 9) {   // STRAIGHT FLUSH
        if (player1[0][RANK] > player2[0][RANK])
            return 1;
        else if (player1[0][RANK] < player2[0][RANK])
            return 2;
        else
            return 0;
    }
    else // ROYAL FLUSH
        return 0;
    return 0;
}
check_winner *untie_dx(check_winner *list_head, int n_of_players_tied, int *players_tied) {

    check_winner *player1 = list_head, *winner = NULL;

    if (n_of_players_tied == 1)
        return player1;
    else if (n_of_players_tied == 2) {
        check_winner *player2 = player1->next;
        return winner = untie_2_players(player1, player2, players_tied);
    }
    else if (n_of_players_tied == 3) {
        check_winner *player2 = player1->next, *player3 = player2->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        return winner = untie_2_players(aux_winner1, player3, players_tied);
    }
    else if (n_of_players_tied == 4) {
        check_winner *player2 = player1->next, *player3 = player2->next, *player4 = player3->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        check_winner *aux_winner2 = untie_2_players(player3, player4, players_tied);
        return winner = untie_2_players(aux_winner1, aux_winner2, players_tied);
    }
    else if (n_of_players_tied == 5) {
        check_winner *player2 = player1->next, *player3 = player2->next, *player4 = player3->next, *player5 = player4->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        check_winner *aux_winner2 = untie_2_players(player3, player4, players_tied);
        check_winner *aux_winner3 = untie_2_players(aux_winner1, aux_winner2, players_tied);
        return winner = untie_2_players(aux_winner3, player5,players_tied);
    }
    else if (n_of_players_tied == 6) {
        check_winner *player2 = player1->next, *player3 = player2->next, *player4 = player3->next;
        check_winner *player5 = player4->next, *player6 = player5->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        check_winner *aux_winner2 = untie_2_players(player3, player4, players_tied);
        check_winner *aux_winner3 = untie_2_players(player5, player6, players_tied);
        check_winner *aux_winner4 = untie_2_players(aux_winner1, aux_winner2, players_tied);
        return winner = untie_2_players(aux_winner3, aux_winner4, players_tied);
    }
    else if (n_of_players_tied == 7) {
        check_winner *player2 = player1->next, *player3 = player2->next, *player4 = player3->next;
        check_winner *player5 = player4->next, *player6 = player5->next, *player7 = player6->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        check_winner *aux_winner2 = untie_2_players(player3, player4, players_tied);
        check_winner *aux_winner3 = untie_2_players(player5, player6, players_tied);
        check_winner *aux_winner4 = untie_2_players(aux_winner1, aux_winner2, players_tied);
        check_winner *aux_winner5 = untie_2_players(aux_winner3, aux_winner4, players_tied);
        return winner = untie_2_players(aux_winner5, player7, players_tied);
    }
    else if (n_of_players_tied == 8) {
        check_winner *player2 = player1->next, *player3 = player2->next, *player4 = player3->next;
        check_winner *player5 = player4->next, *player6 = player5->next, *player7 = player6->next, *player8 = player7->next;
        check_winner *aux_winner1 = untie_2_players(player1, player2, players_tied);
        check_winner *aux_winner2 = untie_2_players(player3, player4, players_tied);
        check_winner *aux_winner3 = untie_2_players(player5, player6, players_tied);
        check_winner *aux_winner4 = untie_2_players(player7, player8, players_tied);
        check_winner *aux_winner5 = untie_2_players(aux_winner1, aux_winner2, players_tied);
        check_winner *aux_winner6 = untie_2_players(aux_winner3, aux_winner4, players_tied);
        return winner = untie_2_players(aux_winner5, aux_winner6, players_tied);
    }

    return 0;
}
check_winner *untie_2_players(check_winner *player1, check_winner *player2, int *players_tied) {

    int result_untie;
    check_winner *aux1 = player1, *aux2 = player2;
    result_untie = untie(aux1->player_hand, aux2->player_hand, aux1->value_player_number);
    if (result_untie == 1) {
        for (int i = 0; i < 8; i++) {
            players_tied[i] = 0;
        }
        return aux1;
    } else if (result_untie == 2) {
        for (int i = 0; i < 8; i++) {
            players_tied[i] = 0;
        }
        return aux2;
    } else {
        players_tied[(player1->player_number) - 1]++;
        players_tied[(player2->player_number) - 1]++;
        return aux1;
    }
}
