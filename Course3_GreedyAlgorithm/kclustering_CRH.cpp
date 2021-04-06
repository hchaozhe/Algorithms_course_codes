#include "Graph_Undirected_CRH.hpp"
#include <math.h>
#include <queue>
#include <stack>
#include <algorithm>    // std::sort
using namespace std;

// Aux function that put edges in increaseing cost 
bool edge_comp(const Edge a, const Edge b){
     if (a.value<b.value) {
         return true;
    } else {
         return false;
     }

}


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


int KClustering(Graph &graph, int k){
    int space_max = 0;
    int count = graph.V;
    vector<vector<int>> AllV;
    AllV.resize(graph.V);
    for (int i = 0; i < graph.V; i++)
    {   // individual 
        AllV[i]={i,0,1};
    }
    
    // first sort the edge according with increasing distance
    sort(graph.edges.begin(),graph.edges.end(),edge_comp);
    
    int indx = 0;
    for (int i = 0;i<graph.E;i++){
        // check all the edges, if it has no cycle
        int u = graph.edges[i].src;
        int w = graph.edges[i].dest;

        /* Method 2, use lazy union */
        int root1, root2;
        root1 = Find(AllV,u);
        root2 = Find(AllV,w);
        if (root1!=root2){
           // merge theset two cluster into one
           Union(AllV,root1,root2); 
           count--;   
        }
        // when reaching the cluster
        if (count == k){
            indx = i;
            break;
            }
    }
    // identify the minimum spacing from the reminder path
    bool found = false;
    while (!found)
    {   
        int u = graph.edges[indx].src;
        int w = graph.edges[indx].dest;

        /* Method 2, use lazy union */
        int root1, root2;
        root1 = Find(AllV,u);
        root2 = Find(AllV,w);
        if (root1!=root2){
            found = true;
            space_max = graph.edges[indx].value;
        }
        indx++;
        if (indx==graph.V){
            cout << "soemthing is wrong, should not be here" << endl;
            return 0;
        }
    }
    
    

    return space_max;

}


int main(int argc, char *argv[]){

    // load graph
    string path = "";
	
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{

    filename = "clustering1.txt";

    }
	string Name = path + filename; // absolute path
    Graph graph;
    
    
    loadGraphFromEdgestxt(Name, graph); 

    if (graph.V<10){
    printGraph(graph);
    } 
    // int src = 0;
    int space_max = 0;
    space_max = KClustering(graph, 4);
    
    cout << " max spacing " <<space_max << endl;
    // answer is 106
    return 0;
}