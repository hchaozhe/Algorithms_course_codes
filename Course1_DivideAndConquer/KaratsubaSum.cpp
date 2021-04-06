#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
//#define DEBUG

void PlotHelp(vector<int> &num){
    for (int i = 0; i<num.size();i++){
      cout << num[i];
    }
    cout<< endl;
}

void PlotHelp2(vector<int> &num){
    for (int i = 0; i<num.size();i++){
      cout << num[i];
    }
    cout<< "  ";
}
vector<int> getvector(vector<int> &v1,int i,int j){
       vector<int> sub_v;
       for (int k =i;k<=j;k++){
           sub_v.push_back(v1[k]);
       }
       return sub_v;
}



 vector<int> simpleadd(vector<int> &v1,vector<int> &v2 ){
        // the size wil be according to the actual size,
           int len = max(v1.size(),v2.size());
           vector<int> result;
           int carryover = 0;
           int sum = 0;
           int v1_value = 0;
           int v2_value = 0;
           for (int m = 0;m<len;m++){
                if (m<v1.size()){
                    v1_value = v1[v1.size()-1-m]; 
                  }else{
                    v1_value = 0;
                 }

                if (m<v2.size()){
                    v2_value = v2[v2.size()-1-m]; 
                  }else{
                   v2_value = 0;
                }

                sum = v1_value + v2_value + carryover; 
                result.insert(result.begin(), sum%10);
                carryover = sum/10;
                }
                if (carryover>0){
                result.insert(result.begin(), carryover);
                }
                return result;
}

vector<int> subtractlong(vector<int> &v1, vector<int> &v2){
            // assume v1 is larger than v2;
            // v2 might be shorter
            // the final one will have the size to the none 0 significant bit.

            int len = v1.size(); // the longer one
            int len2 = v2.size(); // shorter one
            int carryover = 0;
            vector<int> result(len,0);
            int v2_value = 0;
            for (int i=1;i<=len;i++){
               if (i>len2){
                 // no more value on v2 
                 v2_value = 0;
               }else{
                 v2_value = v2[len2-i]; 
               }              
               if (v1[len-i]+carryover<v2_value){
                   result[len-i] = v1[len-i] + carryover+10 -v2_value;
                   carryover = -1;
               }   else{
                   result[len-i] = v1[len-i] + carryover -v2_value;
                   carryover = 0;
               }
               
            }
            while(result[0]==0&&result.size()>1){
                result.erase(result.begin());
            }
            return result;
} 
                     
vector<int> laststep(vector<int> ac, vector<int> bd, vector<int> ab_cd, int m){
           // b and d are of size m
           // a and c might be smaller (m-1) 
           // assuming these vectors are already of proper length
           vector<int> e;
           // (a+b)*(c+d) - ac - bd = bc+ad
           e = subtractlong(ab_cd,ac);
           e = subtractlong(e,bd);
           // ac = ac*10^2m
           if (ac[0]>0){
           for (int i = 0;i<2*m;i++){
               ac.push_back(0);
           }
           }
           // e = e * 10^m
           if (e[0]>0){
           for (int i = 0;i<m;i++){
               e.push_back(0);
           }
           }
           vector<int> sum;
           // ac + e + bd
           sum = simpleadd(ac,e);
           sum = simpleadd(sum,bd);
           return sum;
}

vector<int> mutliple(vector<int> &num1,vector<int> &num2 ){

        // we assume it is always same size?
        // intialization do not specify result
        // make same length
           while (num1.size()<num2.size()){
                  num1.insert(num1.begin(),0);  
                 }
           while (num2.size()<num1.size()){
                  num2.insert(num2.begin(),0);  
                 }
                 
            vector<int> result;
                    
                    if (num1.size()==1){
                        // at most len = 2;
                        // two digits put at the last two
                        result.push_back(num1[0]*num2[0]%10);
                        if (num1[0]*num2[0]/10>0){
                        result.insert(result.begin(),num1[0]*num2[0]/10); 
                        }
                    }else{
                        int len = num1.size();
                       // get  
                       // a b
                       int a_i = 0;
                       int a_j = len/2-1; // if n = 2m, this is m-1, if n = 2m-1, this is m-2
                       int b_i = len/2;
                       int b_j = len-1;
                       // b is always longer
                       vector<int> a,b,c,d,ab,cd,ac,bd,ab_cd;
                       a = getvector(num1,a_i,a_j);
                       b = getvector(num1,b_i,b_j);
                       c = getvector(num2,a_i,a_j);
                       d = getvector(num2,b_i,b_j);
                       ab = simpleadd(a,b);
                       cd = simpleadd(c,d);
                    // debug print
                    //    cout << a_i << " "<< a_j << " : "<<b_i << " "<<  b_j << endl;
                    //    PlotHelp(a);
                    //    PlotHelp(b);
                    //    PlotHelp(c);
                    //    PlotHelp(d);
                    //    PlotHelp(ab);
                    //    PlotHelp(cd);
                       ac = mutliple(a,c);
                       bd = mutliple(b,d);
                       ab_cd = mutliple(ab,cd);
                       result = laststep(ac,bd,ab_cd,(len+1)/2); 

#ifdef DEBUG
                     // debug print  
                 cout << "ac: " ;
                 PlotHelp2(ac);
                 cout << " bd: " ;
                 PlotHelp2(bd);
                 cout << " ab_cd: " ;
                 PlotHelp2(ab_cd); 
#endif
                     } 
#ifdef DEBUG
                 PlotHelp2(num1);
                 cout << " times " ;
                 PlotHelp2(num2);
                 cout << " equals ";
                 PlotHelp2(result); 
                 cout << endl;
                
#endif             
        return result;        
}
                     

int main()
{   string s1 = "3141592653589793238462643383279502884197169399375105820974944592";
    string s2 = "2718281828459045235360287471352662497757247093699959574966967627";
    vector<int> n1, n2;
    for (int i = 0; i<s1.size();i++){
      n1.push_back(s1[i]-'0');
      n2.push_back(s2[i]-'0');
      cout << n1[i];
    }
    cout << endl;




    // simple test the add and subtract
    vector<int> sum;
    vector<int> u1;
    vector<int> u2;
    u1 = getvector(n1,60,63);
    u2 = getvector(n2,60,63);
    PlotHelp(u1);
    PlotHelp(u2);
    sum = simpleadd(u1,u2);
    
    PlotHelp(sum);

    vector<int> v1{ 1,0,0,0,0,0,0};
    vector<int> v2{     9,9,9,9,7};
    vector<int> subtract;
    subtract=subtractlong(v1,v2);
    PlotHelp(subtract);
    vector<int> add2v;
    add2v=simpleadd(n1,n2);
    PlotHelp(add2v);

    vector<int> result;
    u1 = getvector(n1,0,63);
    u2 = getvector(n2,0,63);
    result = mutliple(u1,u2);
    
    PlotHelp(u1);
    cout << " times " ;
    PlotHelp(u2);
    cout << " equals ";
    PlotHelp(result); 
    

}

