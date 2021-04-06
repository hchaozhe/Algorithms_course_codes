#include <time.h> 
#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
using namespace std;
/* */
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
    

};


Graph::Graph(void)
{
  V = 0;
  E = 0;
  edges.clear(); // intialize an empty edge
  adjList.clear(); // intialize an empty adjList
}
Graph::Graph(int v)
{
  V = v;
  E = 0;
  edges.clear(); // intialize an empty edge
  adjList.resize(v); // get a size of 
}

Graph::Graph(int v, vector<Edge> const &edgesInput)
{
  V = v;
  E = edgesInput.size();
  edges.resize(edgesInput.size()); // intialize an empty edge
  adjList.resize(v); // get a size of
  int i = 0;
  edges = edgesInput;
  // add edges to the directed graph
        for (i = 0;i<edgesInput.size();i++)
        {
            // insert at the end
            adjList[edgesInput[i].src].push_back(edgesInput[i].dest);
            valueList[edgesInput[i].src].push_back(edgesInput[i].value);
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
	#ifdef UNDIRECTED
	// uncomment the following code for undirected graph
	adjList[dest].push_back(src);
	#endif

}

void Graph::AddEdge2(Edge one_edge){
	E++;
	edges.push_back(one_edge);
	adjList[one_edge.src].push_back(one_edge.dest);
    adjList[one_edge.src].push_back(one_edge.value);
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

void loadtxt2Graph(string Name, Graph &graph)
{   // this is to add for a weighted graph
    // read the adjlist first
    vector<vector<int>> adj;
    vector<vector<int>> value;
    ifstream File;
    File.open(Name); 
    string line;
    int n = 0;
    int v = 0;
    int x = 0;
if (File.is_open()){
    while(getline(File,line) ){
        istringstream iss(line);
        
        iss >> v; // vertex number
		adj.resize(v);
        value.resize(v);
        v = v-1;
        // from now on show be double
        bool flag = true;
        while(iss >> x)
        {   
            if (flag) {
                adj[v].push_back(x-1);
                flag = false;
            }else{
                value[v].push_back(x);
                flag = true;
            }
          if (iss.peek() == ',') iss.ignore(); 
        }
	n = n + adj[v].size();
	#ifdef PRINT	
    cout << adj[v].size() << " edges for vertex " << v << endl;
	#endif
     }
    cout << "total vertex " << v+1 << endl; 
    cout << "total edge " << n/2 << endl; 

     File.close();
    
     }else{
         cout << "cannot open file" << endl;
		
     }
    graph.V = v+1;
	graph.E = n/2; 
	graph.edges.resize(n/2);
    graph.adjList = adj;
    graph.valueList = value;
    // convert to graph structure
	int i = 0;
	int j = 0; 
	int k = 0; 
    for (i = 0;i<graph.V;i++){
		for (j = 0 ; j<adj[i].size();j++){
			// to deal with symetric cases
			// src <dest 
			if(adj[i][j]>i){
			graph.edges[k].src = i; 
	        graph.edges[k].dest = adj[i][j];  
            graph.edges[k].value = value[i][j];  
			k++;	
			}
		}
	}
	cout << "evaluated edge: " << k << endl;
};

