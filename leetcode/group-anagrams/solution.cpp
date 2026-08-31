class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string,vector<string>> mpp;
        for(auto ele:strs){
            string k=ele;
            sort(k.begin(),k.end());
            mpp[k].push_back(ele);
        }
        vector<vector<string>> ans;
        for(auto ele:mpp){
            ans.push_back(ele.second);
        }
        return ans;
    }
};