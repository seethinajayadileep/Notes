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
   ListNode* kthfun(ListNode *head,int k){
     ListNode *temp=head;
     while(k && temp){
        temp=temp->next;
        k--;
     }
     return temp;

   }
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head||head->next==NULL){
            return head;
        }
        ListNode *newList =new ListNode(-1);
       
        int cnt=0;
        ListNode *temp=head;
        while(temp){
            cnt++;
            temp=temp->next;
        }
        k=k%cnt;
     
      if(k==0){
            return head;
        }
        ListNode *kthNode=kthfun(head,cnt-k);
        ListNode *newans=newList;
        temp=kthNode;
        while(temp){
            newans->next=new ListNode(temp->val);
            newans=newans->next;
            temp=temp->next;

        }
        temp=head;
        k=cnt-k;
        while(k){
            newans->next=new ListNode(temp->val);
             newans=newans->next;
            temp=temp->next;
            k--;
        }
        return newList->next;
        
    }
};