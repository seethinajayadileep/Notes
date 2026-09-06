class Solution {
public:
    int characterReplacement(string s, int k) {
        int l=0,ans=0,max_freq=0;
      int freq[26]={};
        for(int right=0;right<s.size();right++){
          freq[s[right]-'A']++;
          max_freq=max(max_freq ,freq[s[right]-'A']);
          int window_length=right-l+1;
          int m=window_length-max_freq;
          if(m>k){
            freq[s[l]-'A']--;
            l++;
          }
          ans=max(ans,right-l+1);
           
        }
        return ans;
    }
};