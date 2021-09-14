#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct binary_tree {
  char data;
  struct binary_tree *left, *right;
};

typedef struct binary_tree tree_node;

void tree_insert(tree_node** root, char data){
  tree_node *temp = (tree_node*)malloc(sizeof(tree_node)); //temporary pointer to create root or new node

  if(*root == NULL){ //root empty?
    temp->data = data;
    temp->left = NULL; //null pointer to each branch of root ...
    temp->right = NULL; //^^

    *root = temp;

  }
  else{
    if(data < (*root)->data){ //go to left node
      tree_insert(&(*root)->left, data);
    }
    else{ //go to right node
      tree_insert(&(*root)->right, data);
    }
  }
}

tree_node* tree_search(tree_node* root, char data){
  if(root == NULL){
    printf("\n%c not in tree", data);
    return NULL;
  }
  if(data < (root->data)){//move to left side and continue search
    tree_search((root->left), data);
  }
  else if(data == (root->data)){
    printf("\n%c in tree", data);
    return root;
  }
  else{
    tree_search((root->right), data);
  }
}

void print_tree_sorted(tree_node* root){
  if(root != NULL){
    print_tree_sorted(root->left); //find leftmost node
    printf("%c ", root->data); //print node
    print_tree_sorted(root->right);//traverse right nodes
  }
}

void tree_delete(tree_node* root){
  if(root != NULL){
    tree_delete(root->left);//delete subtrees first left
    tree_delete(root->right); // ^^ then right right
    free(root);
  }
}

int main(){

  tree_node *item;
  item = NULL;

  srand((unsigned)time(NULL)); //generate random seed for rand() different each time

  char info[] = "FLOCCINAUCINIHILIPILIFICATTION";
  char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  printf("ADDING:   ");
  for(int i = 0; i < sizeof(info); i++){
    tree_insert(&item, info[i]); //insert all elements of info into tree
    printf("%c ", info[i]);
  }
  printf("\nSORTED: ");
  print_tree_sorted(item);

  int r_index = rand() % (sizeof(info) - 1);
  int r_index2 = rand() % (sizeof(info) - 1);

  tree_search(item, letters[r_index]);
  tree_search(item, letters[r_index2]);

  tree_delete(item);

  return 0;
}
