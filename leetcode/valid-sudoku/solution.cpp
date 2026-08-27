class Solution {
public:
bool isrule(vector<vector<char>> &board,char digit,int i,int j){
    for(int k=0;k<9;k++){
        if(board[i][k]==digit|| board[k][j]==digit){
            return false;
        }
    }
    int row=(i/3)*3;
    int col=(j/3)*3;
    for(int starti=row;starti<row+3;starti++){
        for(int startj=col;startj<col+3;startj++){
        if(board[starti][startj]==digit){
            return false;
        }
        }

    }
    return true;
}
bool slove(vector<vector<char>> &board){
 for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
        if(board[i][j]!='.'){
       char digit= board[i][j];
       board[i][j]='.';
        if(!isrule(board,digit,i,j)){
            return false;
        }
        board[i][j]=digit;
    }
    }
 }
 return true;
}
    bool isValidSudoku(vector<vector<char>>& board) {
        return slove(board);
    }
};