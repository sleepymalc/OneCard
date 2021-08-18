#ifndef project2_h
#define project2_h

#include <getopt.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct Card {
    int rank;
    int suits;
} card;

typedef struct player {
    struct player *next;
    int score;
    int cardnum;
    card *card;
    int kind;
    int steps;
    char name[1000];
    struct player *prev;
} player;

#endif
