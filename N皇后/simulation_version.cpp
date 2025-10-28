class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> cur(n, string(n, '.'));
        backtracking(cur, 0, n);
        return res;

    }
    void backtracking(vector<string>& cur, int level, int n) {
        if (level == n) {
            res.push_back(cur);
            return;
        }
        for (int j = 0; j < n; j++) {
            if(isValid(cur, level, j)) {
                cur[level][j] = 'Q';
                backtracking(cur, level + 1, n);
                cur[level][j] = '.';
            }
        }
    }
    bool isValid(const vector<string>& cur, int i, int j) {
        int n = cur.size();
        for (int a = 0; a < n; a++) { // 上
            if (cur[a][j] == 'Q') return false;
        }
        for (int a = i, b = j; a >= 0 && b >= 0; a--, b--) { // 左上
            if (cur[a][b] == 'Q') return false;
        }
        for (int a = i, b = j; a >= 0 && b < n; a--, b++) { // 右上
            if (cur[a][b] == 'Q') return false;
        }
        return true; // 其他方向都是未放过皇后的，不可能为false
    }
private:
    vector<vector<string>> res;
};