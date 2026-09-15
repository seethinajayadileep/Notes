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
    vector<int> rightSideView(TreeNode* root) {
        if(!root){
            return {};
        }
        queue<TreeNode*> q;
        vector<vector<int>> ans;
        q.push(root);
        while(!q.empty()){
            int size=q.size();
            vector<int> level;
            for(int i=0;i<size;i++){
                TreeNode *ele=q.front();
                q.pop();
                level.push_back(ele->val);
                if(ele->left){

               q.push(ele->left);
                }
                if(ele->right){
                    q.push(ele->right);
                }
        
             
            }
            ans.push_back(level);
        }
        vector<int> res;
       for(auto ele:ans){
          res.push_back(ele.back());
       }
       return res;
    }
};