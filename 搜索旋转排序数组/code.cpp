class Solution {
public:
    int search(vector<int>& nums, int target) {
         int n = nums.size();
        int left = 0; int right = n-1;
        while(left<=right)
        {
            int mid = left + (right - left) /2;
            

            if(nums[mid] == target)
            {
                return mid;
            }

            //左半部分有序
            if(nums[0] <= nums[mid]){
                
                //target在左半部分
                if(nums[0]<=target && target<=nums[mid])
                {
                    right = mid - 1;
                }else{
                    left = mid + 1;
                }

            //右半部分有序
            }else{

                if(nums[mid]<= target && target<=nums[n-1])
                {
                    left = mid + 1;
                }else
                {
                    right = mid - 1;
                }

            }
        }

        return -1;
    }
};