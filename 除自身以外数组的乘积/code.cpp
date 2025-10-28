// 除自身以外数组的乘积
// 算法思路：
// 1. 方法一：先计算所有非零元素的乘积，然后根据零的个数分情况处理
// 2. 方法二：使用左右乘积数组，分别存储每个元素左侧和右侧的乘积

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;


class Solution {
public:
    // productExceptSelf函数：计算除当前元素外所有元素的乘积
    // 参数：nums - 输入整数数组
    // 返回值：包含每个元素对应结果的数组
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> ans;        // 存储结果的数组
        int len = nums.size();  // 数组长度
        ans.reserve(len);       // 预分配内存，优化性能
        long int total_m = 1;   // 存储非零元素的总乘积
        int zero_num = 0;       // 统计数组中零的个数
        
        // 遍历数组，计算非零元素乘积并统计零的个数
        for(const auto & x : nums)
        {
            if(zero_num>1) break;  // 如果零的个数超过1，提前结束循环
            if(x==0){zero_num++; continue;}  // 如果元素为零，计数并跳过
            total_m *= x;  // 计算非零元素的乘积
        }

        // 情况1：数组中有超过1个零，所有结果都是零
        if(zero_num>1)
        {
            for(int i=0; i<len;i++)
            {
                ans.emplace_back(0);
            }
        }

        // 情况2：数组中只有1个零，零所在位置的结果为非零元素乘积，其他为零
        else if(zero_num == 1)
        {
            for(const auto &x : nums)
            {
                if(x==0){ans.emplace_back(total_m);}  // 零的位置存储总乘积
                else{ ans.emplace_back(0);}           // 非零位置存储0
            }
        }

        // 情况3：数组中没有零，每个位置等于总乘积除以当前元素
        else{
            for(const auto &x : nums)
            {
                ans.emplace_back(total_m/x);
            }
        }
        return ans;
    }
};



// 方法二：使用左右乘积数组的实现（空间优化版本）
// class Solution {
// public:
//     // productExceptSelf函数：使用左右乘积数组方法计算结果
//     // 参数：nums - 输入整数数组
//     // 返回值：包含每个元素对应结果的数组
//     vector<int> productExceptSelf(vector<int>& nums) {
//         vector<int> pL, pR, ans;  // pL:左乘积数组, pR:右乘积数组, ans:结果数组
//         int len = nums.size();    // 数组长度
//         pL.resize(len); pR.resize(len); ans.resize(len);  // 调整数组大小
//         pL[0] = 1; pR[len-1] = 1;  // 边界条件：第一个元素左侧乘积为1，最后一个元素右侧乘积为1
//         
//         // 同时计算左乘积和右乘积
//         // pL[i]表示nums[0]到nums[i-1]的乘积
//         // pR[i]表示nums[i+1]到nums[len-1]的乘积
//         for (int i = 0; i < len-1; i++)
//         {
//             pL[i+1] = pL[i] * nums[i];
//             pR[len-2-i] = pR[len-1-i] * nums[len-1-i];
//         }

//         // 每个元素的结果等于其左侧乘积乘以右侧乘积
//         for(int i=0; i < len ; i++)
//         {
//             ans[i] = pL[i] * pR[i];
//         }
        
        
//         return ans;
//     }
// };

// 主函数：测试Solution类的productExceptSelf方法
int main()
{
    Solution solution;  // 创建Solution对象
    vector<int> ans;    // 存储结果
    vector<int> nums = {1,2,3,4,5};  // 测试用例
    
    // 调用方法并获取结果
    ans = solution.productExceptSelf(nums);
    
    // 输出结果
    for(const auto &x : ans)
    {
        cout << x << " ";    
    }
    cout << endl;
	return 0;
}
