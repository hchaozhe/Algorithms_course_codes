#include <iostream>
#include <fstream>
#include <sstream> // istringstream
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>    // std::sort
using namespace std;


template <typename T>
void loadtxt(string Name, vector<vector<T>> &numbers){  
ifstream File;
    File.open(Name); 
    T x;
    T job_weight;
    T job_length;
    string line;
if (File.is_open()){
    // first row is task number
    File >> x;
    cout << " total " << x <<" jobs " << endl;
    x = 0;
    while(getline(File,line) ){
    istringstream iss(line);
       if (x==0){
           x++;
           continue;
        }
        iss >> job_weight;
        iss >> job_length;
        numbers.push_back({job_weight,job_length});
        x++;
    }

    File.close();
    
    }else{
        cout << "cannot open file" << endl;
    }
 
}
template <typename T>
void printtask(vector<vector<T>> &numbers, int ratio){
    int i =0;
    while (i<numbers.size())
    {   cout << i+1 << " " << numbers[i][0] << " " << numbers[i][1] << endl;
        i = i+ratio;
    }
    if (i==numbers.size()){
        cout << i << " " << numbers[i-1][0] << " " << numbers[i-1][1] << endl;
    }
    
}

bool GA1_comp(const vector<int> a, const vector<int> b){
    // using the value weight [0] - length[1] as the score
    // put the higher score one at the front
    // tie breaker, use the one with larger weight if score are the same
    // return true if a should be in from of b;
    int scorea, scoreb;
    scorea = a[0]-a[1];
    scoreb = b[0]-b[1];
    if(scorea > scoreb){
        return true;
    }else if(scorea == scoreb){
        // tie breaker;
        return a[0] > b[0];
    }else{
        return false;
    }

}

bool GA2_comp(const vector<int> a, const vector<int> b){
    // using the value weight [0]/length[1] as the score 
    // Remark!! one need to convert data type here.
    // put the higher score one at the front
    // tie breaker, use the one with larger weight if score are the same
    // return true if a should be in from of b;
    double scorea, scoreb;
    scorea = ((double) a[0])/((double) a[1]);
    scoreb = ((double) b[0])/((double) b[1]);
    if(scorea > scoreb){
        return true;
    }else if(scorea == scoreb){
        // tie breaker;
        // should be vary rare
        return a[0] > b[0];
    }else{
        return false;
    }

}


long int TotalCostCal(vector<vector<int>> &numbers){
    long int cost = 0;
    long int ft = 0;
    for (int i = 0; i < numbers.size(); i++)
    {   
        cost = cost + ((long int) numbers[i][0]*(numbers[i][1]+ft));
        ft = ft + (long int) numbers[i][1];
    }
    
    return cost;
}
int main(int argc, char *argv[]){
 
    string path = "";
	
	string filename;
    if (argc>1){
    filename = argv[1];
    }else{
   
    filename = "job.txt";
    }
    int ratio =1000;
    if (argc>2){
    ratio = stoi(argv[2]);
    }
	string Name = path + filename; // absolute path
    vector<vector<int>> numbers;
    loadtxt<int>(Name, numbers);
    printtask<int>(numbers,ratio);
    
    // 
    vector<vector<int>> greed1;

    greed1 = numbers;

    cout << "before sort" << endl;
    printtask<int>(greed1,ratio);
    sort(greed1.begin(),greed1.end(),GA1_comp);
    cout << "after sort" << endl;
    printtask<int>(greed1,ratio);
    cout << "Greedy 1 total cost is " <<TotalCostCal(greed1) << endl;
    //69119377652
    vector<vector<int>> greed2;
    greed2 = numbers;
    sort(greed2.begin(),greed2.end(),GA2_comp);
    cout << "after sort" << endl;
    printtask<int>(greed2,ratio);
    cout << "Greedy 2 total cost is " <<TotalCostCal(greed2) << endl;
    //67311454237
    return 0;
}