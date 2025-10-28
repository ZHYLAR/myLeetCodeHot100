class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        int ans = INT_MAX;
        while(left <= right)
        {
            int mid = left + (right - left) / 2;
            
            //左半部分有序
            if(nums[0] <= nums[mid])
            {
                ans = min(ans, nums[0]); //该有序区的最小值
                left = mid + 1;
            }
            //右半部分有序
            else
            {
                ans = min(ans, nums[mid]); //该有序区的最小值
                right = mid - 1;
            }
        }
        return ans;
    }
};