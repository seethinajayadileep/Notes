class Solution {
public: 
   int dfs(vector<vector<bool>> &visited,vector<vector<int>> &grid,int row,int col){
    if(col<0||row<0||col>=grid[0].size()||row>=grid.size() ||grid[row][col]==0||visited[row][col]){
        return 0;
    }
   
    int count=1;
    visited[row][col]=true;
    count+=dfs(visited,grid,row-1,col);
    count+=dfs(visited,grid,row+1,col);
    count+=dfs(visited,grid,row,col+1);
    count+=dfs(visited,grid,row,col-1);
    return count;
   

   }
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxcount=0;
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[i].size();j++){
             if(!visited[i][j]&&grid[i][j]==1){
              int   count=dfs(visited,grid,i,j);
                 maxcount=max(count,maxcount);

             }
            }
         }
         return maxcount;
    }



};