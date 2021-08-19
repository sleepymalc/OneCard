# README - OneCard

## About OneCard

### Overview

​	One Card is a rather simple game played by n persons over a pre-decided number of rounds r. A total of d decks of Poker cards, excluding Jokers, are shuffled and c cards are offered to each player. Before the game start each player is offered an extra card to determine the playing order. This game is then discarded. The game will be played counter-clockwise, starting with the player who received the extra card with lowest rank. Once the playing order has been decided all those initial n cards are directly put in the discard pile. Finally, the game starts with the first card of the stock pile being posed face-up, to initiate the rank and suit. 

​	As the game starts each player, following the defined order, plays exactly one card either following the rank or the suit defined by the previous card. Any played card directly goes into the discard pile, and anyone who is unable to play should draw a card from the top of the stock pile. If the stock pile is exhausted, the discard pile is shuffled and used as stock pile. 

​	As soon as a player has discarded all his cards the rounds stops. All other players receive a penalty equal to the number of cards left their hands. The player who won the round initiates the following one, all the other rules remain unchanged. At the end of the r rounds the final score of each player is determined by summing up of all his penalties. The person with highest score wins. In case of equality more than one player can be declared winner. 	--from project2.pdf

### Cards

Cards split into four main categories: 

• Attack: 

​		– Cards with rank 2: the next player draws two cards from the stock pile; 

​		– Cards with rank 3: the next player draws three cards from the stock pile; 

• Defense: 

​		– Cards with rank 7: cancel an attack, i.e. do not draw any card if a 2 or a 3 was played before; 

• Action: 

​			–  Queen cards: reverse the playing order from counter-clockwise to clockwise or clockwise to counter- clockwise; 

​			–  Jack cards: skip the next player; 

•  Regular: any other card has no special effect and is only used to match the previous card’s rank or suit; 

Notes on cards and attacks: 

•  The effect of the attack cards is cumulative. 

•  A Queen or a Jack, of same suit as the previous card, can be played to redirect an attack on the previous player, or the player after the next one, respectively; 

•  When under an attack, a player not playing any special card (2, 3, 7, Q, J) must draw cards from the stock pile, and this ends his turn; 	--from project2.pdf

## Code Structure

Since this is a big project, the **Code Structure** need to be well organized. In order to complete the whole 

project without spending lots of time to debug and to add function more easily after, in this project we use 

the **Layer coding**, which means that split every function out of the main function, and arrange their order 

reasonable.

## Compile the program

​	You can easily use terminal and input this

```bash
make
```

by using Cmake. After compiling done, we can run this program by

```bash
./cardgame
```

this will run the project in default mode, that means:

​	**Players : 4**

​	**Decks : 2**

​	**Initial cards : 5**

​	**Rounds : 1**

​	**Log filename : ondcard.txt**

​	For adjustment of other parameters, please check the help list by

```bash
./cardgame -h
```

or

```bash
./cardgame --help
```

for more information.

## Ascii art

In order to let the whole game more playable, I use the Ascii art to draw the card, but this will lead to some problem, that is the suits can only display on the **MacOs**, because this is a special library on **MacOs** but not on Window. 

## About Honor Code

If there is same questions or labs in the future, it is the responsibility of JI students not to copy or modify these codes, or TeX files because it is against the Honor Code. The owner of this repository dosen't take any commitment for other's faults.

According to the SJTU student handbook (2019 version),

> It is a violation of the Honor Code for students to submit, as their own, work that is not the result of their own labor and thoughts. This applies, in particular, to ideas, expressions or work obtained from other students as well as from books, the internet, and other sources. The failure to properly credit ideas, expressions or work from others is considered plagiarism.

## Contribution

YuYang Chen(Maxwell)
The work are partially contributed to some other students, TAs and professors in JI, which would be listed if known.

## Reminder

The first ever **1st JIntegration Bee** is held by me and other TAs in 2021SU Vv285. We create a separate repo for it, please go to [here](https://github.com/sleepymalc/UM-JI-IntegrationBee) if you are interested.

If you find any problems in the reposity, welcome to make an issue or pull request.
