class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string,int>> q;
        unordered_set<string> t(wordList.begin(),wordList.end());
        q.push({beginWord,1});
        while(!q.empty()){
            pair<string,int> p=q.front();

            string s=p.first;
            int steps=p.second;
            q.pop();
            if(s==endWord){
                return steps;
            }
            t.erase(s);
            for(int i=0;i<s.size();i++){
                char orginal=s[i];
                for(int j='a';j<='z';j++){
                    s[i]=j;
                    if(t.find(s)!=t.end()){
                        q.push({s,steps+1});
                    }
                }
                s[i]=orginal;
            }
        }
        return 0;
    }
};