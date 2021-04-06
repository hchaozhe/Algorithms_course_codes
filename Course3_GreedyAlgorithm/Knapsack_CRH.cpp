#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>    // std::sort
#include <queue>
#include <stack>

using namespace std;

int loaddata(string Name, vector<vector<int>> &nodes){
    ifstream File;
    File.open(Name); 
    string line;
    int n = 0;
    int size_cap = 0;
    int line_count = 0;
    int x =0;
   if (File.is_open()){
      while(getline(File,line) ){
          line_count++;
          istringstream iss(line);
          if (line_count==1){
            iss >> size_cap;
            iss >> n; // vertex number
            nodes.resize(n);
            continue;
            }
         int i = 0;
         while(iss >> x){
             nodes[line_count-2].push_back(x);
             i++;
         }

     }
    cout << "total node " <<  line_count - 1 << " " << n << endl;  

     File.close();
    return size_cap;
     }else{
         cout << "cannot open file" << endl;
         return 0;
		
     }
}

bool compare(vector<int> x, vector<int> y){
    // compare according to size, wich is y[1];
    return x[1]<=y[1];
}
// this may not be the most optimized one
// but it was not too bad. 
int DP_knapsack(vector<vector<int>> nodes, int size_cap){
    sort(nodes.begin(),nodes.end(),compare);
    vector<int> Vix(size_cap+1,0); // i = 0 intially
    vector<int> Vi1x(size_cap+1,0); // i = 1 intially
    int v_nw = 0;
    for (int i = 0;i<nodes.size();i++){
        for (int x = 0;x<=size_cap;x++){
            if (x<nodes[i][1]){
                Vi1x[x] = Vix[x]; // could not add vi
            }else{
                // see whether swap vi in is more benefitial
                Vi1x[x] = max(Vix[x],Vix[x-nodes[i][1]]+nodes[i][0]);
            }
        }
        // roll into new rows.
        Vix = Vi1x;
    }
    v_nw = Vix[size_cap];
    return v_nw;
}


int main(int argc, char *argv[]){

    // load graph
   string path = "";
	
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
    filename = "knapsack1.txt"; // result should be 2493893
    // filename = "Knapsack_big.txt"; // result should be 4243395, much slower but not bad

    }
	string Name = path + filename; // absolute path
    vector<vector<int>> nodes;
    int size_cap = loaddata(Name,nodes);
    cout << size_cap << "  "<< nodes.size() << endl;
    cout << DP_knapsack(nodes,size_cap) << endl;
    return 0;
}