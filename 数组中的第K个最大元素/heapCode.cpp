/*
时间复杂度：
- 单次 push / pop 为 O(log k)。
- 遍历 n 个元素，每个元素最多触发一次 push（堆未满）或一次“push+pop”（堆已满且需要更新）。
- 总体时间复杂度为 O(n log k)；其中前 k 次插入为 O(k log k)，后续为 O((n - k) log k)。

空间复杂度：
- 算法本质空间为 O(k)。
- 但本实现预先将 `heap` resize 为常量 N（1e5+1），导致实际占用为 O(N)。如需更优，建议按需分配或仅 `reserve(k+1)`。
*/

class Solution {
public:
    const int N = 1e5+1;
    
    //用线性表模拟实现一个堆，第一个元素index为1，
    //某个节点索引为index，左子节点索引为index * 2，右index * 2 + 1
    //这里用小根堆，保证节点比它的子节点都大，容量固定为k，最后维护好堆的堆头就是倒数第k小的元素，即第k大的元素
    vector<int> heap;
    
    //初始化堆，将堆元素个数设为0
    Solution(){
        heap.resize(N);
    }
    
    int hSize = 0; //堆的元素个数

    //对索引为index的元素上浮操作
    void up(int index)
    {
        //index / 2为 index节点的父节点
        while((index >> 1) > 0 && heap[ index>>1 ] > heap[index])
        {
            swap(heap[ index>>1 ] , heap[ index ]);
            index = index >> 1;
        }
    }

    void down(int index)
    {
        while(index < hSize)
        {
            int temp = index;
            //如果节点元素比左子节点大，准备向左下沉
            if( index * 2 <= hSize && heap[temp] > heap[index * 2]) temp = index * 2;

            //如果节点元素比右子节点大，改为准备向右下沉
            if( index * 2 + 1 <= hSize && heap[temp] > heap[index * 2 + 1]) temp = index * 2 + 1;

            //如果上述比较条件都没有成立，当前index不用再移动
            if(temp == index) break;
            swap(heap[index],heap[temp]);
            
            //原index元素现在的位置到了temp，更新一下，下一轮继续下沉
            index = temp;
        }
    }

    //往堆里插入一个数
    void push(int num)
    {
        hSize++;
        heap[hSize] = num;
        up(hSize);
    }

    void pop()
    {
        // if(hSize<1) throw "pop error";
        //用最后一个元素取代掉现在的堆头，然后下沉它
        heap[1] = heap[hSize];
        hSize--;
        down(1);
    }

    //取堆顶元素
    int top()
    {
        //可以判断一下，实际上根据数据范围不会越界。
        // return hSize >= 1 ? heap[1] : 0;
        // if(hSize<1) throw "get top error";
        return heap[1];
    }

    int findKthLargest(vector<int>& nums, int k) {
        // int kk = top();
        const int n = nums.size();
        for(int i=0; i<n; i++)
        {
            int temp = nums[i];

            //元素不够，直接塞入堆
            if (hSize < k)
            {
                push(temp);
            }

            //元素够k个了，如果temp比top大，塞入temp下沉，然后把现在的堆头淘汰
            else if( temp > top())
            {
                push(temp);
                pop();
            }

        }

        return top();
    }
};
