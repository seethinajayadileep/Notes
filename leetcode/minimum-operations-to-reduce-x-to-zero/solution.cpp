class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int sum=0;
       for(auto ele:nums){
        sum+=ele;

       }
       int target=sum-x;
       if(target<0){
        return -1;
       }
       if(target==0){
        return nums.size();
       }
       int left=0;
       sum=0;
       int maxlen=-1;
       for(int right=0;right<nums.size();right++){
           sum+=nums[right];
           while(target<sum){
            sum-=nums[left];
            left++;
           }
           if(target==sum){
             maxlen=max(maxlen,right-left+1);

           }
          
       }
       if(maxlen==-1){
        return maxlen;
       }
       return nums.size()-maxlen;
    }
};