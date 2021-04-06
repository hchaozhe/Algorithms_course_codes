#include "binary_heap_CRH.hpp"
#include "Graph_Undirected_CRH.hpp"
#include <math.h>

void CreateHeap(Graph &graph, MinHeap &heap){
 for(int i = 0;i<graph.V;i++){
      heap.insertKey(INT_MAX,i);
     
  }
}

int Prim(Graph &graph, int src){
    int totalcost = 0;
    int min_value = INT_MIN;
    MinHeap heap(graph.V);
    CreateHeap(graph,heap);
    // make src the smallest value, in order to be extracted
    
    heap.decreaseKey(src,0);
    
    while(min_value<INT_MAX && !heap.empty()){

        // Extract the vertex with minimum distance value
        int u = heap.getMinv(); // extracted vertex
        min_value = heap.extractMin(); 
        totalcost = totalcost + min_value;

        // Traverse all the adjacent vertex of u and update their distance

        for (int i =0;i<graph.adjList[u].size();i++){
            int w = graph.adjList[u][i];
            // w may be the same as u, but if it is, it should not be in heap
            if (heap.isInMinHeap(w) ){
                    
                    // and update its key in the heap with the value on the edge
                    // and this by definition would trigger the heapify and thus move the
                    // current minimum one to the top
                    // REMARK, this first index should not be the vertex, but its
                    // position on the vertex 

                      // update only if it is smaller value
                    if (graph.valueList[u][i]<heap.getval(w)){
                        heap.decreaseKey(heap.getpos(w),graph.valueList[u][i]);
                        } 
                }
        }


    }
    if (heap.empty()){
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

    }
	string Name = path + filename; // absolute path
    Graph graph;


    loadGraphFromEdgestxt(Name, graph); 
    if (graph.V<100){
    printGraph(graph);
    } 
    int src = 0;
    int total_cost = 0;
    total_cost = Prim(graph, src);
    cout << " total cost " <<total_cost << endl;
    

    return 0;
}
