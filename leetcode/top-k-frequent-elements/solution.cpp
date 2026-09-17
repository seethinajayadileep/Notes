class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<pair<int,int>> ans;
        map<int,int> mpp;
        for(int i=0;i<nums.size();i++){
            mpp[nums[i]]++;
        }
        for(auto ele:mpp){
            ans.push_back({ele.first,ele.second});
        }
        sort(ans.begin(),ans.end(),[](const pair<int,int> &a,const pair<int,int> &b){
            return a.second>b.second;
        });
        vector<int> res;
        for(int i=0;i<k;i++){
            res.push_back(ans[i].first);
        }
        return res;
    }
};