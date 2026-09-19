class Solution {
public:
   void dfs(vector<vector<char>> &board,vector<vector<bool>> &visited,int i,int j){
    visited[i][j]=true;
    int rows[]={0,0,-1,1};
    int cols[]={-1,1,0,0};
    for(int k=0;k<4;k++){
        int row=rows[k]+i;
        int col=cols[k]+j;
        if(row>=0&&col>=0&&row<board.size()&&col<board[0].size()&&!visited[row][col]&&board[row][col]=='O'){
            dfs(board,visited,row,col);
        }
    }
   }
    void solve(vector<vector<char>>& board) {
        
        vector<vector<bool>> visited(board.size(),vector<bool>(board[0].size(),false));

        for(int i=0;i<board.size();i++){
            for(int j=0;j<1;j++){
                if(board[i][j]=='O'){
                    dfs(board,visited,i,j);
                }
            }
        }

        for(int i=0;i<board.size();i++){
            for(int j=board[0].size()-1;j<board[0].size();j++){
                if(board[i][j]=='O'){
                    dfs(board,visited,i,j);
                }
            }
        }

         for(int i=0;i<1;i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]=='O'){
                    dfs(board,visited,i,j);
                }
            }
        }
          for(int i=board.size()-1;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]=='O'){
                    dfs(board,visited,i,j);
                }
            }
        }

        for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(visited[i][j]){
                    board[i][j]='O';
                }
                else{
                    board[i][j]='X';
                }
            }
        }
        

    }
};