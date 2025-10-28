#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
// #include<string.h>
// #include<bits/stdc++.h>

using namespace std;
/*
滑动窗口模板：
//外层循环扩展右边界，内层循环扩展左边界
for (int r = 0, r = 0 ; r < n ; r++) {
	//当前考虑的元素
	while (l <= r && check()) {//区间[left,right]不符合题意
		//扩展左边界
	}
	//区间[left,right]符合题意，统计相关信息
}

*/
// 右指针右移，扩大窗口，如果扩大到不满足非重复条件了，左指针收缩，直到再次满足条件
class Solution
{
public:
	int lengthOfLongestSubstring(string s)
	{
		unordered_set<char> letterSet;
		int ans = 0;
		int left = 0, right = 0;
		int n = s.length();
		for (right = 0; right < n; right++)
		{
			char ch = s[right]; // 记录当前右指针的char

			//用while缩小窗口，直到set内没有右指针指向的char
			while (letterSet.count(ch))
			{
				letterSet.erase(s[left]);
				left++;
			}
			letterSet.insert(s[right]);
			ans = max(ans, right-left+1);
			
		}
	}
};

// class Solution {
// public:
// 	int lengthOfLongestSubstring(string s) {
// //			string  s = "abcabcbb";
// 		unordered_set<int> letter_table;
// //		int current_len = 1;
// 		int left, right=0;
// 		int strlen = s.size();
// 		int res=0;
// 		if(strlen==0) return 0;
// 		if(strlen==1) return 1;
// //		char current_char;
// 		for (left = 0; left < strlen; left++) {
// 			//左指针循环
// 			// letter_table.insert(s[left]);
// //			current_len = 1;

// 			if(left!=0) letter_table.erase(s[left-1]);

// 			while(right<strlen && letter_table.count(s[right]) == 0) {
// 				letter_table.insert(s[right]);
// 				right++;
// 			}

// 			res = max(right-left,res);

// 		}

// 		return res;
// 	}
// };

int main()
{
	Solution solution;
	string s = "abcaccbb";
	// string  s = "aaaaccc";
	int res;
	res = solution.lengthOfLongestSubstring(s);
	cout << res << endl;
	return 0;
}
