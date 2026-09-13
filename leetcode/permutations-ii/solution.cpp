class Solution {
public:
    void fun(vector<int> &nums,set<vector<int>> &st,int index){
        if( nums.size()==index){
            st.insert(nums);
            return ;
        }
        for(int i=index;i<nums.size();i++){
            swap(nums[index],nums[i]);
            fun(nums,st,index+1);
            swap(nums[index],nums[i]);
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        set<vector<int>> st;
        fun(nums,st,0);
        return vector<vector<int>>(st.begin(),st.end());
    }
};