#include <vector>
using namespace std;

/**
 * 在排序数组中查找元素的第一个和最后一个位置
 * 使用两次二分查找：第一次找左边界，第二次找右边界
 */
class Solution
{
public:
    /**
     * 查找目标值在排序数组中的起始和结束位置
     * @param nums 已排序的整数数组
     * @param target 要查找的目标值
     * @return 包含目标值起始和结束位置的数组，如果未找到则返回[-1, -1]
     */
    vector<int> searchRange(vector<int> &nums, int target)
    {
        int n = nums.size();
        // 处理空数组情况
        if (!n)
            return {-1, -1};
            
        int left = 0, right = n - 1;
        int mid;
        int first_target = -1, second_target = -1;
        
        // 第一次二分查找：寻找目标值的左边界（第一个出现的位置）
        while (left <= right)
        {
            // 计算中间位置，避免整数溢出
            mid = left + (right - left) / 2;
            
            if (nums[mid] == target)
            {
                // 找到目标值，记录当前位置，并继续向左搜索更早的出现位置
                first_target = mid;
                right = mid - 1;  // 向左收缩搜索范围
            }
            else if (nums[mid] > target)
            {
                // 中间值大于目标值，目标值在左半部分
                right = mid - 1;
            }
            else
            {
                // 中间值小于目标值，目标值在右半部分
                left = mid + 1;
            }
        }

        // 如果第一次查找未找到目标值，直接返回[-1, -1]
        if (first_target == -1)
            return {-1, -1};
            
        // 第二次二分查找：寻找目标值的右边界（最后一个出现的位置）
        // 从第一次找到的位置开始向右搜索
        left = first_target;
        right = n - 1;
        
        while (left <= right)
        {
            mid = left + (right - left) / 2;
            
            if (nums[mid] == target)
            {
                // 找到目标值，记录当前位置，并继续向右搜索更晚的出现位置
                second_target = mid;
                left = mid + 1;  // 向右收缩搜索范围
            }
            else if (nums[mid] > target)
            {
                // 中间值大于目标值，目标值在左半部分
                right = mid - 1;
            }
            else
            {
                // 中间值小于目标值，目标值在右半部分
                left = mid + 1;
            }
        }

        // 返回目标值的起始和结束位置
        return {first_target, second_target};
    }
};