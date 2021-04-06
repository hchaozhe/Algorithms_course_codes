#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include "BH_simple_CRH.hpp"
// #define DEBUG
using namespace std;

void loadtxtarray(string name, vector<int> &numbers){
    ifstream File;
    int x;
    File.open(name); 
    if (File.is_open()){
    while(File >> x )
    {
          numbers.push_back(x);
    }
    File.close();
    for (int i =0;i<numbers.size();i=i+1000){
        cout << i+1 << ":  " << numbers[i] <<endl;
    }
    cout << numbers.size() << ":  " << numbers[numbers.size()-1] <<endl;
    }else{
        cout << "cannot open file" << endl;
    }
}

int main(int argc, char *argv[]){

    // load graph
    string path = "";
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
    filename = "Median.txt";
    }
	string Name = path + filename; // absolute path

    vector<int> numbers;
    loadtxtarray(Name,numbers);

    int checksum = 0;
    if (argc>2){
    checksum = stoi(argv[2]);
    }else{
    checksum = numbers.size();
    }

	int capacity = numbers.size(); // maximum possible size of min heap
	int median = 0; 
    int all_median_sum = 0;
    int v_s = numbers[0];
    int v_l = numbers[1];
    int v = 0;
    int v1 = 0;
    int v2 = 0;
    int v3 = 0;
    MinHeap heap_small(capacity/2+1); 
    MinHeap heap_large(capacity/2+1);
    // make sure that small >= large, and at most large by 1
    all_median_sum = numbers[0];
    heap_small.insertKey(-numbers[0],numbers[0]);
    #ifdef DEBUG
     cout << all_median_sum << endl;
    #endif

    if (numbers[1]<numbers[0]){
       all_median_sum = all_median_sum + numbers[1]; 
       heap_small.extractMin();
       heap_small.insertKey(-numbers[1],numbers[1]);
       heap_large.insertKey(numbers[0],numbers[0]);
    }else{
       all_median_sum = all_median_sum + numbers[0];
       heap_large.insertKey(numbers[1],numbers[1]); 

    }

    #ifdef DEBUG
     cout << all_median_sum << endl;
    #endif

    int i = 2;
    for (i=2; i<checksum; i++){
      // get new number
      v = numbers[i];
      // get the two median value 
      // v_s < v_l, and = only when  
      if (!heap_small.empty()){
          v_s = -heap_small.extractMin();
      }
      if (!heap_large.empty()){
          v_l = heap_large.extractMin();
      }

      // sort v_s v_l and v
      if (v<=v_s){
         v1 = v; v2 = v_s; v3 = v_l;    
      }else if(v>v_s && v<=v_l){
          v1 = v_s; v2=v; v3 = v_l;
      }else{
          v1 = v_s; v2 = v_l; v3 = v;
      }

      // insert back to the heap, making sure that 
      // left >=right but at most by 1

      if (heap_small.getsize()==heap_large.getsize()){
          
          heap_small.insertKey(-v1,v1);
          heap_small.insertKey(-v2,v2);
          heap_large.insertKey(v3,v3);
      }else{
          heap_small.insertKey(-v1,v1);
          heap_large.insertKey(v2,v2);
          heap_large.insertKey(v3,v3);
      }

      // get the new median
      
        median = -heap_small.getMin(); // the top one should be the maximum
        all_median_sum = all_median_sum + median;
        #ifdef DEBUG
        cout << all_median_sum << endl;
        #endif

    }
    cout << all_median_sum << " " << all_median_sum % 10000 << endl;
    return 0;
 
}



