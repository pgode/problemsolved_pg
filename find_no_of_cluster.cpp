#include <iostream>
#include <vector>
using namespace std;


/*#define NUM 5
int input[NUM][NUM]=
{
0, 0, 0, 0, 0,
0, 1, 1, 1, 1,
0, 1, 1, 0, 0,
0, 1, 1, 1, 1,
0, 0, 0, 1, 0 };
//ans = 4
*/

/*#define NUM 9
int input[NUM][NUM]=
{
0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 1, 1, 1, 1, 1, 1, 1,
0, 0, 1, 1, 1, 1, 1, 1, 1,
0, 0, 1, 0, 1, 1, 1, 1, 1,
0, 0, 1, 0, 1, 1, 1, 1, 1,
0, 0, 1, 0, 1, 1, 1, 1, 1,
0, 0, 1, 0, 0, 0, 1, 1, 1,
0, 0, 1, 1, 1, 1, 1, 1, 0,
0, 0, 0, 0, 1, 1, 1, 0, 0
};
//ans = 4
*/

/*#define NUM 2
int input[NUM][NUM]=
{
0, 0,
0, 0
};
//ans = 1
*/

/*#define NUM 5
int input[NUM][NUM]=
{
1, 1, 1, 1, 0,
1, 0, 0, 0, 0,
1, 1, 1, 0, 0,
1, 0, 0, 1, 1,
1, 1, 1, 0, 0
};
//ans = 5
*/
#define NUM 10
int input[NUM][NUM]=
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
0, 1, 1, 1, 0, 1, 0, 1, 1, 0,
0, 1, 1, 1, 1, 1, 0, 1, 1, 0,
0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 1
};
//ans = 6

int cluster_count = 0;

//int queue[NUM * NUM];
pair<int, int> queue[NUM * NUM];
int front = -1; int rear = -1;

//to store color of node, for visited.
int colored_nodes[NUM*NUM];

void mark_visited( int i, int j)
{
  int position = i*NUM + j;
  colored_nodes[position] = 1;//visited.
}


