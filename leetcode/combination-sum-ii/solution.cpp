class Solution {
public:
    void fun(vector<int> &candidates,vector<vector<int>> &ans,vector<int> &res,int index,int target){
        if(target==0){
           ans.push_back(res);
            return ;
        }
        if(target<0 || index==candidates.size()){
            return ;
        }
        res.push_back(candidates[index]);
        fun(candidates,ans,res,index+1,target-candidates[index]);
        res.pop_back();
        while(index+1<candidates.size()&&candidates[index]==candidates[index+1]){
            index++;
        }
       
        fun(candidates,ans,res,index+1,target);

    }
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> res;
        sort(candidates.begin(),candidates.end());
        fun(candidates,ans,res,0,target);
        return ans;
    }
};