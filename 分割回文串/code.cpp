#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    void backtrack(const string& s, int start, vector<string>& current, vector<vector<string>>& result) {
        //结束条件：如果已经处理完整个字符串，将当前分割方案加入结果
        if (start == s.length()) {
            result.push_back(current);
            return;
        }

        //处理当前节点，遍历所有可能的分割点
        for (int end = start; end < s.length(); end++) {
            // 检查从start到end的子串是否是回文
            if (isPalindrome(s, start, end)) {
                // 如果是回文，将其加入当前分割方案
                current.push_back(s.substr(start, end - start + 1));//substr 接收两个参数，第一个是起始位置，第二个是长度
                // 递归处理剩余部分
                backtrack(s, end + 1, current, result);
                
                // 回溯，移除当前选择
                current.pop_back();
            }
        }
    }
    
    // 这个地方传入子串的索引，是为了在不复制子串的情况下判断是否是回文
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

// 辅助函数：打印分割结果
void printPartitions(const vector<vector<string>> &partitions)
{
    cout << "[";
    for (int i = 0; i < partitions.size(); i++)
    {
        cout << "[";
        for (int j = 0; j < partitions[i].size(); j++)
        {
            cout << "\"" << partitions[i][j] << "\"";
            if (j < partitions[i].size() - 1)
            {
                cout << ",";
            }
        }
        cout << "]";
        if (i < partitions.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "]" << endl;
}

int main()
{
    Solution solution;

    // 测试用例1: "aab"
    cout << "输入: \"aab\"" << endl;
    vector<vector<string>> result1 = solution.partition("aab");
    cout << "输出: ";
    printPartitions(result1);
    cout << endl;

    // 测试用例2: "a"
    cout << "输入: \"a\"" << endl;
    vector<vector<string>> result2 = solution.partition("a");
    cout << "输出: ";
    printPartitions(result2);
    cout << endl;

    // 测试用例3: "aaa"
    cout << "输入: \"aaa\"" << endl;
    vector<vector<string>> result3 = solution.partition("aaa");
    cout << "输出: ";
    printPartitions(result3);
    cout << endl;

    // 测试用例4: "ababa"
    cout << "输入: \"ababa\"" << endl;
    vector<vector<string>> result4 = solution.partition("ababa");
    cout << "输出: ";
    printPartitions(result4);
    cout << endl;

    return 0;
}