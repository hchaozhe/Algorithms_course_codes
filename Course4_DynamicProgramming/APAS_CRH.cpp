#include "binary_heap_CRH.hpp"
#include "Graph_Directed_CRH.hpp"
#include <math.h>
using namespace std;

void loadtxt2Graph(string Name, Graph &graph)
{   // this is to add for a weighted graph
    // read the adjlist first
    vector<vector<int>> adj;
    vector<vector<int>> adj_back;
    vector<vector<int>> value;
    vector<Edge> edges;
    
    ifstream File;
    File.open(Name); 
    string line;

    int x = 0;
    int u,v,C;
    int count_line=0;
    vector<vector<int>> val_matrix;

if (File.is_open()){
    while(getline(File,line) ){
        istringstream iss(line);
        count_line++;

        if (count_line ==1){
        iss >> x; // vertex number
		adj.resize(x);
        adj_back.resize(x);
        value.resize(x);
        vector<vector<int>> val(x, vector<int> (x,INT_MAX));
        val_matrix = val;
        graph.V = x;

        iss >> x; // number of edges
        graph.E = x;
        edges.resize(x);
        continue;
        }
        // from now on show be double
        iss >> u; // starts from 1
        iss >> v; // starts from 1
        iss >> C;
        adj[u-1].push_back(v-1);
        value[u-1].push_back(C);
        adj_back[v-1].push_back(u-1);
        edges[count_line-2].src = u-1;
        edges[count_line-2].dest= v-1;
        edges[count_line-2].value = C;
        // in case there are multiple values pick the minimum one
        val_matrix[u-1][v-1] = min(val_matrix[u-1][v-1],C); 
        

    }
    cout << "total vertex " << graph.V << endl; 
    cout << "total edge " << graph.E << endl; 


    graph.edges = edges;
    graph.adjList = adj;
    graph.valueList = value;
    graph.adjList_back = adj_back;
    graph.valueMatrix = val_matrix;
    File.close();
    
     }else{
         cout << "cannot open file" << endl;
		
     }
    
    
	
};

void CreateHeap(Graph &graph, MinHeap &heap){
 for(int i = 0;i<graph.V;i++){
       heap.insertKey(INT_MAX,i);
 }
}

void CreatHeap(Graph &graph, MinHeap &heap){
 for(int i = 0;i<graph.V;i++){
      //  heap.insertKey(INT_MAX,i);
      heap.insertKey(i+1,i);
 }
}


void dijkstra(Graph &graph, int src, vector<int> &dist){
    MinHeap heap(graph.V);
    CreateHeap(graph,heap);
    // make src the smallest value 
    dist[src] = 0;
    heap.decreaseKey(src,dist[src]);
    
    while(!heap.empty()){

        // Extract the vertex with minimum distance value
        int u = heap.getMinv(); // extracted vertex
        heap.extractMin(); 
        
        // dist[u] it should not be INT_MAX

        // Traverse all the adjacent vertex of u and update their distance
        // note that this is undirected graph, so one may have repeated edge
        for (int i =0;i<graph.adjList[u].size();i++){
            int w = graph.adjList[u][i];
            if (heap.isInMinHeap(w) && 
                dist[u] != INT_MAX && 
                dist[u] + graph.valueList[u][i] < dist[w] ){
                    // update the new distance to v
                    dist[w] = dist[u] + graph.valueList[u][i];  
                    // and update its key in the heap
                    // and this by definition would trigger the heapify and thus move the
                    // current minimum one to the top
                    // REMARK, this first index should not be the vertex, but its
                    // position on the vertex 
                    heap.decreaseKey(heap.getpos(w),dist[w]);
                    

                }
        }


    }

}

// aux function for overflow protection
int addof(int a, int b){
   if (a==INT_MAX || b == INT_MAX){
       return INT_MAX;
   }else{
       return a+b;
   }
   
}
bool BellmanFord(Graph &graph, int src, vector<int> &dist){
    // use Bellman Ford algorithm
    // good for negative edges
    // no reconstruction 
    // A0[i] is the shortest distance to i with at most up to jth vertex as inner vertex
    
    vector<int> A0(graph.V,INT_MAX); //
    vector<int> A1(graph.V,INT_MAX); //
    // intialization to have at most 0 and 1 edges, 
    // which is no immdiate node, only the src to itself, or source to those adjcent neighbour, 
    // may have nontrivial value 
    A0[src] = 0;
    bool acyclic = true;

    // DP, tranverse value
    bool change = true;
    int k = 1;
    int j,v,w,Cwv;
    while (k<=graph.V&& change)
    {    // may loop, traverse all the vertex
        change = false;
        for (v = 0;v<graph.V;v++){
            // for each vertex
            A1[v] = A0[v];
            for (j = 0;j<graph.adjList_back[v].size();j++){
                w = graph.adjList_back[v][j];
                Cwv = graph.valueMatrix[w][v];
                A1[v] = min(A1[v], addof(A0[w],Cwv));
              }
        if (A1[v]!=A0[v]) change = true;      
        }
        A0 = A1; // sychronized update
        k++;
    }
    if (change){
        // this means that even up to v (vertext number)th iteration, there is still changes
        // cout << " there is nonnegative cycle in the graph. " << endl;
        acyclic = false;
    }
    // cout << "SP from src " << src +1 <<" iteration stopped at " << k-1 << " for this " << graph.V <<" vertexes graph" << endl; 
    
    dist = A1;
    return acyclic;

}

