class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        queue<pair<pair<int,int>,int>> q;
        int mini=INT_MAX;
        q.push({{entrance[0],entrance[1]},0});
        vector<vector<int>> dist(maze.size(),vector<int>(maze[0].size(),INT_MAX));
        while(!q.empty()){
        auto ele=q.front();
        q.pop();
        int row=ele.first.first;
        int col=ele.first.second;
        int distance=ele.second;
        int rows[]={0,0,-1,1};
        int cols[]={-1,1,0,0};
        bool isEntrance = (row == entrance[0] && col == entrance[1]);
        if((row==0||col==0||row==maze.size()-1||col==maze[0].size()-1)&&!isEntrance){
             mini=min(mini,distance);
        }
        for(int i=0;i<4;i++){
            int newr=rows[i]+row;
            int newc=cols[i]+col;
            if(newr<0||newc<0||newr>=maze.size()||newc>=maze[0].size()||maze[newr][newc]=='+'){
                continue;
            }
            if(distance+1<dist[newr][newc]){
                q.push({{newr,newc},distance+1});
                dist[newr][newc]=distance+1;
            }

        }

        }
        return mini==INT_MAX?-1:mini;
        

    }
};