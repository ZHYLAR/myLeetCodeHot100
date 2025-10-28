#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
核心思路：用一个二层循环遍历节点
从每一个岛屿节点 dfs，把这个节点相邻的岛屿部分都删除掉（赋值为 0）

也就是说每遍历到一个岛屿的部分，就会从“上岛地”开始，用 dfs 把这个岛屿“删除”
最后遍历到几个岛屿，就知道岛屿数量。

dfs 采用递归写法
*/

class Solution
{

private:
    /*
    dfs: (图 ， 起始节点row ， 起始节点col ) (vector<vector<char>> , int , int)
     */
    void dfs(vector<vector<char>> &grid, int r, int c)
    {
        const int row = grid.size();
        const int col = grid[0].size();
        grid[r][c] = '0';

        //这个地方是大于等于0，易错
        if (r - 1 >= 0 && grid[r - 1][c] == '1')
            dfs(grid, r - 1, c);

        if (r + 1 < row && grid[r + 1][c] == '1')
            dfs(grid, r + 1, c);

        if (c - 1 >= 0 && grid[r][c - 1] == '1')
            dfs(grid, r, c - 1);

        if (c + 1 < col && grid[r][c + 1] == '1')
            dfs(grid, r, c + 1);
    }

public:
    int numIslands(vector<vector<char>> &grid)
    {
        const int row = grid.size();
        const int col = grid[0].size();
        if (!row)
        {
            return 0;
        }

        int numisland = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (grid[i][j] == '1')
                {
                    numisland++;
                    dfs(grid, i, j);
                }
            }
        }

        return numisland;
    }
};

// class Solution
// {
// public:
//     void dfs(vector<vector<char>> &grid, int r, int c)
//     {
//         const int nr = grid.size();
//         const int nc = grid[0].size();

//         grid[r][c] = '0';
//         if (r - 1 >= 0 && grid[r - 1][c] == '1')
//             dfs(grid, r - 1, c);

//         if (r + 1 < nr && grid[r + 1][c] == '1')
//             dfs(grid, r + 1, c);

//         if (c - 1 >= 0 && grid[r][c - 1] == '1')
//             dfs(grid, r, c - 1);

//         if (c + 1 < nc && grid[r][c + 1] == '1')
//             dfs(grid, r, c + 1);
//     }

//     int numIslands(vector<vector<char>> &grid)
//     {
//         const int nr = grid.size();
//         if (nr == 0)
//             return 0;
//         const int nc = grid[0].size();

//         int num_island = 0;
//         for (int r = 0; r < nr; r++)
//         {
//             for (int c = 0; c < nc; c++)
//             {
//                 if (grid[r][c] == '1')
//                 {
//                     num_island++;
//                     dfs(grid, r, c);
//                 }
//             }
//         }

//         return num_island;
//     }
// };

int main()
{
    Solution solution;
    int ans = 0;
    vector<vector<char>> grid = {
        {'1', '1', '1'},
        {'0', '1', '0'},
        {'1', '1', '1'}};

    ans = solution.numIslands(grid);
    cout << ans << endl;
    return 0;
}
