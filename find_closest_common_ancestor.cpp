#include <iostream>

using namespace std;

int V, E;

int E1[20], E2[20];

bool stack_empty(int * stack, signed int top)

{

if(top == -1)

return true;

else

return false;

}

int get_total_edges_visited(int *color)

{

int count = 0;

//count the visited vertices

for(int i = 0; i < V; i++)

{

if(color[i] == 1)

count++;

}

return count;

}

//color -1 initial, 1(grey) and 2 (black)

int *color;

//job scheduling using dfs

int main()

{

int i;

int **G;

/*/ Inputs

V = 8; E = 8;

E1[0] = 4; E2[0] = 1;

E1[1] = 1; E2[1] = 2;

E1[2] = 2; E2[2] = 3;

E1[3] = 2; E2[3] = 7;

E1[4] = 7; E2[4] = 6;

E1[5] = 5; E2[5] = 6;

E1[6] = 6; E2[6] = 5;

E1[7] = 1; E2[7] = 8;	*/

V = 5; E = 7;

//Allocate space for Graph

G = new int *[V];

for(i=0; i < V; i++)

G[i] = new int[V];

//INITIALIZE

//stack

int *stack; signed int top = -1;

stack = new int[V];

for(i=0; i < V; i++)

stack[i] = -1;

//initialize color

color = new int[V];

for(i=0; i < V; i++)

color[i] = 0;

//initialize graph edges

for(i = 0; i < V; i++)

for(int j = 0; j < V; j++)

G[i][j] = 0;

/*for(i = 0; i < V; i++)

G[E1[i]][E2[i]] = 1;*/

G[0][1] = 1;

G[1][2] = 1;

G[1][4] = 1;

G[2][3] = 1;

G[2][4] = 1;

G[4][1] = 1;//cycle

//G[3][2] = 1;//cycle

//G[3][0] = 1;//cycle

//G[4][2] = 1;

//DISPLAY graph

for(i = 0; i < V; i++)

for(int j = 0; j < V; j++)

if( G[i][j] == 1)

cout << " G["<< i <<"][" << j << "]=" <<G[i][j] << endl;

//cout << " G["<< E1[i]<<"]["<<E2[i] << "]=" <<G[E1[i]][E2[i]] << endl;

cout << endl;

//INITIALIZE DFS. push 1st item to stack

top = top + 1;

stack[top] = 0;//E1[0];

color[stack[top]] = 1;//discovered

cout << " pushing on stack:" << stack[top] << endl;//E1[0] << endl;

int no_of_edges_visit_complete = 0;//no. of nodes totally visited.

//perform dfs

// color 0, means not visited

// color 1, means discovered

// color 2, means fully visited

do

{

//if still nodes to process but stack empty.

if( (get_total_edges_visited(color) != V) && stack_empty(stack, top))

{

for(int v=0; v< V; v++)

{

if( color[v] == 0){

top = top + 1;

stack[top] = v;//E1[0];

color[stack[top]] = 1;//discovered

break;

}

}

}

//consider element on top of stack

int u = stack[top];

top = top -1; //pop from stack

cout << "\n consider:" << u << endl;

for(int v = 0; v < V; v++)

{

if( G[u][v] && (color[v] == 0))

{

//insert on top

top = top + 1;

stack[top] = v;

color[v] = 1;//discovered

no_of_edges_visit_complete++;

cout << " pushing on stack1:" << v << endl;

break;//In DFS only 1 node, so break, in BFS all nodes, so comment break

} else if( G[u][v] && (color[v] != 1) ){

cout << " ----> cycle for edge, G[" << u << "][" << v << "]"

<< ", Already visited " << u << endl;

exit(1);

}

/*else if( G[u][v] && (color[v]==2)) { //if fully visited vertex, then cycle //for bfs

//cout << " ----> cycle for edge, G[" << u << "][" << v << "]"

//<< ", Already visited " << u << endl;

//exit(1);

}*/

//color 1 means just discovered, not fully visited

}//for

/*/update color //for bfs

if(color[u] == 1){//if discovered already then, as we visited all adjs, so color next.

color[u] = 2;//complete visit //visited

no_of_nodes_visit_complete++;

}

else{

cerr << "u's color not set " << endl;

exit(1);

}	*/

}while( !stack_empty(stack, top) || (get_total_edges_visited(color) != V) );//|| (no_of_nodes_visit_complete <= V) );

return 0;

}//main