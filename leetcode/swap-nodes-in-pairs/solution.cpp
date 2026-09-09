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
    ListNode* swapPairs(ListNode* head) {
        if(!head||head->next==NULL){
            return head;
        }
        ListNode *slow=head;
        ListNode *fast=head->next;
        while(fast){
            int temp=slow->val;
            slow->val=fast->val;
            fast->val=temp;
            if(slow->next!=NULL&&fast->next!=NULL){
                fast=fast->next->next;
                slow=slow->next->next;
            }
            else{
                break;
            }
        }
        return head;
    }
};