#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 40

typedef enum{ FALSE, TRUE } bool;
typedef struct node{
    bool isLeaf;
    int keyCounter;
    int keyArray[ORDER];
    struct node *children[ORDER-1];
} TREE;

TREE *initTREE(void);
int search(TREE *, int);
void insert(TREE *, int);
void printTREE(TREE *, int);

int main(void){
    TREE *root = initTREE();
    int key;
    while(scanf("%d",&key) == 1){
        search(root, key);
        insert(root, key);
        search(root, key);
    }
    printTREE(root, 40);
    free(root);
    return 0;
}

TREE *initTREE(void){
    TREE *child = (TREE *)malloc(sizeof(child));
    child->isLeaf = TRUE;
    child->keyCounter = 0;
    return child;
}

static int searchKey(int keyCounter, int *keyArray, int key){
    int lower = -1, center;
    while (lower + 1 < keyCounter){
        center = (lower + keyCounter) / 2;
        if (keyArray[center] == key)
            return center;
        else if (keyArray[center] < key)
            lower = center;
        else
            keyCounter = center;
    }
    return keyCounter;
}

int search(TREE *tree, int key){
    if (tree->keyCounter){
        int index = searchKey(tree->keyCounter, tree->keyArray, key);
        if (index < tree->keyCounter && tree->keyArray[index] == key)
            return 1;
        else
            return (!tree->isLeaf && search(tree->children[index], key));
    }
    return 0;
}

TREE *split(TREE *tree, int *median, int key){
    TREE *auxiliar;
    int center, index = searchKey(tree->keyCounter, tree->keyArray, key);
    if (index < tree->keyCounter && tree->keyArray[index] == key)
        return 0;
    
    if (tree->isLeaf){
        memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
        tree->keyArray[index] = key;
        tree->keyCounter++;
    } else {
        auxiliar = split(tree->children[index], &center, key);
        if (auxiliar){
            memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
            memmove(&tree->children[index + 2], &tree->children[index + 1], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
            tree->keyArray[index] = center;
            tree->children[index + 1] = auxiliar;
            tree->keyCounter++;
        }
    }

    if (tree->keyCounter >= ORDER){
        center = tree->keyCounter / 2;
        *median = tree->keyArray[center];
        auxiliar = (TREE *)malloc(sizeof(*auxiliar));
        auxiliar->keyCounter = tree->keyCounter - center - 1;
        auxiliar->isLeaf = tree->isLeaf;
        memmove(auxiliar->keyArray, &tree->keyArray[center + 1], sizeof(*(tree->keyArray)) * auxiliar->keyCounter);
        if (!tree->isLeaf)
            memmove(auxiliar->children, &tree->children[center + 1], sizeof(*(tree->children)) * (auxiliar->keyCounter + 1));
        tree->keyCounter = center;
        return auxiliar;
    } else
        return 0;
}

void insert(TREE *tree, int key){
    TREE *leftChild, *rightChild;
    int median;
    rightChild = split(tree, &median, key);

    if (rightChild){
        leftChild = (TREE *)malloc(sizeof(*leftChild));
        memmove(leftChild, tree, sizeof(*tree));
        tree->keyCounter = 1;
        tree->isLeaf = FALSE;
        tree->keyArray[0] = median;
        tree->children[0] = leftChild;
        tree->children[1] = rightChild;
    }
}

void printTREE(TREE *root, int numSpaces){
    if (root){
        char space = ' ';
        printf("%*c", numSpaces, space);
        printf("| ");
        for (int index = 0; index < root->keyCounter; index++){
            if (root->isLeaf)
                printf("%d ", root->keyArray[index]);
        }
        printf("|\n");
        printTREE(root->children[1], numSpaces + 10);
    }
}
