class Solution {
public:
  void dfs(vector<vector<int>> &adj,int i ,vector<int> &visited){
           visited[i]=1;
           for(auto ele:adj[i]){
            if(!visited[ele])
               dfs(adj,ele,visited);
           }
  }
    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<vector<int>> adj(isConnected.size());
        vector<int> visited(isConnected.size(),0);
        for(int i=0;i<isConnected.size();i++){
            for(int j=0;j<isConnected[i].size();j++){
                if(isConnected[i][j]==1){
                    adj[i].push_back(j);

                }
            }
        }
        int count=0;

        for(int i=0;i<visited.size();i++){

            if(!visited[i]){
                count++;
                dfs(adj,i,visited);
            }
        }
        return count;
    }
};