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
    ListNode *reversefun(ListNode *temp){
        ListNode *prev=NULL;
        ListNode *curr=temp;
        while(curr){
            ListNode *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        return prev;

    }
    bool isPalindrome(ListNode* head) {
        ListNode *slow=head;
        ListNode *fast=head;
        while(fast->next &&fast->next->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        ListNode *sec=reversefun(slow->next);
        while(sec){
            if(head->val!=sec->val){
                return false;
            }
            head=head->next;
            sec=sec->next;
            
        }
        return true;
    }
};