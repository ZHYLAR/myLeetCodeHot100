#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// class Solution {
// public:
//     /**
//      * 计算腐烂橘子扩散感染所有新鲜橘子所需的最少时间
//      * @param grid 表示橘子网格的二维向量，其中：
//      *             0: 空单元格
//      *             1: 新鲜橘子
//      *             2: 腐烂橘子
//      * @return 所有新鲜橘子被感染的最少时间，若有无法感染的橘子则返回-1
//      */
//     int orangesRotting(vector<vector<int>>& grid) {
//         // 获取网格的行数和列数
//         int rows = grid.size();
//         if (rows == 0) return 0;  // 空网格直接返回0
//         int cols = grid[0].size();
        
//         // 队列用于存储腐烂橘子的坐标，实现BFS
//         queue<pair<int, int>> rottenQueue;
//         // 统计新鲜橘子的数量，用于判断最终是否全部被感染
//         int freshCount = 0;
        
//         // 第一步：初始化队列和统计新鲜橘子
//         for (int i = 0; i < rows; ++i) {
//             for (int j = 0; j < cols; ++j) {
//                 // 如果是腐烂橘子，加入队列
//                 if (grid[i][j] == 2) {
//                     rottenQueue.push({i, j});
//                 }
//                 // 如果是新鲜橘子，计数加1
//                 else if (grid[i][j] == 1) {
//                     freshCount++;
//                 }
//             }
//         }
        
//         // 特殊情况1：没有新鲜橘子，不需要时间
//         if (freshCount == 0) {
//             return 0;
//         }
        
//         // 特殊情况2：没有腐烂橘子但有新鲜橘子，无法感染
//         if (rottenQueue.empty()) {
//             return -1;
//         }
        
//         // 定义四个方向的偏移量：上、下、左、右
//         vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//         // 记录所需时间
//         int time = 0;
        
//         // 第二步：BFS扩散过程
//         // 当队列不为空且仍有新鲜橘子时继续扩散
//         while (!rottenQueue.empty() && freshCount > 0) {
//             // 每处理一层腐烂橘子，时间加1（代表一分钟）
//             time++;
            
//             // 当前层腐烂橘子的数量（同一时间点的腐烂橘子）
//             int currentLevelSize = rottenQueue.size();
            
//             // 处理当前层的所有腐烂橘子
//             for (int i = 0; i < currentLevelSize; ++i) {
//                 // 取出队列前端的腐烂橘子坐标
//                 auto current = rottenQueue.front();
//                 rottenQueue.pop();
                
//                 int x = current.first;  // 当前腐烂橘子的行坐标
//                 int y = current.second; // 当前腐烂橘子的列坐标
                
//                 // 检查四个方向的相邻单元格
//                 for (auto& dir : directions) {
//                     // 计算相邻单元格的坐标
//                     int newX = x + dir.first;
//                     int newY = y + dir.second;
                    
//                     // 检查相邻单元格是否有效（在网格范围内且是新鲜橘子）
//                     if (newX >= 0 && newX < rows &&  // 行坐标有效
//                         newY >= 0 && newY < cols &&  // 列坐标有效
//                         grid[newX][newY] == 1) {     // 是新鲜橘子
                        
//                         grid[newX][newY] = 2;        // 将新鲜橘子感染为腐烂橘子
//                         freshCount--;                // 新鲜橘子数量减1
//                         rottenQueue.push({newX, newY});  // 将新腐烂的橘子加入队列
//                     }
//                 }
//             }
//         }
        
//         // 第三步：判断结果
//         // 如果所有新鲜橘子都被感染，返回时间；否则返回-1
//         return freshCount == 0 ? time : -1;
//     }
// };


