#include "Graph_Directed_CRH.hpp"
#include <algorithm>    // std::sort
// this version works for the test cases, but will not run for the big case
// test cases, good up to 60 80000

int ft = 0;
int s_leader = 0;
int scc_size_count = 0;
// DFS recursive over inversse
void DFSFirst(Graph &graph, vector<bool> &exp, 
       int v_start,vector<int> &ft_all){
   exp[v_start] = true;
   for (int i = 0;i<graph.adjListInv[v_start].size();i++){
       if (exp[graph.adjListInv[v_start][i]] == false){
          DFSFirst(graph, exp, graph.adjListInv[v_start][i],ft_all); 
       }
   }
   // means all neighbour complete
   // the finish time of this v_start is set
   ft_all[ft] = v_start;
   ft++;
}

void DFSSecond(Graph &graph, vector<bool> &exp, 
       int v_start,vector<int> &leader){
   exp[v_start] = true;
   leader[v_start] = s_leader; // in current call, they all belongs to the same 
   scc_size_count++;
   for (int i = 0;i<graph.adjList[v_start].size();i++){
       if (exp[graph.adjList[v_start][i]] == false){
           
          DFSSecond(graph, exp, graph.adjList[v_start][i],leader); 
       }
   }

}


int main(int argc, char *argv[]){
    string path = "H:\\GoogleDrive\\Career\\AlgorithmCourse\\AllCode\\GraphSearch\\Week1\\";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
    // filename = "TestCase5.txt";    
    filename = "SCC.txt";
    }
	string Name = path + filename; // absolute path
    Graph graph;


    loadtxtedge2Grap(Name, graph); 
    if (graph.V<100){
    printGraph(graph);
    } 
    vector<bool> exp(graph.V,false);
    vector<int> ftall(graph.V,0);
    vector<int> leader(graph.V,0);

    // This set up has overflow
    // first round inverse map reverse, get all the finish time
    for(int i =graph.V-1;i>-1;i--){
        // iterative DFS
        if (exp[i]==false){
            DFSFirst(graph,exp,i,ftall);
           // cout<< i << endl;
        }
    }

    // ft has updated 
    vector<bool> exp2(graph.V,false);
    vector<int> scc_size;
    scc_size.clear();
    int scc_count = 0;
    for(int i =graph.V-1;i>-1;i--){
        if (exp2[ftall[i]]==false){
            s_leader = ftall[i];
            scc_count++;
            scc_size_count=0;
            DFSSecond(graph,exp2,ftall[i],leader);
            scc_size.push_back(scc_size_count);
        }
    }
    // all those belongs to the same leader gives one SCC
    // count the leader occurrence
    
    cout << "There are " << scc_count << " SCCs" << endl;
    sort(scc_size.begin(), scc_size.end()); 
    
    for (int i = scc_count-1;i>max(scc_count-6,-1);i--){
      cout << scc_size[i] << ",";
    }

    return 0;
}

