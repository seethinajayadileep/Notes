class Solution {
public:
   void dfs(vector<vector<int>> &image,int i,int j,int color,int oldcolor,vector<vector<bool>> &visited){
    visited[i][j]=true;
    image[i][j]=color;
    int newrow[]={-1,1,0,0};
    int newcol[]={0,0,-1,1};
    for(int k=0;k<4;k++){
        int rows=i+newrow[k];
        int cols=j+newcol[k];
        if(rows>=0&&rows<image.size()&&cols>=0&&cols<image[0].size()&&!visited[rows][cols]&&image[rows][cols]==oldcolor){
            dfs(image,rows,cols,color,oldcolor,visited);
        }
    }
   }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int oldcolor=image[sr][sc];
        vector<vector<bool>> visited(image.size(),vector<bool>(image[0].size(),false));
        if(oldcolor!=color){
            dfs(image,sr,sc,color,oldcolor,visited);
        }
        return image;

    }
};