class Solution {
public:
    /**
     * 计算腐烂橘子扩散感染所有新鲜橘子所需的最少时间
     * @param grid 表示橘子网格的二维向量，其中：
     *             0: 空单元格
     *             1: 新鲜橘子
     *             2: 腐烂橘子
     * @return 所有新鲜橘子被感染的最少时间，若有无法感染的橘子则返回-1
     */
    int orangesRotting(vector<vector<int>>& grid) {
        int row = grid.size();
        if(!row) return 0;
        int col = grid[0].size();

        queue<pair<int, int>> rottenQueue;
        int freshCount = 0;
        //双循环初始化队列和新鲜橘子数量
        for(int i=0; i < row; i++)
        {
            for(int j=0; j< col ; j++)
            {
                //是腐烂橘子
                if(grid[i][j]==2)
                {
                    rottenQueue.push({i,j});
                }
                else if(grid[i][j]==1)
                {
                    freshCount++;
                }
            }
        }

        //简单情况先处理
        if(freshCount == 0)
        {
            return 0;
        }
        if(rottenQueue.empty())
        {
            return -1;
        }

        vector<pair<int,int>> direction  = {{-1,0}, {1,0} , {0,-1}, {0,1}}; //方向，方便后续使用
        int time = 0; // 遍历过程中记录时间。


        //开始bfs，当队列不为空且仍有新鲜橘子时继续扩散
        //从队列里的腐烂橘子开始往四个方向遍历，新的腐烂橘子就加入队列
        //while每一次循环就是 1 分钟的遍历（处理一层）
        while(!rottenQueue.empty() && freshCount>0)
        {
            time++;

            //处理当前层的烂橘子扩散（取所有队列元素进行处理）  
            int currentlevelsize = rottenQueue.size();

            //这一层循环处理一层的遍历（出一层腐烂橘子数量的队列）
            for(int i = 0; i < currentlevelsize; i++)
            {
                auto current  = rottenQueue.front(); 
                rottenQueue.pop(); //出队列

                //当前处理橘子坐标
                int x = current.first;
                int y = current.second;

                //处理当前坐标上下左右四个方向相邻橘子
                for(auto dir : direction) // dir: pair<int, int>
                {
                    int newx = x + dir.first;
                    int newy = y + dir.second;

                    //处理前检查 不越界并且当前处理的上下左右是新鲜橘子
                    if( newx < row && newx >= 0 &&
                        newy >= 0 && newy < col &&
                        grid[newx][newy] == 1
                    )
                    {
                        grid[newx][newy] = 2;
                        freshCount--;
                        rottenQueue.push({newx, newy});
                    }
                }

            }

        }
        //while 结束; 直接根据 time 判断是否所有橘子都被感染
        return freshCount == 0 ? time : -1;
    }
};




int main() {
    Solution solution;
    
    // 测试用例1：正常情况，所有橘子可被感染
    vector<vector<int>> grid1 = {
        {2, 1, 1},
        {1, 1, 0},
        {0, 1, 1}
    };
    cout << "测试用例1结果: " << solution.orangesRotting(grid1) << endl;  // 预期输出: 4
    
    // 测试用例2：存在无法感染的橘子（角落的橘子被空单元格隔离）
    vector<vector<int>> grid2 = {
        {2, 1, 1},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << "测试用例2结果: " << solution.orangesRotting(grid2) << endl;  // 预期输出: -1
    
    // 测试用例3：只有腐烂橘子，没有新鲜橘子
    vector<vector<int>> grid3 = {
        {0, 2}
    };
    cout << "测试用例3结果: " << solution.orangesRotting(grid3) << endl;  // 预期输出: 0
    
    // 测试用例4：没有腐烂橘子但有新鲜橘子（无法感染）
    vector<vector<int>> grid4 = {
        {1, 1, 0},
        {0, 1, 1},
        {1, 0, 1}
    };
    cout << "测试用例4结果: " << solution.orangesRotting(grid4) << endl;  // 预期输出: -1
    
    // 测试用例5：全部是腐烂橘子
    vector<vector<int>> grid5 = {
        {2, 2, 0},
        {0, 2, 2},
        {2, 0, 2}
    };
    cout << "测试用例5结果: " << solution.orangesRotting(grid5) << endl;  // 预期输出: 0
    
    return 0;
}
    