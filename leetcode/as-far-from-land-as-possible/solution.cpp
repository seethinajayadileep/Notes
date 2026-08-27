class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        queue<pair<pair<int,int>,int>> q;
        vector<vector<bool>> visited(grid.size(),vector<bool>(grid[0].size(),false));
        for(int i=0;i<grid.size();i++){
            for(int j=0;j<grid[0].size();j++){
               if(grid[i][j]==1){
                q.push({{i,j},0});
                visited[i][j]=true;
               }
            }

        }
    int maxdis=0;
        while(!q.empty()){
            auto ele=q.front();
            q.pop();
            int row=ele.first.first;
            int col=ele.first.second;
            int dist=ele.second;
            int rows[]={0,0,1,-1};
            int cols[]={1,-1,0,0};
            maxdis=max(maxdis,dist);
            for(int i=0;i<4;i++){
                int newr=rows[i]+row;
                int newc=cols[i]+col;
                if(newr<0||newc<0||newr>=grid.size()||newc>=grid[0].size()|| visited[newr][newc]){
                    continue;

                }
                visited[newr][newc]=true;
                q.push({{newr,newc},dist+1});

            }
        }
        return maxdis==0?-1:maxdis;
    }
};