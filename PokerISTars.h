#ifndef POKERISTARS_H_INCLUDED
#define POKERISTARS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define RANK 0
#define SUIT 1
#define KEY 0
#define VALUE 1

typedef struct _card {
    char card[3];
    struct _card *next;
} card;
typedef struct _number {
    int number;
    struct _number *next;
} number;
typedef struct players {
    int hand[7][2];
    int hand_value;
    int royal_flush;
    int straight_flush;
    int flush;
    int straight;
    int four;
    int three;
    int pairs;
    int fold;
    int inactive;
    int rounds_played;
    int untie_hand[5][2];
} player;
typedef struct _check_winner {
    int player_number;
    int value_player_number;
    int player_hand[5][2];
    struct _check_winner *next;
} check_winner;

//general functions used to check inputs and to convert inputs
int analyze_input(int, char *[]);
int card_exists(int [][2], int);
void convert_input(int, char *[], int [][2]);
//5 card analyze function
void analyze_hand_5(int [][2], int, bool *, bool *, bool *, bool *, bool *, int *);
bool is_flush(int [][2], int);
bool is_straight(int [][2], int);
void count_ranks_in_hand(int, int [][2], int [][2]);
void print_result_c(bool, bool, bool, bool, bool, int);
//7 card analyze function
void analyze_hand_7(int [][2], int, int *, int *, int *, int *, int *, int *, int *);
void is_straight_7(int [][2], int *);
void is_flush_7(int [][2], int, int *);
void is_straight_flush_7(int [][2], int *, int *);
int *choose_5_out_of_7 (int [][2], int *, int *, int *, int *, int *, int *, int *);
int *organize_straight_flush_7 (int [][2], int);
int *organize_straight_7 (int [][2]);
void print_result_7_c(int [][2], int *, int *, int *, int *, int *, int *, int *);
//9 card analyze function for "-c" mode
void analyze_hand_9_c(int, int [][2], int, int *, int *, int *, int *, int *, int *, int *, int *, int *);
//10 card analyze function for "-c" mode
void analyze_hand_10_c(int [][2], bool *, bool *, bool *, bool *, bool *, int *, int *, int *);
//Untie function for 9 and 10 card modes
int untie(int [][2], int [][2], int );
//analyze d mode function
int analyze_di_mode(int, char *[]);
void analyze_dx_mode(int, char *[]);
//5 card analyze and print results standard or in file functions
int analyze_c_mode (int, char *[]);
void print_result_file(bool, bool, bool, bool, bool, int, char *[], int *);
void print_result_stdout(bool, bool, bool, bool, bool, int, int *);
//7 card print results standard or in file functions
void print_result_7_stdout(int[][2], int *, int *, int *, int *, int *, int *, int *, int *);
void print_result_7_file(int[][2], int *, int *, int *, int *, int *, int *, int *, char *[], int *);
//9 card analyze function
void analyze_hand_9_di(int[][2], int, int , char *[], int *, int *, int *, int *, int *, int *, int *, int *, int *, int *, int *);
//10 card analyze function
void analyze_hand_10_di(int[][2], int, char *[], bool *, bool *, bool *, bool *, bool *, int *, int *, int *, int *, int *);
//Stats Functions
void print_stats_stdout(int *, int *, int, int);
void print_stats_file(char *[], int *, int *, int, int);

card *create_card(char *);
card *insert_card_end(card *, card *);
number *create_number(int);
number *insert_number_end(number *, number *);
void print_list(card *);
void print_list_file(card *, char *[]);
void free_list(card *);
void free_list_numbers(number *);
void reverse(card **);
card *find_card(card *, int);
void print_list_numbers(number *);
void merge(card *, card *);
int analyze_shuffle_mode(int, char *[]);

check_winner *create_player(int, int, int [][2]);
check_winner *insert_player_end(check_winner *, check_winner *);
void bubble_sort(check_winner *);
void swap(check_winner *, check_winner *);
void print_stats_stdout_dx(int *, int);
void print_winners_dx(double *);
int count(check_winner *, int);
void print_untie_dx(int [][2], int, int, int *);

check_winner *untie_2_players(check_winner *, check_winner *, int *);
check_winner *untie_dx(check_winner *, int, int *);
void free_list_dx(check_winner *);
void counnt_stats_dx(int *, int *, double *);

#endif //POKERISTARS_H_INCLUDED