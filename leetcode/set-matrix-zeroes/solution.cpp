class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        map<int,bool> r;
        map<int,bool> c;
    
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix[i].size();j++){
                if(matrix[i][j]==0){
                  r[i]=true;
                  c[j]=true;
                }
            }
        }
        for(int i=0;i<matrix.size();i++){
            for(int j=0;j<matrix[i].size();j++){
                if(r[i]){
                    matrix[i][j]=0;
                }
                else if(c[j]){
                    matrix[i][j]=0;
                    
                }
            }
        }
    }
};