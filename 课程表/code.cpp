#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
题目的本质是构建一个有向图结构，如果图不成环就可以修完

需要构造一个邻接表和入度数组
邻接表 edge[u] 表示 u出发指向的节点 (u 课程修之后能修的课程)
入度数组indeg[v] 表示 v的入度数量（先修课数量）

从indeg = 0 的节点出发（无先修或先修已经修完的节点），每处理一个节点（修了这个课程），这个节点指向的其他节点入度--
每次循环用一个队列记录下一轮可以修的课程，类似 BFS

如果图未成环，则可以修完（可以遍历完所有节点），最后访问的节点数量等于总节点数量
*/

class Solution {
private:
    /*
    邻接表 edge[u] 表示 u出发指向的节点列表
    入度数组indeg[v] 表示 v的入度数量（先修课数量）
    */
    vector< vector<int> > edges;
    vector<int> indeg;

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		
		//初始化容器大小,保证后续随机访问或写入不越界
        edges.resize(numCourses);
        indeg.resize(numCourses);

        //根据题目给的变量prerequisites 构建 edges 和 indeg
        /*
        // class_pair: vector<int> [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
        // prerequisites其实就是一个特殊形式的邻接表，需要转换一下变成标准的邻接表方便处理。注意 bi 是 ai 的先修，容易弄反
        */
        for(const auto & class_pair : prerequisites) 
        {
            edges[class_pair[1]].emplace_back(class_pair[0]);
            indeg[class_pair[0]]++;
        }

        //入度为 0的课程队列，也就是下一轮可以修读的课程
        queue<int> q;

        //先处理第一轮情况，初始 indeg 就为 0 的课程先放入队列待修
        for(int i=0; i<numCourses ; i++)
        {
            if(indeg[i]==0)
            {
                q.push(i);
            }
        }
        
        //开始 BFS
        int visitedCourse = 0;
        //队列空了就代表没有可以修读的课程了，循环结束
        while (!q.empty())
        {
            visitedCourse++;
            int current_q = q.front();
            q.pop();
            //遍历 current_q 的所有邻接节点，减小他们的入度
            for(const auto &it : edges[current_q])
            {
                indeg[it]--;
                //如果当前节点的indeg 为 0 了，就可以送入队列下一轮修读
                if(indeg[it] == 0)
                {
                    q.push(it);
                }
            }
        }
        
        return visitedCourse == numCourses;
    }
};

// 辅助函数：打印测试结果
void printTestResult(int testCase, int numCourses, const vector<vector<int>>& prerequisites, bool result) {
    cout << "测试用例 " << testCase << ":" << endl;
    cout << "课程总数: " << numCourses << endl;
    cout << "先修课程对: ";
    for (const auto& pair : prerequisites) {
        cout << "[" << pair[0] << "," << pair[1] << "] ";
    }
    cout << endl;
    cout << "是否能完成所有课程: " << (result ? "是" : "否") << endl << endl;
}

int main() {
    Solution solution;
    
    // 测试用例1：简单无环情况
    int testCase1 = 1;
    int numCourses1 = 2;
    vector<vector<int>> prerequisites1 = {{1, 0}};
    bool result1 = solution.canFinish(numCourses1, prerequisites1);
    printTestResult(testCase1, numCourses1, prerequisites1, result1);
    
    // 测试用例2：有环情况
    int testCase2 = 2;
    int numCourses2 = 2;
    vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
    bool result2 = solution.canFinish(numCourses2, prerequisites2);
    printTestResult(testCase2, numCourses2, prerequisites2, result2);
    
    // 测试用例3：多课程无环情况
    int testCase3 = 3;
    int numCourses3 = 4;
    vector<vector<int>> prerequisites3 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
    bool result3 = solution.canFinish(numCourses3, prerequisites3);
    printTestResult(testCase3, numCourses3, prerequisites3, result3);
    
    // 测试用例4：无先修课程情况
    int testCase4 = 4;
    int numCourses4 = 3;
    vector<vector<int>> prerequisites4 = {};
    bool result4 = solution.canFinish(numCourses4, prerequisites4);
    printTestResult(testCase4, numCourses4, prerequisites4, result4);
    
    // 测试用例5：更复杂的有环情况
    int testCase5 = 5;
    int numCourses5 = 5;
    vector<vector<int>> prerequisites5 = {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {0, 4}};
    bool result5 = solution.canFinish(numCourses5, prerequisites5);
    printTestResult(testCase5, numCourses5, prerequisites5, result5);
    
    return 0;
}
