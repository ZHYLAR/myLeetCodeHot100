
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
    /*
        1.范围收缩（抽屉原理）:长度为 n 的数组里，最小缺失正整数一定落在 [1, n+1]。    
            1.1如果 1..n 都在，那答案就是 n+1；
            1.2否则就是其中某个缺失的数。
            → 所以我们只需关注 1..n 这些“有用数”，其他（≤0 或 >n）都可以视为“垃圾”。

        2.用数组当哈希桶（原地哈希 / 置换）:把每个在 [1..n] 范围内的数 x 放到“它的家”——下标 x-1 的位置：
            2.1想让 nums[x-1] == x；
            2.2通过不断交换把数放回家；
            2.3处理过程中忽略 ≤0、>n、以及 重复 的数（避免死循环）。
            
        3.最终一遍扫描：第一个不在家（nums[i] != i+1）的位置 i，答案就是 i+1；若都在家，答案是 n+1。
    */
    int firstMissingPositive(vector<int>& nums) {
        const int n = nums.size();

        // 第一步：把在 [1..n] 范围内的元素放到“对应的家”下标 x-1 上
        for (int i = 0; i < n; ++i) {
            while (nums[i] >= 1 && nums[i] <= n) { // 注意：用 while 而不是 if，因为换过来一个新数后还需要继续检查
                int to = nums[i] - 1;           // 目标位置（它的家）
                if (nums[to] == nums[i]) break; // 已在家 或 出现重复，停止以防死循环
                swap(nums[i], nums[to]);   // 交换，把当前数送回家
            }
        }

        // 第二步：查找第一个“不在家”的位置
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1; // 1..n 都在，则答案是 n+1
    }
};

int main() {
	Solution s;
	vector<int> nums = {3,4,-1,1};
	int ans = 0;
	ans = s.firstMissingPositive(nums);
	
	cout << ans;
    return 0;
}
