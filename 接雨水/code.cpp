#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;
/*
每个位置能接住的雨水量，
取决于它「左右两侧的最大高度中的较小值」与「自身高度」的差值。
双指针可以减少遍历次数，不用对于每一个索引处都往两边找最大
对于left的一个位置，左侧的leftmax是确定的，右侧的最大值至少不会比rightmax小。
所以当leftmax < rightmax的时候
可以计算left位置能接的雨水数量后，再left++，
因为此时leftmax是准确的，并且left++后rightmax仍然有效

同样的，如果leftmax > rightmax
就计算right位置的雨水量

等于的时候算左算右都可以

因为不关心每一处的雨水量，ans用+=
*/
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0,right = height.size()-1;
        int leftmax = 0, rightmax = 0;

        while(left < right)
        {
            leftmax = max(leftmax , height[left]);
            rightmax = max(rightmax, height[right]);

            if(leftmax < rightmax)
            {
                ans += leftmax - height[left];
                left++;
            }
            else{
                ans += rightmax - height[right];
                right--;    
            }

            // ans = min(leftmax , rightmax) 
        }
        return ans;
    }
};


int main()
{



    return 0;
}