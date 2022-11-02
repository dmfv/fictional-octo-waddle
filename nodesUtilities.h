#ifndef NODES_UTILITIES_H
#define NODES_UTILITIES_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum NodsType { 
    leaf = 0,
    notLeaf = 1,
} NodeType_e;

typedef struct Node {
    int32_t val;
    uint8_t nodeType;  // possible to insert something for 3 bytes for "free" (because of packing for 64 bit win)
    struct Node* parent;
} Node_t;

typedef struct NodesArr {
    Node_t** ptr;
    volatile size_t size;
    size_t capacity;
} NodesArr_t;

typedef struct IntArr {
    int* ptr;
    size_t size;
} IntArr_t;

typedef struct Tree {
    NodesArr_t* leafsArr; 
    NodesArr_t* notLeafsArr;
} Tree_t;

void initNodesArr (NodesArr_t* arr, const int size);
void deInitNodesArr (NodesArr_t* arr);
void printNodesArr (const NodesArr_t* nodsArr);
void printIntArr(const IntArr_t* arr);

#endif