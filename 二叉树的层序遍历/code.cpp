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
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode* > q;
        vector<vector<int>> ans;
        if(!root) return ans;
        q.push(root);
        
        while(!q.empty())
        {
            int n = q.size(); //n 为当前层的节点数量
            vector<int> cen;
            while(n)
            {
                auto node = q.front();
                q.pop();
                n--;
                cen.emplace_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }        

            ans.emplace_back(cen);
            
        }

        return ans;
    }
};