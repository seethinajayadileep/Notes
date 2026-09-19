class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<pair<int,int>,int>> q;
        vector<vector<int>> visited(grid.size(),vector<int>(grid[0].size(),0));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==2){
                    q.push({{i,j},0});
                    visited[i][j]=2;
                }
            }
        }
        int rows[]={0,0,-1,1};
        int cols[]={-1,1,0,0};
        int maxtime=0;
        while(!q.empty()){
            auto ele=q.front();
            int first=ele.first.first;
            int second=ele.first.second;
            int time=ele.second;
            maxtime=max(time,maxtime);
            q.pop();
            for(int i=0;i<4;i++){
                int newrow=rows[i]+first;
                int newcol=cols[i]+second;
                if(newrow<0||newcol<0|| newrow>=grid.size()|| newcol>=grid[0].size()||visited[newrow][newcol]==2||grid[newrow][newcol]==0){
                   continue;

                }
                 q.push({{newrow,newcol},time+1});
                 visited[newrow][newcol]=2;

            }
          

        }
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
                if(grid[i][j]==1&&visited[i][j]!=2){
                    return -1;
                }
            }
        }
        return maxtime;
    }
};