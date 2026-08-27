class Solution {
public:
bool check(vector<int> &piles,int mid,int h){
    long long int count=0;
    for(int i=0;i<piles.size();i++){
      count+= (piles[i] + mid - 1) / mid;
    }
    return count<=h;
}
    int minEatingSpeed(vector<int>& piles, int h) {
        int low=1;
        int high=INT_MAX;
      
        while(low<high){
            int mid=low+(high-low)/2;
            if(check(piles,mid,h)){
                
                high=mid;
            }
            else{
                low=mid+1;
            }
        }
        return  low;
    }
};