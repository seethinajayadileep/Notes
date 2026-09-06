class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s2.size() <s1.size()){
            return false;
        }
        int freq1[26]={};
        int freq2[26]={};
        for(int i=0;i<s1.size();i++){
            freq1[s1[i]-'a']++;
                freq2[s2[i]-'a']++;
        }
        int l=0;
        for(int i=s1.size();i<s2.size();i++){
            freq2[s2[i]-'a']++;
            freq2[s2[l]-'a']--;
            l++;
            bool flag=true;
            for(int i=0;i<26;i++){

                if(freq1[i]!=freq2[i]){
                        flag=false;
                }
             
            }
              if(flag){
                    return true;
                }

        }
         return false;
    }
};