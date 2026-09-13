class Solution {
public:
   void fun(vector<int> &candidates,vector<vector<int>> &ans,vector<int> &res,int index,int target){
    if(target==0){
        ans.push_back(res);
        return ;
    }
    if(index==candidates.size()||target<0){
        return ;
    }
     res.push_back(candidates[index]);
     fun(candidates,ans,res,index,target-candidates[index]);
     res.pop_back();

     fun(candidates,ans,res,index+1,target);


   }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> res;
        fun(candidates,ans,res,0,target);
        return ans;
    }
};