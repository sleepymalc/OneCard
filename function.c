#include "function.h"

//player structer:double link list
player *playerct(player *head, int num, int demo) {
    head = (player *)malloc(sizeof(player));
    head->prev = NULL;
    head->next = NULL;
    head->score = 0;
    head->cardnum = 0;
    head->steps = 0;
    head->card = NULL;
    head->kind = 1;

    if (demo == 1) head->kind = 0;
    player *list = head;
    for (int i = 2; i <= num; i++) {
        player *body = (player *)malloc(sizeof(player));
        body->score = 0;
        body->cardnum = 0;
        body->steps = 0;
        body->card = NULL;
        body->kind = 1;
        if (demo == 1) body->kind = 0;
        list->next = body;
        body->prev = list;

        if (i != num)
            list = list->next;
        else {
            body->next = head;
            head->prev = body;
        }
    }
    return head;
}

//draw the card
void print_image(FILE *fptr, FILE *log) {
    char read_string[12];
    printf("\n");
    fprintf(log, "\n");
    while (fgets(read_string, sizeof(read_string), fptr) != NULL) {
        printf("%s", read_string);
        fprintf(log, "%s", read_string);
    }
    printf("\n");
    fprintf(log, "\n");
}

//draw the ascii card
void drawcard(card *card, int cardnum, int o, FILE *log) {
    char filename[100];
    if (o == 0) {
        for (int i = 0; i < cardnum; i++) {
            sprintf(filename, "Ascii_Card/%d.txt", 100 * (card + i)->suits + (card + i)->rank);
            FILE *fptr = fopen(filename, "r");
            print_image(fptr, log);
            fclose(fptr);
        }
    } else if (o == 1) {
        printf("0 - skip this round\n");
        fprintf(log, "0 - skip this round\n");
        for (int i = 0; i < cardnum; i++) {
            printf("%d:", i + 1);
            fprintf(log, "%d:", i + 1);
            sprintf(filename, "Ascii_Card/%d.txt", 100 * (card + i)->suits + (card + i)->rank);
            FILE *fptr = fopen(filename, "r");
            print_image(fptr, log);
            fclose(fptr);
        }
    }
}

//initial the card pile
void init(card *stock, int cardnum) {
    for (int i = 0; i < cardnum; ++i) {
        (stock + i)->rank = i % 13 + 2;
        (stock + i)->suits = (i / 13) % 4 + 1;
    }
}

//shuffle the card pile
void shuffle(card *stock, int num) {
    int a = 0, b = 0;
    srand((int)time(NULL));
    for (int i = 0; i <= 1000; ++i) {
        a = rand() % num;
        while (b == a) {
            b = rand() % num;
        }
        card temp = *(stock + b);
        *(stock + b) = *(stock + a);
        *(stock + a) = temp;
    }
}

//sort the card pile
void sort(card *Card, int num) {
    for (int i = 0; i < num - 1; i++) {
        int min = i;
        for (int j = i + 1; j < num; j++) {
            if ((Card + j)->suits * 100 + (Card + j)->rank < (Card + min)->suits * 100 + (Card + min)->rank) {
                min = j;
            }
        }
        card temp = *(Card + min);
        *(Card + min) = *(Card + i);
        *(Card + i) = temp;
    }
}

//deal the cards to the player
void deal(player *name, int dnum, card **stock, int *stocknum) {
    name->cardnum += dnum;
    name->card = (card *)realloc(name->card, sizeof(card) * (name->cardnum));
    while (name->card == NULL) {
        printf("\n\nasking error\n\n");
        name->card = (card *)realloc(name->card, sizeof(card) * (name->cardnum));
    }
    for (int i = 0; i < dnum; i++) {
        name->card[name->cardnum - dnum + i] = *(*stock + i);
    }
    for (int j = 0; j < *stocknum - dnum; j++) {
        *(*stock + j) = *(*stock + j + dnum);
    }
    *stocknum -= dnum;
    *stock = (card *)realloc(*stock, sizeof(card) * (*stocknum));
    while (*stock == NULL) {
        printf("\n\nasking error\n\nm");
        *stock = (card *)realloc(*stock, sizeof(card) * (*stocknum));
    }
    sort(name->card, name->cardnum);
}

