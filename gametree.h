#ifndef GAME_H
#define GAME_H

#define NUM_ROWS 3
#define NUM_COLS 3

typedef struct GameNodeTag GameNode;

/* game node data structure */
struct GameNodeTag
{
    char board[3][3];  // current game board ('X', 'O', or ' ' in each position)
    char score;        // game score ('X', 'O', or 'T') showing its score
    char player;       // player 'X' or 'O'
    GameNode * children[3][3];   // children nodes (note: some will be null --
    // meaning that position in the board is full)
};

/* functions defined in ttthelper.c */
// functions to help with tic tac toe game
void printBoard(char b[3][3]);
int isFull(char b[3][3]);
int winner(char b[3][3], char player);
int isPosEmpty(char b[3][3], int row, int col);
// functions that support the game tree
GameNode * createTree(char player);
int isLeaf(GameNode * tree);
void printNode(GameNode * tree);
GameNode * humanMove(GameNode * tree);
GameNode * play(GameNode * tree, int row, int col, char player);
void freeTree(GameNode * tree);


/* in gametree.c -- students define */
GameNode * createNode(char b[3][3], int row, int col, char player);
GameNode * computerMove(GameNode * tree);
void calculateScores(GameNode * tree);

#endif