void visit_neighbors(int i, int j)
{
  cout << " ============ \n";
  cout << " visiting: "<< i << "," << j << endl; 
  if(colored_nodes[(i* NUM) + j] == 0){
    //mark this visited. 
    mark_visited( i, j);    
    cout << " marking: " << i << "," << j << " vistted" << endl;    
  }  

  //check for all neighbors. 
  // Considering 
  // 1. neighbor not visited
  // 2. neighbor index in range 0 to NUM
  // 3. value of current node is same as neighbor, to form a cluster.
  //Diagonal is not allowed
  /*if( (colored_nodes[(i-1) * NUM + (j -1)] ==0)  &&
          ( (i-1) >=0 && (j-1)>=0 )  &&  ( (i-1) <NUM && (j-1)< NUM )  &&
          (input[i][j] == input[i-1][j-1]) ) {    
    //queue[++rear] = (i-1) * NUM + (j -1);
    queue[++rear] = make_pair((i-1), (j-1) );
    mark_visited( i-1, j-1);
    cout << " adding : " << (i-1) << " , " << (j-1) << endl;
  }*/
  if( (colored_nodes[(i-1) * NUM + (j)] ==0) &&
        ( (i-1)>=0 && j >= 0) && ( (i-1)<NUM && j < NUM) &&
        (input[i][j] == input[i-1][j])
        ){    
    //queue[++rear] = (i-1) * NUM + (j);
    queue[++rear] = make_pair((i-1), (j) );
    mark_visited( i-1, j);
    cout << " adding : " << (i-1) << " , " << (j) << endl;    
  }
  //Diagonal is not allowed
  /*if( (colored_nodes[(i-1) * NUM + (j +1)] ==0) &&
         ( (i-1)>=0 && (j+1) >= 0) && ( (i-1) < NUM && (j+1) < NUM) &&
         (input[i][j] == input[i-1][j+1])
         ){    
    //queue[++rear] = (i-1) * NUM + (j +1);
    queue[++rear] = make_pair((i-1), (j+1) );
    mark_visited( i-1, j+1);
    cout << " adding : " << (i-1) << " , " << (j+1) << endl;
  }*/
  if( (colored_nodes[(i) * NUM + (j -1)] ==0) &&
        (i>=0 && (j-1)>= 0) && (i<NUM && (j-1)<NUM) &&
        (input[i][j] == input[i][j-1])
        ){    
    //queue[++rear] = (i) * NUM + (j -1);
    queue[++rear] = make_pair((i), (j-1) );
    mark_visited( i, j-1);
    cout << " adding : " << (i) << " , " << (j-1) << endl;    
  }
  //else if(input[i][j]) mark_visited( i, j);
  if( colored_nodes[(i) * NUM + (j +1)] ==0 &&
          (i>=0 && (j+1) >= 0) && (i<NUM && (j+1) <NUM) &&
          (input[i][j] == input[i][j+1])
          ) { 
    //queue[++rear] = (i) * NUM + (j +1);
    queue[++rear] = make_pair((i), (j +1));
    mark_visited( i, j+1);
    cout << " adding : " << (i) << " , " << (j+1) << endl;    
  }
  //Diagonal is not allowed
  /*if( (colored_nodes[(i+1) * NUM + (j -1)] ==0) &&
          ((i+1)>=0 && (j-1)>= 0) && ((i+1) < NUM && (j-1) < NUM) &&
          (input[i][j] == input[i+1][j-1])
          ) {
    //queue[++rear] = (i+1) * NUM + (j -1);
    queue[++rear] = make_pair( (i+1), (j -1));
    cout << " adding : " << (i+1) << " , " << (j-1) << endl;
  }*/
  if( (colored_nodes[(i+1) * NUM + (j)] ==0) &&
           ( (i+1)>=0 && j >= 0) && ( (i+1) < NUM && j < NUM) &&
           (input[i][j] == input[i+1][j])
           ) {
    //queue[++rear] = (i+1) * NUM + (j);
    queue[++rear] = make_pair( (i+1), (j));
    mark_visited( i+1, j);
    cout << " adding : " << (i+1) << " , " << (j) << endl;    
  }
  //Diagonal is not allowed
  /*if( (colored_nodes[(i+1) * NUM + (j +1)] ==0) &&
          ( (i+1)>=0 && (j+1) >= 0) && ( (i+1) < NUM && (j+1) < NUM) &&
          (input[i][j] == input[i+1][j+1])
          ) {
    //queue[++rear] = (i+1) * NUM + (j+1);
    queue[++rear] = make_pair( (i+1), (j+1));
    mark_visited( i+1, j+1);
    cout << " adding : " << (i+1) << " , " << (j+1) << endl;
  }*/
  
  //queue empty. return
  if(front==rear){   
    return;    
  }   

  //delete from queue and visit it's neighbors (BFS , breadth first search used here)
  if( front < (NUM * NUM) ){
    //get row and col position to pass. could not get how to get row col position, so used pair.
    /*int linear_position = queue[++front]; int row = linear_position % ; int col = linear_position % NUM;*/    
    pair<int, int> temp = queue[++front];
    cout << " front=" << front << " rear=" << rear << endl;
    visit_neighbors( temp.first, temp.second);
  }  
}


//finds the number of subgraphs possible. 
// for this traverse from node in bfs. for each graph traversed, increment cluster count by 1.
int main()
{

  for(int i =0 ; i < NUM * NUM; i++)
    colored_nodes[i] = 0;//0 not visited. 1 visited.

  for(int i=0; i < NUM; i++)
  {
    for(int j=0; j < NUM; j++)
    {
      //if node is not visited, then this is 1st node of a cluster.
      if(colored_nodes[i* NUM + j] ==0){
        cluster_count++;
        visit_neighbors(i, j);        
      }        
    }//for j
  }//for i

  cout << " Number of cluster ="  << cluster_count << endl;

  return 0;
}