#include <iostream>
#include <vector>
#include <string>

class Solution {
private:
     std::vector<std::string> ans;
     std::string t;

    /*剩余左括号个数、右括号个数*/
     void backtrack(int l, int r)
     {
        //退出条件
            //不合规序列
        if(l<0 || r<0 || l>r) //右括号不能多过左括号，这里 l,r 分别表示剩余个数，所以 l>r 时一定不合规
        {
            return;
        }
            //合规序列
        if(l == 0 && r == 0)
        {
            ans.emplace_back(t);
            return; //记得返回
        }

        //处理当前节点
        t.push_back('(');
        backtrack(l-1,r);
        t.pop_back();
        //回溯

        t.push_back(')');
        backtrack(l,r-1);
        t.pop_back();
     }

public:
    std::vector<std::string> generateParenthesis(int n) {
       backtrack(n,n);
       return ans; 
    }
};

int main() {
    Solution sol;
    int n = 3; // 示例：生成3对括号
    std::vector<std::string> result = sol.generateParenthesis(n);

    std::cout << "为 n = " << n << " 生成的所有有效括号组合:" << std::endl;
    for (const std::string& s : result) {
        std::cout << s << std::endl;
    }

    n = 1; // 示例：生成1对括号
    sol = Solution(); // 重置Solution对象以清除之前的状态
    result = sol.generateParenthesis(n);
    std::cout << "\n为 n = " << n << " 生成的所有有效括号组合:" << std::endl;
    for (const std::string& s : result) {
        std::cout << s << std::endl;
    }

    n = 0; // 示例：生成0对括号
    sol = Solution(); // 重置Solution对象以清除之前的状态
    result = sol.generateParenthesis(n);
    std::cout << "\n为 n = " << n << " 生成的所有有效括号组合:" << std::endl;
    for (const std::string& s : result) {
        std::cout << s << std::endl;
    }

    return 0;
}