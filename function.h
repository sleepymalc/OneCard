//
//  function.h
//  project2
//
//  Created by 胡平邦 on 2019/11/13.
//  Copyright © 2019 胡平邦. All rights reserved.
//

#ifndef function_h
#define function_h

#include "project2.h"

player *playerct(player *head, int num, int demo);

void print_image(FILE *fptr, FILE *log);

void drawcard(card *card, int cardnum, int o, FILE *log);

void init(card *stock, int cardnum);

void shuffle(card *stock, int num);

void sort(card *Card, int num);

void deal(player *name, int dnum, card **stock, int *stocknum);

int first(int num, card **stock, card **discard, int *discardnum, int *cardnum, FILE *log);

int judgeplay(card *discard, card Pcard);

int judgehave(card *discard, player *name);

int playcard(player *name, card **discard, int *discardnum, card **stock, int *stocknum, int *add, FILE *log);

void ClearScreen();

void OneCard(int n,int r,int d,int c,int demo,char *filename);
#endif /* function_h */
