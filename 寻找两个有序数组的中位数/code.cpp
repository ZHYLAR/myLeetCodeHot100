#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;

/* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
 * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
 * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
 * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
 * 这样 pivot 本身最大也只能是第 k-1 小的元素
 * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
 * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
 * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
 */

class Solution
{
public:
    // 在两个非降序（升序）数组中查找第 k 小元素（k≥1，k 从 1 开始）。
    // 示例：nums1=[1,3,5], nums2=[2,4,6]，第 4 小元素为 4。
    int getKthElement(const vector<int> &nums1, const vector<int> &nums2, int k)
    {
        int m = nums1.size(); // 示例中m=3（nums1有3个元素）
        int n = nums2.size(); // 示例中n=3（nums2有3个元素）
        // index1：当前考虑的nums1子数组的起始索引（初始从0开始）
        // index2：当前考虑的nums2子数组的起始索引（初始从0开始）
        int index1 = 0, index2 = 0;

        while (true)
        {
            // 边界情况1：nums1已无剩余元素（所有元素都被排除）
            // 则第k小元素一定在nums2中，位置为index2 + k - 1
            if (index1 == m)
            {
                return nums2[index2 + k - 1];
            }

            // 边界情况2：nums2已无剩余元素，同理返回nums1中对应位置
            if (index2 == n)
            {
                return nums1[index1 + k - 1];
            }

            // 边界情况3：k=1时，取当前剩余元素的最小值
            if (k == 1)
            {
                return min(nums1[index1], nums2[index2]);
            }

            // 正常情况：计算当前需要比较的枢轴（pivot）位置
            // 示例初始状态：index1=0, index2=0, k=4
            // 说明：k/2 使用整数除法。newIndex1 表示从 index1 开始的第 k/2 个元素的索引（0 基），即 index1 + k/2 - 1；超过数组边界则取 m-1。
            // 同理 newIndex2 = min(index2 + k/2 - 1, n - 1)。示例首次：newIndex1=1（nums1[1]=3），newIndex2=1（nums2[1]=4）。
            // 若超过数组长度则取最后一个索引（避免越界）
            int newIndex1 = min(index1 + k / 2 - 1, m - 1); // 示例首次计算：min(0+2-1,2)=1（nums1[1]=3）
            int newIndex2 = min(index2 + k / 2 - 1, n - 1); // 示例首次计算：min(0+2-1,2)=1（nums2[1]=4）

            // 取两个枢轴元素的值
            int pivot1 = nums1[newIndex1]; // 示例首次：nums1[1]=3
            int pivot2 = nums2[newIndex2]; // 示例首次：nums2[1]=4

            // 比较枢轴，排除不可能是第k小的元素
            if (pivot1 <= pivot2)
            { // 示例首次：3 <= 4，满足条件
                // 排除nums1中从index1到newIndex1的元素（共newIndex1 - index1 + 1个）
                // 示例中：排除nums1[0..1]（元素1、3），共2个元素
                k -= newIndex1 - index1 + 1; // 这里减去被排除的元素个数（区间长度 = newIndex1 - index1 + 1）。示例：k=4-2=2。
                index1 = newIndex1 + 1;      // 示例：index1=2（nums1 剩余元素从索引 2 开始：[5]）
            }
            else
            {
                // 若pivot2更小，则排除nums2中对应范围的元素（逻辑同上）
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }

            // 示例第二次循环：index1=2, index2=0, k=2
            // 计算newIndex1：min(2 + 2/2 -1, 2) = min(2+1-1,2)=2（nums1[2]=5）
            // 计算newIndex2：min(0 + 2/2 -1, 2)=min(0+1-1,2)=0（nums2[0]=2）
            // pivot1=5, pivot2=2 → pivot2更小，进入else
            // 排除nums2[0..0]（元素2），共1个元素
            // k=2-1=1，index2=1（nums2剩余元素从索引1开始：[4,6]）

            // 示例第三次循环：index1=2, index2=1, k=1
            // 触发k==1的边界条件，返回min(nums1[2]=5, nums2[1]=4) → 4（符合预期第4小元素）
        }
    }

    // 计算两个非降序（升序）数组的中位数
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int totalLength = nums1.size() + nums2.size(); // 示例中总长度=6（偶数）
        if (totalLength % 2 == 1)
        {
            // 总长度为奇数：中位数是第 (totalLength + 1)/2 小的元素
            return getKthElement(nums1, nums2, (totalLength + 1) / 2);
        }
        else
        {
            // 总长度为偶数：中位数是第 totalLength/2 和 totalLength/2 + 1 小元素的平均值
            // 示例中：第3小（3）和第4小（4）的平均值 → (3+4)/2=3.5
            return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
        }
    }
};

int main()
{
    auto runTest = [](vector<int> a, vector<int> b, double expected)
    {
        Solution sol;
        double res = sol.findMedianSortedArrays(a, b);
        cout << fixed << setprecision(6)
             << "Result: " << res << ", Expected: " << expected
             << (fabs(res - expected) < 1e-6 ? " [OK]" : " [FAIL]")
             << endl;
    };

    // 测试用例 1：奇数总长度；nums1={1,3}，nums2={2}；中位数=2.0
    runTest({1, 3}, {2}, 2.0);

    // 测试用例 2：偶数总长度；nums1={1,3,5}，nums2={2,4,6}；中位数=3.5
    runTest({1, 3, 5}, {2, 4, 6}, 3.5);

    // 测试用例 3：一个数组为空；nums1={}，nums2={1}；中位数=1.0
    runTest({}, {1}, 1.0);

    // 测试用例 4：两个数组包含相同元素；nums1={0,0}，nums2={0,0}；中位数=0.0
    runTest({0, 0}, {0, 0}, 0.0);

    // 测试用例 5：不同规模分布；nums1={1,2}，nums2={3,4,5,6}；中位数=3.5
    runTest({1, 2}, {3, 4, 5, 6}, 3.5);

    return 0;
}


//无注释版
// class Solution
// {
// public:
//     int getke(vector<int> &nums1, vector<int> &nums2, int k)
//     {
//         int m = nums1.size();
//         int n = nums2.size();
//         int index1 = 0;
//         int index2 = 0;

//         while (1)
//         {
//             if (index1 == m)
//             {
//                 return nums2[index2 + k - 1];
//             }

//             if (index2 == n)
//             {
//                 return nums1[index1 + k - 1];
//             }

//             if (k == 1)
//             {
//                 return min(nums1[index1], nums2[index2]);
//             }

//             int newIndex1 = min(index1 + k / 2 - 1, m - 1);
//             int newIndex2 = min(index2 + k / 2 - 1, n - 1);

//             int mid1 = nums1[newIndex1];
//             int mid2 = nums2[newIndex2];

//             // 排除mid1左边的所有元素
//             if (mid1 <= mid2)
//             {
//                 k -= newIndex1 - index1 + 1;
//                 index1 = newIndex1 + 1;
//             }
//             else
//             {
//                 k -= newIndex2 - index2 + 1;
//                 index2 = newIndex2 + 1;
//             }
//         }
//     }

//     double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
//     {
//         int totalLen = nums1.size() + nums2.size();

//         // totalLen为奇数
//         if (totalLen & 1)
//         {
//             return getke(nums1, nums2, (totalLen + 1) / 2);
//         }
//         else
//         {
//             return (getke(nums1, nums2, totalLen / 2 + 1) + getke(nums1, nums2, totalLen / 2)) / 2.0;
//         }

//         return 0;
//     }
// };