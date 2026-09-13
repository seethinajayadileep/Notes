class Solution {
public:
   void fun(string &digits,int index,vector<string> &ans,string  res,string arr[]){
    if(index==digits.size()){
        ans.push_back(res);
        return ;
    }
    for(int i=0;i<arr[digits[index]-'0'].size();i++){
        fun(digits,index+1,ans,res+arr[digits[index]-'0'][i],arr);
    }
   }

    vector<string> letterCombinations(string digits) {
        if(digits.size()==0){
            return {};
        }
        string arr[]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> ans;
        fun(digits,0,ans,"",arr);
        return ans;



    }
};