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

//color -1 initial, 1(grey) and 2 (black)
int *color;

//job scheduling using dfs
int main()
{
	int i;
	int **G;

	// Inputs
	V = 9; E = 9;
	E1[0] = 4; E2[0] = 1;
	E1[1] = 1; E2[1] = 2;
	E1[2] = 2; E2[2] = 3;
	E1[3] = 2; E2[3] = 7;
	E1[4] = 5; E2[4] = 6;
	E1[5] = 6; E2[5] = 5;
	E1[6] = 1; E2[6] = 5;
	E1[7] = 8; E2[7] = 5;
	E1[8] = 8; E2[8] = 9;

	//Allocate space for Graph
 	G = new int *[V+1];
	for(i=0; i < V+1; i++)
		G[i] = new int[V+1];

	//stack
	int *stack; signed int top = -1;
	stack = new int[V];

	//add additional property 'start and end time'
	int *start_time, *end_time, time_tick = 1;
	start_time = new int[V+1];
	end_time = new int[V+1];

	//initialize color
	color = new int[V+1];

	//initialize everything
	for(i=0; i < V+1; i++){
		start_time[i] = 0;
		end_time[i] = 0;
		color[i] = 0; //1 for grey 2 for blac(all visited)k
	}
	for(i=0; i < V; i++)
		stack[i] = -1;

	// initialize graph edges
	for(i = 0; i < V; i++)
		G[E1[i]][E2[i]] = 1;

	//Display graph
	for(i = 0; i < V; i++)
		cout << " G["<< E1[i]<<"]["<<E2[i] << "]=" <<G[E1[i]][E2[i]] << endl;
	cout << endl;

	//initialize dfs. push 1st item to stack
	top = top + 1;
	stack[top] = E1[0];
	start_time[E1[0]] = time_tick;

	cout << " pushing on stack:" << E1[0] << " start_time=" << start_time[E1[0]] << " end_time=" << end_time[E1[0]] << endl;

	int no_of_nodes_visit_complete = 1;

	//perform dfs
	while( !stack_empty(stack, top) || (no_of_nodes_visit_complete <= V) ){

		//not	all nodes are visited
		if( stack_empty(stack,top) && (no_of_nodes_visit_complete < V) ){
			for(i=1; i < V+1; i++)
			{
				if( (start_time[i] ==0) &&(end_time[i] == 0) )
				{ 
					top = top + 1;
					stack[top] = i;
					start_time[i] = ++time_tick;
					break;
				}
			}//for
		}//if

		//consider element on top of stack
		int u = stack[top];
		cout << "\n consider:" << u << " start_time=" << start_time[u] << " end_time=" << end_time[u] << endl;

		bool no_more_adjacents = true;
		for(int v = 1; v < V+1; v++){
					//use color instead
			//if (G[u][v] && start_time[v] != 0) cout <<"cycle , backedge on v= " << v << "!!! " << endl;
			//put unvisited nodes on stack.	Put start time for the node
			if( G[u][v] && (start_time[v] == 0) && !color[v]) {
				start_time[v] = ++time_tick;

				//insert on top
				top = top + 1;
				stack[top] = v;

				no_more_adjacents=false; //has adjacents, hence false

			  color[v] = 1;

		  	cout << " pushing on stack1:" << v << " start_time=" << start_time[v] << " end_time=" << end_time[v] << endl;
			}else if( G[u][v] && color[v]) cout << "                 ----> cycle for v=" << v << endl;
		}//for

		//update color
		color[stack[top]] = 1;

 		//'u'	has no adjacent node.
		if(no_more_adjacents && (end_time[u] ==0) ){
			//set	the end time for this, and backtrack
			end_time[u] = ++time_tick;
			top = top -1;

			color[u] =2;

		  cout << " end time update:" << u << " start_time=" << start_time[u] << " end_time=" << end_time[u] << endl;
			no_of_nodes_visit_complete++;
		}

		cout << "  no. of nodes completely visited=" << no_of_nodes_visit_complete << endl;

	}//while

	return 0;

}//main


