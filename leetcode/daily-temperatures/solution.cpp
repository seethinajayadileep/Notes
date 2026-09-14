class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
vector<int> ans(temperatures.size(),0);
stack<int> st;

        for(int i=0;i<temperatures.size();i++){
            while(!st.empty()&&temperatures[i]>temperatures[st.top()]){
                int prev=st.top();
                st.pop();
                ans[prev]=i-prev;
            }
           st.push(i);
        }
        return ans;
    }
};