
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;


class Solution {
public:
	
	void setZeroes(vector<vector<int>>& matrix) {
		int m = matrix.size(); //行
		int n = matrix[0].size();// 列
		bool mE0=0, nE0=0;
		
		
		/*
		-------------------------
		记录行是否存在0 & 列是否存在0
		*/
		for (int i=0; i<m ;i++)
		{
			if(matrix[i][0] == 0){
				nE0 = 1;
				// break;
			}
		}
		
		for (int j=0; j<n ; j++)
		{
			if(matrix[0][j]==0)
			{
				mE0 = 1;
				// break;
			}
		}
		
		/*
		-------------------------
		记录矩阵内容是否存在0，用第0行\第0列存储
		*/
		
		for(int i = 1; i< m ; i++) {
			for(int j = 1; j<n; j++) {
				if(matrix[i][j]==0)
				{
					matrix[i][0] = 0;
					matrix[0][j] = 0;
				}
			}
		}
		
		/*
		-------------------------
		根据第一行第一列0的情况，更新矩阵内容。
		*/
		for(int i = 1; i< m ; i++) {
			for(int j = 1; j<n; j++) {
				if(matrix[i][0]==0 || matrix[0][j]==0){
					matrix[i][j] = 0;
				}
			} 
		}
		
		/*
		-------------------------
		单独处理第一行和第一列
		*/
		if(mE0)
		{
			for(int j=0;j<n;j++){
				matrix[0][j] = 0;
			}
		}
		
		if(nE0)
		{
			for(int i=0;i<m;i++){
				matrix[i][0] = 0;
			}
		}
		
		return;
	}
};

int main() {
	Solution s;
	//  vector<vector<int>> matrix ={{1,1,1},{1,0,1},{1,1,1}} ;
//     vector<vector<int>> matrix = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
	vector<vector<int>> matrix = {{1,0,3}};
	s.setZeroes(matrix);

//	cout << ans;
	return 0;
}
