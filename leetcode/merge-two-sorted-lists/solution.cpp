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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode *final1=new ListNode(-1);
        ListNode *temp=final1;
        while(list1 &&list2){
            if(list1->val<=list2->val){
                final1->next=new ListNode(list1->val);
                final1=final1->next;
                list1=list1->next;
            }
            else{
               final1->next=new ListNode(list2->val);
                final1=final1->next;
                list2=list2->next;
            }
        

        }
        if(list1){
            final1->next=list1;
        }
         if(list2){
            final1->next=list2;
        }
        return temp->next;
    }
};