//determine the first player and draw the order-card of each player gets
int first(int num, card **stock, card **discard, int *discardnum, int *cardnum, FILE *log) {
    int fir = 0;
    *cardnum -= num + 1;
    for (int i = 0; i < num; i++) {
        if ((*stock + i)->suits * 100 + (*stock + i)->rank < (*stock + fir)->suits * 100 + (*stock + fir)->rank) {
            fir = i;
        }
    }
    (*discardnum) += num + 1;
    *discard = (card *)realloc(*discard, sizeof(card) * (*discardnum));
    if (*discard == NULL) {
        printf("\n\nasking error\n\n");
    }
    for (int i = 0; i <= num; i++)
        *(*discard + i) = *(*stock - i + num);
    for (int i = 0; i < *cardnum; i++)
        *(*stock + i) = *(*stock + i + num + 1);
    *stock = (card *)realloc(*stock, sizeof(card) * (*cardnum));
    if (*stock == NULL) {
        printf("\n\nasking error\n\n");
    }
    drawcard(*discard, 1, 0, log);
    return fir;
}

//judge if this card is allow to play
int judgeplay(card *discard, card Pcard) {
    if ((discard->suits) == Pcard.suits || discard->rank == Pcard.rank) {
        return 1;
    }
    return 0;
}

//judge if the player have suitable card to play
int judgehave(card *discard, player *name) {
    int n = 0;
    for (int i = 0; i < name->cardnum; i++) {
        if ((name->card + i)->rank == discard->rank || (name->card + i)->suits == discard->suits) {
            n = 1;
            break;
        }
    }

    return n;
}

int playcard(player *name, card **discard, int *discardnum, card **stock, int *stocknum, int *add, FILE *log) {
    int num = 0, eff = -1, play = 1;
    while (name->cardnum != 0) {
        if (judgehave(*discard, name) == 1) {  //if you have at least a card to play
            printf("Play a card!\n");
            if (name->kind == 1) {
                if (scanf("%d", &num)) {
                };
            } else {
                if (name->cardnum > num) {
                    num++;
                } else {
                    num = 0;
                }
            }
            if (num == 0) {  //skip this turn
                if (*add == 0) {
                    printf("Draw a card\n\n");
                    drawcard(*stock, 1, 0, log);
                    deal(name, 1, stock, stocknum);
                    break;
                } else {
                    printf("Draw %d card\n\n", *add);
                    drawcard(*stock, *add, 0, log);
                    deal(name, *add, stock, stocknum);
                    *add = 0;
                    break;
                }
            } else if (num >= 1 && num <= (name->cardnum)) {  //if you have that card or not
                card Pcard = name->card[num - 1];
                if (judgeplay(*discard, Pcard) == 1) {  //judge can play this card or not
                    if (*add != 0) {
                        play = 1;
                        if (Pcard.rank != 7 && Pcard.rank != 2 && Pcard.rank != 3 && Pcard.rank != 11 && Pcard.rank != 12) {
                            printf("This card can't defend the attack card...\n");
                            play = 0;
                        }
                    }
                    if (play == 1) {
                        (*discardnum) += 1;  //normal card
                        name->cardnum -= 1;
                        *discard = (card *)realloc(*discard, sizeof(card) * (*discardnum));
                        if (*discard == NULL) {
                            printf("\n\nasking error\n\n");
                        }
                        for (int i = *discardnum - 1; i > 0; i--)
                            *(*discard + i) = *(*discard + i - 1);
                        *discard[0] = name->card[num - 1];
                        drawcard(*discard, 1, 0, log);
                        for (int i = num - 1; i < name->cardnum; i++)
                            name->card[i] = name->card[i + 1];
                        name->card = (card *)realloc(name->card, sizeof(card) * name->cardnum);
                        if ((*discard[0]).rank == 2 || (*discard[0]).rank == 3 || (*discard[0]).rank == 7 || (*discard[0]).rank == 11 || (*discard[0]).rank == 12) {
                            switch ((*discard[0]).rank) {
                                case 2:
                                    eff = 2;
                                    printf("\n+2!!\n");
                                    break;
                                case 3:
                                    eff = 3;
                                    printf("\n+3!!\n");
                                    break;
                                case 7:
                                    eff = -2;
                                    printf("\nDEFENSE!!\n");
                                    break;
                                case 11:
                                    eff = 1;
                                    printf("\nJUMP!!\n");
                                    break;
                                case 12:
                                    eff = 0;
                                    printf("\nTURN!!\n");
                                    break;
                            }
                        }
                        break;
                    }
                } else {
                    printf("Your can't play that card!\n");
                }
            } else {
                printf("Your don't have that card!\n");
            }
        } else {  //if you don't have any card can play
            printf("You don't have any card to play...\n\n");
            if (*add == 0) {
                printf("Draw a card...\n\n");
                drawcard(*stock, 1, 0, log);
                deal(name, 1, stock, stocknum);
            } else {
                printf("Draw %d cards...\n\n", *add);
                drawcard(*stock, *add, 0, log);
                deal(name, *add, stock, stocknum);
            }
            break;
        }
    }
    return eff;
}

