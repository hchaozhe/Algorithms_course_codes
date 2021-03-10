#include "Graph_CRH.hpp"

#define UNDIRECTED


int main() 
{ 
	/* example: simple unweighted graph 
		0------1 
		|\    | 
		|  \   | 
		|	 \| 
		2------3 */
	// int V = 4; // Number of vertices in graph 
    // vector<Edge> edges =
    // {
    //     { 0, 1 }, { 0, 2 }, { 0, 3 }, { 1, 3 },
    //     { 2, 3 }
    // };
    int V = 6;
    vector<Edge> edges =
    {
        { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
        { 3, 2 }, { 4, 5 }, { 5, 4 }
    };

    // Define with full list of edges
	Graph graph1(V,edges);
	printGraph(graph1);
   	// graph1.AddEdge(2,1);
	graph1.AddEdge(2,3);   
    printGraph(graph1);

	Graph graph2(V);
	for (int i=0;i<edges.size();i++)
    graph2.AddEdge2(edges[i]);
	printGraph(graph2);

    Graph graph3;
	for (int i=0;i<V;i++)
	graph3.AddVertex();
	for (int i=0;i<edges.size();i++)
    graph3.AddEdge2(edges[i]);
	printGraph(graph3);

	string Name = "H:\\GoogleDrive\\Career\\AlgorithmCourse\\AllCode\\DevideAndconquer\\Week4\\Code\\KargerMinCut.txt"; // absolute path 
	Graph graph;
    loadtxt2Graph(Name, graph);
	printGraph(graph);

 

	return 0; 
}