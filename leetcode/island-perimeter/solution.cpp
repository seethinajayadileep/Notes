class Solution {
public:
   void dfs(vector<vector<bool>> &visited,vector<vector<int>> &grid,int &perimeter,int row,int col){
    visited[row][col]=true;
    int rows[]={0,0,-1,1};
    int cols[]={-1,1,0,0};
    for(int i=0;i<4;i++){
        int newrow=rows[i]+row;
        int newcol=cols[i]+col;
        if(newrow>=0&&newcol>=0&&newrow<grid.size()&&newcol<grid[0].size()&&!visited[newrow][newcol]&&grid[newrow][newcol]==1){
            dfs(visited,grid,perimeter,newrow,newcol);
        }
        else if(newrow < 0 || newcol < 0 || newrow >= grid.size() || newcol >= grid[0].size() || grid[newrow][newcol] == 0){
            perimeter+=1;
        }
    }
   }
    int islandPerimeter(vector<vector<int>>& grid) {
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(!visited[i][j]&&grid[i][j]==1){
                  int perimeter=0;  
                 dfs(visited,grid,perimeter,i, j);
                 return perimeter;
                }
            }
        }
        return 0;
    }
};