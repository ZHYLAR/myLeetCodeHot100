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
    int ans = 0;
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        auto L = maxDepth(root->left);
        auto R = maxDepth(root->right);
        //L + R 就是经过当前节点左右边的最长直径 （注意本题的直径是以边数计算的）
        ans = max(ans, L+R); //ans 维护递归遍历过程中，最大的直径（左右最路径大节点和）
        return max(L, R) + 1;
    }
 
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 0; //如果整棵树只有一个节点的情况
        maxDepth(root);
        return ans;
    }
};