
/*
    桶排序法
 * 时间复杂度：O(n + m)，其中n是数组长度，m是数据范围
 * 空间复杂度：O(m)，m是数据范围，用于存储桶数组
 * 
 * 优点：
 * - 当数据范围较小时，效率很高
 * - 避免了元素之间的比较操作
 * 
 * 缺点：
 * - 当数据范围很大时，空间复杂度会变得很高
 * - 只适用于整数等可以明确映射到有限范围的元素
 */
class Solution {
public:
    /**
     * 使用桶排序法查找数组中的第K个最大元素
     * 
     * @param nums 输入数组
     * @param k 要查找的是第k大的元素
     * @return 返回第k大的元素值
     */
    int findKthLargest(vector<int>& nums, int k) {
        // 步骤1：确定数组元素的范围（min和max）
        // 使用STL算法找到数组中的最小值和最大值
        int min_val = *min_element(nums.begin(), nums.end());
        int max_val = *max_element(nums.begin(), nums.end());
        int range = max_val - min_val + 1;  // 桶的数量等于数据范围大小
        
        // 步骤2：创建桶并统计每个元素的频率
        // 每个桶初始化为0，表示对应数值出现的次数为0
        vector<int> bucket(range, 0);
        // 遍历原数组，将每个元素出现的次数统计到对应的桶中
        for (int num : nums) {
            // 通过减去最小值，将元素映射到桶数组的索引位置
            // 这确保了最小元素对应的索引为0，避免负数索引问题
            bucket[num - min_val]++;
        }
        
        // 步骤3：从最大的元素开始累加频率，找到第K个最大元素
        // count变量用于累计已经遍历过的元素数量
        int count = 0;
        // 从最大元素对应的桶开始反向遍历（从右到左）
        for (int i = range - 1; i >= 0; i--) {
            // 累加当前桶中元素的数量
            count += bucket[i];
            // 当累加数量达到或超过k时，说明找到了第k大的元素
            if (count >= k) {
                // 通过反向映射计算实际的元素值：最小值 + 当前桶索引
                return min_val + i;
            }
        }
        
        // 理论上不会走到这里（题目保证k是有效的）
        // 仅作为防御性编程的返回值
        return -1;
    }
};