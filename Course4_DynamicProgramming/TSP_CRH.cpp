#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
#include <math.h>
#include <limits>
#include <stdio.h>
using namespace std;
#define MAXVAL (100000000.00)

double distcal(vector<double> X,vector<double>Y){
     double d = sqrt((X[0]-Y[0])*(X[0]-Y[0]) + (X[1]-Y[1])*(X[1]-Y[1]) );
     return d;
}

vector<vector<double>>  loadtspPos(string Name)
{   // this is to add for a weighted graph
    // read the adjlist first

    
    ifstream File;
    File.open(Name); 
    string line;

    float x = 0,y = 0;
    int v = 0;
    int count_line =0;
    vector<vector<double>> pos;
if (File.is_open()){
    while(getline(File,line) ){
        istringstream iss(line);
        count_line++;

        if (count_line ==1){
        iss >> v; // vertex number
        pos.resize(v);
        
        continue;
        }
        // from now on show be double
        iss >> x; // starts from 1
        iss >> y; // starts from 1
        pos[count_line-2].push_back(x);
        pos[count_line-2].push_back(y);

    }
    cout << "total cites: " << v << endl; 
    File.close();
    vector<vector<double>> dist(v, vector<double> (v,0));
    double d = 0;
    for (int i = 0; i < v;i++){
        for (int j = i+1;j<v;j++){
            d = distcal(pos[i],pos[j]);
            dist[i][j] = d;
            dist[j][i] = d; 
        }
    }
    return dist;
    // calculate difference 

     }else{
         cout << "cannot open file" << endl;
		
     }
    return {};
   
    
	
};

// this works different from the lecture, as this is a recursive approach
//
//  idea use an integer to describe S, name as visited, and 1 means only the first cities is visited
//       tsp gives the solution from 0 with S 
//       use (1 << i) to denote that the ith position is in the Set S
//       use  |(1 << i) to add i to the S list 
//       use  &(1 << i) to check that i is in S (because only i th bit will be 1 if i is in S)
// pos is the starting position of the tsp, 
// The sub optimal 
double tsp(const vector<vector<double>>& cities, int pos, int visited, vector<vector<double>>& state)
{
    if(visited == ((1 << cities.size()) - 1))
        return cities[pos][0]; // return to starting city

    if(state[pos][visited] != MAXVAL)
        return state[pos][visited];

    for(int i = 0; i < cities.size(); ++i)
    {
        // can't visit ourselves unless we're ending & skip if already visited
        if(i == pos || (visited & (1 << i)))
            continue;

        double distance = cities[pos][i] + tsp(cities, i, visited | (1 << i), state);
        if(distance < state[pos][visited])
            state[pos][visited] = distance;
    }

    return state[pos][visited];
}

void printdist(const vector<vector<double>>& cities){
     for (int i =0;i<cities.size();i++){
         for (int j = 0;j<cities.size();j++){
             cout << cities[i][j] << " " ;
         }
         cout << endl;
     }
}

int main(int argc, char *argv[]){
 
    // load graph
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{

    filename = "tsp.txt"; // my answer is 26442.7
    }
	string Name = path + filename; // absolute path
    vector<vector<double>> dist = loadtspPos(Name);
    if (dist.size()<5){
        printdist(dist);
    }
    vector<vector<double>> state(dist.size());
    for(auto& neighbors : state)
        neighbors = vector<double>((1 << dist.size()) - 1, MAXVAL);

    cout << "minimum: " << tsp(dist, 0, 1, state) << endl;
    return 0;
}
