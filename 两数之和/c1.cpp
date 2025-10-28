//https://leetcode.cn/problems/two-sum/

#include <iostream>
#include <iomanip>
#include <vector>
//#include <stdio.h>
#include <unordered_map>
using namespace std;


//class Solution {
//public:
//	vector<int> twoSum(vector<int>& nums, int target) {
//		int n = nums.size();
//		for (int i = 0; i < n; ++i) {
//			for (int j = i + 1; j < n; ++j) {
//				if (nums[i] + nums[j] == target) {
//					return {i, j};
//				}
//			}
//		}
//		return {};
//	}
//};
//
//class Solution {
//public:
//	vector<int> twoSum(vector<int>& nums, int target) {
//		unordered_map<int, int> hashtable;
//		for (int i = 0; i < nums.size(); ++i) {
//			auto it = hashtable.find(target - nums[i]);
//			if (it != hashtable.end()) {
//				return {it->second, i};
//			}
//			hashtable[nums[i]] = i;
//		}
//		return {};
//	}
//};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
//		int n = nums.size();
		unordered_map<int, int> hashtable;

//		for (int i = 0; i < nums.size(); i++) {
//			hashtable[nums[i]] = i;
//		}

		for (int i = 0; i < (int)nums.size(); i++) {
			auto it = hashtable.find(target - nums[i]);
			if (it != hashtable.end()) {
				return {(*it).second, i};
			}
			hashtable[nums[i]] = i;

		}
		return {};
	}

};

int main() {
	Solution s;
	vector<int> nums = {2, 4, 5, 6, 7, 8, 10};
	vector<int> res = {0, 0};
	res = s.twoSum(nums, 6);
	for (int i = 0; i < (int)res.size(); i++) {
		cout << res[i] << " ";
	}

//	for(auto it = res.begin();it!=res.end(); it++){
//		cout << *it << " ";
//	}
//	cout >> s.twoSum(nums,8);


	return 0;
}

//int main()
//{
//	vector<int> a;
//	a.push_back(1);a.push_back(2);
////	cout << a.size() << endl;
//	for(auto i=a.begin();i!=a.end();i++){
//		cout << *i << endl;
////		printf("%d\n",*i);
//	}
//
//	for(int i=0;i<a.size();i++){
//		cout << a[i] << endl;
//	}
//
//
//	cout<<fixed<<setprecision(6);
////	cout<<6.666;
//	return 0;
//}
