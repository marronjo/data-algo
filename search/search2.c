#include <stdio.h>
#include <stdlib.h>


// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

struct tree{
	int doc_id;
	char *name;
	int word_count;
	struct tree *right, *left;
};

typedef struct tree tree_node;


int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	tree_node *init = (tree_node*)malloc(sizeof(tree_node));

	if(init){ //check if malloc worked... Initialise left and right
		init->left = NULL;
		init->right = NULL;
    return 1;
	}
	else{ //if init does not exist/ malloc failed
		printf("Malloc Failed!");
		return 0;
	}
}

int
bstdb_add ( tree_node **root, char *name, int word_count) {
	// This function should create a new node in the binary search tree,
	// populate it with the name and word_count of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node

	//srand((unsigned)time(NULL)); //random seed for doc id, used initially improved later

	int doc_id = 25;
  //rand();

	tree_node *temp = (tree_node*)malloc(sizeof(tree_node)); //temporary pointer to create root or new node of bst

	if(temp != NULL){						//Check if malloc worked!
		if(*root == NULL){ 					//root empty?
			temp->name = name; 				//store name in bst
			temp->word_count = word_count;	//store word count in bst
			temp->doc_id = doc_id;			//store docdid in bst
			temp->left = NULL; 				//null pointer to each branch of root ...
			temp->right = NULL;

			*root = temp;					//place temp into root... adds every element into bst
		}
		else{
			if(doc_id < (*root)->doc_id){ //go to left node
				bstdb_add((&(*root)->left), name, word_count);
			}
			else if(doc_id == (*root)->doc_id){
				bstdb_add(&(*root), name, word_count);	//recurse function with same arguements, will use rand function again for new doc id
			}
			else{ //go to right node
				bstdb_add((&(*root)->right), name, word_count);
			}
		}
		return doc_id;
	}
	else{
		return -1;
	}
}

int
bstdb_get_word_count (tree_node* node,  int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1

	if(node == NULL){
		return -1;
	}
	else if(doc_id < node->doc_id){
		bstdb_get_word_count(node->left, doc_id);
	}
	else if(doc_id == node->doc_id){
		return node->word_count;
	}
	else{
		bstdb_get_word_count(node->right, doc_id);
	}
}

char*
bstdb_get_name (tree_node* node, int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	if(node == NULL){
		return NULL;							//nothing present
	}
	else if(doc_id < node->doc_id){
		bstdb_get_name(node->left, doc_id);		//recurse using left node as input
	}
	else if(doc_id == node->doc_id){
		return node->name;						//node found, return name
	}
	else{
		bstdb_get_name(node->right, doc_id);	//recurse using right node as input
	}
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result

	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result?
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
	printf("woop woop");
}

void
bstdb_quit ( tree_node *root) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	if(root != NULL){
    bstdb_quit(root->left);//delete subtrees first left
    bstdb_quit(root->right); // ^^ then right right
    free(root);
  }
}

int main(){
  tree_node *item;
  item = NULL;

  bstdb_init();
  bstdb_add(&item, "Charlie and Choc Factory", 1000);
  printf(" %d ", bstdb_get_word_count(item, 25));
  printf(" %s ", bstdb_get_name(item, 25));
  bstdb_quit(item);
  return 0;
}
