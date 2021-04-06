#include <time.h> 
#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
using namespace std;

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
  valueList.clear();
}
Graph::Graph(int v)
{
  V = v;
  E = 0;
  edges.clear(); // intialize an empty edge
  adjList.resize(v); // get a size of 
  valueList.resize(v); 
}

Graph::Graph(int v, vector<Edge> const &edgesInput)
{
  V = v;
  E = edgesInput.size();
  edges.resize(edgesInput.size()); // intialize an empty edge
  adjList.resize(v); // get a size of
  valueList.resize(v);
  int i = 0;
  edges = edgesInput;
  // add edges to the directed graph
        for (i = 0;i<edgesInput.size();i++)
        {
            // insert at the end
            adjList[edgesInput[i].src].push_back(edgesInput[i].dest);
            valueList[edgesInput[i].src].push_back(edgesInput[i].value);
            // undirected graph
            adjList[edgesInput[i].dest].push_back(edgesInput[i].src);
            valueList[edgesInput[i].dest].push_back(edgesInput[i].value);
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
	adjList[dest].push_back(src);

}

void Graph::AddEdge2(Edge one_edge){
	E++;
	edges.push_back(one_edge);
	adjList[one_edge.src].push_back(one_edge.dest);
    valueList[one_edge.src].push_back(one_edge.value);
    adjList[one_edge.dest].push_back(one_edge.src);
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
void loadGraphFromEdgestxt(string Name, Graph &graph)
{   // this is initialize the graph from edge list
    // to adjacent list
    vector<vector<int>> adj;
    vector<vector<int>> value;
    ifstream File;
    File.open(Name); 
    string line;
    int n = 0;
    int v = 0;
    int e = 0;
    int x = 0;
    int line_count = 0;
    Edge Newedge;
   if (File.is_open()){
      while(getline(File,line) ){
          line_count++;
          istringstream iss(line);
          if (line_count==1){
            iss >> v; // vertex number
		    adj.resize(v);
            value.resize(v);
            graph.V = v;
            iss >> e;
            graph.E = e;
            graph.edges.resize(e);
            continue;
            }
        // should not be the first row
        // from now on show be showing edges in src dest and value tuple 
	     
         iss >> x; Newedge.src = x-1; // data count from 1
         iss >> x; Newedge.dest = x-1; // data count from 1
         iss >> x; Newedge.value = x;

         graph.edges[line_count-2] = Newedge;
         adj[Newedge.src].push_back(Newedge.dest);
         value[Newedge.src].push_back(Newedge.value);
         // since it is undirected graph
         // note that there might be circle
         if (Newedge.dest!=Newedge.src){
         adj[Newedge.dest].push_back(Newedge.src);
         value[Newedge.dest].push_back(Newedge.value);
         }
     }
    cout << "total vertex " << v << endl; 
    cout << "total edge " << line_count << " " << e << endl; 

     File.close();
    
     }else{
         cout << "cannot open file" << endl;
		
     }

    graph.adjList = adj;
    graph.valueList = value;
};

