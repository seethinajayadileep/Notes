class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
      priority_queue<
    pair<int, pair<int, int>>,
    vector<pair<int, pair<int, int>>>,
    greater<pair<int, pair<int, int>>>
> pq;
        for(int i=0;i<points.size();i++){
            int x=points[i][0];
            int y=points[i][1];
            int z=(x*x)+(y*y);
            pq.push({z,{x,y}});

        }
        int i=0;
        vector<vector<int>> ans;
        while(k>0){
            auto p=pq.top();
            pq.pop();
            ans.push_back({p.second.first,p.second.second});
            k--;
            i++;
        }
        return ans;
    }
};