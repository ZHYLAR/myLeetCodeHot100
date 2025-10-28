#include<iostream>
#include<vector>
// #include<unordered_set>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
		unordered_map<int,int> mp;
		int current_sum=0;
		int ans=0;
		mp[0] = 1;

		for(auto i : nums)
		{
			current_sum+=i;
			if(mp.count(current_sum-k))
			{
				ans += mp[current_sum-k];
			}
			mp[current_sum]++;
		}
        return ans;
    }
};

int main() {
	Solution solution;
    vector<int> nums = {1,2,3,1,2};
	int res;
	res = solution.subarraySum(nums,3);
	cout << res << endl;
	return 0;
}
