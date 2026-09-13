class Solution {
public:
bool palindrome(string s){
    int l=0;
    int r=s.size()-1;
    while(l<=r){
        if(s[l]!=s[r]){
            return false;
        }
        l++;
        r--;
    }
    return true;
}
void fun(string s,vector<vector<string>> &ans,vector<string> &res,int index){
    if(index==s.size()){
        ans.push_back(res);
        return ;
    }
    for(int i=index;i<s.size();i++){
        string k=s.substr(index,i-index+1);
        if(palindrome(k)){
            res.push_back(k);
            fun(s,ans,res,i+1);
            res.pop_back();
        }
    }

}
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;
        vector<string> res;
        fun(s,ans,res,0);
        return ans;
    }
};