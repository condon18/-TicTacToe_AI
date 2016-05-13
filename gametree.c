/*
 * @Author Teresa Condon
 * @Date April 04, 2016
 * Gametree creates a new node each time the computer or human moves.  Gametree controls the computer's
 * movements and calculates who will win.
*/
#include <stdio.h>
#include <stdlib.h>
#include "gametree.h"

/*
 * createNode - inserts a new node each time the computer or human moves.
*/
GameNode * createNode(char b[3][3], int row, int col, char player)
{
    if (b[row][col] != ' ')
    {
        return NULL; // one way to exit recursion
    }
    GameNode * newNode= (GameNode *) malloc(sizeof(GameNode));

    // copies existing board
    int i, j;
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            newNode->board[i][j] = b[i][j];
        }
    }
    newNode->board[row][col] = player; //Assign this node’s board at row/col to player
    newNode->score = '#';  // special symbol for unprocessed score
    newNode->player = player;
    //	If this board is a winner, set all this node’s children to NULL
    if (winner(newNode->board, player) )
    {
        for (i=0; i<3; i++)
        {
            for (j=0; j<3; j++)
            {
                newNode->children[i][j] = NULL;
            }
        }
    }
    else
    {
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                // The C ?: operator ternary operator
                newNode->children[i][j] = createNode(newNode->board, i, j, ((player == 'X') ? 'O' : 'X'));
            }
        }
    }

    return newNode;

};

/*
 * computerMove - recursively determines the ideal move for the computer.
*/

GameNode * computerMove(GameNode * tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    GameNode *bestScoringChild = NULL;
    int legali=0, legalj=0;
    int i, j;
    for (i = 0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            if (tree->board[i][j] == ' ')    // if legal move
            {
                legali = i;
                legalj = j;
                if(tree->children[i][j] != NULL)
                {
                    bestScoringChild = tree->children[legali][legalj];
                }
            }
        }
    }

    for (i = 0; i<3; i++)
    {
        for (j=0; j<3; j++)
        {
            if (tree->children[i][j] != NULL)
            {
                if (tree->children[i][j]->score == 'X')
                {
                    return tree->children[i][j];  // early exit from nested for-loops
                }
                if (tree->children[i][j]->score == 'T')
                {
                    bestScoringChild = tree->children[i][j];
                }
            }
        }
    }
    return bestScoringChild;
}
/*
 * calculateScores - determines the final score if at the end of game.
*/
void calculateScores(GameNode * tree)
{
    if (tree == NULL)
    {
        //  If the tree is NULL, return
        return;
    }
    if (isLeaf(tree))
    {
        if (winner(tree->board, tree->player))
        {
            tree->score = tree->player;
        }
        else
        {
            tree->score = 'T';
        }
    }
    else
    {

        int i, j;
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                if (tree->children[i][j] != NULL)
                {
                    calculateScores(tree->children[i][j]);
                }
            }
        }
        // all our children have scores...

        tree->score = tree->player;   // Assuming we don't override it
        char oppositePlayer = (tree->player== 'X' ? 'O' : 'X');
        for(i=0; i<3; i++)
        {
            for(j=0; j<3; j++)
            {
                if(tree->children[i][j] != NULL)
                {
                    if (tree->children[i][j]->player = oppositePlayer)  // what is a rating?
                    {
                        tree->score = oppositePlayer;
                        return;  /* one of the children leads to opposite winner.  Don't bother checking others */
                    }
                    if (!winner(tree->children[i][j]->board, tree->children[i][j]->player))
                    {
                        tree->score = 'T';  // we do NOT return immediately here
                    }
                }
            }
        }

    }
};
