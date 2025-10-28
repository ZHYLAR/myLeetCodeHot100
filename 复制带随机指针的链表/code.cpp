#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

/*
思路：哈希表+回溯（递归）

先new 一个链表节点，复制原链表节点的 val（先不管 next 和 random）
将这个新链表节点，以原链表节点作为 key，新链表节点作为值，放入哈希表

为这个新链表节点的 next 和 random 赋值，这个地方运用递归思想，
用copyRandomList处理复制对应原链表节点的 next 和 random，
return复制后的新链表头，给这一轮递归的 next 和 random 赋值

哈希表的作用是，如果这个原链表节点对应的复制节点已经被创建了，就不会被重复new
head 当做工作指针用
*/

class Solution
{
public:
    unordered_map<Node *, Node *> cachedNode;

    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
        {
            return nullptr;
        }

        if (!cachedNode[head]) // 如果当前节点没有复制过
        {
            auto newHead = new Node(head->val);
            cachedNode[head] = newHead;
            newHead->next = copyRandomList(head->next);
            newHead->random = copyRandomList(head->random);
        }

        // 返回当前原节点对应的复制节点（已缓存，直接取用）
        return cachedNode[head];
    }
};

/*
改进，一次 p->next 递归已经把节点全部都创建好了
p 为新链表节点的工作指针
直接查表调用 random 就行
*/

class Solution
{
public:
    unordered_map<Node *, Node *> node_map;
    Node *copyRandomList(Node *head)
    {
        if (!head)
            return nullptr;
        Node *p = new Node(head->val);
        node_map[head] = p;
        p->next = copyRandomList(head->next);
        // 此处递归会有一直向后遍历链表，最后由 return nullptr结束。
        // 此时哈希表已经维护好了，每一个原链表节点都有一个映射
        if (head->random)
            p->random = node_map[head->random];
        return p;
    }
};


/*
三轮迭代
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        //新建节点，放到原节点的 next 位置，这一轮遍历之后整个链表会是：原节点->复制节点 交替的一串链
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = new Node(node->val);
            nodeNew->next = node->next;
            node->next = nodeNew;
        }

        //给新建节点的 random 赋值
        for (Node* node = head; node != nullptr; node = node->next->next) {
            Node* nodeNew = node->next;
            nodeNew->random = (node->random != nullptr) ? node->random->next : nullptr;
        }

        //从新链表的第二个节点开始（复制节点的第一个），将链表串起来 (难)
        //A - A' - B - B' 
        Node* headNew = head->next;
        for (Node* node = head; node != nullptr; node = node->next) {
            Node* nodeNew = node->next; // nodeNew = A'
            node->next = node->next->next;  // A->next = B ； 这个地方如果先接 A'->next = B'的话，会丢失 B 的地址，所以只能先接 node next
            nodeNew->next = (nodeNew->next != nullptr) ? nodeNew->next->next : nullptr;  // A'->next = B' 这个地方要放越界

            //下一轮node = B
        }
        return headNew;
    }
};

