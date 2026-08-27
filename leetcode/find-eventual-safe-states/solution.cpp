class Solution {
public:
  bool dfs(int node,vector<vector<int>> &graph,vector<bool> &visited,vector<bool> &pathvisited,vector<bool> &check){
    visited[node]=true;
    pathvisited[node]=true;
    for(auto neigh:graph[node]){
        if(!visited[neigh]){
            if(dfs(neigh,graph,visited,pathvisited,check)){
                return true;
            }
        }
        else if(pathvisited[neigh]){
         return true;
        }
    }
    pathvisited[node]=false;
    check[node]=true;
    return false;
  }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<bool> visited(n,false);
        vector<bool> pathvisited(n,false);
        vector<bool> check(n,false);
        for(int i=0;i<graph.size();i++){
          dfs(i,graph,visited,pathvisited,check);
        }
        vector<int> ans;
        for(int i=0;i<n;i++){
            if(check[i]){
                ans.push_back(i);
            }
        }
        return ans;
    }
};