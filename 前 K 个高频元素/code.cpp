class Solution {
public:
    // 静态比较函数，用于定义优先队列的排序规则
    // 比较两个pair对象，pair的第一个元素是数组元素值，第二个元素是该值的出现次数
    // 返回true表示m的出现次数大于n的出现次数，即按出现次数从大到小排序
    class compare{
        public:
        bool operator()(pair<int, int>& m, pair<int, int>& n) {
            return m.second > n.second;
        }
    };


    // 主函数：找出数组中出现次数前k多的元素
    // 参数：nums为输入数组，k为需要返回的高频元素个数
    // 返回值：包含前k个高频元素的vector
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 哈希表：键为数组中的元素值，值为该元素出现的次数，用于统计频率
        unordered_map<int, int> occurrences;
        for (auto& v : nums) {
            // 遍历数组，对每个元素的出现次数进行计数
            occurrences[v]++;
        }

        // 定义优先队列（堆），用于维护出现次数前k多的元素
        // 队列元素为pair<int, int>：(元素值, 出现次数)
        // 底层容器使用vector<pair<int, int>>
        // 比较器使用上面定义的cmp函数，结合优先队列的特性，这里实际会形成一个"小顶堆"
        // （优先队列默认是大顶堆，使用自定义cmp后，堆顶会是出现次数最小的元素）
        priority_queue<pair<int, int>, vector<pair<int, int>>, compare> q;
        
        // 遍历哈希表中的每个元素及其出现次数
        for (auto& [num, count] : occurrences) {
            // 如果队列中已有k个元素，需要判断当前元素是否比队列中出现次数最少的元素更频繁
            if (q.size() == k) {
                // 若当前元素的出现次数大于堆顶元素（队列中出现次数最少的），则替换
                if (q.top().second < count) {
                    q.pop();           // 弹出出现次数最少的元素
                    q.emplace(num, count);  // 加入当前更频繁的元素
                }
            } else {
                // 若队列元素不足k个，直接加入当前元素
                q.emplace(num, count);
            }
        }
        
        // 收集结果：从优先队列中取出所有元素，这些元素即为前k个高频元素
        vector<int> ret;
        while (!q.empty()) {
            // 取出堆顶元素的键（元素值），加入结果集
            ret.emplace_back(q.top().first);
            q.pop();
        }
        
        return ret;
    }
};



/* 优先队列实现 */

//扫描一遍序列，统计哈希表 频次-元素 On
//利用小根堆\priority_queue，取前k个频次 O n*logk
//遍历这k个频次，累加直到获取到k个元素就结束

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        
        unordered_map<int, int> umap1; //元素 - 频次
        unordered_map<int, vector<int> > umap2; //频次 - 元素列表
        priority_queue<int> pqueue;// 频次的优先队列
        vector<int> ans;
        // vector<int> tmp(k);

        for(const int &i : nums)
        {
            umap1[i]++;
        }

        for(auto &i : umap1)
        {
            umap2[i.second].emplace_back(i.first);
        }

        for(auto &i : umap2)
        {
            pqueue.push(i.first);
        }

        int flag = k;//需要插入的剩余个数

        while(flag > 0)
        {
            //pqueue顶对应列表, 当前频次最高的元素列表
            auto pqDingYuanSu = umap2[pqueue.top()];

             //pqueue顶对应列表的元素个数
            int pqDingYuanSuGeShu = pqDingYuanSu.size();

            // if(flag > pqDingYuanSuGeShu)
            // {
                for(int i=0; i<pqDingYuanSuGeShu; i++)
                {
                    ans.emplace_back( pqDingYuanSu[i] );
                }
                flag -= pqDingYuanSuGeShu;
                pqueue.pop();      
            // }
    
        }

        return ans;
    }
};