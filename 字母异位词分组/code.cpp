#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<string> // 需包含string头文件用于字符串操作

using namespace std;

// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         unordered_map<string, vector<string>> mp; // 键：频率字符串，值：异位词组
//         vector<vector<string>> ans;

//         for(const auto &str : strs) {
//             vector<int> count(26, 0); // 统计每个字母的出现次数
//             for(char c : str) {
//                 count[c - 'a']++; // 对应字母位置计数+1
//             }

//             // 构建键：将每个字母的频率用"#"分隔（例如 "1#0#1#..."）
//             string key;
//             for(int i = 0; i < 26; i++) {
//                 key += to_string(count[i]) + "#"; // 拼接频率和分隔符
//             }

//             mp[key].push_back(str); // 相同键的字符串放入同一组
//         }

//         // 将哈希表中的值收集到结果中
//         for(const auto &pair : mp) {
//             ans.push_back(pair.second);
//         }

//         return ans;
//     }
// };


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
		//map： 排序后str - 原str的列表
		unordered_map <string, vector<string>> mp;
		vector<vector<string>> ans;
		for(string &str : strs)
		{
			string key = str;
			sort(key.begin(),key.end());
			mp[key].emplace_back(str);
		}


		for(const auto &it : mp) {
			ans.emplace_back(it.second); // 正确！it.second是vector，直接传入
		}

        return ans;
    }
};

// class Solution {
// public:
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         unordered_map<string, vector<string>> mp;
//         for (string& str: strs) {
//             string key = str;
//             sort(key.begin(), key.end());
//             mp[key].emplace_back(str);
//         }
//         vector<vector<string>> ans;
//         for (auto it = mp.begin(); it != mp.end(); ++it) {
//             ans.emplace_back(it->second);
//         }
//         return ans;
//     }
// };


int main() {
    Solution s;
    vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> ans = s.groupAnagrams(strs);

    // 打印结果
    for(const auto &group : ans) {
        cout << "[";
        for(const auto &str : group) {
            cout << "\"" << str << "\", ";
        }
        cout << "], ";
    }
    // 输出应为：["eat", "tea", "ate", ], ["tan", "nat", ], ["bat", ], 

    return 0;
}
