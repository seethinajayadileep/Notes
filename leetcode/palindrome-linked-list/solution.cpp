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
   ListNode *reversefun(ListNode* head){
   ListNode *prev=NULL;
   ListNode *temp=head;
   while(temp){
    ListNode *next=temp->next;
    temp->next=NULL;
    prev=temp;
    temp=next;
   }
   return prev;
   }
    bool isPalindrome(ListNode* head) {
        
        ListNode *sec=reversefun(head);
        while(head &&sec){
            if(head->val!=sec->val){
                return false;
            }
            head=head->next;
            sec=sec->next;
        }
        if(!head &&!sec){
            return true;
        }
        return false;

    }
};