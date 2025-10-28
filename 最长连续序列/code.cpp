#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;

// class Solution {
// public:
// 	int longestConsecutive(vector<int>& nums) {

// 		unordered_set <int> numset;
// 		for (int &num : nums) {
// 			numset.insert(num);
// 		}

// 		int res = 0;
// 		int current_len = 0;
// 		int current_num;

// 		for (const int &it : numset) {
// 			if (!numset.count(it - 1)) {
// 				current_len = 1;
// 				current_num = it;

// 				while (numset.count(current_num + 1)) {
// 					current_len++;
// 					current_num++;
// 				}
// 			}f

// 			res = max(res, current_len);
// 		}
// 		return res;

// 	}
// };

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
		//放入哈希表 + 去重

		unordered_set<int> numset;
		for(const auto & num : nums)
		{
			numset.emplace(num);
		}

		int ans = 0;
		int current_len = 0;
		int current_num = 0;

		for(const auto & it : numset)
		{
			//判断是否一个连续序列的开头，如果前一个数没有的话就是
			if(numset.find( it-1 ) == numset.end())
			{
				current_len = 1;
				current_num = it;

				//从这个数开始向后查找下一个数，每找到一个数，当前len++，直到连续序列结束
				while( numset.find( current_num+1 ) != numset.end())
				{
					current_len++;
					current_num++;
				}
			}
			ans = max(ans,current_len);
		}
		return ans;
	
    }
};

int main() {
	Solution s;
	vector<int> nums = {100, 4, 200, 1, 3, 2};
	int res;
	res = s.longestConsecutive(nums);
	cout << res;
	return 0;
}
