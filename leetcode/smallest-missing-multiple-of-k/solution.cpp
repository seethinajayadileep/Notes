class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        set<int> st;
        for(int i=0;i<nums.size();i++){
            st.insert(nums[i]);
        }//time complexity nlogn ;
        bool flag=true;
        int result;
        int i=1;
        while(flag){
            int ans=k*i;
            if(st.find(ans)==st.end()){
                flag=false;
                result=ans;
            }
            i++;
            
        }
        return result;
    }
};