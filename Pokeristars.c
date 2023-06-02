#include "PokerISTars.h"

int main(int argc, char *argv[]) {

    if (strncmp(argv[1], "-c", 2) == 0)
        analyze_c_mode(argc, argv);
    else if (strncmp(argv[1], "-d1", 3) == 0 || strncmp(argv[1], "-d2", 3) == 0 || strncmp(argv[1], "-d3", 3) == 0 || strncmp(argv[1], "-d4", 3) == 0)
        analyze_di_mode(argc, argv);
    else if (strncmp(argv[1], "-dx", 3) == 0)
        analyze_dx_mode(argc, argv);
    else if (strncmp(argv[1], "-s1", 3) == 0)
        analyze_shuffle_mode(argc, argv);
    else
        printf("-1\n");
    return 0;
}
