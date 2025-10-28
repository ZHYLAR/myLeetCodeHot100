//1 快速选择法
// 数组中的第K个最大元素
// 使用快速选择算法（快速排序的变体）实现
// 时间复杂度：平均O(n)，最坏O(n²)
// 空间复杂度：O(log n)，递归调用栈的深度

#include <vector>
#include <algorithm>

class Solution {
public:
    /**
     * 快速选择算法的递归实现
     * @param nums 待操作的数组
     * @param l 搜索范围的左边界（包含）
     * @param h 搜索范围的右边界（包含）
     * @param k 要查找的是第k小的元素
     * @return 返回第k小的元素值
     */
    int quick_search(vector<int>& nums, int l, int h, int k) {
        // 基本情况：搜索范围只有一个元素时，直接返回
        if (l == h) return nums[l];
        
        // 初始化双指针和基准值
        // i初始化为左边界左侧，j初始化为右边界右侧，这样可以在循环中先移动指针再比较
        // m为基准值，选择中间位置的元素，避免在有序数组上的最坏情况
        int i = l - 1, j = h + 1, m = nums[l + (h - l)/2];
        
        // 快速排序的分区过程
        // 交换后nums 从左到右递增
        while (i < j) {
            // 从左向右找到第一个大于等于基准值的元素
            while(nums[++i] < m);

            // 从右向左找到第一个小于等于基准值的元素
            while(nums[--j] > m);
            // 如果i还在j的左侧，交换这两个元素
            if (i < j) swap(nums[i], nums[j]);
        }
        
        // 分区完成后，数组被分为两部分：[l...j]和[j+1...h]
        // 计算左半部分的元素个数
        int lcnt = j - l + 1;
        
        // 递归搜索
        if (lcnt >= k) {
            // 如果第k小的元素在左半部分，递归搜索左半部分
            return quick_search(nums, l, j, k);
        } else {
            // 否则，递归搜索右半部分，注意k要减去左半部分的元素个数
            return quick_search(nums, j+1, h, k - lcnt);
        }
    }

    /**
     * 查找数组中的第K个最大元素
     * @param nums 输入数组
     * @param k 要查找的是第k大的元素
     * @return 返回第k大的元素值
     */
    int findKthLargest(vector<int>& nums, int k) {
        const int n = nums.size();
        // 将问题转换为查找第(n-k+1)小的元素
        // 例如：第1大 = 第n小，第2大 = 第n-1小，以此类推
        return quick_search(nums, 0, n - 1, n - k + 1);
    }
};

