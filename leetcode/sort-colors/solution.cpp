class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zeros=0,ones=0,twos=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==0){
                zeros++;

            }
            else if(nums[i]==1){
                ones++;
            }
            else{
                twos++;
            }
        }
        for(int i=0;i<nums.size();i++){
            if(zeros){
                nums[i]=0;
                zeros--;
            }
            else if(ones){
                nums[i]=1;
                ones--;
            }
            else{
                nums[i]=2;
                twos--;
            }
        }
       
    }
};