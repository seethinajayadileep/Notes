class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if(s.size()<p.size()){
            return {};
        }
        vector<int> ans;
        int res[26]={0};
        for(auto ele:p){
            res[ele-'a']++;

        }
        for(int i=0;i<s.size()-p.size()+1;i++){
           int freq[26]={0};
            for(int j=i;j<i+p.size();j++){
                
                   freq[s[j]-'a']++;

                
            }
            int count=0;
            for(auto ele:p){
                if(freq[ele-'a']==res[ele-'a']){
                   count+=1;
                }

            }
            if(count==p.size()){
                ans.push_back(i);
            }

            

        }
        return ans;

    }
};