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


/*
    BFS
    思路：层序遍历的每层最后一个节点
*/ 
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode* > q;
        vector<int> ans;
        if(!root) return vector<int>();
        q.push(root);
        
        while(!q.empty())
        {
            int n = q.size(); //n 为当前层的节点数量
            while(n)
            {
                auto node = q.front();
                q.pop();
                if(n == 1) ans.emplace_back(node->val); //层序遍历的每层最后一个元素
                n--;
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }        

            // ans.emplace_back(cen);
            
        }

        return ans;
    }
};



/*DFS 版本*/

class Solution {
    vector<int> res;
    void dfs(TreeNode *node, int u){ //u为当前层数，从 0 开始计

        //这个地方比较细节，因为每一层只有一个元素是右视图看得见的
        //所以 res 的第 i 个元素就是第 i 层右视图看到的元素
        //优先遍历右子树的话，最右边的元素会占好位置，这一层后续遍历到的节点不会插入 res
        if(u == res.size()) res.push_back(node->val); 
        if(node->right) dfs(node->right, u+1); //优先遍历右子树
        if(node->left) dfs(node->left, u+1);
    }
public:
    vector<int> rightSideView(TreeNode* root) {
        if(root) dfs(root, 0);
        return res;
    }
};