// Johnson's algortihm
// AUX reweight function using BellmanFord
bool Reweight(Graph &graph, Graph &graphrw, vector<int> &weightot){
   Graph graph2; 
   graph2 = graph;
   // add one vertex, then add all edges with 0 value from this edge to others
   graph2.AddVertex();
   for (int i = 0;i<graph.V;i++){
       graph2.AddEdge(graph.V,i,0);
   }
   vector<int> weight(graph2.V,0);
   bool flag = BellmanFord(graph2, graph.V, weight);
   weight.pop_back();
   // redefine the graphrw with this new
   vector<Edge> Newedges;
   Newedges = graph.edges;
   for (int i =0;i<graph.E;i++){
     Newedges[i].value = Newedges[i].value + 
                         weight[Newedges[i].src] - weight[Newedges[i].dest];
   }  
   Graph graph3(graph.V,Newedges);
   graphrw = graph3;
   weightot = weight;
   return flag;
}

void recoverdist(vector<int> &dist, int src, vector<int> &weight){
    for (int i = 0; i < dist.size();i++){
      dist[i] = addof(dist[i], - (weight[src]-weight[i]));
    }
}
// 
void printDistance(vector<int> &dist, vector<int> &n)
{   if (n.size()==0){
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < dist.size(); ++i){
        printf("%d \t\t %d\n", i+1, dist[i]);
    }

}else{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n.size(); ++i){
        if(n[i]<dist.size()) printf("%d \t\t %d\n", n[i]+1, dist[n[i]]);
        }
    for (int i = 0; i < n.size(); ++i){
        if(n[i]<dist.size()) cout << dist[n[i]] <<",";
    } 
}  
}
int findmin(vector<int> &dist){
    int m = INT_MAX;
    for(int i =0;i<dist.size();i++){
        m = min(m,dist[i]);
    }
    return m;
}
// Floyd - Warshall algorithm 
// didn't implement
int main(int argc, char *argv[]){
 
    // load graph
    // string path = "H:\\GoogleDrive\\Career\\AlgorithmCourse\\AllCode\\DynamicProgramming\\Week1\\";
    // string path = "./ShortestPath/"; // for debugging
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
    // filename = "TestCase1.txt";    
    // filename = "input_random_1_4.txt";
       filename = "g1.txt"; // NULL   by Bellman Ford
    // filename = "g2.txt"; % NULL   by Bellman Ford 
    // filename = "g3.txt"; % -19  by Bellman Ford also by Johnson, much faster
    // filename = "large.txt"; % -6 by johnson still very slow
    // filename = "./assignment1AllPairsShortestPath/input_random_1_2.txt";
    // filename = "ExampleBF.txt";
    // filename = "ExampleRW.txt";
    }
	string Name = path + filename; // absolute path
    Graph graph;
    
    loadtxt2Graph(Name, graph); 
    if (graph.V<20){
    printGraph(graph);

    }
    // Bellman ford ASAP
    // vector<int>  dist(graph.V,INT_MAX);
    int min_dis = INT_MAX;
    vector<int>  dist(graph.V,INT_MAX);
    bool flag = true; 
    for (int i=0;i<graph.V;i++){
        flag = BellmanFord(graph,i, dist);
        if (flag){
            min_dis = min(min_dis,findmin(dist));
        }else{
            cout << "there is negative cycle" << endl;
            break;
        }

    }
    
    if (flag){
    cout << "minimum shortest path" << endl;    
    cout << min_dis << endl;
    }else {
        cout << "NULL" << endl;
    }


     // ASAP using Johnson's algorithm
    Graph graphrw;
    vector<int>  weight(graph.V,INT_MAX);
    bool flag2 = true;
    
    min_dis = INT_MAX;
    dist = vector<int> (graph.V,INT_MAX);
    flag2 = Reweight(graph, graphrw, weight);


    if (graphrw.V<20){
        cout << "Reweight graph is " << endl;   
        printGraph(graphrw);
    }    

    if (flag2){
        for (int i=0;i<graph.V;i++){
            dist = vector<int> (graph.V,INT_MAX);
            dijkstra(graphrw, i, dist);
            recoverdist(dist,i,weight);
            min_dis = min(min_dis,findmin(dist));
        }    
    cout << "minimum shortest path" << endl;    
    cout << min_dis << endl;
    }else{
        cout << "NULL" << endl;
    }
    return 0;
}


