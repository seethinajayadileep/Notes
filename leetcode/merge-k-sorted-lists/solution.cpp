/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> ans;
        for(int i=0;i<lists.size();i++){
            ListNode *head=lists[i];
            while(head){
                ans.push_back(head->val);
                head=head->next;
            }

        }
        sort(ans.begin(),ans.end());
        ListNode *res=new ListNode(-1);
        ListNode *newdum=res;
        for(int i=0;i<ans.size();i++){
            newdum->next=new ListNode(ans[i]);
            newdum=newdum->next;
        }
        return res->next;
        
    }
};