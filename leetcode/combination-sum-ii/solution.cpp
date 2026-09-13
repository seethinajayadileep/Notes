class Solution {
public:
    void fun(vector<int> &candidates,set<vector<int>> &ans,vector<int> &res,int index,int target){
        if(target==0){
           ans.insert(res);
            return ;
        }
        if(target<0 || index==candidates.size()){
            return ;
        }
        res.push_back(candidates[index]);
        fun(candidates,ans,res,index+1,target-candidates[index]);
        res.pop_back();
       
        fun(candidates,ans,res,index+1,target);

    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        set<vector<int>> ans;
        vector<int> res;
        sort(candidates.begin(),candidates.end());
        fun(candidates,ans,res,0,target);
        return vector<vector<int>>(ans.begin(),ans.end());
    }
};