class Solution {
public:
    int countSubstrings(string s) {
       int count=0;
        for(int i=0;i<s.size();i++){
                string dum="";
            for(int j=i;j<s.size();j++){
                 dum+=s[j];
                 string last=dum;
                 reverse(last.begin(),last.end());
                 if(last==dum){
                      count++;
                 }
            }
        }
        return count;
    }
};