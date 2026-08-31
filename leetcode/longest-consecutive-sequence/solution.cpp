class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        set<int> st;
        for(int i=0;i<nums.size();i++){
            st.insert(nums[i]);
        }
        int prev=*st.begin();
        int maxcount=1;
        int count=1;
        for(auto ele:st){
            if(ele-1==prev){
                count++;
                maxcount=max(count,maxcount);

            }
            else{
                count=1;
            }
            prev=ele;

        }
        return maxcount;
    }
};