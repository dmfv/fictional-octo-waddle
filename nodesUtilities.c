#include "nodesUtilities.h"

void initNodesArr (NodesArr_t* arr, const int size) {
    arr->ptr = (Node_t**)malloc(size * sizeof(Node_t*));
    arr->size = 0;
}

void deInitNodesArr (NodesArr_t* arr) {
    free(arr->ptr);
    arr->size = 0;
}

void printNodesArr (const NodesArr_t* nodsArr) {
    printf("printing tree with size %lu\n", nodsArr->size);
    if (!nodsArr) return;
    for (int i = 0; i < nodsArr->size; ++i) {
        Node_t* leaf = nodsArr->ptr[i];
        while (leaf != NULL) {
            printf("%d ", leaf->val);
            leaf = leaf->parent;
        }
        printf("\n");
    }
}

void printIntArr(const IntArr_t* arr) {
    printf("print arr: "); // delete this if necessary
    for (int i = 0; i < arr->size; ++i) {
        printf("%d ", arr->ptr[i]);
    }
    printf("\n");
}