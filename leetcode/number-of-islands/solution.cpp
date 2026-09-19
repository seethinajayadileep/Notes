class Solution {
public:
    void fun(vector<vector<char>> &grid,int i,int j,vector<vector<bool>> &visited){
        visited[i][j]=1;
        int rows[]={0,0,-1,1};
        int cols[]={-1,1,0,0};
        for(int k=0;k<4;k++){
            int newrow=rows[k]+i;
            int newcol=cols[k]+j;
            if(newrow>=0&&newrow<grid.size()&&newcol>=0&&newcol<grid[0].size()&&!visited[newrow][newcol]&&grid[newrow][newcol]=='1'){
                fun(grid,newrow,newcol,visited);
            }
        }
    }
    int numIslands(vector<vector<char>>& grid) {
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        int count=0;
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                   if(!visited[i][j]&& grid[i][j]=='1'){
                    fun(grid,i,j,visited);
                    count++;
                   }
            }
        }
        return count;
    }
};