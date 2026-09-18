class Solution {
public:
    bool canJump(vector<int>& nums) {
        int target=0;
        for(int i=0;i<nums.size();i++){
            if(i>target){
                return false;
            }
         target=max(target,nums[i]+i);
        }
        return true;
    }
};