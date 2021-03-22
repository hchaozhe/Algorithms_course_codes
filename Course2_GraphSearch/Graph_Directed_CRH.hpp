#include <time.h> 
#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
using namespace std;

// Data tructure to store a graph edge
// specially made for Kosaraju's algorithm, supports inverse edges
struct Edge 
{ 
	int src;
    int dest; 
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
    void AddEdge(int src, int dest);
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
    // adjacent list inverse, for SCC calculation
    vector<vector<int>> adjListInv;
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
}

void Graph::AddEdge(int src, int dest){
	E++;
	Edge e;
    e.src = src;
	e.dest = dest;
	edges.push_back(e);
	adjList[src].push_back(dest);

	#ifdef UNDIRECTED
	// uncomment the following code for undirected graph
	adjList[dest].push_back(src);
	#endif

}

void Graph::AddEdge2(Edge one_edge){
	E++;
	edges.push_back(one_edge);
	adjList[one_edge.src].push_back(one_edge.dest);
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
        for (int v: graph.adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

void loadtxt2Graph(string Name, Graph &graph)
{
    // read the adjlist first
    vector<vector<int>> adj;
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
        v = v-1;
        while(iss >> x)
        { 
          adj[v].push_back(x-1);
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
			k++;	
			}
		}
	}
	cout << "evaluated edge: " << k << endl;
};

void loadtxtedge2Grap(string Name, Graph &graph)
{
    // read the edge
    int v = 0;
    ifstream File;
    File.open(Name); 
    string line;
    int src;
    int dest;
    Edge edge;
if (File.is_open()){
    while(getline(File,line) ){
        istringstream iss(line);   
        iss >> src; // src
		iss >> dest;
        v=max(v,src);
        v=max(v,dest);
        edge.src = src-1;
        edge.dest = dest-1;
        graph.edges.push_back(edge);
        graph.E++;
    }
    File.close();

    cout << "total edge (directed) " << graph.E << endl; 
    }else{
        cout << "cannot open file" << endl;
		
    }

    graph.V = v;
    graph.adjList.resize(v);
    graph.adjListInv.resize(v);
    // convert to graph structure
	int i = 0;
    for (i = 0;i<graph.E;i++){
        graph.adjList[graph.edges[i].src].push_back(graph.edges[i].dest);
        graph.adjListInv[graph.edges[i].dest].push_back(graph.edges[i].src);
	}

    cout << "total vertex (directed) " << graph.V << endl; 
};