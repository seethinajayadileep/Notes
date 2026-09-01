class Solution {
public:
    string longestPalindrome(string s) {
        string max_string ="";
        int maxcount=0;
        for(int i=0;i<s.size();i++){
                string dum="";
            for(int j=i;j<s.size();j++){
                 dum+=s[j];
                 string last=dum;
                 reverse(last.begin(),last.end());
                 if(last==dum){
                      if(maxcount<last.size()){
                        maxcount=last.size();
                        max_string=last;
                      }
                 }
            }
        }
        return max_string;
    }
};