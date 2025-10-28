#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int >>& intervals) {
		vector<vector<int>> ans;
		bool chongdie;
		sort(intervals.begin(), intervals.end());

		int intervals_len = intervals.size();
		if(intervals_len == 1) return intervals;

		vector<int> temp = intervals[0];

		for (int i = 1; i < intervals_len; i++) {

			//四个角都不重叠

//			chongdie = !(intervals[i][1] < temp[0] || intervals[i][0] > temp[1]);
			chongdie = intervals[i][1] >= temp[0] && intervals[i][0] <= temp[1];

			//判断重叠 总长度小于等于分别长度和 或者一个覆盖一个

			if (chongdie) {
				temp = { min (temp[0], intervals[i][0]), max(intervals[i][1], temp[1]) };
			} else {
				ans.emplace_back(temp);
				temp = {intervals[i][0], intervals[i][1]};
			}
		}

		ans.emplace_back(temp); //遍历到最后两个vector，如果重叠，将这一次的合并结果emplace，如果不重叠，还剩下最后一个区间，也是emplace


		return ans;
	}
};

int main() {
	Solution solution;
	vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
	vector<vector<int>> ans;

	ans = solution.merge(intervals);


	return 0;
}
