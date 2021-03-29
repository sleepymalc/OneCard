//
//  project2.h
//  project2
//
//  Created by 胡平邦 on 2019/11/13.
//  Copyright © 2019 胡平邦. All rights reserved.
//
#ifndef project2_h
#define project2_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <memory.h>
#include <unistd.h>
#include <getopt.h>

typedef struct Card{
    int rank;int suits;
}card;


typedef struct player{
    struct player *next;
    int score;
    int cardnum;
    card *card;
    int kind;
    int steps;
    char name[1000];
    struct player *prev;
}player;

void OneCard(int n,int r,int d,int c,int demo,char *filename);
#endif /* project2_h */
