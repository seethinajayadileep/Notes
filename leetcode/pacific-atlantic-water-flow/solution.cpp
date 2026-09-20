class Solution {
public:
void dfs(vector<vector<int>> &heights,int i,int j,vector<vector<bool>> &visited){
    visited[i][j]=true;
    int rows[]={0,0,-1,1};
    int cols[]={-1,1,0,0};
    for(int k=0;k<4;k++){
        int newrow=rows[k]+i;
        int newcol=cols[k]+j;
        if(newrow<0||newcol<0||newrow>=heights.size()||newcol>=heights[0].size()){
            continue;
        }
        if(visited[newrow][newcol]){
           continue;
        }
        if(heights[newrow][newcol]<heights[i][j]){
            continue;
        }
        dfs(heights,newrow,newcol,visited);
    }
}
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<bool>> pacific(heights.size(),vector<bool>(heights[0].size(),false));
        vector<vector<bool>> altantic(heights.size(),vector<bool>(heights[0].size(),false));
        for(int i=0;i<heights.size();i++){
             dfs(heights,i,0,pacific);
        }
        for(int i=0;i<heights[0].size();i++){
            dfs(heights,0,i,pacific);
        }
        int n=heights.size();
        int m=heights[0].size();
        for(int j=0;j<m;j++){
            dfs(heights,n-1,j,altantic);
        }
        for(int j=0;j<n;j++){
            dfs(heights,j,m-1,altantic);
        }
        vector<vector<int>> sol;
        for(int i=0;i<heights.size();i++){
            for(int j=0;j<heights[0].size();j++){
                if(pacific[i][j]&&altantic[i][j]){
                    sol.push_back({i,j});
                }
            }
        }
        return sol;
    }
};