
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // int right,down,left,up;
        int i=0,j=0;
        int visited_cnt = 0;
        const int m = matrix.size();
        const int n = matrix[0].size();
        vector<int> ans;
        ans.reserve(m*n);

        while (visited_cnt < m*m)
        {
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

			j--
             while (1) //向左
            {
                if(j==-1) {j=0 ; break;}
                if(matrix[i][j] == 101) {j++; break;}

                ans.emplace_back(matrix[i][j]);
                visited_cnt++;
                matrix[i][j] = 101;
                j--;
            }
            
        }

        return ans;
    }
};


int main() {
	Solution s;
    vector<int> ans;
    vector<vector<int>> matrix = {{1,2,3}, {4,5,6}};
    ans = s.spiralOrder(matrix);
	for(const auto &x : ans){
        cout << x << " "<<endl;
    }
	// cout << ans;
    return 0;
}
