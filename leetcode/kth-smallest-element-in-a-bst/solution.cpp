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
   void fun(TreeNode *root,int &count ,int k,int &found){
    if(!root){
        return ;
    }
    fun(root->left,count,k,found);
    count++;
    if(count==k){
        found=root->val;

        return ;
    }
    fun(root->right,count,k,found);
   }
    int kthSmallest(TreeNode* root, int k) {
        int found=-1;
        int count=0;
        fun(root,count,k,found);
        return found;
        
    }
};