#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;                 
        vector<string> board(n, string(n, '.')); // 初始化n×n的棋盘，全部为'.'
        vector<char> colsOccupied(n, false); // 列标记数组，表示哪些列已经被占用
        vector<char> diag1(2 * n - 1, false); // 主对角线标记数组
        vector<char> diag2(2 * n - 1, false); // 副对角线标记数组
        
        backtrack(result, board, colsOccupied, diag1, diag2, 0, n);
        return result;
    }
    
private:
    //大循环（递归）遍历行，内层循环遍历列，判断是否安全
    void backtrack(vector<vector<string>>& result, vector<string>& board, 
                   vector<char>& colsOccupied, vector<char>& diag1, vector<char>& diag2, 
                   int rowIndex, int n) {
        // 如果已经放置完所有皇后，将当前棋盘加入结果
        if (rowIndex == n) {
            result.push_back(board);
            return;
        }
        
        // 尝试在当前行的每一列放置皇后
        for (int colIndex = 0; colIndex < n; colIndex++) {
            // 检查当前位置是否安全
            if (isSafe(colsOccupied, diag1, diag2, rowIndex, colIndex, n)) {
                // 放置皇后
                board[rowIndex][colIndex] = 'Q';
                colsOccupied[colIndex] = true;
                // 标记主对角线, 行索引加列索引相等
                diag1[rowIndex + colIndex] = true;

                // 标记副对角线, 同一条线上 行索引减列索引相等
                diag2[rowIndex - colIndex + n - 1] = true;
                                
                // 递归处理下一行
                backtrack(result, board, colsOccupied, diag1, diag2, rowIndex + 1, n);
                
                // 回溯，移除皇后
                board[rowIndex][colIndex] = '.';
                colsOccupied[colIndex] = false;
                diag1[rowIndex + colIndex] = false;
                diag2[rowIndex - colIndex + n - 1] = false;
            }
        }
    }
    
    bool isSafe(vector<char>& colsOccupied, vector<char>& diag1, vector<char>& diag2, 
                int rowIndex, int colIndex, int n) {
        // 检查列是否已被占用
        if (colsOccupied[colIndex]) return false;
        // 检查主对角线是否已被占用 (row + col)
        if (diag1[rowIndex + colIndex]) return false;
        // 检查副对角线是否已被占用 (row - col + n - 1)
        if (diag2[rowIndex - colIndex + n - 1]) return false;
        
        return true;
    }
};

// 辅助函数：打印所有解决方案
void printSolutions(const vector<vector<string>>& solutions) {
    cout << "共有 " << solutions.size() << " 种解决方案：" << endl;
    for (int i = 0; i < solutions.size(); i++) {
        cout << "解决方案 " << i + 1 << ":" << endl;
        for (const string& row : solutions[i]) {
            cout << row << endl;
        }
        cout << endl;
    }
}

int main() {
    Solution solution;
    
    // 测试用例1: n = 4
    cout << "=== n = 4 ===" << endl;
    vector<vector<string>> result4 = solution.solveNQueens(4);
    printSolutions(result4);
    
    // 测试用例2: n = 1
    cout << "=== n = 1 ===" << endl;
    vector<vector<string>> result1 = solution.solveNQueens(1);
    printSolutions(result1);
    
    // 测试用例3: n = 2
    cout << "=== n = 2 ===" << endl;
    vector<vector<string>> result2 = solution.solveNQueens(2);
    printSolutions(result2);
    
    // 测试用例4: n = 3
    cout << "=== n = 3 ===" << endl;
    vector<vector<string>> result3 = solution.solveNQueens(3);
    printSolutions(result3);
    
    // 测试用例5: n = 8 (经典8皇后问题)
    cout << "=== n = 8 (8皇后问题) ===" << endl;
    vector<vector<string>> result8 = solution.solveNQueens(8);
    cout << "8皇后问题共有 " << result8.size() << " 种解决方案" << endl;
    
    // 测试用例6: n = 9
    cout << "=== n = 9 ===" << endl;
    vector<vector<string>> result9 = solution.solveNQueens(9);
    cout << "9皇后问题共有 " << result9.size() << " 种解决方案" << endl;
    
    return 0;
}



// class Solution {
// public:
//     vector<vector<string>> solveNQueens(int n) {
//         vector<string> cur(n, string(n, '.'));
//         backtracking(cur, 0, n);
//         return res;

//     }
//     void backtracking(vector<string>& cur, int level, int n) {
//         if (level == n) {
//             res.push_back(cur);
//             return;
//         }
//         for (int j = 0; j < n; j++) {
//             if(isValid(cur, level, j)) {
//                 cur[level][j] = 'Q';
//                 backtracking(cur, level + 1, n);
//                 cur[level][j] = '.';
//             }
//         }
//     }
//     bool isValid(const vector<string>& cur, int i, int j) {
//         int n = cur.size();
//         for (int a = 0; a < n; a++) { // 上
//             if (cur[a][j] == 'Q') return false;
//         }
//         for (int a = i, b = j; a >= 0 && b >= 0; a--, b--) { // 左上
//             if (cur[a][b] == 'Q') return false;
//         }
//         for (int a = i, b = j; a >= 0 && b < n; a--, b++) { // 右上
//             if (cur[a][b] == 'Q') return false;
//         }
//         return true; // 其他方向都是未放过皇后的，不可能为false
//     }
// private:
//     vector<vector<string>> res;
// };