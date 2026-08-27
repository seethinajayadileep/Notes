class Solution {
public:
  bool check(vector<int> &bloomDay,int m,int k,int mid){
    int count=0;
    int boquets=0;
    for(int i=0;i<bloomDay.size();i++){
        if(bloomDay[i]<=mid){
             count++;
             if(count==k){
                boquets++;
                 count=0;
             }
            
        }
        else{
            count=0;
        }
    }
    return boquets>=m;
  }
    int minDays(vector<int>& bloomDay, int m, int k) {
        int low=0;
        int high=INT_MAX;
 
        while(low<high){
            int mid=low+(high-low)/2;
            if(check(bloomDay,m,k,mid)){
                high=mid;
            }
            else{
                low=mid+1;
            }
        }
        return low==INT_MAX?-1:low;
    }
};