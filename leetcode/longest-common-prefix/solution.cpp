class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()){
            return "";
        }
        size_t mini=INT_MAX;
        for(int i=0;i<strs.size();i++){
            mini=min(strs[i].size(),mini);
        }
         string pref="";
        int i=0;
        while(i<mini){
            char  k=strs[0][i];
            for(int j=0;j<strs.size();j++){
                if(strs[j][i]!=k){
                return pref;
            }
            }
            pref+=k;
            i++;
        }
        return pref;
    }
};