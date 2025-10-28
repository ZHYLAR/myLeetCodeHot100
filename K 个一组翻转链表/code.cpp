#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:

/*
(1 - 2 - 3 - 4) - 5
1先接到 5, 2 再接到 1 ，3 接 2 ，4 接 3。得到：
(4 - 3 - 2 - 1) - 5

需要三个指针
1. 保存当前接好的工作指针，下轮工作节点的 next 接到这个节点上：prevNode。循环过程中分别是 5、1、2、3、4
2. 工作指针: currentNode
3. 保存下一轮工作节点: nextNode 。 防止工作指针的 next 修改之后，丢失下一个要处理的节点
*/

pair<ListNode* , ListNode*> reverseSubList(ListNode* subGroupHead, ListNode* subGroupTail)
{
    auto prevNode = subGroupTail->next;
    auto currentNode = subGroupHead;

    /*
    prevNode是下一轮工作节点需要接上去的节点，
    如果prevNode等于子链尾就说明循环结束了，（例子里的 4）
    原来的尾变成了现在的第一个节点
    */
    while(prevNode!=subGroupTail)
    {
        auto nextNode = currentNode->next;
        currentNode->next= prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }

    return {subGroupTail , subGroupHead};
}

/*
    main 中也需要三个指针，保存子链前后节点，以及当前待翻转子链的尾。
    流程： 
    1. 获取子链的前一个元素preGroupTail
    2. 获取子链的后一个元素nextGroupHead
    3. 翻转子链（需要遍历得到currentGroupTail）
    4. preGroupTail连到子链头、子链尾连到nextGroupHead
    
    head 当工作节点用，指向反转前，待翻转的子链的头
    sentinel 哨兵节点、哑节点，Sentinel 的 next 是新头，因为第一轮处理的时候sentinel是preGroupTail
*/
    ListNode* reverseKGroup(ListNode* head, int k) {
        auto sentinel = new ListNode(0);
        sentinel->next = head;
        auto preGroupTail = sentinel;

        while(head)
        {
            auto currentGroupTail = preGroupTail; //先指向上一组尾，循环向后 next 找到这一组的 tail
            for(int i=0; i<k ;i++)
            {
                currentGroupTail = currentGroupTail->next;

                //如果发现这一组剩下不到k 个元素了，直接 return，跳过最后一轮的翻转操作
                if(!currentGroupTail)
                {
                    return sentinel->next;
                }
            }

            auto nextGroupHead = currentGroupTail->next;

            // tie(head , currentGroupTail) = reverseSubList(head, currentGroupTail);

            auto result = reverseSubList(head, currentGroupTail); // pair<listnode* , listnode*>
            head = result.first;
            currentGroupTail = result.second;
            
            preGroupTail->next = head;
            currentGroupTail->next = nextGroupHead;

            preGroupTail = currentGroupTail;  // 上一组的尾变为当前组的尾
            head = currentGroupTail->next;     // 下一组的头作为新的处理起点

        }
        
        
        return sentinel->next;
    }
};