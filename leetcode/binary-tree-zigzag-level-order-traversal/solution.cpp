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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if(!root){
            return {};
        }
        vector<vector<int>> ans;
        q.push(root);
        bool flag=true;
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
            if(!flag){
                reverse(level.begin(),level.end());
            }
            ans.push_back(level);
            flag=!flag;
        }
        return ans;

    }
};