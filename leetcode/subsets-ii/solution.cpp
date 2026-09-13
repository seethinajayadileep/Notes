class Solution {
public:
   void fun(vector<vector<int>> &ans,vector<int> &res,int index,vector<int> &nums){
        if(index==nums.size()){
            ans.push_back(res);
            return;
        }
        res.push_back(nums[index]);
        fun(ans,res,index+1,nums);
        res.pop_back();
       for(int i=index+1;i<nums.size();i++){
            if(nums[i]!=nums[index]){
                fun(ans,res,i,nums);
                return ;
            }
        }
        fun(ans,res,nums.size(),nums);
   }
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> res;
        fun(ans,res,0,nums);
      return ans;
    }
};