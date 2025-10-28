/**
 * 整体原理：
 * 采用自底向上的归并排序算法对链表进行排序，满足时间复杂度O(nlogn)、空间复杂度O(1)
 * 
 * 核心思路（分治思想）：
 * 1. 分：将链表拆分为若干个短链表（从长度1开始，逐步翻倍）
 * 2. 治：每个长度为1的链表天然有序，通过合并操作将两个有序短链表合并为一个更长的有序链表
 * 3. 迭代升级：从长度1→2→4→...→n，逐步合并直到整个链表有序
 * 
 * 为什么用自底向上而非递归：
 * 递归版归并排序会因调用栈产生O(logn)的空间开销，而自底向上通过迭代实现，仅用常数空间
 */

#include <iostream>

// 链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

    //合并两个有序链表
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


    ListNode* sortList(ListNode* head) {
        if(!head)
        {
            return nullptr;
        }
        
        // 示例初始链表：4->2->1->3
        /*
        第一轮长度为 1, 
        取 4,2 merge得到（2,4）然后取 1,3 merge（1,3）
        第二轮长度为 2
        取（2,4）、（1,3） merge （1,2,3,4)

        流程比较复杂，首先需要两个变量 head1、head2，记录需要传给 merge 的两个子链表头
        然后要取 head1、2 的过程中要断开链表
        断开的同时要用一个变量 next 记录后续链表节点的开头，防止丢失地址
        还得有一个变量 prev 将已排序的子链的最后一个元素记录下来，使merge过后的子链表能暂时连接上
        */

        //1计算链表长度
        int length = 0;
        auto p = head;
        while(p)
        {
            p = p->next;
            length++;
        }

        auto dummy = new ListNode(0,head);

        // 2.自底向上归并，子链表长度 1-2-4-8……增长
        //也就是先相邻两个一元子链排序，然后相邻两个排序后的二元子链排序，然后相邻两个排序后的四元子链排序……
        for(int subLength = 1 ; subLength < length ; subLength*=2)
        {
            auto prev = dummy; //前驱节点，用于保存目前已经排好序部分的最后一个节点、用于后续连接
            auto curr = dummy->next; //工作节点

            while(curr)
            {
                auto head1 = curr;
                for(int i=1 ; i<subLength && curr->next ; i++)
                {
                    curr = curr->next;
                }

                auto head2 = curr->next; //保存第二个子链表的头
                curr->next = nullptr; //断开表 1 表 2
                curr = head2;
                
                //这个地方不保证剩余长度还够不够 subLength，curr,curr->next 都要判断是否非 null
                for(int i=1 ; i<subLength && curr && curr->next ; i++)
                {
                    curr = curr->next;
                }

                ListNode * next = nullptr; //用于记录后续组的开头 ，例如4,2 排好后，这里记录 1 的地址
                if(curr)
                {
                    next = curr->next;
                    curr->next = nullptr; //断开 head2 开头的子链表和后续链表节点
                }

                auto merged = merge(head1,head2); //合并第一组
                prev->next = merged; //排序后子链之间的连接
                
                //移动 prev 到目前已排序部分的尾部，例子中第一轮排序好 2-4 后移动到 4
                while(prev->next)
                {
                    prev = prev->next; 
                }

                curr = next; //工作指针移动到下一轮的开头，继续 while
            }
        }

        auto ans = dummy->next;
        delete dummy;
        return ans;
    }
};



/*
为了方便记忆题解、将部分功能拆分为函数
merge(l1, l2)： 合并两个升序链表
cut(l, n)： 将链表 l 切掉前 n 个节点，并返回后半部分的链表头
*/

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        auto dummyHead = new ListNode(0, head);
        auto p = head;
        int length = 0;
        while(p)
        {
            length++;
            p = p->next;
        }

        for(int subLength = 1; subLength < length ; subLength*=2)
        {
            auto curr = dummyHead->next; // 工作指针 
            auto tail = dummyHead;

            while (curr)
            {
                auto left = curr;
                auto right = cut(left, subLength); // left->@->@ right->@->@->@...
                curr = cut(right, subLength); // left->@->@ right->@->@  cur->@->...
                //如果不够长的话 curr 会返回 null，while 循环在处理完这一轮后退出

                tail->next = merge(left, right); // tail->（ ……->@ ） cur->@->……

                while (tail->next) 
                {
                    tail = tail->next;  // ……->@->tail cur->@->……
                }
                
            }
            
        }
        auto ans = dummyHead->next;
        delete dummyHead;
        return ans;
    }

    ListNode* cut(ListNode* l, int n)
    {
        auto p = l;
        while(p && --n)
        {
            p = p->next;
        }

        if(p == nullptr) //不够长了，这一题需要直接返回 null
        {
            return nullptr;
        }

        auto next = p->next;
        p->next = nullptr;
        return next;

    }


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


};



/*
空间复杂度非 O(1)


class Solution {
public:
    ListNode* sortList(ListNode* head) {
       vector<int> a;
    //    a.reserve(5*10000);
       auto p = head;
       while(p)
       {
        a.emplace_back(p->val);
        p = p->next;
       }

       sort(a.begin(), a.end());

       p = head;
       int i=0;
       while(p)
       {
        p->val = a[i++];
        p = p->next;
       }

       return head;
    } 
};

*/