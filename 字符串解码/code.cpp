#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <vector>
using namespace std;
class Solution
{
public:
    // 算法说明：使用两个栈（数字栈 num_stk、字符串栈 str_stk）与一个当前累积字符串 str。
    // 逐字符扫描 s：
    // - 遇到连续数字，解析为重复次数 n，入数字栈；
    // - 遇到 '['，将当前 str 入字符串栈，并清空 str 开始记录子串；
    // - 遇到 ']'，将当前子串按数字栈顶次数展开，并与字符串栈顶前缀拼接；
    // - 其他普通字符，直接累积到 str。
    // 例：s = "3[a2[c]]"
    //   i=0:'3' -> 解析 n=3 入 num_stk=[3]
    //   i=1:'[' -> str_stk.push("")，str=""
    //   i=2:'a' -> str="a"
    //   i=3:'2' -> 解析 n=2 入 num_stk=[3,2]
    //   i=4:'[' -> str_stk.push("a")，str=""
    //   i=5:'c' -> str="c"
    //   i=6:']' -> 重复2次得到 tmp="cc"，pop 2；拼接前缀：str_stk.top()="a" -> str="acc"
    //   i=7:']' -> 重复3次得到 tmp="accaccacc"，pop 3；拼接前缀：str_stk.top()="" -> str="accaccacc"
    string decodeString(string s)
    {
        stack<int> num_stk;    // 数字栈（示例：依次入栈 3、2）
        stack<string> str_stk; // 字符串栈（示例：在遇到 '[' 时入栈当前累积串）
        string str;            // 当前正在累积的字符串（示例：逐步从 "" -> "a" -> "acc" -> "accaccacc"）
        for (int i = 0; i < s.size(); ++i)
        {
            if (isdigit(s[i]))
            { // 遇到数字：连续读取多位数字，得到重复次数 n
                int n = s[i] - '0'; // 将字符数字转换为对应的整型值（更规范、易读）
                // 使用前瞻解析多位数字，避免在 while 中前置自增导致越界或错过后续字符
                while (i + 1 < s.size() && isdigit(s[i + 1])) {
                    i++;
                    n = n * 10 + (s[i] - '0');
                }
                num_stk.push(n); // 将 n 入数字栈
                // 移除回退操作：此时 i 停在最后一个数字位置，for 的自增会让下轮从后续字符（如 '['）开始
            }
            else if (s[i] == '[')
            {                      // 遇到左括号：保存当前累积的前缀串
                str_stk.push(str); // 将当前累积的字符串入栈（示例：第一次入栈 ""，第二次入栈 "a"）
                str = "";          // 清空，开始记录被括号包裹的子串（示例：准备记录 "a2[c]" 中的 "c"）
            }
            else if (s[i] == ']')
            { // 遇到右括号：完成一次扩展与拼接
                string tmp;
                // 将当前字符串按数字栈栈顶元素为倍数进行扩展（将 str 重复 num_stk.top() 次）
                for (int i = 0; i < num_stk.top(); ++i)
                {
                    tmp += str;
                }
                // 示例（继续 "3[a2[c]]"）：当读到第一个 ']' 时，num_stk.top()=2，str="c" -> tmp="cc" -> str="cc"
                str = tmp;
                num_stk.pop(); // 弹出本轮使用的数字
                // 将上一次的前缀串与当前扩展后的子串拼接
                // 示例：第一次 ']'：str_stk.top()="a"，当前 str="cc" -> 新 str="acc"；第二次 ']'：str_stk.top()=""，当前 str="accaccacc" -> 新 str="accaccacc"
                str = str_stk.top() + str;
                str_stk.pop();
            }
            else
            {
                str += s[i]; // 累积普通字符；示例：读到 'a' 或 'c' 时追加
            }
        }
        // 完整示例轨迹（s="3[a2[c]]"）总结：最终返回 str="accaccacc"
        return str;
    }
};

int main() {
    Solution sol;
    auto run = [&](const string& s, const string& expected) {
        string res = sol.decodeString(s);
        cout << "Input: " << s << " -> " << res
             << " | Expected: " << expected
             << (res == expected ? " [OK]" : " [FAIL]") << endl;
    };

    // 基础用例
    run("3[a]2[bc]", "aaabcbc");
    // 嵌套用例
    run("3[a2[c]]", "accaccacc");
    // 多段组合
    run("2[abc]3[cd]ef", "abcabccdcdcdef");
    // 含普通字符与重复块
    run("abc3[cd]xyz", "abccdcdcdxyz");
    // 多位数字
    run("10[a]", "aaaaaaaaaa");
    // 无重复块
    run("leetcode", "leetcode");
    // 零次重复
    run("0[a]", "");
    // 更复杂嵌套
    run("2[2[b]c]", "bbcbbc");

    return 0;
}