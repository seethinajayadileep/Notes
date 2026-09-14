/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void dfs(vector<vector<int>> &ans,vector<int> &res,TreeNode *root){
        if(!root){
            return ;
        }
        if(!root->left&&!root->right){
            res.push_back(root->val);
            ans.push_back(res);
            res.pop_back();
            return ;
        }
       res.push_back(root->val);
       dfs(ans,res,root->left);
       dfs(ans,res,root->right);
       res.pop_back();
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> res;
        dfs(ans,res,root);
        for(int i=0;i<ans.size();i++){
            int sum=0;
            for(int j=0;j<ans[i].size();j++){
                sum+=ans[i][j];
            }
            if(sum==targetSum){
                return true;
            }
        }
        return false;

    }
};