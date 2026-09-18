class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int freq[26]={0};

         for(int i=0;i<tasks.size();i++){
            freq[tasks[i]-'A']++;
         }
         int maxfreq=0;
         for(int i=0;i<26;i++){
            maxfreq=max(maxfreq,freq[i]);
         }
         int maxcount=0;
        
         for(int i=0;i<26;i++){
            if(freq[i]==maxfreq){
                maxcount++;
            }
            
         }
         int k=(maxfreq-1)*(n+1)+maxcount;
         int size=tasks.size();
       int m= max(size,k);
       return m;


    }
};