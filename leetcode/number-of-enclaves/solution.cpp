class Solution {
public:
void dfs(vector<vector<bool>> &visited,bool &boundary,int &count,vector<vector<int>> &grid,int row,int col){
visited[row][col]=true;
int rows[]={0,0,-1,1};
int cols[]={-1,1,0,0};
if(row==0||col==0||row==grid.size()-1||col==grid[0].size()-1){
    boundary=true;
}
for(int i=0;i<4;i++){
    int newrow=rows[i]+row;
    int newcol=cols[i]+col;
    if(newrow>=0&&newcol>=0&&newrow<grid.size()&&newcol<grid[0].size()&&grid[newrow][newcol]==1&&!visited[newrow][newcol]){
        count=count+1;
       dfs(visited,boundary,count,grid,newrow,newcol);
    }
}
}
    int numEnclaves(vector<vector<int>>& grid) {
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        int cnt=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(!visited[i][j]&&grid[i][j]==1){
                    bool boundary=false;
                    int count=1;
                    dfs(visited,boundary,count,grid,i,j);
                    if(!boundary){
                        cnt+=count;
                    }

                }
            }
        }
        return cnt;
    }
};