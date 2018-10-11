#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024

//Define type 'bool' as enumeration of FALSE (0), TRUE (1);
typedef enum { FALSE, TRUE } bool;

//Define type 'Tree' as struct of {
typedef struct node{
  int isLeaf;
  int keyAmmount;
  int keyArray[MAX];
  struct node *children[MAX+1];
} Tree;

//Create prototype functions
Tree* initialize(void);
int search(Tree *, int);
void insert(Tree *, int);
void printKeys(Tree *);
void memFree(Tree *);

//Main function
int main(void){
  Tree *tree = initialize();
  search(tree, 12);
  insert(tree, 12);
  search(tree, 12);
  memFree(tree);

  tree = initialize();
  for(int iterator = 0; iterator < 100; iterator++) {
      search(tree, iterator);
      insert(tree, iterator);
      search(tree, iterator);
  }

  for(int iterator = 0; iterator < 100; iterator++) {
      search(tree, iterator);
      insert(tree, iterator);
      search(tree, iterator);
  }    
  memFree(tree);

  tree = initialize();
  for(int iterator = 0; iterator < 10000000; iterator += 2) {
      search(tree, iterator);
      insert(tree, iterator);
      search(tree, iterator+1);
      search(tree, iterator);
  }
  memFree(tree);

  return 0;
}

/* ----------  helper functions  ------------ */
Tree* initialize(void){
  Tree *child = (Tree *)malloc(sizeof(Tree));
  child->isLeaf = TRUE;
  child->keyAmmount = 0;

  return child;
}

void memFree(Tree *tree){
  if(!tree->isLeaf){
    for(int index = 0; index < tree->keyAmmount + 1; index++){
      memFree(tree->children[index]);
    }
  }
  free(tree);
}

static int searchKey(int keyAmmount, int *keyArray, int key){
  int high = keyAmmount, low = -1, center;
  while(low + 1 < high){
    center = (low + high)/2;
    if(keyArray[center] == key)
      return center;
    else if(keyArray[center] < key)
      low = center;
    else
      high = center;
  }
  return high;
}

int search(Tree *tree, int key){
  int index;
  if(!tree->keyAmmount)
    return 0;
    
  index = searchKey(tree->keyAmmount, tree->keyArray, key);
  if(index < tree->keyAmmount && tree->keyArray[index] == key)
    return 1;
  else
    return(!tree->isLeaf && search(tree->children[index], key));
}

static Tree* split(Tree *tree, int *median, int key){
  Tree *auxiliar;
  int center, index;

  index = searchKey(tree->keyAmmount, tree->keyArray, key);
  if(index < tree->keyAmmount && tree->keyArray[index] == key)
    return 0;

  if(tree->isLeaf){
    memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyAmmount - index));
    tree->keyArray[index] = key;
    tree->keyAmmount++;
  } else {
    auxiliar = split(tree->children[index], &center, key);
    if(auxiliar){
      memmove(&tree->keyArray[index + 1], &tree->keyArray[index], sizeof(*(tree->keyArray)) * (tree->keyAmmount - index));
      memmove(&tree->children[index + 2], &tree->children[index + 1], sizeof(*(tree->keyArray)) * (tree->keyAmmount - index));
      tree->keyArray[index] = center;
      tree->children[index + 1] = auxiliar;
      tree->keyAmmount++;
    }
  }

  if (tree->keyAmmount >= MAX){
    center = tree->keyAmmount/2;
    *median = tree->keyArray[center];

    auxiliar = (Tree *)malloc(sizeof(*auxiliar));
    auxiliar->keyAmmount = tree->keyAmmount - center - 1;
    auxiliar->isLeaf = tree->isLeaf;
    memmove(auxiliar->keyArray, &tree->keyArray[center + 1], sizeof(*(tree->keyArray)) * auxiliar->keyAmmount);

    if (!tree->isLeaf)
      memmove(auxiliar->children, &tree->children[center + 1], sizeof(*(tree->children)) * (auxiliar->keyAmmount + 1));
    
    tree->keyAmmount = center;
    return auxiliar;
  }
  else
    return 0;
}

void insert(Tree *tree, int key){
  int median;
  Tree *leftChild, *rightChild;
  rightChild = split(tree, &median, key);

  if(rightChild){
    leftChild = (Tree *)malloc(sizeof(*leftChild));
    memmove(leftChild, tree, sizeof(*tree));
    tree->keyAmmount = 1;
    tree->isLeaf = 0;
    tree->keyArray[0] = median;
    tree->children[0] = leftChild;
    tree->children[1] = rightChild;
  }
}
