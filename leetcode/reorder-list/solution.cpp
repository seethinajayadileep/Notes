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
    void reorderList(ListNode* head) {
        ListNode *temp=head;
        int cnt=0;
        while(temp){
            temp=temp->next;
            cnt++;
        }
        temp=head;
        vector<int> firsthalf;
        vector<int> secondhalf;
        int k=0;
        while(temp){
            if(k<(cnt+1)/2){
                firsthalf.push_back(temp->val);
            }
            else{
                secondhalf.push_back(temp->val);
            }
            temp=temp->next;
            k++;

        }
        temp=head;
        k=0;
        int i=0;
        int j=secondhalf.size()-1;
        while(temp){
            if(k%2==0){
                temp->val=firsthalf[i++];
            }
            else{
                temp->val=secondhalf[j--];
            }
            k++;
            temp=temp->next;
        }

    }
};