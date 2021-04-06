#include "Graph_Undirected_CRH.hpp"
#include <math.h>
#include <queue>
#include <stack>
#include <algorithm>    // std::sort
using namespace std;

// the goal of the program is to implement the union find data structure
// as well as practice BFS implementation

bool BFS(Graph &graph, int v_start, int v_end){
   
   queue<int> v_to_check; 
   vector<bool> exp(graph.V,false);
   v_to_check.push(v_start);
   exp[v_start] = true;
   while (!v_to_check.empty())
   {   // there are still vertex to check 
       int v = v_to_check.front();
       v_to_check.pop(); 
       for (int i = 0;i<graph.adjList[v].size();i++){
           int w = graph.adjList[v][i];
           if(!exp[w]){
               // find a new vertex that is not explored
               v_to_check.push(w); 
               // and marked it as visited, so it won't be added to the queue again
               exp[w]=true;

           }
       }
   }
    
   return exp[v_end];
    
}

// Aux function that put edges in increaseing cost 
bool edge_comp(const Edge a, const Edge b){
     if (a.value<b.value) {
         return true;
    } else {
         return false;
     }

}
// using BFS going to be very slow
int Kruskal(Graph &graph){
    int totalcost = 0;
    Graph MST(graph.V); // this record the MST, same v but no edges
   
    // first sort the edge according with increasing cost
    sort(graph.edges.begin(),graph.edges.end(),edge_comp);
    for (int i = 0;i<graph.E;i++){
        // check all the edges, if it has no cycle
        int u = graph.edges[i].src;
        int w = graph.edges[i].dest;

        /*Method 1, use BFS */
        if (BFS(MST,u,w) == false){
          // means that there is no cycle
          MST.AddEdge2(graph.edges[i]);
          totalcost = totalcost + graph.edges[i].value;
        }
 
        // when the tree is connected
        if (MST.E==MST.V-1) break;
    }
    
    if (MST.E==MST.V-1){
        cout << "MST span the whole graph" << endl;

    }else{
        cout << "graph is not connected" << endl; 
    }
    return totalcost;

}



// use Union Find
// lazy union and union by rank

// AllV first column is the parent, 
// second column is the rank
// third column is the size
// int Find(vector<vector<int>> &AllV, int v){
//     while (AllV[v][0]!=v)
//     {
//         v = AllV[v][0];
//     }
//     return v;
// }

// find with path compression
int Find(vector<vector<int>> &AllV, int v){
    stack<int> path;
    while (AllV[v][0]!=v)
    {   
        v = AllV[v][0];
        path.push(v);
    }
    int root = v;
    // update all vertex along the path with the root 
    while(!path.empty()){
        v = path.top();
        AllV[v][0] = root;
        path.pop();
    }
    return root;
}

void Union(vector<vector<int>> &AllV, int v1,int v2){
    int root1, root2;
    root1 = Find(AllV,v1);
    root2 = Find(AllV,v2);

    if (root1!=root2){
        // do lazy union
        if (AllV[root1][1]>AllV[root2][1]){
            // merge root 2 to root 1
            AllV[root2][0] = AllV[root1][0];
            // add the size of root2 branch to root 1;
            AllV[root1][2] = AllV[root1][2] + AllV[root2][2]; 
        }else if (AllV[root1][1]<AllV[root2][1]){
            // merge root 1 to root 2
            AllV[root1][0]=AllV[root2][0];
            // add the size of root 1 branch to root 2;
            AllV[root2][2] = AllV[root2][2] + AllV[root1][2];  
        }else{
            // equal ranking
            // merge the smaller size one to the larger size one
             if (AllV[root1][2]>=AllV[root2][2]){
                 // add root 1 to higher rank
                 AllV[root1][1]++;
                 // merge root 2 to root 1
                 AllV[root2][0] = AllV[root1][0];
                 // add the size of root2 branch to root 1;
                 AllV[root1][2] = AllV[root1][2] + AllV[root2][2]; 
             }else{
                 // add root 2 to higher rank
                 AllV[root2][1]++;
                 // merge root 2 to root 1
                 AllV[root1][0] = AllV[root2][0];
                 // add the size of root2 branch to root 1;
                 AllV[root2][2] = AllV[root2][2] + AllV[root1][2]; 
             }
            
        }
        
    } 
     
}

// using Union-Find much faster
int Kruskal2(Graph &graph){
    int totalcost = 0;
    Graph MST(graph.V); // this record the MST, same v but no edges
    
    vector<vector<int>> AllV;
    AllV.resize(graph.V);
    for (int i = 0; i < graph.V; i++)
    {
        AllV[i]={i,0,1};
    }
    
    // first sort the edge according with increasing cost
    sort(graph.edges.begin(),graph.edges.end(),edge_comp);
    for (int i = 0;i<graph.E;i++){
        // check all the edges, if it has no cycle
        int u = graph.edges[i].src;
        int w = graph.edges[i].dest;

        /* Method 2, use lazy union */
        int root1, root2;
        root1 = Find(AllV,u);
        root2 = Find(AllV,w);
        if (root1!=root2){
           // these two are merged 
           Union(AllV,root1,root2); 
           MST.AddEdge2(graph.edges[i]);
           totalcost = totalcost + graph.edges[i].value; 
        }
        // when the tree is connected
        if (MST.E==MST.V-1) break;
    }
    
    if (MST.E==MST.V-1){
        cout << "MST span the whole graph" << endl;

    }else{
        cout << "graph is not connected" << endl; 
    }
    return totalcost;

}



int main(int argc, char *argv[]){

    // load graph
    // string path = "H:\\GoogleDrive\\Career\\AlgorithmCourse\\AllCode\\GreedyAlgorithm\\Week1\\";
    string path = "";
	
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{

    filename = "edges.txt";
    // filename = "question3\\input_random_1_10.txt";

    }
	string Name = path + filename; // absolute path
    Graph graph;
    
    
    loadGraphFromEdgestxt(Name, graph); 

    if (graph.V<100){
    printGraph(graph);
    } 
    int src = 0;
    int total_cost = 0;
    
    total_cost = Kruskal2(graph);
    cout << " total cost " <<total_cost << endl;

    return 0;
}
