#include <stdio.h>
#include <stdlib.h>

typedef struct vertex{
    int data;
    int distance;
    struct vertex* next;
}vertex, * vertex_ptr;

typedef struct edge{
    unsigned int start;
    unsigned int end;
    unsigned int weight;
} edge, *edge_ptr;

edge_ptr edge_set_ptr;
int number_of_vertex;

int number_of_visited_vertex;

int number_of_edge_sets;

int unvisited[100000];

int number_of_visited;

int i;

vertex graph_vertex;

// This pointer is the dynamic pointer for the 
// linkedlist nodes from 0 to number of vertices -1
vertex_ptr linked_list_ptr;

edge_ptr edge_set_ptr;


edge_ptr minimum_spanning_tree;

// This is used for infinity distance for node
#define INF 2147483647;


// This is used for selecting next node to be visited
int min_distance;

//This is the pointer for unvisited array
int unvisited[100000];




