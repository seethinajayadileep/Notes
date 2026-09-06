class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s2.size() <s1.size()){
            return false;
        }
       vector<int> freq1(26,0);
          vector<int> freq2(26,0);
       
        for(int i=0;i<s1.size();i++){
            freq1[s1[i]-'a']++;
                freq2[s2[i]-'a']++;
        }
        if(freq1==freq2){
            return true;
        }
        int l=0;
        for(int i=s1.size();i<s2.size();i++){
            freq2[s2[i]-'a']++;
            freq2[s2[l]-'a']--;
            l++;
            
            if(freq1==freq2){
                return true;
            }

        }
         return false;
    }
};