class Solution {
public:
   void fun(vector<vector<int>> &ans,vector<int> &res,int index,vector<int> &nums){
    
     if(index==nums.size()){
        ans.push_back(res);
        return ;
     }
     res.push_back(nums[index]);
     fun(ans,res,index+1,nums);
     res.pop_back();
     fun(ans,res,index+1,nums);
   }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> res;
        fun(ans,res,0,nums);
        return ans;
    }
};