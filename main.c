#include "nodesUtilities.h"

void initTreeFromConsole(Tree_t* tree) {
    int nodsNumber = 0; // int is ok because number of nods less than 10000
    printf("please enter nodes number\n");
    scanf("%d", &nodsNumber);

    tree->notLeafsArr = (NodesArr_t*)malloc(sizeof(NodesArr_t));
    initNodesArr(tree->notLeafsArr, nodsNumber);
    
    tree->leafsArr = (NodesArr_t*)malloc(sizeof(NodesArr_t));
    initNodesArr(tree->leafsArr, nodsNumber);

    int nodeVal;
    int parentNodeVal;
    int nodeType;
    for (int i = 0; i < nodsNumber; ++i) {
        scanf("%d %d %d", &nodeVal, &parentNodeVal, &nodeType);
        Node_t * newNode = (Node_t*)malloc(sizeof(Node_t)); // create new Node
        newNode->val = nodeVal; // set node val
        newNode->parent = NULL; // set parent as NULL to understand 
        newNode->nodeType = nodeType; // set node flag
        // find parent for node (leafs coundn't have parents)
        for (int j = 0; j < tree->notLeafsArr->size; ++j) {
            if (tree->notLeafsArr->ptr[j]->val == parentNodeVal) {
                newNode->parent = tree->notLeafsArr->ptr[j];
            }
        }
        // add not a leaf to temp erray
        if (nodeType == notLeaf) {
            tree->notLeafsArr->ptr[tree->notLeafsArr->size++] = newNode;
        // add leafs to leafs array
        } else { // if nodeType == leaf
            tree->leafsArr->ptr[tree->leafsArr->size++] = newNode;
        }
    }
}

void deInitTree(Tree_t* tree) {
    for (int i = 0; i < tree->leafsArr->size; ++i) {
        free(tree->leafsArr->ptr[i]);
    }
    for (int i = 0; i < tree->notLeafsArr->size; ++i) {
        free(tree->notLeafsArr->ptr[i]);
    }
    tree->leafsArr->size = 0;
    tree->notLeafsArr->size = 0;
    deInitNodesArr(tree->leafsArr);
    deInitNodesArr(tree->notLeafsArr);
    free(tree->leafsArr);
    free(tree->notLeafsArr);
}

// return intersected node
// l1Len will be returned length of first  list
// l2Len will be returned length of second list
Node_t* findTwoListsIntersection(Node_t* head1, Node_t* head2, int* l1Len, int* l2Len) {
    Node_t* p1 = head1;
    Node_t* p2 = head2;  
    if (p1 == NULL || p2 == NULL) return NULL;

    while (p1 != NULL && p2 != NULL && p1 != p2) {
        p1 = p1->parent;
        p2 = p2->parent;

        ++(*l1Len);
        ++(*l2Len);
        // Any time they collide or reach end together without colliding 
        // then return any one of the pointers.
        if (p1 == p2) return p1;

        // Once both of them go through reassigning, 
        // they will be equidistant from the collision point.
        if (p1 == NULL) {
            p1 = head2;
            *l2Len = 0;
        }
        if (p2 == NULL) {
            p2 = head1;
            *l1Len = 0;
        }
    }
    return p1;
}

// functiom will return IntArr_t which has path from leafVal1 to leafVal2
IntArr_t findPathBetweenLeafs(const NodesArr_t* nodsArr, int leafVal1, int leafVal2) {
    IntArr_t arr; 
    if (leafVal1 == leafVal2) { // if need to find path from leaf to the same leaf
        arr.size = 1;
        arr.ptr = (int*)malloc(sizeof(int));
        arr.ptr[0] = leafVal1;
        return arr;
    }
    
    Node_t* leaf1 = NULL;
    Node_t* leaf2 = NULL;
    for (int i = 0; i < nodsArr->size; ++i) {
        if (leafVal1 == nodsArr->ptr[i]->val)
            leaf1 = nodsArr->ptr[i];
        if (leafVal2 == nodsArr->ptr[i]->val)
            leaf2 = nodsArr->ptr[i];
    }

    int list1Len = 0;
    int list2Len = 0;
    Node_t* interSectNode = findTwoListsIntersection(leaf1, leaf2, &list1Len, &list2Len);

    // allocate result arr
    arr.ptr = (int*)malloc((list1Len + list2Len + 1)*sizeof(int));
    arr.size = list1Len + list2Len + 1; // + 1 because of intersected

    int cnt = 0;
    // append points from leaf1 intersected node to result arr
    while (leaf1 != interSectNode) {
        arr.ptr[cnt++] = leaf1->val;
        leaf1 = leaf1->parent;
    }
    arr.ptr[cnt] = interSectNode->val;
    cnt = 0;
    // append points from leaf2 to intersected node to result arr in backward order
    while (leaf2 != interSectNode) {
        arr.ptr[arr.size - 1 - (cnt++)] = leaf2->val;
        leaf2 = leaf2->parent;
    }
    return arr;    
}

// read tests from console and find path between leafs
void processTestCasesFromConsole(Tree_t* tree) {
    int numberOfTestCases = 0;
    scanf("%d", &numberOfTestCases);
    int leaf1 = 0, leaf2 = 0;
    IntArr_t arr;
    for (int i = 0; i < numberOfTestCases; ++i) {
        scanf("%d %d", &leaf1, &leaf2);
        arr = findPathBetweenLeafs(tree->leafsArr, leaf1, leaf2);
        printIntArr(&arr);
        free(arr.ptr);
    }
}

int main () {
    Tree_t tree;
    initTreeFromConsole(&tree);
    // printNodesArr(tree.leafsArr); // print array for understand leafs
    processTestCasesFromConsole(&tree);
    deInitTree(&tree);
}