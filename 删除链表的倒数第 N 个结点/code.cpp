#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *right = head;
        ListNode* dummy  = new ListNode(0,head);  
        ListNode *left = dummy;

        if(right->next == nullptr)
        {
            return nullptr;
        }

        for(int i=0; i<n ; i++)
        {
            right = right->next;
        }

        while(right)
        {
            right = right->next;
            left = left->next;
        }

        // ListNode *tmp = left;
        left->next = left->next->next;
        const auto ans  = dummy->next;
        delete dummy;

        return ans;
    }
};

int main()
{
    // 创建链表: 1->2->3->4->5
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    int n = 2; // 删除倒数第2个节点
    Solution sol;
    ListNode *newHead = sol.removeNthFromEnd(head, n);

    // 打印结果
    // 打印结果
    cout << "链表删除倒数第 " << n << " 个节点后的结果: ";
    ListNode *current = newHead; // 声明移到此处
    if (newHead == nullptr) {
        cout << "链表为空" << endl;
    } else {
        while (current != nullptr)
        {
            cout << current->val << " ";
            current = current->next;
        }
        cout << endl;
    }

    // 清理内存
    current = newHead;
    while (current != nullptr)
    {
        ListNode *temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}