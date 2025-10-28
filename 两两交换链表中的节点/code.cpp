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

/*
递归

1 - 2 - 3 - 4 ……

2 -> 1 
1 -> (用函数继续处理3开头的链表，返回的头)
 
return 2

*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {

        //无元素或只有一个元素
        if(!head || !(head->next))
            return head;

        auto one = head;
        auto two = head->next;
        auto three = two->next;

        two->next = one;
        one->next = swapPairs(three);

        return two;
        
        }
};



/*
双指针
初始状态：
temp（dummy） -> node1 -> node2 -> node3……

temp -> node2  （此时 dummy->next 为 node2 ，最后返回 dummy->next）
node1 -> (node2->next) (node3)
node2 -> node1


temp = node1 (node3的前一个节点)
再次循环处理以 node3 开头的子链表
*/


class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        auto dummy = new ListNode(0);
        dummy->next = head;
        auto temp = dummy;

        while (temp->next && temp->next->next)
        {
            auto node1 = temp->next;
            auto node2 = temp->next->next;
            temp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            temp = node1;
        }

        auto ans = dummy->next;
        delete dummy;
        return ans;
    }
};