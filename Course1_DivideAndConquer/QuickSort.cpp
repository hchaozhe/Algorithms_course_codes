#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

// pivot selection 1 always use the first one as pivot
 #define CASEA
// pivot selection 2 always use the final one as pivot
// #define CASEB
// pivot selection 3 use the median of three rule
// #define CASEC
// pivot selection 4 random
// #define CASED

void PlotHelp(vector<int> &num, int every){
    int i;
    for (i =0;i<num.size();i=i+every){
        cout << i+1 << ":  " << num[i] <<endl;
    }
    if (i>num.size()){
    cout << num.size() << ":  " << num[num.size()-1] <<endl;
    }
}

void loadtxt(string Name, vector<int> &numbers){  
ifstream File;
    cout<< INT_MAX << endl;
    File.open(Name); 
    int x;
if (File.is_open()){
    while(File >> x )
    {
       
       numbers.push_back(x);
    }
    File.close();
    
    }else{
        cout << "cannot open file" << endl;
    }
 
}

void simpleswap(vector<int> &nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
int Pivot_mot(vector<int> &nums, int from, int to){
    // get the pivot using median-of-three 
    if (to - from<2){
        return from;
        // does not matter for the result.
    }
    int can1 = nums[from];
    int can2 = nums[(to+from)/2];
    int can3 = nums[to];
    // assume no identical element
    if ( (can1<can3 && can1>can2) || (can1>can3 && can1<can2)){
        return from;
    }
    if ( (can2<can1 && can2>can3) || (can2>can1 && can2<can3)){
        return (to+from)/2;
    }
    if ( (can3<can1 && can3>can2) || (can3>can1 && can3<can2)){
        return to;
    }
    // should not happen
    cout << "ERROR!!!!!" << endl;
    return 0;
}


int QuickSort(vector<int> &nums, int pivot_idx, int from, int to){
    // assume pivot is between from and to pivot >= from pivot < = to
    
    // first check the base case

    if (from == to){
        // means go no need for partition
        return 0;
    } 
    // second always swap with the first one (from)
    simpleswap(nums,from,pivot_idx);

       // second, start partion
    int pivot = nums[from];
 
    int i = from;
    int j = from +1; 
    for (;j<=to;j++){
      if (nums[j]<pivot){
       i++; // pivot should move 
       simpleswap(nums,i,j);
      }else{
        // i should stay, j should move on  
      }
    }
    // move pivot to the correct spot
    if (i!=from){
    simpleswap(nums,from,i);
    }
    
    int p1 = 0;
    int p2 = 0;
    // recursive
    #ifdef CASEA 
    if (i>from){
    p1 = QuickSort(nums, from, from, i-1);
    }
    if (i<to){
    p2 = QuickSort(nums, i+1, i+1, to);
    }
    #endif

    #ifdef CASEB 
    if (i>from){
    p1 = QuickSort(nums, i-1, from, i-1);
    }
    if (i<to){
    p2 = QuickSort(nums, to, i+1, to);
    }
    #endif
#ifdef CASEC 
    int pivot_sub = 0;
    if (i>from){
    pivot_sub = Pivot_mot(nums, from, i-1);    
    p1 = QuickSort(nums, pivot_sub, from, i-1);
    }
    if (i<to){
    pivot_sub = Pivot_mot(nums, i+1, to);     
    p2 = QuickSort(nums, pivot_sub, i+1, to);
    }
#endif

#ifdef CASED
    if (i>from){
    int pivot_sub = rand() % (i-from);
    p1 = QuickSort(nums, from + pivot_sub, from, i-1);
    }
    if (i<to){
    int pivot_sub = rand() % (to-i);    
    p2 = QuickSort(nums, i+1+pivot_sub, i+1, to);
    }
#endif



    // End of partion
    // return number of comparison 
    return to - from + p1 + p2;
}
int main(){

    /* initialize random seed: */
     srand (time(NULL));

    //vector<int> numbers{ 9,8,7,6,5,4,3,2,1,0};
    vector<int> numbers;
    string Name = "QuickSortTable.txt"; // relative path
    loadtxt(Name, numbers);
    

    vector<int> num{ 8,2,4,5,7,1};
 
    int pivot_idx = 0; 
     pivot_idx = Pivot_mot(num, 1, num.size()-1);
     PlotHelp(num,1);
     cout << "Pivot is " << pivot_idx << " " << num[pivot_idx] << endl;

    int total_cmp = 0;

    #ifdef CASEA
    cout << "always first one as pivot" <<endl;
    total_cmp = QuickSort(numbers,0,0,numbers.size()-1);
    #endif
    #ifdef CASEB
    cout << "always final one as pivot" <<endl;
    total_cmp = QuickSort(numbers,numbers.size()-1,0,numbers.size()-1);
    #endif
    #ifdef CASEC
    int pivot_sub = 0;
    pivot_sub = Pivot_mot(numbers, 0, numbers.size()-1);
    cout << "Median of three rule for pivot" <<endl;
    total_cmp = QuickSort(numbers,pivot_sub ,0,numbers.size()-1);
    #endif
    #ifdef CASED
    int pivot_sub = rand() % numbers.size();
    cout << "random pivot" <<endl;
    total_cmp = QuickSort(numbers,pivot_sub ,0,numbers.size()-1);
    #endif
    PlotHelp(numbers,1000);
    cout << "total compared times: " << total_cmp << endl;
    return 0;
}