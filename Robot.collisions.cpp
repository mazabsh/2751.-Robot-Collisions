#include<iostream> 
#include<vector> 
#include<array> 
#include<algorithm> 
#include<stack> 


using namespace std; 

class Solution{
public: 
     vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
       int n = positions.size(); 
       vector<array<int,4>> robots; 
       for(int i=0; i<n; ++i){
         robots.push_back({positions[i], healths[i], i, directions[i]=='R'}); 
       }
       sort(robots.begin(),robots.end()); 
       stack<int> st; 
       for(int i=0; i<n; ++i){
         int health = robots[i][1]; 
         int isRight = robots[i][3]; 
         if(isRight) st.push(i); 
         else{
           while(!st.empty() && health>0){
             int j= st.top(); 
             if(robots[j][1] > health){
               health =-1; 
               --robots[j][1]; 
               break; 
             }else if(robots[j][1]< health){
               --health; 
               robots[j][1] =-1; 
               st.pop(); 
             }else {
               health = -1; 
               robots[j][1]=-1; 
               st.pop(); 
               break; 
             }
           }
         }
         if(health >0) robots[i][1] =health; 
         else robots[i][1] =-1; 
       }
       vector<int> isAlive(n,-1); 
       for(auto r:robots){
         if(r[1]>0) isAlive[r[2]]= r[1];  
       }
       vector<int> res; 
       for(int i=0; i<n; ++i){
         if(isAlive[i]>0) res.push_back(isAlive[i]); 
       }
       return res; 
     }
};
int main(){
  vector<int> positions= {3,5,2,6}; 
  vector<int> healths = {10,10,15,12}; 
  string directions = "RLRL"; 
  Solution sol; 
  vector<int> res= sol.survivedRobotsHealths(positions, healths, directions); 
  for(int n:res) cout << n << ", " ; 
  return 0; 
}
