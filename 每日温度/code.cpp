#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> s;
        
        //栈用于存储 尚未找到更高温度的日期的索引   
        //栈中的索引对应的温度是单调递减的。
        for (int i = 0; i < n; ++i) {
            //当当前温度大于栈顶索引对应的温度时，说明找到了更高的温度
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) {
                int previousIndex = s.top();//弹出栈顶元素，获取之前未找到更高温度的日期的索引
                ans[previousIndex] = i - previousIndex;//差值，即等待天数
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};


/*

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans;
        ans.resize(n);
        stack<int> unsolve_index;

        for(int i=0; i<n; i++)
        {
            while(!unsolve_index.empty() && temperatures[unsolve_index.top()] < temperatures[i] )
            {
                int temp_index =  unsolve_index.top();
                ans[ temp_index ] = i - temp_index;
                unsolve_index.pop();
            }

            unsolve_index.push(i);
        }

        return ans;

    }
};*/

int main() {
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    Solution sol;
    vector<int> ans = sol.dailyTemperatures(temperatures);
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}