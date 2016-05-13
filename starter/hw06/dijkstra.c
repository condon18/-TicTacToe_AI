#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "main.h"
/*
 * @AUTHOR Teresa Condon
 * @Date   April 16, 2016
 * @Class  CS 305  HW 6.

 Implements Dijkstra's Algorithm (which finds the shortest path in a graph).

*/


/*
	Implements Dijkstra's algorithm as follows:
	Find source node by name lookup
	Set the source node’s dValue to 0.
	While the graph is not empty :
	   Let U = getMin(g)  //use getMin function
	   For each neighbor N of U:
	     If N’s dValue > [U’s dValue + cost(U, N)], update N’s dValue to [U’s dvalue + cost(U, N)]. Also, update the predecessor for N to be U.
	   Set U’s color to black


*/
void dijkstra(Graph * g, char * source)
{
    int i, srcIndx = -1;
    for (i=0; i < g->V; i++)    // find node by name
    {
        if (strcmp(source, g->array[i].label) == 0)
        {
            srcIndx = i;
        }
    }
    assert(srcIndx >= 0 );
    g->array[srcIndx].dValue = 0;
    while (!isEmpty(g))
    {
        int u = getMin(g);
        AdjListNode *np = g->array[u].head;   // a pointer to the first neighbor
        while (np != NULL)   // Foreach neighbor N of U
        {
            int n = np->dest;
            int newVal = g->array[u].dValue + np->cost;
            if (g->array[n].dValue > newVal)
            {
                g->array[n].dValue = newVal;
                g->array[n].pred = u;
            }
            np=np->next;
            g->array[u].color = BLACK;
        }
    }
}

    /*
     * Return 1 if graph is empty or has no white nodes
    */
    int isEmpty(Graph * g)
    {
        if (g->array->head == NULL )
        {
            return 1;
        }
        int i;
        for (i=0; i<g->V; i++)
        {
            if (g->array[i].color == WHITE)
            {
                return 0;
            }
        }
        return 1;
    }

// returns the lowest index of a white (unvisited) node
    int getMin(Graph * g)
    {

        if (isEmpty(g))
        {
            return -1;
        }

        int i, min_i = -1, min = INF;

        for (i=0; i<g->V; i++ )
        {
            if (g->array[i].color == WHITE && g->array[i].dValue < min)   // if "white" and minimal
            {
                min = g->array[i].dValue;
                min_i = i;
            }
        }
        assert(min_i >= 0);
        return min_i;
    }
