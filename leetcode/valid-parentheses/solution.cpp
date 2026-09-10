class Solution {
public:
    bool isValid(string s) {
        map<char,char> mpp;
        mpp['(']=')';
        mpp['{']='}';
        mpp['[']=']';
        stack<int> st;
        for(int i=0;i<s.size();i++){
            if(s[i]=='('||s[i]=='['||s[i]=='{'){
                st.push(s[i]);
            }
            else{
                if(!st.empty()&&mpp[st.top()]==s[i]){
                    st.pop();

                }
                else{
                    return false;
                }
            }
        }
      return st.empty()?true:false;
    }
};