void ClearScreen() {
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    if (system("clear")) {
    };
#endif
#if defined(_WIN32) || defined(_WIN64)
    if (system("cls")) {
    };
#endif
}

void OneCard(int n, int r, int d, int c, int demo, char *filename) {
    int stocknum = 52 * d, discardnum = 0;
    player *head = NULL;
    head = playerct(head, n, demo);
    card *stock = (card *)malloc(sizeof(card) * stocknum);
    card *discard = (card *)malloc(sizeof(card) * discardnum);
    FILE *fptr = fopen(filename, "w");

    printf(
        "\
#############################\n\
#                           #\n\
#   Welcome to One Card!    #\n\
#                           #\n\
#############################\n\
---- Initial setup ----\n\
Number of rounds: %d\n\
Number of decks: %d\n\
Number of players: %d\n\
---- Game start ----\n",
        r, d, n);

    fprintf(fptr,
            "\
#############################\n\
#                           #\n\
#   Welcome to One Card!    #\n\
#                           #\n\
#############################\n\
---- Initial setup ----\n\
Number of rounds: %d\n\
Number of decks: %d\n\
Number of players: %d\n\
---- Game start ----\n",
            r, d, n);

    player *Nowplay = head;
    for (int i = 1; i <= n; i++) {
        printf("Enter player%d's name!\n", i);  //input each player's name
        fprintf(fptr, "Enter player%d's name!\n", i);
        if (demo == 0) {
            if (scanf("%s", Nowplay->name)) {
            };
        } else if (demo == 1) {
            sprintf(Nowplay->name, "Computer %d", i);
        }
        Nowplay = Nowplay->next;
    }
    for (int R = 1; R <= r; R++) {  //game start with r rounds
        int win = 0, eff = -1, dir = 1, add = 0;
        printf("Round %d starts!\n", R);
        fprintf(fptr, "Round %d starts!\n", R);
        init(stock, stocknum);
        shuffle(stock, stocknum);
        printf("Shuffling cards...\n\n");
        fprintf(fptr, "Shuffling cards...\n\n");
        if (demo == 1) {
            drawcard(stock, stocknum, 0, fptr);
        }
        printf("\nThe First card:");
        fprintf(fptr, "\nThe First card:");
        int order = first(n, &stock, &discard, &discardnum, &stocknum, fptr);  //determine the order
        printf("\n");
        fprintf(fptr, "\n");
        printf("\n\nDetermining the playing order...\n\n");
        fprintf(fptr, "\n\nDetermining the playing order...\n\n");
        for (int i = 0; i < n; i++) {
            printf("Player %d-%s:", i + 1, Nowplay->name);  //draw every player's order-card
            fprintf(fptr, "Player %d-%s:", i + 1, Nowplay->name);
            drawcard(discard - i + n, 1, 0, fptr);
            Nowplay = Nowplay->next;
        }
        printf("The game will start with player %d\n\n", order + 1);
        fprintf(fptr, "The game will start with player %d\n\n", order + 1);
        for (int o = 0; o < order; o++) {  //start from the order
            Nowplay = Nowplay->next;
        }
        while (win == 0) {  //a round
            if (Nowplay->steps == 0) {
                deal(Nowplay, c, &stock, &stocknum);  //first round deal c cards to each player
            }
            printf("Now is %s's turn!\n\n", Nowplay->name);
            fprintf(fptr, "Now is %s's turn!\n\n", Nowplay->name);
            printf("The last card is:");
            fprintf(fptr, "The last card is:");
            drawcard(discard, 1, 0, fptr);  //the previous card
            printf("\n");
            fprintf(fptr, "\n");
            drawcard(Nowplay->card, Nowplay->cardnum, 1, fptr);  //draw the player's cards
            printf("\n");
            fprintf(fptr, "\n");
            eff = playcard(Nowplay, &discard, &discardnum, &stock, &stocknum, &add, fptr);  //play a card
            Nowplay->steps++;

            if (stocknum <= 10) {  //when stock exhausted
                printf("Stock pile exhausted. Shuffling the discard pile and restore the stock pile\n");
                fprintf(fptr, "Stock pile exhausted. Shuffling the discard pile and restore the stock pile\n");
                stocknum += discardnum - 1;
                stock = (card *)realloc(stock, sizeof(card) * stocknum);
                if (stock == NULL) {
                    printf("\n\nasking error\n\n");
                }
                for (int i = stocknum - discardnum + 1; i < stocknum; i++)
                    *(stock + i) = *(discard + i - stocknum + discardnum);
                shuffle(stock, stocknum);
                discardnum = 1;
                discard = (card *)realloc(discard, sizeof(card) * discardnum);
                if (discard == NULL) {
                    printf("\n\nasking error\n\n");
                }
            }

            if (Nowplay->cardnum == 0) {
                printf("You Win!\n");
                fprintf(fptr, "You Win!\n");
                win = 1;
            } else {
                printf("\nNext player\n");
                fprintf(fptr, "\nNext player\n");
            }
            switch (eff) {  //add the effect
                case 2:
                    add += 2;
                    break;
                case 3:
                    add += 3;
                    break;
                case -2:
                    add = 0;
                    break;
                case 1:
                    if (dir == 1) {
                        Nowplay = Nowplay->next;
                    } else if (dir == -1) {
                        Nowplay = Nowplay->prev;
                    }
                    break;
                case 0:
                    dir *= -1;
                    break;
            }
            if (dir == 1) {  //direct=1 is counter clock wise
                Nowplay = Nowplay->next;
            } else if (dir == -1) {  //direct=2 is clock wise
                Nowplay = Nowplay->prev;
            }
            ClearScreen();
        }
        printf(
            "---- Stats ----\n\
Round %d result:\n",
            R);
        fprintf(fptr,
                "---- Stats ----\n\
Round %d result:\n",
                R);
        Nowplay = head;
        for (int i = 1; i <= n; i++) {  //calculate the score
            Nowplay->score -= (Nowplay->cardnum);
            printf("Player %d--%s: %d, total: %d\n", i, Nowplay->name, -Nowplay->cardnum, Nowplay->score);
            fprintf(fptr, "Player %d--%s: %d, total: %d\n", i, Nowplay->name, -Nowplay->cardnum, Nowplay->score);
            stock = (card *)realloc(stock, sizeof(card) * (stocknum + Nowplay->cardnum));
            for (int j = 0; j < Nowplay->cardnum; j++) {
                *(stock + j + stocknum) = *(Nowplay->card + j);
            }
            stocknum += Nowplay->cardnum;
            Nowplay->cardnum = 0;
            Nowplay->card = (card *)realloc(Nowplay->card, sizeof(card) * Nowplay->cardnum);
            Nowplay->steps = 0;
            Nowplay = Nowplay->next;
        }
        printf("Round %d ends\n", R);
        fprintf(fptr, "Round %d ends\n", R);

        stocknum += discardnum;
        stock = (card *)realloc(stock, sizeof(card) * stocknum);
        for (int i = 0; i < discardnum; i++) {
            *(stock + stocknum - discardnum + i) = *(discard + i);
        }
        discardnum = 0;
        discard = (card *)realloc(discard, sizeof(card) * discardnum);
    }
    player *winner = head, *compare = head;  //determine the winner
    for (int i = 0; i < n; i++) {
        if ((*winner).score < (*compare).score) {
            winner = compare;
        }
        compare = compare->next;
    }
    printf("\n\nCalculating the result... ...\n\nThe WINNER is--\n");
    fprintf(fptr, "\n\nCalculating the result... ...\n\nThe WINNER is--\n");
    for (int i = 0; i < n; i++) {  //print all the winner
        if ((compare->score) == (winner->score)) {
            printf("\t%s!!\n", compare->name);
            fprintf(fptr, "\t%s!!\n", compare->name);
        }
        compare = compare->next;
    }

    free(stock);  //free the memory
    fprintf(fptr, "free stock's memory success\n");
    free(discard);
    fprintf(fptr, "free discard pile's memory success\n");

    for (int i = 0; i < n; i++) {
        winner = compare;
        compare = compare->next;
        free(winner);
    }
    fprintf(fptr, "free player's memory success\n");
    fclose(fptr);
}
