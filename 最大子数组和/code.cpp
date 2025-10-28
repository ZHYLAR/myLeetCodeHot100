#include<iostream>
#include<vector>
// #include<unordered_set>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>


// dp[i] : 以i数字结尾的串中最大子序和
// dp[i] = max(dp[i-1]+nums[i] , nums[i])
// ans = max(dp)

using namespace std;

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
//		int nums_len = nums.size();
//		vector<int> dp(nums_len+1);
//		dp[0] = nums[0];
//		int ans = nums[0];
//		for (int i = 1; i < nums_len; i++) {
//			dp[i] = max(dp[i - 1] + nums[i], nums[i]);
//			ans = max(dp[i], ans);
//		}
		
		int dp = nums[0];
		int ans = nums[0];
		
		for(int i=1; i < (int) nums.size(); i++){
			dp = max(dp+nums[i], nums[i]);
			ans = max(dp, ans);
		}
		
		return ans;
	}
};



int main() {
	Solution solution;
	vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
	int ans;
	ans = solution.maxSubArray(nums);
	cout << ans << endl;
	return 0;
}
