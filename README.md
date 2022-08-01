# OneCard

<p align="center">

```
#############################
#                           #
#   Welcome to One Card!    #
#                           #
#############################
---- Initial setup ----
Number of rounds: 1
Number of decks: 2
Number of players: 4
---- Game start ----
Enter player1's name!
Enter player2's name!
Enter player3's name!
Enter player4's name!
Round 1 starts!
Shuffling cards...


┌─────────┐
│7        │
│♠ ♠   ♠  │
│    ♠    │
│  ♠   ♠  │
│         │
│  ♠   ♠ ♠│
│        7|
└─────────┘

┌─────────┐
│7        │
│♦ ♦   ♦  │
│    ♦    │
│  ♦   ♦  │
│         │
│  ♦   ♦ ♦│
│        7|
└─────────┘

```

</i></b></p>

<p align="center"><b><i>
	A simple Card Game with beautiful ASCII Art
</i></b></p>

## Overview

One Card is a rather simple game played by n persons over a pre-decided number of rounds r. A total of d decks of Poker cards, excluding Jokers, are shuffled and c cards are offered to each player. Before the game start, each player is offered an extra card to determine the playing order. This game is then discarded. The game will be played counter-clockwise, starting with the player who received the extra card with the lowest rank. Once the playing order has been decided all those initial n cards are directly put in the discard pile. Finally, the game starts with the first card of the stockpile being posed face-up, to initiate the rank and suit.

As the game starts each player, following the defined order, plays exactly one card either following the rank or the suit defined by the previous card. Any played card directly goes into the discard pile, and anyone unable to play should draw a card from the top of the stockpile. If the stockpile is exhausted, the discard pile is shuffled and used as a stockpile.

As soon as a player has discarded all his cards the rounds stop. All other players receive a penalty equal to the number of cards left in their hands. The player who won the round initiates the following one, all the other rules remain unchanged. At the end of the r rounds the final score of each player is determined by summing up all his penalties. The person with the highest score wins. In the case of equality, more than one player can be declared the winner.

> A sample [`paly-through`](https://github.com/sleepymalc/CardGame/blob/master/onecard.txt) file is provided.

### Cards

Cards are split into four main categories:

* Attack
  * Cards with rank 2: the next player draws two cards from the stockpile.
  * Cards with rank 3: the next player draws three cards from the stockpile.
* Defense
  * Cards with rank 7: cancel an attack, i.e. do not draw any card if a 2 or a 3 was played before;
* Action
  * Queen cards: reverse the playing order from counter-clockwise to clockwise or clockwise to counter-clockwise;
  * Jack cards: skip the next player;
* Regular
  * Any other card has no special effect and is only used to match the previous card’s rank or suit;

> * The effect of the attack cards is cumulative.
> * A Queen or a Jack, of the same suit as the previous card, can be played to redirect an attack on the previous player, or the player after the next one, respectively.
> * When under an attack, a player not playing any special card (2, 3, 7, Q, J) must draw cards from the stockpile, and this ends his turn.

## Code Structure

The **Code Structure** needs to be well organized. To complete the whole project without spending lots of time debugging and to add functions more easily, in this project we use the **Layer coding**, which means that split every function out of the main function, and arranging their order reasonably.

## Compiling

You can easily use `make` to compile the source code with [CMake](https://cmake.org/). By running `./cardgame` without any arguments, we'll enter the default mode:

1. Players: 4
2. Decks: 2
3. Initial cards: 5
4. Rounds: 1
5. Log filename: `ondcard.txt`

You can use `./cardgame -h` or `./cardgame --help` to see what options you can pass in.

## ASCII Art

To let the whole game more playable, ASCII art is used to draw the card. For example, we have the spade cards:

```
┌─────────┐┌─────────┐┌─────────┐     ┌─────────┐┌─────────┐┌─────────┐
│A        ││2        ││3        │     │J   JUMP!││Q   TURN!││K        │
│♠   .    ││♠   ♠    ││♠   ♠    │     │♠   .    ││♠   .    ││♠   .    │
│   / \   ││         ││         │     │   / \   ││   / \   ││   / \   │
│  (_._)  ││         ││    ♠    │ ... │  (_._)  ││  (_._)  ││  (_._)  │
│    I    ││         ││         │     │    I    ││    I    ││    I    │
│        ♠││    ♠   ♠││    ♠   ♠│     │        ♠││        ♠││        ♠│
│        A││        2││        3│     │        J││        Q││        K│
└─────────┘└─────────┘└─────────┘     └─────────┘└─────────┘└─────────┘
```

## About Honor Code

According to the SJTU student handbook (2019 version),

> It is a violation of the Honor Code for students to submit, as their own, work that is not the result of their own labor and thoughts. This applies, in particular, to ideas, expressions or work obtained from other students as well as from books, the internet, and other sources. The failure to properly credit ideas, expressions or work from others is considered plagiarism.

## Contribution

The works are partially contributed by some other students, TAs, and professors, which would be listed if known.
> If you find any problems in the repository, welcome to make an issue or pull request.
