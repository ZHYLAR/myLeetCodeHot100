/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>

using namespace std;


struct ListNode {
	   int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/*
思想类似于复制一遍链表，然后双指针同时往右走，如果链表有交点，两个指针一定会同时到达同一个位置。否则没有交点
A链表： -
B链表： *
- -         -       --         -   **           *
    (交叉)     ->      (交叉)         （交叉）
* *         *  	    **         *   --           -

*/

class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		
		if(headA==nullptr || headB == nullptr)
		{
			return nullptr;
		}
		
		auto pa = headA, pb = headB;
		while(pa!=pb)
		{
			pa = pa == nullptr ? headB : pa->next;
			pb = pb == nullptr ? headA : pb->next;
		}
		
		return pa;
	}
};

int main()
{
	
	return 0;
}
