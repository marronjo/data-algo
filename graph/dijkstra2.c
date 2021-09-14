#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUM 7666 //max size of adj matrix
#define N 7666 //number of nodes

void display_node(int vertex_value){
	printf("%d ", vertex_value);
}

int cost[N][N];
int distance[N];
int previous[N];
int permanent[N];
int current, minimum, dist, prev;

void dijkstra_algo(int graph[N][N], int start){  //input 2-D adjacent matrix 7x7, 7 nodes, displays connections
	for(int y = 0; y < N; y++){
		for(int x = 0; x < N; x++){
			if(graph[y][x] == 0){
				cost[y][x] = 999999; //large number
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
		minimum = 999999;

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
		//printf(" ... ");
		//display_node(current);
		count++;
	}
	printf("\n");

	for(int c = 3; c < N; c++){
    if(distance[c] < 999999){
		  printf("\nstop 2 -> ");
		  display_node(c);
		  printf(" is %d", distance[c]);
    }
	}
}

int next_field(FILE *csv, char *buffer, int max_len){
  	int count = 0;
  	bool qmark = 0;
  	char c;
	do{
    	c = fgetc(csv);
	    if (c == '"' && qmark == 0){
	      qmark = 1;

	    }
	    else if(c == '"' && qmark == 1){
	      qmark = 0;
	    }

	    if(qmark == 1 && c != '"'){
	      buffer[count] = c;
	      count++;
	    }
	    else{
	      switch(c){
	        case ',':
	          buffer[count] = '\0';
	          return 0;
	          break;

	        case '\n':
	          buffer[count] = '\0';
	          return 1;
	          break;

	        case EOF:
	          return 1;
	          break;

	        case '"':
	          buffer[count] = ' ';
	          break;

	        default:
	          buffer[count] = c;
	          count++;
	          break;
	      	}
	   	}
	} while(count <= max_len);
	fclose(csv);
}

int check_looping_matrix(int graph[NUM][NUM]){
  for(int i = 0; i < NUM; i++){
    if(graph[i][i] != 0){     //checks diagonally for 0, if not then looping occurs. e.g. 2 -> 2 which is incorrect
      printf("Looping in matrix ... value: (%d, %d)\n",i,i);
      return 1;
    }
  }
  printf("\nNo issues in matrix!\n");
  return 0;
}

void build_graph(int graph[NUM][NUM], int vertex1, int vertex2, int weight){
	graph[vertex1-2][vertex2-2] = weight;
	graph[vertex2-2][vertex1-2] = weight;	//-2 since bus stops starts at 2 and graph array starts at 0
}

int matrix[NUM][NUM];

int main(){

	int max = 200;
	int x = 0;

	int temp[2];

	FILE *vert;
	vert = fopen("vertices.csv", "r");
	FILE *edge;
	edge = fopen("edges.csv", "r");

	if(vert == NULL){
	    printf("Error File Empty!");
	}
	else{
	    char *fieldbuff;
	    fieldbuff = (char*)malloc(max);

	    char *edges_num;
	    edges_num = (char*)malloc(max);

	    while(!feof(vert)){

	    	int condition = next_field(vert, fieldbuff, max);

	     	if(condition == 1){
	        	printf("%s  ", fieldbuff);
	        	printf("\n");
	        	printf("\n");
	        	memset(fieldbuff, '\0', sizeof(fieldbuff));
	      }
	    	else if(condition == 0){
	        	printf("%s  ", fieldbuff);
	        	memset(fieldbuff, '\0', sizeof(fieldbuff));
	      }
	   }

     while(!feof(edge)){

       int numero = next_field(edge, edges_num, max);

       if(numero == 1){
         temp[x] = atoi(edges_num);
         printf("%d\n",temp[x]);
         build_graph(matrix, temp[0], temp[1], temp[2]); //bulding graph using 2 vertices and weight
         x = 0;
       }
       else if(numero == 0){
         temp[x] = atoi(edges_num);
         printf("%d ",temp[x]);
         x = x + 1;
       }
     }
	}

  printf("\n\n");
  for(int j = 0; j < 20; j++){
    printf("%d:\t", j+2);
    for(int i = 0; i < 20; i ++){
      printf("%d\t",matrix[j][i]);  //prints first 20 values in adjacency matrix
    }
    printf("\n");
  }

  check_looping_matrix(matrix);

  dijkstra_algo(matrix, 0);

	fclose(vert);
	printf("\nDone");
	return 0;
}
