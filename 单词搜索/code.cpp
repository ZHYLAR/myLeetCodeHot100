#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class Solution {
public:
    // 主方法：判断单词是否存在于网格中
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty() || word.empty()) return false;
        if (word.size() > board.size() * board[0].size()) return false;//单词长度大于网格面积，直接返回false
        int m = board.size();
        int n = board[0].size();
        
        // 遍历网格中的每个单元格，尝试将其作为单词的起始位置
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    // DFS 辅助方法：从 (i,j) 开始搜索单词 word[k...] 是否存在
    // i, j: 当前搜索的网格位置
    // k: 当前匹配到的单词字符索引
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int k) {
        // 1. 退出条件：如果已经匹配了整个单词，返回 true
        if (k == word.size()) {
            return true;
        }
        
        int m = board.size();
        int n = board[0].size();
        
        // 退出条件：检查当前位置是否越界，或者字符不匹配
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[k]) {
            return false;
        }
        
        // 2. 处理当前节点：暂存当前字符，并标记为已访问（用特殊字符替代）
        char temp = board[i][j];
        board[i][j] = '#'; // 标记为已访问
        
        // 3. 递归：向四个方向（上、右、下、左）继续搜索
        bool found = dfs(board, word, i-1, j, k+1) || 
                    dfs(board, word, i, j+1, k+1) || 
                    dfs(board, word, i+1, j, k+1) || 
                    dfs(board, word, i, j-1, k+1);
        
        // 4. 回溯：恢复当前字符，以便其他路径可以使用
        board[i][j] = temp;
        
        return found;
    }
};

// 测试函数
void testExist() {
    Solution solution;
    
    // 测试用例 1
    vector<vector<char>> board1 = {
        {'A','B','C','E'},
        {'S','F','C','S'},
        {'A','D','E','E'}
    };
    string word1 = "ABCCED";
    cout << "测试用例 1: 搜索 \"ABCCED\" -> " << (solution.exist(board1, word1) ? "存在" : "不存在") << endl;
    
    // 测试用例 2
    vector<vector<char>> board2 = board1; // 复用同一个网格
    string word2 = "SEE";
    cout << "测试用例 2: 搜索 \"SEE\" -> " << (solution.exist(board2, word2) ? "存在" : "不存在") << endl;
    
    // 测试用例 3
    vector<vector<char>> board3 = board1; // 复用同一个网格
    string word3 = "ABCB";
    cout << "测试用例 3: 搜索 \"ABCB\" -> " << (solution.exist(board3, word3) ? "存在" : "不存在") << endl;
    
    // 测试用例 4：边界情况 - 空网格
    vector<vector<char>> board4;
    string word4 = "A";
    cout << "测试用例 4: 空网格搜索 \"A\" -> " << (solution.exist(board4, word4) ? "存在" : "不存在") << endl;
    
    // 测试用例 5：边界情况 - 空单词
    vector<vector<char>> board5 = {{'A'}};
    string word5 = "";
    cout << "测试用例 5: 网格 [{'A'}] 搜索空单词 -> " << (solution.exist(board5, word5) ? "存在" : "不存在") << endl;
}

int main() {
    cout << "单词搜索问题的 DFS 解决方案测试：" << endl;
    testExist();
    return 0;
}