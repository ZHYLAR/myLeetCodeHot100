#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;
using std::cout;
using std::endl;


class Solution {
private:
    vector<vector<int >> ans;
    vector<int > curr;
    int sum_cur = 0;

    void backtrack(vector<int >& candidates,int target, int index)
    {
        //结束条件
        if(sum_cur == target)
        {
            ans.emplace_back(curr);
        }

        //遍历&递归
        for(int i=index; i<candidates.size(); i++)
        {
            if(sum_cur+candidates[i] > target)
            {
                continue;
            }

            curr.emplace_back(candidates[i]);
            sum_cur+=candidates[i];

            backtrack(candidates, target, i);//下一层至少要从 index = i 的节点开始遍历
            
             //回溯
            sum_cur -= candidates[i];
            curr.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0);
        return ans;
    }
};

// 辅助函数：打印二维数组
void printCombinations(const vector<vector<int>>& combinations) {
    cout << "[";
    for(int i = 0; i < combinations.size(); i++) {
        cout << "[";
        for(int j = 0; j < combinations[i].size(); j++) {
            cout << combinations[i][j];
            if(j < combinations[i].size() - 1) {
                cout << ",";
            }
        }
        cout << "]";
        if(i < combinations.size() - 1) {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

// 测试用例
void testCombinationSum() {
    Solution solution;
    
    // 测试用例1：基本测试
    cout << "测试用例1: candidates = [2,3,6,7], target = 7" << endl;
    vector<int> candidates1 = {2,3,6,7};
    auto result1 = solution.combinationSum(candidates1, 7);
    cout << "预期结果: [[2,2,3],[7]]" << endl;
    cout << "实际结果: ";
    printCombinations(result1);
    cout << endl;

    // 测试用例2：多个组合
    cout << "测试用例2: candidates = [2,3,5], target = 8" << endl;
    vector<int> candidates2 = {2,3,5};
    auto result2 = solution.combinationSum(candidates2, 8);
    cout << "预期结果: [[2,2,2,2],[2,3,3],[3,5]]" << endl;
    cout << "实际结果: ";
    printCombinations(result2);
    cout << endl;

    // 测试用例3：无解情况
    cout << "测试用例3: candidates = [2], target = 1" << endl;
    vector<int> candidates3 = {2};
    auto result3 = solution.combinationSum(candidates3, 1);
    cout << "预期结果: []" << endl;
    cout << "实际结果: ";
    printCombinations(result3);
    cout << endl;

    // 测试用例4：单个元素
    cout << "测试用例4: candidates = [1], target = 1" << endl;
    vector<int> candidates4 = {1};
    auto result4 = solution.combinationSum(candidates4, 1);
    cout << "预期结果: [[1]]" << endl;
    cout << "实际结果: ";
    printCombinations(result4);
    cout << endl;

    // 测试用例5：多个相同元素
    cout << "测试用例5: candidates = [1], target = 2" << endl;
    vector<int> candidates5 = {1};
    auto result5 = solution.combinationSum(candidates5, 2);
    cout << "预期结果: [[1,1]]" << endl;
    cout << "实际结果: ";
    printCombinations(result5);
    cout << endl;
}

int main() {
    cout << "=== 组合总和问题测试 ===" << endl;
    testCombinationSum();
    return 0;
}