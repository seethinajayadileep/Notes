class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<pair<int,int>,int>> q;
        vector<vector<int>> visited(grid.size(),vector<int>(grid[0].size(),false));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==2){
                    q.push({{i,j},0});
                    visited[i][j]=2;
                }
            }
        }
        int maxtime=0;
        while(!q.empty()){
            auto ele=q.front();
            int row=ele.first.first;
            int col=ele.first.second;
            int time=ele.second;
            maxtime=max(time,maxtime);
            q.pop();
            int rows[]={0,0,1,-1};
            int cols[]={-1,1,0,0};
            for(int i=0;i<4;i++){
                int newr=rows[i]+row;
                int newc=cols[i]+col;
                if(newr<0||newc<0||newr>=grid.size()||newc>=grid[0].size()||visited[newr][newc]==2||grid[newr][newc]==0){
                    continue;
                }
                q.push({{newr,newc},time+1});
                visited[newr][newc]=2;
                grid[newr][newc]=2;


            }
        }
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1){
                    return -1;
                }
            }
        }
        return maxtime;
    }
};