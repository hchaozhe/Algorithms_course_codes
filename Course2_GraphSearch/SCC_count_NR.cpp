#include "Graph_Directed_CRH.hpp"
#include <algorithm>    // std::sort
#include <stack>
// This program is correct as it gives the correct answer on Mac.
// Still haven't resolve the memory issue on Windows
//
// see the following example for how iterative approach was implemented with the finishing time 
// calculation. 
// https://weiming-hu.github.io/strongly-connected-components/
// Note that if without the finishing time calculation, the DFS iterative approach would be 
// much simpler too. 
// see the following for how a typical DFS is implemented
// https://www.geeksforgeeks.org/iterative-depth-first-traversal/

// For BFS implementation
// https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

// somebody's python solution with answer, which is the same with my answer too.
// 434821,968,459,313,211
// https://github.com/rvarun7777/Graph-Search--Shortest-Paths--and-Data-Structures/blob/master/PA%201/scc_finder.py
// tested with https://github.com/beaunus/stanford-algs
// test cases, found issue with this method, the other one seems to be fine


struct SCC {
        vector<int> leaders;
        vector<int> finishings;
        vector<vector<int>> scc_size;
        int counter;
};

// non recursive 
void DFSFirst_NR(Graph &graph,   
       SCC &scc){

   vector<bool> exp(graph.V,false);
   stack<int> v_to_visit;
   // order of search from the i        
   int i; // for vertex
   int j; // for vertex's connection
   int v_curr; // current node whose adjList was being exploring
   int v;
   scc.counter=0; 
for (i=0;i<graph.V;i++){
    v = graph.V-1-i; // pick a node that 
    
    if (exp[v]==false){
        // start from this node which is not visited, do a DFS 
         
        
  
        //***************** start a DFS search from this node ***************
        v_to_visit.push(v); // put this node to the stack 
                            // note that stack stored the ones that are yet to be checked  
        while (!v_to_visit.empty()){

            v_curr = v_to_visit.top();

            bool finished = true;
                // if this stays true, then
                // either it is a visited point (in this case it should have been popped in the 
                // original DFS algorithm 
                // or it is an unvisited point but all its adjcent ones are explored
            if (exp[v_curr]==false){
                // since point in the stack was never explored, start exploring
                exp[v_curr]=true; // mark as visited, in recursive algorithm this would start
                                  // an recursive run
                // important remark!!!!!!
                // in a DFS not for this finishing time thing, it should be pop here
                // but because we need to track the time, it need to stay until 
                // the status where all its adjlist points are visited, then it pops up
                // with the finished flag
                
                 
                for (j = 0;j<graph.adjListInv[v_curr].size();j++){
                    if (exp[graph.adjListInv[v_curr][j]] == false){
                        
                    // for a given node, it can be put in stack more than once, 
                    // as more than one visited node might be connect to a same node

                    // add this unexplored point to the stack
                    v_to_visit.push(graph.adjListInv[v_curr][j]);     

                    // this means that there are node unexplored to the v_curr
                    finished = false;
                    }
                }

            }

            if (finished){
                // means that EITHER (1) it was already explored, just waiting for finish time
                // it may or may not have a finishing time
                // OR (2) it was first explored here but it has no adj that is not explored
                // in this case it for sure do not have a finishing time

                // both cases, it should leave the stack
                v_to_visit.pop();
                    
                    if (scc.finishings[v_curr]==0){
                        // means that it doesn't have a finishing time 
                        // use counter to track the finishing time
                        scc.counter=scc.counter+1;
                        scc.finishings[v_curr]=scc.counter;
                    }
                
            }
            // at this point 
            
        }

       //*************************** end of DFS ***************************** 
       // now go back to the loop that go through all the vertex and start a new DFS
    }
}

}

void Reshuffle(Graph &graph, SCC &scc){

    vector<int> newfinishings(graph.V,0);
    for (int i=0;i<graph.V;i++){
        newfinishings[scc.finishings[i]-1] = i;
    }
    scc.finishings = newfinishings;
    
}


void DFSSecond_NR(Graph &graph,   
       SCC &scc){
   vector<bool> exp(graph.V,false);
   stack<int> v_to_visit;
   // order of search from the i        
   int i; // for vertex
   int j; // for vertex's connection
   int v_curr; // current node whose adjList was being exploring
   int v;
   scc.counter=0; // ree count, this time it is leader
   int leader = 0;
   int scc_size = 0;
for (i=0;i<graph.V;i++){
    v = scc.finishings[graph.V-1-i]; 
    // start from the one with the latest finish time
    
    if (exp[v]==false){
        // start from this node which is not visited, do a DFS 
        leader = v;
        scc.counter++; // potentially find an scc from this node;
        scc_size = 0;   // reset the size of the current scc
  
        //***************** start a DFS search from this node ***************
        v_to_visit.push(v); // put this node to the stack 
                            // note that stack stored the ones that are yet to be checked  
        while (!v_to_visit.empty()){

            v_curr = v_to_visit.top();
            v_to_visit.pop();// normal one just pop right away, because it is visited
            scc.leaders[v_curr] = leader; // all have the same leader 
             if (exp[v_curr]==false){
                // since point in the stack was never explored, start exploring
                exp[v_curr]=true; // mark as visited, in recursive algorithm this would start
                                  // an recursive run
                // normal DFS here
                scc_size++; // this is first time it is visited, count it here
                for (j = 0;j<graph.adjList[v_curr].size();j++){
                    if (exp[graph.adjList[v_curr][j]] == false){
                        
                    // at the point of adding, the point may not be explored
                    // so it could be that one node be added more than once
                    v_to_visit.push(graph.adjList[v_curr][j]);     
                    }
                }

            }


    
            
            // at this point 
            
        }

       //*************************** end of DFS ***************************** 
       // now go back to the loop that go through all the vertex and start a new DFS
       scc.scc_size.push_back({leader,scc_size});
    }
}
}


int main(int argc, char *argv[]){

    // load graph
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
    
    filename = "SCC.txt"; // My answer371762 total SCC, maximum five  434821,968,459,313,211,
    }
	string Name = path + filename; // absolute path
    Graph graph;


    loadtxtedge2Grap(Name, graph); 
    if (graph.V<100){
    printGraph(graph);
    } 
    SCC scc;
    scc.counter = 0;
    scc.finishings.resize(graph.V);
    scc.leaders.resize(graph.V);
    scc.scc_size.clear();
    
    DFSFirst_NR(graph, scc);
    Reshuffle(graph,scc);
    DFSSecond_NR(graph, scc);
    cout << "There are " << scc.counter << " SCCs" << endl;

    vector<int> scc_out(scc.scc_size.size(),0);
    for (int i = 0;i<scc.counter;i++){
        scc_out[i]=scc.scc_size[i][1];
    }
    sort(scc_out.begin(),scc_out.end());
    for (int i = scc.counter-1;i>max(scc.counter-6,-1);i--){
      cout << scc_out[i] << ",";
    }

    return 0;
}