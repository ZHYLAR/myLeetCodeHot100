
// 输入：nums = [-1,0,1,2,-1,-4]
// 输出：[[-1,-1,2],[-1,0,1]]
// 解释：
// nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
// nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
// nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
// 不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
// 注意，输出的顺和为K的子数组序和三元组的顺序并不重要。

// [-4 -1 -1 0 1 2]

#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;

//class Solution {
//public:
//    vector<vector<int>> threeSum(vector<int>& nums) {
//        int n = nums.size();
//        sort(nums.begin(),nums.end());
//        vector<vector<int>> res; 
//        for (int first=0; first<n; first++) //一层循环，第一个数
//        {
//			//重要，去重
//            if(first>0 && nums[first] == nums[first-1]){
//                continue;
//            }
//            
//            int third  = n - 1; // 1从最后一位开始找
//            int target = -nums[first];
//            for (int second = first+1 ; second < n; second++)//二层循环，移动第二三个指针找target
//            {
//                if(second>first+1 && nums[second-1] == nums[second])
//                {
//                    continue;
//                }
//                
//                
//                while(second<third && nums[second]+nums[third] > target)
//                {
//                    third--;
//                }
//
//                if(nums[second]+nums[third] < target)
//                {
//                    continue;
//                }
//
//                if(second == third)
//                {
//                    break;
//                }
//
//                if(nums[second]+nums[third] == target)
//                {
//                    res.push_back({nums[first], nums[second], nums[third]});
//                }
//
//            }
//            
//
//            
//        }
//               
//        return res;
//    }
//};

//用三个指正，重点在于去重复
class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		int n = nums.size();
		sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		// 枚举 a
		for (int first = 0; first < n; ++first) {
			// 需要和上一次枚举的数不相同
			if (first > 0 && nums[first] == nums[first - 1]) {
				continue;
			}
			// c 对应的指针初始指向数组的最右端
			int third = n - 1;
			int target = -nums[first];
			// 枚举 b
			for (int second = first + 1; second < n; ++second) {
				// 需要和上一次枚举的数不相同
				if (second > first + 1 && nums[second] == nums[second - 1]) {
					continue;
				}
				// 需要保证 b 的指针在 c 的指针的左侧
				while (second < third && nums[second] + nums[third] > target) {
					--third;
				}
				// 如果指针重合，随着 b 后续的增加
				// 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
				if (second == third) {
					break;
				}
				if (nums[second] + nums[third] == target) {
					ans.push_back({nums[first], nums[second], nums[third]});
				}
			}
		}
		return ans;
	}
};



int main() {
	Solution s;
	vector<int> nums = {1,-1,-1,0};
	vector<vector<int>> res;
	res = s.threeSum(nums);

    for (auto vecit : res)
    {
        for (auto it : vecit)
        {
            cout << it << ' ' ;
        }
        cout << endl;
        
    }
    // int a;
    // cin >> a;
	return 0;
}
