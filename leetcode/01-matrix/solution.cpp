class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        vector<vector<int>> visited(mat.size(),vector<int>(mat[0].size(),0));
        queue<pair<pair<int,int>,int>> q;
        for(int i=0;i<mat.size();i++){
            for(int j=0;j<mat[0].size();j++){
                if(mat[i][j]==0){
                    q.push({{i,j},0});
                    visited[i][j]=1;

                }
            }
        }
        int rows[]={0,0,-1,1};
        int cols[]={1,-1,0,0};
        vector<vector<int>> dist(mat.size(),vector<int>(mat[0].size(),0));
        while(!q.empty()){

         auto ele=q.front();
         q.pop();
         int first=ele.first.first;
         int second=ele.first.second;
         int step=ele.second;
         dist[first][second]=step;
         for(int i=0;i<4;i++){
            int newrow=rows[i]+first;
            int newcol=cols[i]+second;

            if(newrow>=0&&newcol>=0&&newrow<mat.size()&&newcol<mat[0].size()&&visited[newrow][newcol]==0&&mat[newrow][newcol]==1){
                q.push({{newrow,newcol},step+1});
                visited[newrow][newcol]=1;

            }
         }
         
        }
        return dist;
    }
};