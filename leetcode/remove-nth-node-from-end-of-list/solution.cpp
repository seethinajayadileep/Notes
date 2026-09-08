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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *temp=head;
        int cnt=0;
        while(temp){
            cnt++;
            temp=temp->next;

        }
        temp=head;
        if(cnt==n){
           head=head->next;
           delete temp;
            return head;
        }
         cnt=cnt-n;
        int k=1;
        while(temp){
            if(k==cnt){
                ListNode *deln=temp->next;
                temp->next=temp->next->next;
                delete deln;
            }
            temp=temp->next;
            k++;
        }
        return head;
    }
};