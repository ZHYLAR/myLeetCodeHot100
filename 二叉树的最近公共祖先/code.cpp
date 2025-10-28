#include <iostream>
#include <vector>
#include <algorithm>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 寻找二叉树中两个节点p和q的最近公共祖先
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 基准情况：如果根节点为空，或者根节点就是p或q，则直接返回root
        // 这意味着我们找到了p或q，或者到达了叶子节点之外
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        
        // 递归地在左子树中寻找p和q的LCA
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        // 递归地在右子树中寻找p和q的LCA
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        // 情况1: 如果左右子树都找到了目标节点 (p或q)，则当前root就是LCA
        // 这意味着p和q分别位于root的不同子树中
        if (left != nullptr && right != nullptr) {
            return root;
        }
        // 情况2: 如果只有左子树找到了，说明p和q(或LCA)都在左子树中
        // 或者left本身就是p或q，且另一个节点是其子孙            
        // 情况3: 如果只有右子树找到了，说明p和q(或LCA)都在右子树中
        // 或者right本身就是p或q，且另一个节点是其子孙
        // 如果left和right都为空，则返回nullptr
        return left != nullptr ? left : right;
    }
};

// 辅助函数：构建一个简单的二叉树
TreeNode* buildTree() {
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    return root;
}

// 辅助函数：清理二叉树内存
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // 构建测试用例1的二叉树
    TreeNode* root1 = buildTree();
    // 测试用例1: p=5, q=1. 预期LCA: 3
    TreeNode* p1 = root1->left; // Node with value 5
    TreeNode* q1 = root1->right; // Node with value 1
    TreeNode* lca1 = Solution().lowestCommonAncestor(root1, p1, q1);
    std::cout << "LCA of 5 and 1 is: " << (lca1 ? std::to_string(lca1->val) : "nullptr") << std::endl; // Expected: 3
    deleteTree(root1);

    // 构建测试用例2的二叉树
    TreeNode* root2 = buildTree();
    // 测试用例2: p=5, q=4. 预期LCA: 5
    TreeNode* p2 = root2->left; // Node with value 5
    TreeNode* q2 = root2->left->right->right; // Node with value 4
    TreeNode* lca2 = Solution().lowestCommonAncestor(root2, p2, q2);
    std::cout << "LCA of 5 and 4 is: " << (lca2 ? std::to_string(lca2->val) : "nullptr") << std::endl; // Expected: 5
    deleteTree(root2);

    // 构建测试用例3的二叉树
    TreeNode* root3 = buildTree();
    // 测试用例3: p=6, q=7. 预期LCA: 2
    TreeNode* p3 = root3->left->left; // Node with value 6
    TreeNode* q3 = root3->left->right->left; // Node with value 7
    TreeNode* lca3 = Solution().lowestCommonAncestor(root3, p3, q3);
    std::cout << "LCA of 6 and 7 is: " << (lca3 ? std::to_string(lca3->val) : "nullptr") << std::endl; // Expected: 2
    deleteTree(root3);

    // 构建测试用例4的二叉树
    TreeNode* root4 = buildTree();
    // 测试用例4: p=8, q=0. 预期LCA: 1
    TreeNode* p4 = root4->right->right; // Node with value 8
    TreeNode* q4 = root4->right->left; // Node with value 0
    TreeNode* lca4 = Solution().lowestCommonAncestor(root4, p4, q4);
    std::cout << "LCA of 8 and 0 is: " << (lca4 ? std::to_string(lca4->val) : "nullptr") << std::endl; // Expected: 1
    deleteTree(root4);

    return 0;
}
