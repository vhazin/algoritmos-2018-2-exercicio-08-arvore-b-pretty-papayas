#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 19

typedef enum { FALSE, TRUE } bool;
typedef struct node {
    bool isLeaf;
    int keyCounter;
    int keyArray[ORDER];
    struct node *children[ORDER-1];
} TREE;

TREE *initTREE(void);
int search(TREE *, int);
void insert(TREE *, int);
void printTREE(TREE*);
 
int main(void){
    int length;
    scanf("%d", &length);
    int array[length];
    TREE *root = initTREE();
    for(int index = 0; index < length; index++){
        int key;
        scanf("%d", &key);
        search(root, key);
        insert(root, key);
        search(root, key);
    }
    printTREE(root);
    free(root);
    return 0;
}

TREE* initTREE(void){
  TREE *child = (TREE *)malloc(sizeof(TREE));
  child->isLeaf = TRUE;
  child->keyCounter = 0;

  return child;
}

static int searchKey(int keyCounter, int *keyArray, int key){
  int limit = keyCounter, lower = -1, center;
  while(lower + 1 < limit){
    center = (lower + limit)/2;
    if(keyArray[center] == key)
      return center;
    else if(keyArray[center] < key)
      lower = center;
    else
      limit = center;
  }
  return limit;
}

int search(TREE *tree, int key){
  int index;
  if(!tree->keyCounter)
    return 0;
    
  index = searchKey(tree->keyCounter, tree->keyArray, key);
  if(index < tree->keyCounter && tree->keyArray[index] == key)
    return 1;
  else
    return(!tree->isLeaf && search(tree->children[index], key));
}

TREE* split(TREE *tree, int *median, int key){
  TREE *auxiliar;
  int center, index;

  index = searchKey(tree->keyCounter, tree->keyArray, key);
  if(index < tree->keyCounter && tree->keyArray[index] == key)
    return 0;

  if(tree->isLeaf){
    memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
    tree->keyArray[index] = key;
    tree->keyCounter++;
  } else {
    auxiliar = split(tree->children[index], &center, key);
    if(auxiliar){
      memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
      memmove(&tree->children[index + 2], &tree->children[index + 1], sizeof(*(tree->keyArray)) * (tree->keyCounter - index));
      tree->keyArray[index] = center;
      tree->children[index + 1] = auxiliar;
      tree->keyCounter++;
    }
  }

  if (tree->keyCounter >= ORDER){
    center = tree->keyCounter/2;
    *median = tree->keyArray[center];

    auxiliar = (TREE *)malloc(sizeof(*auxiliar));
    auxiliar->keyCounter = tree->keyCounter - center - 1;
    auxiliar->isLeaf = tree->isLeaf;
    memmove(auxiliar->keyArray, &tree->keyArray[center + 1], sizeof(*(tree->keyArray)) * auxiliar->keyCounter);

    if (!tree->isLeaf)
      memmove(auxiliar->children, &tree->children[center + 1], sizeof(*(tree->children)) * (auxiliar->keyCounter + 1));
    
    tree->keyCounter = center;
    return auxiliar;
  }
  else
    return 0;
}

void insert(TREE *tree, int key){
  int median;
  TREE *leftChild, *rightChild;
  rightChild = split(tree, &median, key);

  if(rightChild){
    leftChild = (TREE *)malloc(sizeof(*leftChild));
    memmove(leftChild, tree, sizeof(*tree));
    tree->keyCounter = 1;
    tree->isLeaf = FALSE;
    tree->keyArray[0] = median;
    tree->children[0] = leftChild;
    tree->children[1] = rightChild;
  }
}

void printTREE(TREE* root){
    if(root){
        for(int index = 0; index < root->keyCounter; index++){
            printf("%d ", root->keyArray[index]);
        }
    }
}
