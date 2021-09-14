#include <stdlib.h>
#include <stdio.h>

#define N 7 //number of nodes

void display_node(int vertex_value){
	char node_value = vertex_value + 'A';  //calculating ASCII value of vertex and storing in char
	printf("%c ", node_value);
}

void dijkstra_algo(int graph[N][N], int start){  //input 2-D adjacent matrix 7x7, 7 nodes, displays connections 
	int cost[N][N];
	int distance[N];
	int previous[N];
	int permanent[N];
	int current, minimum, dist, prev;

	for(int y = 0; y < N; y++){
		for(int x = 0; x < N; x++){
			if(graph[y][x] == 0){
				cost[y][x] = 39273; //large number
			}
			else{
				cost[y][x] = graph[y][x];
			}
		}
	}

	for(int a = 0; a < N; a++){
		distance[a] = cost[start][a]; //setting distances from start using cost matrix
		previous[a] = start;	      //setting start value to previous... move on
		permanent[a] = 0;			  //nothing permanent yet
	}

	distance[start] = 0;
	permanent[start] = 1; //1 permanent so far.... A
	current = 0;
	int count = 0;

	//printf("\nPermanent Nodes .... ");
	//display_node(start);

	while(count < N){
		minimum = 39273;

		for(int b = 1; b < N; b++){
			dist = distance[current] + cost[current][b]; //shortest distanct calculation

			if(dist < distance[b] && permanent[b] == 0){
				distance[b] = dist; //store current distance in distance array
				previous[b] = current;  //use current as previous, then move on...
			}
			if(minimum > distance[b] && permanent[b] == 0){
				minimum = distance[b]; //store distance as path minimum
				current = b;
			}
		}

		permanent[current] = 1;
		count++;
	}
	printf("\n");

	for(int c = 1; c < N; c++){
		printf("\nA -> ");
		display_node(c);
		printf(" is %d", distance[c]);
	}
}


int main(){

	//Adjacent Matrix, shows connections between each node and distances
	int adj_matrix[N][N] = {{0,1,3,0,0,10,0},
				  			{1,0,1,7,5,0,2},
				  			{3,1,0,9,3,0,0},
							{0,7,9,0,2,1,12},
							{0,5,3,2,0,2,0},
							{10,0,0,1,2,0,0},
							{0,2,0,12,0,0,0}};

	dijkstra_algo(adj_matrix, 0);

	printf("\n\nProgram Complete! \n");

	return 0;
}