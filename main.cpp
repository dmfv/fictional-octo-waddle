#include <iostream>

struct Node {
    Node (int val = 0, Node* parent = nullptr) : 
        val(val), parent(parent) {}
    int val;
    Node* parent;
};

struct NodesArr {
    Node** ptr;
    volatile size_t size;
    size_t capacity;
};

struct IntArr {
    int* ptr;
    size_t size;
};

struct Tree {
    NodesArr* leafsArr;
};

enum nodsType {
    leaf = 0,
    notLead = 1,
};

void initNodesArr (NodesArr* arr, int size) {
    arr->ptr = (Node**)malloc(size * sizeof(Node*));
    arr->capacity = size;
    arr->size = 0;
}

void printNodesArr (NodesArr* nodsArr) {
    printf("printing tree with size %d\n", nodsArr->size);
    if (!nodsArr) return;
    for (int i = 0; i < nodsArr->size; ++i) {
        Node* leaf = nodsArr->ptr[i];
        while (leaf) {
            printf("%d ", leaf->val);
            leaf = leaf->parent;
        }
        printf("\n");
    }
}

void initTreeFromConsole(Tree* tree) {
    int nodsNumber = 0; // int is ok because number of nods less than 10000
    scanf("%d", &nodsNumber);

    NodesArr nodsArr;
    initNodesArr(&nodsArr, nodsNumber);
    
    tree->leafsArr = (NodesArr*)malloc(sizeof(NodesArr));
    initNodesArr(tree->leafsArr, nodsNumber);

    int nodVal;
    int parentNodeVal;
    int nodType;
    for (int i = 0; i < nodsNumber; ++i) {
        scanf("%d %d %d", &nodVal, &parentNodeVal, &nodType);
        nodsArr.ptr[i] = (Node*) malloc(sizeof(Node));
        nodsArr.ptr[i]->val = nodVal;
        nodsArr.ptr[i]->parent = nullptr;
        ++nodsArr.size;
        for (int j = 0; j < i; ++j) {
            if (nodsArr.ptr[j]->val == parentNodeVal) {
                nodsArr.ptr[i]->parent = nodsArr.ptr[j];
            }
        }
        if (nodType == leaf) {
            tree->leafsArr->ptr[tree->leafsArr->size++] = nodsArr.ptr[i];
        }
    }
}

Node* findTwoListsIntersection(Node* head1, Node* head2, int* l1Len, int* l2Len) {
    Node* p1 = head1;
    Node* p2 = head2;  
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

IntArr findPathBetweenLeafs(NodesArr* nodsArr, int leafVal1, int leafVal2) {
    Node* leaf1 = NULL;
    Node* leaf2 = NULL;
    for (int i = 0; i < nodsArr->size; ++i) {
        if (leafVal1 == nodsArr->ptr[i]->val)
            leaf1 = nodsArr->ptr[i];
        if (leafVal2 == nodsArr->ptr[i]->val)
            leaf2 = nodsArr->ptr[i];
    }

    IntArr arr; 
    if (leaf1 == leaf2) {
        arr.size = 1;
        arr.ptr = (int*)malloc(sizeof(int));
        arr.ptr[0] = leaf1->val;
        return arr;
    }

    int list1Len = 0;
    int list2Len = 0;
    Node* interSectNode = findTwoListsIntersection(leaf1, leaf2, &list1Len, &list2Len);

    // allocate result arr
    arr.ptr = (int*)malloc((list1Len+list2Len)*sizeof(int));
    arr.size = list1Len + list2Len + 1; // + 1 because of intersected 

    int cnt = 0;
    while (leaf1 != interSectNode) {
        arr.ptr[cnt++] = leaf1->val;
        leaf1 = leaf1->parent;
    }
    arr.ptr[cnt] = interSectNode->val;
    cnt = 0;
    while (leaf2 != interSectNode) {
        arr.ptr[arr.size - 1 - (cnt++)] = leaf2->val;
        leaf2 = leaf2->parent;
    }
    // for (int i = 0; i < list1Len; ++i) {
    //     arr.ptr[i] = leaf1->val;
    //     leaf1->parent;
    // }
    // arr.ptr[list1Len] = interSectNode->val;
    // for (int i = 0; i < list2Len; ++i) {
    //     arr.ptr[arr.size-1-i] = leaf2->val;
    //     leaf2->parent;
    // }

    return arr;    
}

void printIntArr(IntArr* arr) {
    printf("printing int arr with size %d\n", arr->size);
    for (int i = 0; i < arr->size; ++i) {
        printf("%d ", arr->ptr[i]);
    }
    printf("\n");
}


int main () {
    Tree tree;
    initTreeFromConsole(&tree);
    printNodesArr(tree.leafsArr);
    IntArr arr1 = findPathBetweenLeafs(tree.leafsArr, 4, 2); // 4 5 2
    IntArr arr2 = findPathBetweenLeafs(tree.leafsArr, 4, 3); // 4 5 10 3
    IntArr arr3 = findPathBetweenLeafs(tree.leafsArr, 3, 2); // 3 10 5 2
    printIntArr(&arr1);
    printIntArr(&arr2);
    printIntArr(&arr3);
}


// 5
// 10 10 1
// 5 10 1
// 3 10 0
// 2 5 0
// 4 5 0

// 8
// 10 10 1
// 5 10 1
// 2 10 0
// 3 10 0
// 4 5 0
// 6 5 0
// 8 5 0
// 9 5 0


