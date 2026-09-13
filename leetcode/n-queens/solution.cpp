class Solution {
public:
   bool safe(int i,int j,vector<string> &board){

       int k1=i,k2=j;
       //left diagonal
       while(k1>=0 &&k2>=0){
        if(board[k1][k2]=='Q'){
            return false;
        }
        k1--;
        k2--;

       }
       k1=i,k2=j;
       //right diagonal
       while(k1>=0&& k2<=board.size()-1){

         if(board[k1][k2]=='Q'){
            return false;
        }
        k1--;
        k2++;
       }
       k1=i ,k2=j;
       while(k1>=0){
        if(board[k1][k2]=='Q'){
            return false;
        }
        k1--;
       }
return true;

   }
    void fun(int n,vector<vector<string>> &ans,vector<string> &res,int i,vector<string> &board){
        if(i==n){
            ans.push_back(res);
            return ;
        }
      for(int j=0;j<n;j++){
        if(safe(i,j,board)){
            board[i][j]='Q';
            res.push_back(board[i]);
            fun(n,ans,res,i+1,board);
            res.pop_back();
            board[i][j]='.';
        }
      }


    }
    vector<vector<string>> solveNQueens(int n) {
        
        vector<vector<string>>  ans;
        vector<string> board(n,string(n,'.'));
        vector<string> res;
        fun(n,ans,res,0,board);
        return ans;
    }
};