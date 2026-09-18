class Solution {
public:
    int jump(vector<int>& nums) {
        int fathest=0;
        int jump=0;
        int currentend=0;
        for(int i=0;i<nums.size()-1;i++){
            fathest=max(fathest,nums[i]+i);
            if(i==currentend){
                jump++;
                currentend=fathest;
            }
        }
        return jump;
    }
};