
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // int right,down,left,up;
        int i=0,j=-1; //行\列 指针 第一次进入循环j++，所以j设置为-1
        int visited_cnt = 0;
        const int m = matrix.size();
        const int n = matrix[0].size();
        vector<int> ans;
        ans.reserve(m*n);

        while (visited_cnt < m*n)
        {
			j++;
            while (1)//向右
            {
                //退出条件 -> 指针归位并退出循环
                if(j==n) {j = n-1; break;}
                if(matrix[i][j] == 101) { j--; break;}

                ans.emplace_back(matrix[i][j]);
                visited_cnt++;
                matrix[i][j] = 101;
                j++;
            }        
            
			i++; //先向下走一步
            while (1) //向下
            {
                if(i==m) {i = m-1 ; break;}
                if(matrix[i][j] == 101) {i--; break;}

                ans.emplace_back(matrix[i][j]);
                visited_cnt++;
                matrix[i][j] = 101;
                i++;
            }

			j--;
             while (1) //向左
            {
                if(j==-1) {j=0 ; break;}
                if(matrix[i][j] == 101) {j++; break;}

                ans.emplace_back(matrix[i][j]);
                visited_cnt++;
                matrix[i][j] = 101;
                j--;
            }
            
			
			i--;
			while(1){
				if(i==-1) {i = 0 ; break;}
				if(matrix[i][j] == 101) {i++; break;}
				
				ans.emplace_back(matrix[i][j]);
				visited_cnt++;
				matrix[i][j] = 101;
				i--;
			}
        }

        return ans;
    }
};


int main() {
	Solution s;
    vector<int> ans;
//    vector<vector<int>> matrix = {{1,2,3}, {4,5,6},{7,8,9}};
//	vector<vector<int>> matrix  = {{1,2,3}};
//	vector<vector<int>> matrix  = {{1}};
		vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    ans = s.spiralOrder(matrix);
	for(const auto &x : ans){
        cout << x << " ";
    }
	// cout << ans;
    return 0;
}


// #include<iostream>
// #include<vector>

// using namespace std;

// class Solution {
// public:
//     vector<int> spiralOrder(vector<vector<int>>& matrix) {
//         // 处理空矩阵的边界情况
//         if (matrix.empty() || matrix[0].empty()) {
//             return {};
//         }

//         int i = 0, j = -1; // 行/列指针，j初始化为-1以配合第一次向右的循环
//         const int m = matrix.size();
//         const int n = matrix[0].size();
//         const int total_elements = m * n;
//         vector<int> ans;
//         ans.reserve(total_elements); // 预分配内存，提高效率

//         // 当ans中的元素数量未达到总数时，继续循环
//         while (ans.size() < total_elements) {
//             // ---> 向右
//             // 循环条件：j没有越过右边界(j < n) 且 下一个位置未被访问过
//             for (j++; j < n && matrix[i][j] != 101; j++) {
//                 ans.emplace_back(matrix[i][j]);
//                 matrix[i][j] = 101; // 标记为已访问
//             }
//             j--; // 循环结束后j多走了一步，需要退回一格以保证位置正确

//             // | 向下
//             // V
//             for (i++; i < m && matrix[i][j] != 101; i++) {
//                 ans.emplace_back(matrix[i][j]);
//                 matrix[i][j] = 101;
//             }
//             i--; // 指针归位

//             // <--- 向左
//             for (j--; j >= 0 && matrix[i][j] != 101; j--) {
//                 ans.emplace_back(matrix[i][j]);
//                 matrix[i][j] = 101;
//             }
//             j++; // 指针归位

//             // ^ 向上
//             // |
//             for (i--; i >= 0 && matrix[i][j] != 101; i--) {
//                 ans.emplace_back(matrix[i][j]);
//                 matrix[i][j] = 101;
//             }
//             i++; // 指针归位
//         }

//         return ans;
//     }
// };

// // main 函数保持不变
// int main() {
// 	Solution s;
//     vector<int> ans;
// 	vector<vector<int>> matrix = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
//     ans = s.spiralOrder(matrix);
// 	for(const auto &x : ans){
//         cout << x << " ";
//     }
//     cout << endl;
//     return 0;
// }