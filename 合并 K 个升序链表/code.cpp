#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        auto dummyHead = new ListNode(0);
        auto p1 = head1, p2 = head2;
        auto curr = dummyHead;

        while (p1 && p2)
        {
            if (p1->val <= p2->val)
            {
                curr->next = p1;
                p1 = p1->next;
                curr = curr->next;
            }
            else
            {
                curr->next = p2;
                p2 = p2->next;
                curr = curr->next;
            }
        }
        if (p1)
            curr->next = p1;
        if (p2)
            curr->next = p2;

        auto res = dummyHead->next;
        delete dummyHead;
        return res;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        queue<ListNode *> waitingList;
        int len = lists.size();
        if (!len)
            return nullptr;

        // 压入队列
        for (auto list : lists)
        {
            waitingList.push(list);
        }

        ListNode *l1 = nullptr, *l2 = nullptr;

        // 思想是将队列两两合并，合并结果继续压入队列，直到队空最后得到的结果就是合并后的链表
        while (!waitingList.empty())
        {
            l1 = waitingList.front();
            waitingList.pop();
            if (waitingList.empty())
                return l1;
            else
            {
                l2 = waitingList.front();
                waitingList.pop();
            }

            waitingList.push(merge(l1, l2));
        }

        //这一行 return 啥都行，上面的 return能保证覆盖所有的情况
        return nullptr;
    }
};



/*
简单写法，虽然时间复杂度O(N)、空间复杂度O(1)，但是实际用时会比上面的分治算法多很多

class Solution {
public:

    ListNode* merge(ListNode* head1, ListNode* head2)
    {
        auto dummyHead = new ListNode(0);
        auto p1 = head1, p2 = head2;
        auto curr = dummyHead;

        while(p1&&p2)
        {
            if(p1 -> val <= p2->val)
            {
                curr -> next = p1;
                p1 = p1->next;
                curr = curr->next;
            }
            else{
                curr -> next = p2;
                p2 = p2->next;
                curr = curr->next;
            }
        }
        if(p1) curr->next = p1;
        if(p2) curr->next = p2;

        auto res = dummyHead->next;
        delete dummyHead;
        return res;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        queue<ListNode*> waitingList;
        ListNode* ans = nullptr;
        for(auto list : lists)
        {
            ans = merge(ans, list);
        }
        return ans;
    }
};
*/