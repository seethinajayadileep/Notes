class Solution {
public:
    int characterReplacement(string s, int k) {
        int l=0,ans=0,max_freq=0;
        map<char,int> mpp;
        for(int right=0;right<s.size();right++){
          mpp[s[right]]++;
          max_freq=max(max_freq,mpp[s[right]]);
          int window_length=right-l+1;
          int m=window_length-max_freq;
          if(m>k){
            mpp[s[l]]--;
            l++;
          }
          ans=max(ans,right-l+1);
           
        }
        return ans;
    }
};