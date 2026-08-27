class Solution {
public:
void dfs(vector<vector<bool>> &visited,vector<vector<char>> &board,int row,int col){
    visited[row][col]=true;
    int rows[]={0,0,-1,1};
    int cols[]={-1,1,0,0};
    for(int i=0;i<4;i++){
        int newrow=rows[i]+row;
        int newcol=cols[i]+col;
        if(newrow>=0&&newcol>=0&&newrow<board.size()&&newcol<board[0].size()&&board[newrow][newcol]=='O'&&!visited[newrow][newcol]){
            dfs(visited,board,newrow,newcol);
        }
    }
}
    void solve(vector<vector<char>>& board) {
        int n=board.size();
        int m=board[0].size();
        vector<vector<bool>> visited(n,vector<bool>(m,false));
        for(int i=0;i<n;i++){
            for(int j=0;j<1;j++){
                if(!visited[i][j]&&board[i][j]=='O'){
                dfs(visited,board,i,j);
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=m-1;j<m;j++){
                if(!visited[i][j]&&board[i][j]=='O'){
                dfs(visited,board,i,j);
                }
            }
        }
        for(int i=0;i<1;i++){
            for(int j=0;j<m;j++){
                 if(!visited[i][j]&&board[i][j]=='O'){
                dfs(visited,board,i,j);
                }
            }
        }
         for(int i=n-1;i<n;i++){
            for(int j=0;j<m;j++){
                 if(!visited[i][j]&&board[i][j]=='O'){
                dfs(visited,board,i,j);
                }
            }
        }
        for(int i=0;i<visited.size();i++){
            for(int j=0;j<visited[0].size();j++){
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