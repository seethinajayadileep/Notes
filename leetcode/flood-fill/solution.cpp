class Solution {
public:
   void dfs(vector<vector<bool>> &visited,vector<vector<int>> &image,int sr,int sc,int color,int oldcolor){
    visited[sr][sc]=true;
    image[sr][sc]=color;
    int row[]={0,0,-1,1};
    int col[]={-1,1,0,0};
    for(int i=0;i<4;i++){
       int newrow=row[i]+sr;
       int newcol=col[i]+sc;
       if(newrow>=0&&newcol>=0&&newrow<image.size()&&newcol<image[0].size()&&!visited[newrow][newcol]&&image[newrow][newcol]==oldcolor){
        dfs(visited,image,newrow,newcol,color,oldcolor);
       }
    }

   }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        vector<vector<bool>> visited(image.size(),vector<bool>(image[0].size(),false));
     
               int oldcolor=image[sr][sc];
               if(oldcolor!=color)
                dfs(visited,image,sr,sc,color,oldcolor);
          return image;
    }
};