class Solution {
public:
    int maxArea(vector<int>& height) {
        int l=0;
        int r=height.size()-1;
        int maxarea=0;
        while(l<r){
            int mini=min(height[l],height[r]);
            int area=mini*(r-l);
            maxarea=max(maxarea,area);
            if(height[l]<height[r]){
                l++;
            }
            else if(height[l]>height[r]){
                r--;
            }
            else{
                l++;
                r--;
            }
        }
        return maxarea;

    }
};