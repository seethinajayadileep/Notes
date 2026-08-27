class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        queue<pair<pair<int,int>,int>> q;
        if (grid[0][0] == 1 || grid[grid.size() - 1][grid[0].size() - 1] == 1) return -1;
        q.push({{0,0},1});
        vector<vector<int>> dist(grid.size(),vector<int>(grid[0].size(),INT_MAX));
        dist[0][0]=1;
        while(!q.empty()){
            auto ele=q.front();
            int row=ele.first.first;
            int col=ele.first.second;
            int distance=ele.second;
          q.pop();
            for(int i=-1;i<=1;i++){
                for(int j=-1;j<=1;j++){
                    int newr=row+i;
                    int newc=col+j;
                    if(newr<0||newc<0||newr>=grid.size()||newc>=grid[0].size()||grid[newr][newc]==1){
                        continue;
                    }
                    if(distance+1<dist[newr][newc]){
                        dist[newr][newc]=distance+1;
                        q.push({{newr,newc},distance+1});
                    }

                }
            }

        }
        return dist[grid.size()-1][grid[0].size()-1]==INT_MAX?-1:dist[grid.size()-1][grid[0].size()-1];
    }
};