class Solution {
public:
void dfs(vector<vector<bool>> &visited,vector<vector<char>> &grid,int row1,int col1){
    int rows[]={0,0,-1,1};
    int cols[]={-1,1,0,0};
    visited[row1][col1]=true;
    for(int i=0;i<4;i++){
       
            int newrow=row1+rows[i];
            int newcol=col1+cols[i];
            if(newrow>=0&& newcol>=0&& newrow<grid.size()&&newcol<grid[0].size()&& !visited[newrow][newcol]&&grid[newrow][newcol]=='1'){
                dfs(visited,grid,newrow,newcol);
            }
        
    }
}
    int numIslands(vector<vector<char>>& grid) {
        int count=0;
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(!visited[i][j]&&grid[i][j]=='1'){
                    dfs(visited,grid,i,j);
                    count++;
                }
            }
        }
        return count;
    }
};