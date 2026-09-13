class Solution {
public:
   void fun(vector<int> &nums,vector<vector<int>> &ans,int index){
    if(index==nums.size()){
        ans.push_back(nums);
        return ;
    }
    for(int i =index;i<nums.size();i++){
        swap(nums[index],nums[i]);
        fun(nums,ans,index+1);
          swap(nums[index],nums[i]);
    
    }
   }

    vector<vector<int>> permute(vector<int>& nums) {
        
    vector<vector<int>> ans;
    fun(nums,ans,0);
return ans;

    }
};