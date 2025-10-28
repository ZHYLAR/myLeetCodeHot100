/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    vector<int> ans;
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(!root) return ans; 
        //这个地方返回什么都没关系，因为递归过程中没人接收返回值
        //只需要保证节点的 root 压入了 ans 就好
        inorderTraversal(root->left);
        ans.emplace_back(root->val);
        inorderTraversal(root->right);

        return ans;
    }
};


/*
    迭代，对于某一个节点、先不断将左树树根压栈（保存处理顺序），然后处理栈内元素（写入 ans），然后将工作指针指向这个节点的右树
    这样下一轮循环就可以按照右节点继续开始左根右

*/
class Solution {
    
public:
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> stk;
        vector<int> ans;
        
        while(root || !stk.empty())
        {
            while(root)
            {
                stk.push(root);
                root = root->left;
            }

            root = stk.top();
            stk.pop();
            ans.push_back(root->val);
            root = root->right;
        }
    
        return ans;
    }
};