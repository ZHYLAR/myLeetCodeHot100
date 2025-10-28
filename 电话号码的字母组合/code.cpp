#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    vector<string> ans;
    string curr;
    vector<string> phoneMap = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    /*
    回溯算法：
    1. 选择列表：当前号码对应的所有字母
    2. 路径：已经选择的字母
    3. 结束条件：路径长度等于输入数字的长度
    参数：
    digits：输入的数字字符串
    index：当前处理的数字索引
    */
    void backtrack(string digits, int index)
    {
        //退出条件：每个号码都取完了一个字符
        if (curr.size() == digits.size())
        {
            ans.emplace_back(curr);
            return;
        }

        //获取当前数字对应的字母
        char digit = digits[index];
        string letters = phoneMap[digit - '0'];

        //循环遍历当前数字对应的所有字母
        for (int i = 0; i < letters.size(); i++)
        {
            //处理当前号码：添加当前字母e
            curr.push_back(letters[i]);
            
            backtrack(digits, index + 1); //回溯 处理下一个号码（减少候选列表）

            //撤销操作：移除当前字母
            curr.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        ans.clear();
        curr.clear();
        backtrack(digits, 0);
        return ans;
    }
};