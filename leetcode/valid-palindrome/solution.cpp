class Solution {
public:
    bool isPalindrome(string s) {
        string first="";
        for(auto ele:s){
            if((ele>='a'&&ele<='z')||(ele>='A'&&ele<='Z')){
                first+=tolower(ele);
            }
        }
        string last=first;
        reverse(last.begin(),last.end());
        return first==last;
    }
};