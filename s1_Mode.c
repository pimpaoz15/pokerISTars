#include "PokerISTars.h"

int analyze_shuffle_mode(int argc, char *argv[]) {

    if (argc != 3 && argc != 5) {
        printf("-1\n");
        exit(0);
    }
    int len = strlen(argv[2]);
    char ext_argv[9], shuffle[] = ".shuffle";
    for (int m = 0; m < 9; m++) {
        ext_argv[m] = argv[2][len + m - 8];
    }
    if (strcmp(ext_argv, shuffle) != 0) {
        printf("-1\n");
        exit(0);
    }
    if (argc == 5) {
        if (strncmp(argv[3], "-o", 2) != 0) {
            printf("-1\n");
            exit(0);
        }
    }

    const int n_of_cards = 52;
    FILE *fp = fopen(argv[2], "r");

    while (1) {
        number *head_numbers = NULL;
        char token[3];
        while (fscanf(fp, "%2s", token) == 1 && strlen(token) == 1 && isdigit((unsigned char) token[0]))
            // insere número no fim da lista
            head_numbers = insert_number_end(head_numbers, create_number(token[0] - '0'));

        if (feof(fp))
            break;

        card *head_cards = create_card(token);
        for (int i = 1; i < n_of_cards; ++i) {
            char aux_card[3];
            if (fscanf(fp, "%2s", aux_card) == 1)
                // insere carta no fim da lista
                head_cards = insert_card_end(head_cards, create_card(aux_card));
        }
        number* current_number = head_numbers;
        while (current_number != NULL) {
            if (current_number->number == 1) {
                card *card26 = find_card(head_cards, 26);
                card *card27 = find_card(head_cards, 27);
                card26->next = NULL;
                card *second_half = card27;
                merge(head_cards, second_half);
            } else if (current_number->number == 2) {
                card *card26 = find_card(head_cards, 26);
                card *card27 = find_card(head_cards, 27);
                card26->next = NULL;
                card *second_half = card27;
                reverse(&second_half);
                merge(head_cards, second_half);
            } else if (current_number->number == 3) {
                card *card26 = find_card(head_cards, 26);
                card *card27 = find_card(head_cards, 27);
                card *card52 = find_card(head_cards, 52);
                card26->next = NULL;
                card52->next = head_cards;
                head_cards = card27;
            }
            current_number = current_number->next;
        }
        if (argc == 3)
            print_list(head_cards);
        else
            print_list_file(head_cards, argv);

        free_list(head_cards);
        free_list_numbers(head_numbers);
        if (feof(fp))
            break;
    }
    fclose(fp);

    return 0;
}

card *create_card(char *aux_card) {
    card *new_crd;

    if ((new_crd = (card *) malloc(sizeof(card))) == NULL) {
        printf("Error: unable to allocate memory block.\n");
        exit(EXIT_FAILURE);
    }

    sprintf(new_crd->card, "%s", aux_card);
    new_crd->next = NULL;

    return new_crd;
}
card *insert_card_end(card *list_head, card *new_card) {

    if (list_head == NULL)
        return new_card;

    card *aux = list_head;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new_card;

    return list_head;
}
number *create_number(int aux_number) {
    number *new_nbr;
    if ((new_nbr = (number *) malloc(sizeof(number))) == NULL) {
        printf("Error: unable to allocate memory block.\n");
        exit(EXIT_FAILURE);
    }
    new_nbr->number = aux_number;
    new_nbr->next = NULL;

    return new_nbr;
}
number *insert_number_end(number *list_head, number *new_number) {

    if (list_head == NULL)
        return new_number;

    number *aux = list_head;
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = new_number;

    return list_head;
}
void print_list(card *list_head) {

    int new_line = 1;
    card *aux = list_head;
    while (aux != NULL) {
        printf("%s ", aux->card);
        if (new_line % 13 == 0)
            printf("\n");
        new_line++;
        aux = aux->next;
    }
    printf("\n");
}
void print_list_file(card *list_head, char *argv[]) {

    int new_line = 1;
    card *aux = list_head;
    FILE *print_file;
    print_file = fopen(argv[4], "a");
    while (aux != NULL) {
        fprintf(print_file, "%s ", aux->card);
        if (new_line % 13 == 0)
            fprintf(print_file, "\n");
        new_line++;
        aux = aux->next;
    }
    fprintf(print_file, "\n");
    fclose(print_file);
}
void free_list(card *list_head) {
    while (list_head != NULL) {
        card *aux = list_head;
        list_head = list_head->next;
        free(aux);
    }
}
void free_list_numbers(number *list_head) {
    while (list_head != NULL) {
        number *aux = list_head;
        list_head = list_head->next;
        free(aux);
    }
}
card *find_card(card *list_head, int card_number) {

    card *current_card = list_head;
    int count = 1;
    while (current_card != NULL) {
        if (count == card_number)
            return current_card;
        count++;
        current_card = current_card->next;
    }
    return NULL;
}
void merge(card *first_half, card *second_half) {

    card *first_half_curr = first_half;
    card *second_half_curr = second_half;

    while (first_half_curr != NULL && second_half_curr != NULL) {

        card *first_half_next = first_half_curr->next;
        card *second_half_next = second_half_curr->next;


        second_half_curr->next = first_half_next;
        first_half_curr->next = second_half_curr;

        first_half_curr = first_half_next;
        second_half_curr = second_half_next;
    }
}
void reverse(card **list_head) {
    card *prev = NULL;
    card *current = *list_head;

    while (current != NULL) {
        card *next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }
    *list_head = prev;
}