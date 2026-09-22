class Solution {
public:
    int scoreOfString(string s) {
        int prev=int(s[0]);
        int sum=0;
        for(int i=1;i<s.size();i++){
               sum+=abs(prev-s[i]);
               prev=int(s[i]);
        }
        return sum;
    }
};