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

// global variable
int bits = 0;
int bit2int(vector<int> bit);
int Hammingdis(int u, int v);
vector<int> int2bit(int v);

int Find(vector<vector<int>> &AllV, int v);
void Union(vector<vector<int>> &AllV, int v1,int v2);

void loaddata(string Name, vector<int> &nodes){
    ifstream File;
    File.open(Name); 
    string line;
    int n = 0;
    
    int line_count = 0;
    int x =0;
    vector<int> node;
   if (File.is_open()){
      while(getline(File,line) ){
          line_count++;
          istringstream iss(line);
          if (line_count==1){
            iss >> n; // vertex number
		    iss >> bits;
            nodes.resize(n);
            node.resize(bits);
            continue;
            }
         int i = 0;
         while(iss >> x){
             node[i] = x;
             i++;
         }
         nodes[line_count-2] = bit2int(node); 

     }
    cout << "total node " <<  line_count - 1<< endl; 
    cout << "each node has " << bits << " bits " << endl; 

     File.close();
    
     }else{
         cout << "cannot open file" << endl;
		
     }
}

int bit2int(vector<int> bit){
    int value = 0;
    int i;
    int base = 1;
    // remark: the order doesn't make, this is just for better calculation 
    for (i=bits;i>0;i--){
        value = value + base*bit[i-1];
        base = base *2;
    }
    return value;
}

vector<int> int2bit(int v){
    vector<int> bit(bits,0);
    int i=0;
    int base = 2;
    for (i=bits;i>0;i--){
       bit[i-1] = v % base;
        v = v/2;
    }
    return bit;
}

int Hammingdis(int u, int v){
    int w = u^v;
    int dis = 0;
    int i =0;
    for (i=0;i<bits;i++){
        dis = dis + (w & 1);
        w>>=1;// move to the right;
    }
    return dis;
}

void printnodes(vector<int> &nodes){
    int i = 0;
    vector<int> bit(bits,0);
    for (i=0;i<nodes.size();i++){
        cout << nodes[i] << " = ";
        bit = int2bit(nodes[i]);
        for (int j=0;j<bits;j++){
             cout << bit[j] << " " ;    
        }
        cout << endl;
    }
    
}

void printneightbor(vector<int> &nodes, int u){
    int i = 0;
    vector<int> bit(bits,0);
    cout << "Neighbour of " << u << " = ";
    bit = int2bit(u);
    for (int j=0;j<bits;j++){
             cout << bit[j] << " " ;    
        }
    cout << endl; 
    for (i=0;i<nodes.size();i++){
        cout << nodes[i] << " = ";
        bit = int2bit(nodes[i]);
        for (int j=0;j<bits;j++){
             cout << bit[j] << " " ;    
        }
        cout << " distance " << Hammingdis(nodes[i], u) << endl;
    }
    
}

vector<int> getneightbor(int u){
     // first all with distance 1
     // inspired by the following link
     // https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit

    vector<int> uk(bits+bits*(bits-1)/2,0);
    // first get all the distance 1 neighbor
    int i = 0;
    for (i=0;i<bits;i++){
        uk[i] = u^(1 << i); // bit wise xor will flip the bit
    }
    // second get all the distance 2 neighbor
    int v = 0;
    for (int j =0;j<bits;j++){
        for (int l=j+1;l<bits;l++){
          v = u^(1 << j); 
          uk[i]=v^(1 << l); 
          i++;  
        }
    }
    return uk;
}

// The idea is to use greedy algorithm
// with a hash like structure
// that is, use bit2int function as hash map, which is indeed a non conflict hash function 
// when the numbers are limited in bits
// 
// Here the goal is not to find the maximum margent for a given number of cluster
// but rather, given margent (2), what is the maximum cluster
// the algorithm can be for each node try to connect to the node that 

// note that for maximum margenet k, it means that any pairs of margin 2, should be 
// in one group, REMARK, this doesn't mean that all pairs within one group has to be 
// spacing of 2 or 1, it can be larger. 
int bigclustering(vector<int> nodes){
    
    // assume that nodes are none repeated
    // get rid of repeated points 
    int count = 0;; 
    // generate hash map
    // hashmap[v] = -1 if v is not in the nodes list
    vector<int> hashmap(nodes.back()+1,-1);
    vector<bool> exp(nodes.size(),false);
    // for union and find, first parent, second rank, third size
    vector<vector<int>> AllV;
    AllV.resize(nodes.size());

    for (int i = 0;i<nodes.size();i++){
        hashmap[nodes[i]]=i; 
        AllV[i]={i,0,1};
    }

    for (int i =0;i<nodes.size();i++){
        if (!exp[i]){
            // this is a node that is not spanned by its neighbor yet
            queue<int> v_to_go;
            v_to_go.push(i);
            int u;
            int v;
            int w;
            while(!v_to_go.empty()){
              vector<int> neightbor;  
               u = v_to_go.front();
               v_to_go.pop();
               exp[u]=true; // declare neighbor explored
               neightbor = getneightbor(nodes[u]); // get all u's neightbor of 1 and 2 distance
               // printneightbor(neightbor,nodes[u]);
              for (int j = 0;j<neightbor.size();j++){
                   // check if the neighbor is in the map
                   w = neightbor[j];
                   if (w<=nodes.back() && w>=nodes.front()){
                       v = hashmap[w];
                       if (v!=-1){
                           // in the map, 
                           int root1, root2;
                           root1 = Find(AllV,u);
                           root2 = Find(AllV,v);
                           if (root1!=root2){
                           // and not in the branch yet add to queue
                           // add this v and its branch to the map
                           // also need to explore this one.    
                           v_to_go.push(v);
                           Union(AllV,u,v);
                           }
                      }
                  }
                 // all neighbor checked
              } 
              // all the << 2 distance along this span has been explored
            }
            
        }
        // else will coninune
    }
    
    // count all the roots; need find the have pass compression
    for (int i=0;i<nodes.size();i++){
        if (AllV[i][0]==i){
            count++;
        }
    }
     return count;

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

void printdistance(vector<int> &nodes){
    for (int i = 0; i < nodes.size(); i++)
    {   for (int j = i+1; j < nodes.size(); j++)
        {
         cout << i+1 << " and " << j+1 << " : " << Hammingdis(nodes[i],nodes[j]) << endl;
         if (Hammingdis(nodes[i],nodes[j])<3){
             int t =1;
         }
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

    filename = "clustering_big.txt";

    }
	string Name = path + filename; // absolute path
    vector<int> nodes;
    // !!!! this will set the bits number for all the rest of the operation
    loaddata(Name, nodes);
    sort(nodes.begin(),nodes.end()); // there might be repeated points
    int i = 0;
    while(i<nodes.size()-1){
        if (nodes[i]==nodes[i+1]){
            nodes.erase(nodes.begin()+i);
        }else{
            i++;
        }
    }

    int class_count=0;
    class_count = bigclustering(nodes); 
    cout << "maximum class " << class_count << endl;
    // answer is 6118
    return 0;
}
