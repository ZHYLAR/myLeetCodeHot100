class Solution {
public:
    bool isValid(string s) {
        //如果字符串长度是奇数，先排除
        if(s.size() & 1)
        {
            return false;
        }

        //提高可扩展性
        unordered_map<char, char> pairs = 
        {
            {'(', ')'},
            {'[', ']'},
            {'{', '}'}
        };

        stack<char> stk;
        for(const char &c : s)
        {
            if(pairs.count(c))
            {
                stk.push(c);
            }
            else
            {
                if(stk.empty() || pairs[stk.top()] != c)
                {
                    return false;
                }
                stk.pop();
            }
        }

        if(stk.empty())
        {
            return true;
        }
        return false;
    }
};