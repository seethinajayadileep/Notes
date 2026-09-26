class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> ans;
        
        int carry=1;
        for(int i=digits.size()-1;i>=0;i--){
            int sum=digits[i]+carry;
            carry=sum/10;
            ans.insert(ans.begin(),sum%10);
        }
        if(carry){
            ans.insert(ans.begin(),carry);
        }
        return ans;
    }
};