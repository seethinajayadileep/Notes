class Solution {
public:
bool dfs(vector<vector<int>> &grid,int row,int col){
    if(row<0 ||col<0||row>=grid.size()||col>=grid[0].size()){
        return false;
    }
    if(grid[row][col]==1){
        return true;
    }
    grid[row][col]=1;

    bool top=dfs(grid,row-1,col);
    bool down=dfs(grid,row+1,col);
    bool left=dfs(grid,row,col-1);
    bool right=dfs(grid,row,col+1);
    return top&&down&&left&&right;
}
    int closedIsland(vector<vector<int>>& grid) {
        int ans=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==0){
                    if(dfs(grid,i,j)){
                        ans++;
                    }
                
                }
            }
        }
        return ans;
    }
};