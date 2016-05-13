/* CS 305 HW5
 * Spring 2016
 * Author: Tammy VanDeGrift
 * tic tac toe game loop
 * tictactoe.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // for random #s
#include "gametree.h"

/* main
   game loop to play tic tac toe
   note: 'X' is the computer player; 'O' is the human player */
int main(void)
{
    GameNode * tree = NULL;

    // decide who goes first randomly
    srand(time(NULL));
    int first = rand() % 2; // set first to 0 or 1

    if(first == 0)
    {
        // computer goes first
        tree = createTree('X');  // tree's first level has player 'X'
        printf("Computer goes first.\n");
    }
    else
    {
        // human goes first
        tree = createTree('O');
        printf("Human player goes first.\n");
    }
    //printf("Made the tree\n");
    // populate scores for each node in the tree
    calculateScores(tree);
    //printf("Calculated scores\n");
    // game loop
    int noWinner = 1;
    while(noWinner)
    {
        if(first == 1)    // human goes first
        {

            tree = humanMove(tree);

            if(winner(tree->board, 'O'))
            {
                printf("Congratulations! You win!\n");
                printBoard(tree->board);
                noWinner = 0;
                break;
            }
            else if(isFull(tree->board))
            {
                printf("Tie game.\n");
                printBoard(tree->board);
                noWinner = 0;
                break;
            }
        }
        first = 1; // so above code is executed in next loop

        tree = computerMove(tree);

        if(winner(tree->board, 'X'))
        {
            printf("Computer wins.\n");
            printBoard(tree->board);
            noWinner = 0;
            break;
        }
        else if(isFull(tree->board))
        {
            printf("Tie game.\n");
            printBoard(tree->board);
            noWinner = 0;
            break;
        }
    }
    // game over
    printf("Thanks for playing.\n");
    freeTree(tree);
    return EXIT_SUCCESS;
}
