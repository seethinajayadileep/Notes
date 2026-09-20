class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses,0);
        vector<int> adj[numCourses];
        for(int i=0;i<prerequisites.size();i++){
            int u=prerequisites[i][0];
            int v=prerequisites[i][1];
            adj[v].push_back(u);

        }
        for(int i=0;i<numCourses;i++){
            for(auto ele:adj[i]){
                indegree[ele]++;
            }
        }
        queue<int> q;
        for(int i=0;i<indegree.size();i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            int node=q.front();
            q.pop();
            for(auto ele:adj[node]){
               indegree[ele]--;
            if(indegree[ele]==0){
                q.push(ele);
            }
            }
            
        }
        for(int i=0;i<indegree.size();i++){
            if(indegree[i]!=0){
                return false;
            }
        }
        return true;
    }
};