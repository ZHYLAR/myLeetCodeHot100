#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // 存储所有生成的子集
    vector<vector<int>> ans;

    /**
     * @brief 回溯函数，用于生成所有子集
     * 
     * @param nums 原始输入数组，包含所有可能的元素
     * @param cur 当前正在构建的子集
     * @param index 当前考虑从nums数组哪个位置开始选择元素
     */
    void backtrack(vector<int>& nums, vector<int>& cur, int index){
        // 每当进入回溯函数，当前的cur就是一个有效的子集，将其加入结果集ans
        ans.push_back(cur);

        // 从当前索引index开始遍历nums数组，尝试将后续元素添加到当前子集cur中
        for (int i = index; i < nums.size(); i++){
            // 选择操作：将当前元素nums[i]添加到子集cur中
            cur.push_back(nums[i]);
            
            // 递归调用：继续从下一个位置（i + 1）开始，构建包含nums[i]的子集
            backtrack(nums, cur, i + 1);
            
            // 撤销选择（回溯）：当递归返回后，将nums[i]从cur中移除
            // 这是回溯算法的关键步骤，确保不影响上层或同层后续的选择，恢复到上一个状态
            cur.pop_back();
        }        
    }

    /**
     * @brief 主函数，用于计算给定数组的所有子集
     * 
     * @param nums 输入的整数数组
     * @return 包含所有子集的向量
     */
    vector<vector<int>> subsets(vector<int>& nums) {
        // 初始化一个空的当前子集向量
        vector<int> cur;
        // 调用回溯函数，从索引0开始生成子集
        backtrack(nums, cur, 0);
        // 返回存储所有子集的结果集
        return ans;
    }
};


// 主函数，用于测试Solution类
int main() {
    Solution sol; // 创建Solution类的实例
    vector<int> nums = {1, 2, 3}; // 定义测试用例，例如：nums = [1, 2, 3]

    // 调用subsets方法计算所有子集
    // 对于 nums = [1, 2, 3]，`subsets`方法将通过回溯算法生成以下子集（示例打印顺序可能有所不同，但所有子集都会生成）：
    // - 初始：[]
    // 1. 选择 1 -> [1]
    //    1.1. 选择 2 -> [1, 2]
    //        1.1.1. 选择 3 -> [1, 2, 3]
    //        1.1.1. 回溯，移除 3 -> [1, 2]
    //    1.1. 回溯，移除 2 -> [1]
    //    1.2. 选择 3 -> [1, 3]
    //    1.2. 回溯，移除 3 -> [1]
    // 1. 回溯，移除 1 -> []
    // 2. 选择 2 -> [2]
    //    2.1. 选择 3 -> [2, 3]
    //    2.1. 回溯，移除 3 -> [2]
    // 2. 回溯，移除 2 -> []
    // 3. 选择 3 -> [3]
    // 3. 回溯，移除 3 -> []
    // 最终结果将包含所有这些子集：[], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]
    // 最终结果将包含所有这些子集。
    vector<vector<int>> result = sol.subsets(nums);

    // 打印结果
    cout << "所有子集:" << endl;
    for (const auto& subset : result) {
        cout << "[";
        for (size_t i = 0; i < subset.size(); ++i) {
            cout << subset[i];
            if (i < subset.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    return 0;
}

/*
nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
*/