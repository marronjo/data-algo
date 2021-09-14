#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM 3 //maximum numbers of connected nodes to each node
#define NODES 6 //number of nodes in graph

typedef struct node{
	char name;
	int visited;
	struct node* next[MAX_NUM];
}node;

void insert_edge(node *start, node* end){
	int i = 0;
	node* now = start->next[i]; //points current node to first adjacent node

	while(now != NULL){
		i = i + 1;
		now = start->next[i]; 	//adds all edges between now node and adjacent nodese
	} 
	start->next[i] = end;	//final adjacent node connected to start
}

node* add_node(char name){
	node* new_node = (node*)malloc(sizeof(node));
	new_node->name = name;

	for(int i = 0; i < MAX_NUM; i++){
		new_node->next[i] = NULL; //points new node to 3 adjacent null nodes
	}
	return new_node;
}

void visited_setup(node* node_array[]){
	for(int i = 0; i < NODES; i++){
		node_array[i]->visited = 0; 	//initialising visits, initially all 0
	}
}

void depth_first(node* stem){
	if(stem->visited != 1 && stem->name < 71 && stem->name > 64){

		printf("%c  ", stem->name);
		stem->visited = 1;			//node has been visited
		int i = 0;
		node* now = stem->next[i];

		while(now != NULL){ //recursively calls each node and each neighbour
			depth_first(now);
			i = i + 1;
			now = stem->next[i];
		}
	}
}

void print_nodes(node* stem){
	int i = 0;
	node* now = stem->next[i];

	while(now != NULL){
		if(now->visited != 1){
			printf("%c  ", now->name);
			now->visited = 1;
		}
		i = i + 1;
		now = stem->next[i];
	}
}

void breadth_first(node* stem){
	if(stem->visited != 1){
		printf("%c  ", stem->name);
		stem->visited = 1;
	}

	print_nodes(stem);

	int i = 0;
	node* now = stem->next[i];

	while(now != NULL){
		print_nodes(now);

		i = i + 1;
		now = stem->next[i];
	}
}

int main(){

	node* node_array[NODES]; //array to hold the 6 nodes in the graph
	node* stem = node_array[0]; //first node is first index in array

	char name = 'A';  //stores ASCII value of A in name;

	printf("Loading in values.... ");
	for(int i = 0; i < NODES; i++){
		node_array[i] = add_node(name);
		printf("%c ", node_array[i]->name);
		name = name + 1; 		//add 1 to ASCII value ... A - B - C ...
	}	

	//add each connection on graph.....
	insert_edge(node_array[0], node_array[1]); //connecting A -> B
	insert_edge(node_array[1], node_array[2]); //connecting B -> C
	insert_edge(node_array[0], node_array[3]); //connecting A -> D
	insert_edge(node_array[0], node_array[4]); //connecting A -> E
	insert_edge(node_array[4], node_array[3]); //connecting E -> D
	insert_edge(node_array[1], node_array[3]); //connecting B -> D
	insert_edge(node_array[2], node_array[1]); //connecting C -> B
	insert_edge(node_array[2], node_array[3]); //connecting C -> D
	insert_edge(node_array[3], node_array[5]); //connecting D -> F
	insert_edge(node_array[5], node_array[2]); //connecting F -> C

	visited_setup(node_array);

	printf("\n\nDFS:\t");
	depth_first(node_array[0]);

	visited_setup(node_array);

	printf("\nBFS:\t");
	breadth_first(node_array[0]);


	printf("\n\nProgram Complete!\n");
	return 0;
}