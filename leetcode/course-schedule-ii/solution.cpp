class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        for(int i=0;i<prerequisites.size();i++){
            int u=prerequisites[i][0];
            int v=prerequisites[i][1];
            adj[v].push_back(u);

        }
         vector<int> indegree(numCourses,0);
         for(int i=0;i<numCourses;i++){
            for(auto node:adj[i]){
                indegree[node]++;
            }
         }
         queue<int> q;

         for(int i=0;i<numCourses;i++){
            if(indegree[i]==0){
                q.push(i);
            }
         }
         vector<int> topo;
         while(!q.empty()){
            int front=q.front();
            topo.push_back(front);
            q.pop();
            for(auto node:adj[front]){
                indegree[node]--;
                if(indegree[node]==0){
                    q.push(node);
                }
                
            }
         }
         if(topo.size()<numCourses){
            return {};
         }
         return topo;
        
    }
};