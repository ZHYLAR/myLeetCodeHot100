#include<iostream>
#include<vector>
//#include<unordered_set>
#include<unordered_map>
#include<algorithm>
//#include<string.h>
//#include<bits/stdc++.h>

using namespace std;
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> pTable(26), sTable(26); //单词表，用于判断两个 string 是否为字母异位
		int sLen = s.size();
		int pLen = p.size();
		vector<int> ans(0);

		//s 比 p 短，简单样例先输出
		if(sLen < pLen)
		{
			return ans;
		}

		//先判断第一组，后续循环只需要加入新字母，删去旧字母
		for(int i=0 ; i<pLen ; i++)
		{
			pTable[p[i]-'a']++;
			sTable[s[i]-'a']++;
		}
		if(sTable == pTable)
		{
			ans.emplace_back(0);
		}

		//开始移动窗口
		int right = pLen;//窗口右侧边界，窗口内的最后一个数
		int left = 0; //窗口移动前的第一个数，也就是新窗口要丢出去的数
		for(right = pLen; right < sLen ; right++)
		{
			sTable[s[right]-'a']++;
			sTable[s[left]-'a']--;
			if(sTable == pTable)
			{
				ans.emplace_back(left+1);
			}

			//窗口长度不变，这里缩小窗口可以无脑++
			left++;
		}

		return ans;

    }
};

// //使用哈希表的版本, 这个比用 vector 慢很多
// class Solution {
// public:
// 	unordered_map<char,int> pTable, sTable; //单词表，用于判断两个 string 是否为字母异位

// 	bool check_map()
// 	{
// 		for(const auto &it : pTable)
// 		{
// 			if(pTable[it.first] != sTable[it.first])
// 			{
// 				return 0;
// 			}
// 		}
// 		return 1;
// 	}

//     vector<int> findAnagrams(string s, string p) {
        
// 		int sLen = s.size();
// 		int pLen = p.size();
// 		vector<int> ans(0);

// 		//s 比 p 短，简单样例先输出
// 		if(sLen < pLen)
// 		{
// 			return ans;
// 		}

// 		//先判断第一组，后续循环只需要加入新字母，删去旧字母
// 		for(int i=0 ; i<pLen ; i++)
// 		{
// 			pTable[p[i]]++;
// 			sTable[s[i]]++;
// 		}
		
// 		if(check_map())
// 		{
// 			ans.emplace_back(0);
// 		}

// 		//开始移动窗口
// 		int right = pLen;//窗口右侧边界，窗口内的最后一个数
// 		int left = 0; //窗口移动前的第一个数，也就是新窗口要丢出去的数
// 		for(right = pLen; right < sLen ; right++)
// 		{
// 			sTable[s[right]]++;
// 			sTable[s[left]]--;
// 			if(check_map())
// 			{
// 				ans.emplace_back(left+1);
// 			}

// 			//窗口长度不变，这里缩小窗口可以无脑++
// 			left++;
// 		}

// 		return ans;

//     }
// };

// class Solution {
// public:
// 	vector<int> findAnagrams(string s, string p) {
// 		vector<int> targetLetterTable(26);
// 		vector<int> stringLetterTable(26);
// 		int targetLen = p.size();
// 		int strlen = s.size();
// 		int flag;
// 		int loop = strlen - targetLen;
// 		vector<int> ans = {};
// 		if(targetLen==0) return ans;
		
// 		for(int i = 0; i < targetLen; ++i){
// 			targetLetterTable[s[i] - 'a']++; 
// 			stringLetterTable[p[i] - 'a']++;
// 		}
		
// 		if(stringLetterTable==targetLetterTable)
// 		{
// 			ans.push_back(0);
// 		}
		
// 		for(int i=0;i < loop ;i++)// 滑动窗口循环
// 		{
// 			stringLetterTable[s[i]-'a']--;
// 			stringLetterTable[s[i+targetLen]-'a']++;
			
// 			if(stringLetterTable==targetLetterTable)
// 			{
// 				ans.push_back(i+1);
// 			}
			
// 		}
		
// 		return ans;
// 	}
// };

//class Solution {
//public:
//	vector<int> findAnagrams(string s, string p) {
//		unordered_map<char,int> targetLetterTable;
//		unordered_map<char,int> stringLetterTable;
//		int targetLen = p.length();
//		int strlen = s.length();
//		int loop = strlen - targetLen;
//		vector<int> ans = {};
//		if(targetLen==0) return ans;
//		
//		for(auto letter : p){
//			targetLetterTable[letter]++; 
//		}
//		
//		for(int i=0;i <= loop ;i++)// 滑动窗口循环
//		{
//			stringLetterTable.clear();
////			if(targetLetterTable.count(s[i+targetLen]) == 0) {i = i+targetLen-1; break; }
//			for(int j=0 ;j < targetLen ;j++){ // 窗口内循环
//				if(targetLetterTable.count(s[i+j]) == 0) {i = i+j; break; }
//				stringLetterTable[s[i+j]]++;
//			}
//			
//			if(stringLetterTable == targetLetterTable)
//			{
//				ans.push_back(i);
//			}
//		}
//		
//		return ans;
//	}
//};


int main() {
	Solution solution;
	string s = "abaa";
	string p = "a";
	vector<int> ans;
//
	ans = solution.findAnagrams(s,p);

	for(const auto it : ans)
	{
		cout << it << " ";
	}
	cout << endl;
	return 0;
}
