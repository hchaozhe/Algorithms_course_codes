#include <time.h> 
#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
using namespace std;
/* May have to consult online
https://www.softwaretestinghelp.com/graph-implementation-cpp/

To learn some basics
https://www.tutorialspoint.com/cplusplus/cpp_pointers.htm

I created this based on the following
https://www.techiedelight.com/graph-implementation-using-stl/
*/
// Data tructure to store a graph edge
// add a value to each edge
struct Edge 
{ 
	int src;
    int dest; 
    int value;
}; 

class Graph{
    public:

    // Method
    // constructor
    Graph(void);

    // if define with edges
    Graph(int v);
    //
    Graph(int v, vector<Edge> const &edgesInput);
    
    // destructor
    ~Graph(void);
    // Add Edge used when creating graph
    void AddEdge(int src, int dest, int value);
    // 
    void AddEdge2(Edge one_edge);

    // add a Vertex
    void AddVertex();
    
    // constant
    // V-> Number of vertices, E-> Number of edges 
	int V;
    int E; 

    // adjacent list
    vector<vector<int>> adjList;
    // adjacent list corresponding value
    vector<vector<int>> valueList;
    // store all the edges, in case one want to use the list
	vector<Edge> edges; 
    // store all vertex's source
    vector<vector<int>> adjList_back;

    vector<vector<int>> valueMatrix;
    

};


Graph::Graph(void)
{
  V = 0;
  E = 0;
  edges.clear(); // intialize an empty edge
  adjList.clear(); // intialize an empty adjList
  adjList_back.clear(); 
  valueList.clear();
  valueMatrix.clear();
}
Graph::Graph(int v)
{
  V = v;
  E = 0;
  edges.clear(); // intialize an empty edge
  adjList.resize(v); // get a size of 
  valueList.resize(v); // 
  adjList_back.resize(v); // 
  vector<vector<int>> vec( v , vector<int> (v, 0));
  valueMatrix = vec;
}

Graph::Graph(int v, vector<Edge> const &edgesInput)
{
  V = v;
  E = edgesInput.size();
  edges.resize(edgesInput.size()); // intialize an empty edge
  adjList.resize(v); // get a size of
  valueList.resize(v);
  adjList_back.resize(v);
  vector<vector<int>> vec( v , vector<int> (v, 0));
  valueMatrix = vec;
  int i = 0;
  edges = edgesInput;
  // add edges to the directed graph
        for (i = 0;i<edgesInput.size();i++)
        {
            // insert at the end
            adjList[edgesInput[i].src].push_back(edgesInput[i].dest);
            valueList[edgesInput[i].src].push_back(edgesInput[i].value);
            adjList_back[edgesInput[i].dest].push_back(edgesInput[i].src);
            valueMatrix[edgesInput[i].src][edgesInput[i].dest]=edgesInput[i].value;
        } 
        // for (auto &edgesInput: edgesInput)
        // {
        //     // insert at the end
        //     adjList[edgesInput.src].push_back(edgesInput.dest);
        //     #ifdef UNDIRECTED
        //     // uncomment the following code for undirected graph
        //     adjList[edgesInput.dest].push_back(edgesInput.src);
		// 	#endif
        // } 
}



Graph::~Graph(void)
{

}

void Graph::AddVertex(){
	V++;
	adjList.push_back({});
    valueList.push_back({});
    adjList_back.push_back({});
    // add one more column
    // add one more row, all with zero
    for (int i=0;i<V-1;i++){
        valueMatrix[i].push_back(0);
    }
    valueMatrix.push_back(vector<int> (V,0));
}

void Graph::AddEdge(int src, int dest, int value){
	E++;
	Edge e;
    e.src = src;
	e.dest = dest;
    e.value = value;
	edges.push_back(e);
	adjList[src].push_back(dest);
    valueList[src].push_back(value);
    adjList_back[dest].push_back(src);
    valueMatrix[e.src][e.dest]=e.value;
	#ifdef UNDIRECTED
	// uncomment the following code for undirected graph
	adjList[dest].push_back(src);
	#endif

}

void Graph::AddEdge2(Edge one_edge){
	E++;
	edges.push_back(one_edge);
	adjList[one_edge.src].push_back(one_edge.dest);
    valueList[one_edge.src].push_back(one_edge.value);
    adjList_back[one_edge.dest].push_back(one_edge.src);
    valueMatrix[one_edge.src][one_edge.dest]=one_edge.value;
}


// Function to print adjacency list representation of a graph
void printGraph(Graph const &graph)
{   int N = graph.V;
    for (int i = 0; i < N; i++)
    {
        // print the current vertex number
		#ifndef UNDIRECTED
        cout << i << " ——> ";
        #endif
        // print all neighboring vertices of a vertex `i`
        for (int j=0;j<graph.adjList[i].size();j++) {
            cout << graph.adjList[i][j]  << ","  << graph.valueList[i][j] << " ";
        }
        cout << endl;
    }
}



