#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
//#include<cmath>
//#include<string.h>
//#include<bits/stdc++.h>
#include <limits.h>
//#include<cmath>

using namespace std;


class Solution {
public:
	
	unordered_map<char,int> ori,cnt; // ori: 字符串t的词频 ； cnt 当前窗口里的词频
	
	bool check()
	{
		for(const auto &it : ori)
		{
			if(cnt[it.first] < it.second)
			{
				return false;
			}
		}
		return true;
	}
	
	string minWindow(string s, string t) {
		//统计t中词频
		for(const auto & s_char : t)
		{
			ori[s_char]++;
		}
		
		//滑动窗口下标
		int l = 0;//左
		int r = -1;//右
		int s_len = s.size();
		int win_len = INT_MAX;
		int ansL = -1; //初始值设置为-1 ，后续用于区分找不到解的情况
		
		while(r<s_len){
			
			if(ori.count(s[++r])){ //如果下一个位置的单词有出现在 t 里。 （无关字符不需要统计）
				cnt[s[r]]++;
			}
			
			//移动左下标
			while(l <= r && check())
			{
				if(r-l+1 < win_len) //是否扫描到了更优的解 ，是的话更新
				{
					win_len = r-l+1;
					ansL = l;
				}
				
				if(ori.count(s[l]))
				{
					cnt[s[l]]--;
				}
				l++;
			}
		}
		
		return ansL==-1 ? "" : s.substr(ansL, win_len);
		
	}
};

int main() {
//	cout << INT_MAX;
	Solution solution;
	string ans;
	string s = "abckmg";
	string t = "kmg";
	ans = solution.minWindow(s, t);
	cout << ans << endl;
	return 0;
}
