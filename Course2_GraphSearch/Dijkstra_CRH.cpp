#include "binary_heap_CRH.hpp"
#include "Graph_Directed_CRH_DJ.hpp"
#include <math.h>



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

void printDistance(vector<int> &dist, vector<int> &n)
{
	printf("Vertex Distance from Source\n");
	for (int i = 0; i < n.size(); ++i){
        if(n[i]<dist.size()) printf("%d \t\t %d\n", n[i]+1, dist[n[i]]);
        }
    for (int i = 0; i < n.size(); ++i){
        if(n[i]<dist.size()) cout << dist[n[i]] <<",";
    }   
}

int main(int argc, char *argv[]){

    // load graph
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
 
    filename = "dijkstraData.txt";
    }
	string Name = path + filename; // absolute path
    Graph graph;


    loadtxt2Graph(Name, graph); 
    if (graph.V<100){
    printGraph(graph);
    } 
    int src = 0;
    vector<int> dist(graph.V,INT_MAX); // intiallly all are maximum
    dijkstra(graph,src, dist);
    vector<int> posplot = {6,36,58,81,98,114,132,164,187,196};
    printDistance(dist, posplot);
    // My answer is 2599,2610,2947,2052,2367,2399,2029,2442,2505,3068,

    return 0;
}


