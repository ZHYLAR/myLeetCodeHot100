#include <vector>
using namespace std;

/*

void backtracking(参数) {
    if (终止条件) {
        存放结果;
        return;
    }
    for (选择 : 本层集合中的元素) {
        处理节点;
        backtracking(路径, 选择列表); // 递归 一般应该是在递归过程中选择列表列表越来越小
        撤销处理; // 回溯 撤销当前节点的处理，增加上一层的选择列表
    }
}

*/

class Solution {
private:
    // 回溯函数，用于生成排列
    void backtrack(const vector<int>& nums, vector<vector<int>>& result, vector<int>& path, vector<char>& used) {
        // 终止条件：当路径长度等于数组长度时，找到一个完整排列
        
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }
        
        // 尝试选择每一个未使用过的元素
        for (int i = 0; i < nums.size(); i++) {
            // 剪枝：如果当前元素已经使用过，则跳过
            if (used[i]) continue;
            
            // 做出选择
            used[i] = true;         // 标记为已使用
            path.push_back(nums[i]); // 添加到当前路径
            
            // 递归到下一层，继续选择下一个元素
            backtrack(nums, result, path, used);
            
            // 撤销选择（回溯）
            path.pop_back();        // 从路径中移除
            used[i] = false;        // 标记为未使用
        }
    }
    
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;  // 存储所有排列结果
        vector<int> path;           // 当前排列路径
        vector<char> used(nums.size(), 0); // 记录元素是否已使用 (0: 未使用, 1: 已使用)
        
        // 调用回溯函数生成所有排列
        backtrack(nums, result, path, used);
        
        return result;
    }
};