class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(p.size()>s.size()){
            return {};
        }
        vector<int> p_freq(26,0);
        vector<int> wind_freq(26,0);
        vector<int> ans;
        int k=p.size();
        for(int i=0;i<p.size();i++){
            p_freq[p[i]-'a']++;
            wind_freq[s[i]-'a']++;

            
        }
        if(p_freq==wind_freq){
            ans.push_back(0);
        }
        for(int i=k;i<s.size();i++){
            wind_freq[s[i]-'a']++;
            wind_freq[s[i-k]-'a']--;
            if(wind_freq==p_freq){
                ans.push_back(i-k+1);
            }
        }
        return ans;

    }
};