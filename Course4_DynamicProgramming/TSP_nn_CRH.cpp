#include <string>
#include <iostream>
#include <sstream> // istringstream
#include <fstream>
#include <vector>
#include <math.h>
#include <limits>
#include <stdio.h>
using namespace std;
#define MAXVAL (1.79769e+30)

double distcal(vector<double> X,vector<double>Y){
     //double d = sqrt((X[0]-Y[0])*(X[0]-Y[0]) + (X[1]-Y[1])*(X[1]-Y[1]) );
     double d = (X[0]-Y[0])*(X[0]-Y[0]) + (X[1]-Y[1])*(X[1]-Y[1]) ;
     
     return d;
}

double distcalx(vector<double> X,vector<double>Y){
     //double d = sqrt((X[0]-Y[0])*(X[0]-Y[0]) + (X[1]-Y[1])*(X[1]-Y[1]) );
     double d = (X[0]-Y[0])*(X[0]-Y[0]) ;
     
     return d;
}

void printdist(const vector<vector<double>>& cities){
     for (int i =0;i<cities.size();i++){
         for (int j = 0;j<cities.size();j++){
             cout << cities[i][j] << " " ;
         }
         cout << endl;
     }
}



vector<vector<double>>  loadtspPos(string Name)
{   // this is to add for a weighted graph
    // read the adjlist first

    
    ifstream File;
    File.open(Name); 
    string line;

    double x = 0,y = 0;
    string s;
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
        // One need to pay special attention to the precision.....
        // from now on show be double
        iss >> x; // beacuse there is one more at the beginning
        //
        
        iss >> s; // starts from 1
        x = stod(s); // make sure one match the format, use stof if x y are float variables.
        iss >> s; // starts from 1
        y = stod(s);
        pos[count_line-2].push_back(x);
        pos[count_line-2].push_back(y);

    }
    
    cout << "total cites: " << v << endl; 
    File.close();
    return pos;
     }else{
         cout << "cannot open file" << endl;
		
     }
    return {};
   
    
	
};

double tsp_nn( vector<vector<double>> pos, vector<double> &order){
    // nearest neighour heuristics 
    // may not be optimal
    // assume always start from 0
    vector<int> cities_togo (pos.size()-1,0);
    order = {0}; // start from zero
    for (int i = 1 ;i<pos.size();i++){
        cities_togo[i-1]=i;
    }
    double total_dist = 0;
    double min_dis = 0;
    int next = cities_togo.size();
    int curr = order[0];
     double dis = 0;
     double max_dis=0;
    while(!cities_togo.empty()){
       min_dis=MAXVAL;    
       next = cities_togo.size();
       for (int j = 0;j<cities_togo.size();j++){
           dis = distcal(pos[curr],pos[cities_togo[j]]);
           if (min_dis > dis){
               // find a cite with smaller distance
               min_dis = dis;
               next = j;
               // not needed because j tranverse in the order of cities
        //    }else if (min_dis == dis){
        //        // tie breaker 
        //        if (cities_togo[j]<cities_togo[next]){
        //         //    min_dis = dist[curr][cities_togo[j]];
        //            next = j;
        //        }
           }
           
           
       }
       // after search the minimum value should eb identified
        order.push_back(cities_togo[next]);
        curr = cities_togo[next];
        total_dist = total_dist+sqrt(min_dis);
        cout.precision(30);
        cout << max_dis <<" " << min_dis << " " << curr << "  "<< total_dist << endl;
        // delete the selected cities 
        cities_togo.erase(cities_togo.begin()+next);
        
    }
    dis =  distcal(pos[0],pos[curr]);
    total_dist = total_dist + sqrt(dis);
    return total_dist;
}


double tsp_nn_xsort( vector<vector<double>> pos, vector<int> &order){
    // nearest neighour heuristics 
    // may not be optimal
    // assume always start from 0
    vector<int> cities_togo (pos.size()-1,0);
    order = {0}; // start from zero
    for (int i = 1 ;i<pos.size();i++){
        cities_togo[i-1]=i;
    }
    double total_dist = 0;
    double min_dis = 0;
    int next = cities_togo.size();
    int curr = order[0];
     double dis = 0;
     double max_dis=0;
     double dis_x; // use the fact that the pos is exciding in x
     int c=0;
    while(cities_togo.size()>0){
       min_dis=MAXVAL;    
       next = cities_togo.size();
    //    max_dis = 0;
       for (int j = 0;j<cities_togo.size();j++){
           dis = distcal(pos[curr],pos[cities_togo[j]]);
           dis_x = distcalx(pos[curr],pos[cities_togo[j]]);
            // beacuse x can only get further, if it is smaller than the current one, then
            // one can stop searching. 
           if (dis_x>min_dis) break;
        //    max_dis = max(dis,max_dis);
           if (min_dis > dis){
               // find a cite with smaller distance
               c = cities_togo[j]; // for debugging purpose
               min_dis = dis;
               next = j;
           } // don't really need this since always search from the beginning
        //    }else if (min_dis == dis){
        //        // tie breaker 
        //        if (cities_togo[j]<cities_togo[next]){
        //         //    min_dis = dist[curr][cities_togo[j]];
        //            next = j;
        //        }
        //    }
           
           
       }
       // after search the minimum value should eb identified
        order.push_back(cities_togo[next]);
        curr = cities_togo[next];
        total_dist = total_dist+sqrt(min_dis);
        cities_togo.erase(cities_togo.begin()+next);
        
        if (cities_togo.size()%1000 == 0){
            cout.precision(30);
        cout << " travel to " << curr << "  "<< total_dist <<" "<< cities_togo.size() << " cites left"<< endl;
        }
        // delete the selected cities 
        
        
    }
    dis =  distcal(pos[0],pos[curr]);
    total_dist = total_dist + sqrt(dis);
    return total_dist;
}


int main(int argc, char *argv[]){
 
    // load graph
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{

    filename = "nn.txt"; //  my answer 1203406.50127088557928800582886
    }
	string Name = path + filename; // absolute path
    vector<vector<double>> pos = loadtspPos(Name);

    vector<int> order = {0};
    // double total_dist = tsp_nn(pos, order); // this would work for test case
    double total_dist = tsp_nn_xsort(pos, order); // would not work for test case
                                                  // as the cities orders are different
     if (order.size()<=10){
         cout << "visit order: " << endl;
        for (int i =0;i<order.size();i++){
          cout << order[i]+1 << " " ;
        }
    }
    cout.precision(30);
    cout << "total distance "<< total_dist <<endl;
    return 0;
}