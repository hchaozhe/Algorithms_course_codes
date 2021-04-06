#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
// #define DEBUGLL
#define DEBUGSS
void PlotHelp(vector<int> &num, int from, int to, long long int inv){
    for (int i = from; i<=to;i++){
      cout << num[i] << " ";
    }
    cout<< " with inversion " << inv << endl;
}

void PlotHelp2(int from, int to, long long int inv){
    cout<< " from " << from <<" to " << to <<" inversion " << inv << endl;
}

long long int sort_and_count(vector<int> &v, int from, int to){
    
    if (from == to){
        return 0;
    }
    long long int inversion_count = 0;
    int n = to - from+1; // size of the sorted section
    vector<int> sorted(n,0);
     
     // devide
     int from_left = from;
     int to_left = (from + to)/2;
     int from_right = to_left+1;
     int to_right = to;
     long long int inversion_left = 0;
     long long int inversion_right = 0;
     inversion_left = sort_and_count(v,from_left,to_left);
     inversion_right = sort_and_count(v,from_right,to_right);
     inversion_count = inversion_right+ inversion_left;

#ifdef DEBUGLL
     cout << "left: " ;
     PlotHelp(v,from_left,to_left, inversion_left);
     cout << "right: " ;
     PlotHelp(v,from_right,to_right, inversion_right);
#endif
#ifdef DEBUGSS
     if (n>=5000){
     PlotHelp2(from_left,to_left, inversion_left);
     PlotHelp2(from_right,to_right, inversion_right);
     }
#endif     

     // merge sort
     int l=from_left;
     int r=from_right;
     int left_num = 0;
     int right_num = 0;
     for(int i =0;i<n;i++){
        if (l<=to_left && r<=to_right){ 
            // there are still left
        left_num = v[l];
        right_num = v[r];

        if (left_num<=right_num){
            // no inversion
            sorted[i] = left_num;
            l++;
        }else{
            // there are inversions 
            sorted[i] = right_num;
            inversion_count = inversion_count + 
                         ( (long long int) (to_left - l + 1) );
            r++;              
        }
        }else if(r<=to_right){
           // left is all gone, no more inversion
           sorted[i] = v[r];
           r++;
        }else{
            // right is all gone, no more inversion
           sorted[i] = v[l];
           l++;
        }
     }     

    // after sort and merged, override v 
    for (int i = 0;i<n;i++){
        v[from + i]=sorted[i];
    }
#ifdef DEBUGLL    
    // cout << "merged: " ;
    // PlotHelp(v,from,to, inversion_count);
#endif
#ifdef DEBUGSS
     if (n>=5000){
     PlotHelp2(from,to, inversion_count);
     }
#endif     
    return inversion_count; 
}





int main(){

    //vector<int> numbers{ 9,8,7,6,5,4,3,2,1,0};
    vector<int> numbers;

    ifstream File;
    cout<< INT_MAX << endl;
    File.open("IntegerArray.txt");
    int x;
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

    long long int inversion = 0;
    cout << inversion <<endl;

    int from = 0;
//    int to = 4999;
    // int from = 0;
    int to = numbers.size()-1;

    inversion = sort_and_count(numbers, from, to);
    cout<< "Final result: ";

    // cout<< "Final result: "; // my answer is 2407905288
    #ifdef DEBUGLL
     PlotHelp(numbers, from, to, inversion);
    #endif
    #ifdef DEBUGSS
    PlotHelp2(from, to, inversion);
    #endif

    return 0;
}