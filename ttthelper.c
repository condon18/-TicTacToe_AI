/* CS 305 HW5
 * Spring 2016
 * Author: Tammy VanDeGrift
 * tic tac toe helper functions
 * ttthelper.c
 */

#include <stdlib.h>
#include <stdio.h>
#include "gametree.h"

// functions to support the tic tac toe game
/* printBoard -- prints current board */
void printBoard(char b[3][3])
{
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            printf("[%c] ", b[i][j]);
        }
        printf("\n");
    }
}

/* isFull -- returns 0 if board has at least one
   open space, returns 1 if board has no open spaces */
int isFull(char b[3][3])
{
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            if(b[i][j] == ' ')
            {
                return 0;  // non-used cell in TTT board
            }
        }
    }
    return 1;
}

/* winner -- returns 0 if player has not won game, returns
   1 if player has won game */
int winner(char b[3][3], char player)
{
    int i, j;
    // check all 9 wins
    if(b[0][0] == b[0][1] && b[0][1] == b[0][2] && b[0][0] == player)
    {
        return 1;
    }
    if(b[1][0] == b[1][1] && b[1][1] == b[1][2] && b[1][0] == player)
    {
        return 1;
    }
    if(b[2][0] == b[2][1] && b[2][1] == b[2][2] && b[2][0] == player)
    {
        return 1;
    }
    if(b[0][0] == b[1][0] && b[1][0] == b[2][0] && b[0][0] == player)
    {
        return 1;
    }
    if(b[0][1] == b[1][1] && b[1][1] == b[2][1] && b[0][1] == player)
    {
        return 1;
    }
    if(b[0][2] == b[1][2] && b[1][2] == b[2][2] && b[0][2] == player)
    {
        return 1;
    }
    if(b[0][0] == b[1][1] && b[1][1] == b[2][2] && b[0][0] == player)
    {
        return 1;
    }
    if(b[0][2] == b[1][1] && b[1][1] == b[2][0] && b[0][2] == player)
    {
        return 1;
    }
    return 0;
}

/* isPosEmpty -- returns 1 if b[row][co] is a space; returns 0
   otherwise */
int isPosEmpty(char b[3][3], int row, int col)
{
    // error-check row
    if(row < 0 || row > NUM_ROWS)
    {
        return 0;
    }
    // error-check col
    if(col < 0 || col > NUM_COLS)
    {
        return 0;
    }
    if(b[row][col] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// functions that use the game tree
/* createTree -- creates root node for the game tree */
GameNode * createTree(char player)
{
    // create root node
    GameNode * root = (GameNode *) malloc(sizeof(GameNode));

    // create new board that is all spaces
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            root->board[i][j] = ' ';
        }
    }

    root->score = '#';  // special symbol for unprocessed score
    root->player = '$'; // invalid player

    // create children nodes
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            root->children[i][j] = createNode(root->board, i, j, player);
        }
    }
    return root;
}

/* isLeaf -- returns 1 if this node is a leaf; returns 0 otherwise */
int isLeaf(GameNode * tree)
{
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            if(tree->children[i][j] != NULL)
            {
                return 0;
            }
        }
    }
    return 1;  // all children are NULL
}

/* printNode -- prints node information
 * can be used for debugging */
void printNode(GameNode * tree)
{
    printf("player: %c, score: %c, address: %p\n", tree->player, tree->score, tree);
    printBoard(tree->board);
}

/* humanMove -- gets row/col information from human
   player and returns child node of tree corresponding
   to that game state */
GameNode * humanMove(GameNode * tree)
{
    printBoard(tree->board);
    char *line = NULL;
    char *line2 = NULL;
    size_t len = 0;
    size_t len2 = 0;
    ssize_t read;
    ssize_t read2;

    int row = -1;
    int col = -1;
    printf("Enter row (0 to 2): ");
    read = getline(&line, &len, stdin);

    printf("Enter column (0 to 2): ");
    read2 = getline(&line2, &len2, stdin);

    int ok = 1;
    if(read != 2 || read2 != 2)   // reads include '\n'
    {
        ok = 0;
    }
    if(read == 2)
    {
        sscanf(line, "%d", &row);
    }
    if(read2 == 2)
    {
        sscanf(line2, "%d", &col);
    }
    if(ok == 1)
    {
        ok = isPosEmpty(tree->board, row, col);
    }
    // process new information if row/col are not valid
    while(!ok)
    {
        ok = 1;
        printf("Row or column is invalid. Enter row (0 to 2): ");
        read = getline(&line, &len, stdin);

        printf("Enter column (0 to 2): ");
        read2 = getline(&line2, &len2, stdin);

        if(read != 2 || read2 != 2)
        {
            ok = 0;
        }
        if(read == 2)
        {
            sscanf(line, "%d", &row);
        }
        if(read2 == 2)
        {
            sscanf(line2, "%d", &col);
        }
        if(ok == 1)
        {
            ok = isPosEmpty(tree->board, row, col);
        }
    }

    // play position (human is always 'O')
    GameNode * nextNode = play(tree, row, col, 'O');
    return nextNode;
}

/* play -- returns child node of current tree that corresponds
   to the row/col played by player */
GameNode * play(GameNode * tree, int row, int col, char player)
{
    // error-check tree
    if(tree == NULL)
    {
        printf("Tree is null. Cannot make play.\n");
        return NULL;
    }
    // error-check player
    if(player != 'X' && player != 'O')
    {
        printf("Player invalid: %c\n", player);
        return tree;
    }
    // find child of tree that corresponds to this row and column
    GameNode * child = tree->children[row][col];

    // error-check that the player is correct for the child level
    if(child->board[row][col] != player)
    {
        printf("Something went wrong.\n");
        return NULL;
    }
    return child;
}

/* freeTree -- frees all memory associated with tree */
void freeTree(GameNode * tree)
{
    if(tree == NULL)
    {
        return;
    }
    // free children
    int i, j;
    for(i=0; i<NUM_ROWS; i++)
    {
        for(j=0; j<NUM_COLS; j++)
        {
            freeTree(tree->children[i][j]);
        }
    }
    // free the memory address for tree
    free(tree);
    tree = NULL;
}
