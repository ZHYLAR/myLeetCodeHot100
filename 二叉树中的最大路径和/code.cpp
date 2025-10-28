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
    写一个递归,
    int maxDepth(node)

    return 这个结点向下最大值路径（注意是可以不走到树底的）
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int ans = INT_MIN;

    /*输入：结点； 输出：含这个结点值在内的向下和最大路径*/
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        int L,R;

        L = maxDepth(root->left);
        R = maxDepth(root->right);

        /*这样写运行快一些，节省创建列表开销*/
        ans = max(ans, L + R + root->val);
        ans = max(ans, L + root->val);
        ans = max(ans, R + root->val);
        ans = max(ans, root->val);

        // ans = max({ans, L + R + root->val, L + root->val, R + root->val, root->val}); 
        //ans 维护递归遍历过程中，最大结果
        
        //对于返回值也是一样的，可以采纳加上L或R或者不加
        return max(max(L, R) + root->val,  root->val);
    }


    int maxPathSum(TreeNode* root) {
        maxDepth(root);
        return ans;
    }
};

int main() {
    // Test case 1
    // Tree:   -10
    //        /   \
    //       9     20
    //            /  \
    //           15   7
    TreeNode* root1 = new TreeNode(-10);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    Solution sol1;
    std::cout << "Test Case 1 (Expected: 42): " << sol1.maxPathSum(root1) << std::endl;

    // Clean up memory for Test Case 1
    delete root1->left;
    delete root1->right->left;
    delete root1->right->right;
    delete root1->right;
    delete root1;

    // Test case 2
    // Tree:   1
    //        / \
    //       2   3
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);

    Solution sol2;
    std::cout << "Test Case 2 (Expected: 6): " << sol2.maxPathSum(root2) << std::endl;

    // Clean up memory for Test Case 2
    delete root2->left;
    delete root2->right;
    delete root2;

    // Test case 3
    // Tree:   -3
    TreeNode* root3 = new TreeNode(-3);
    Solution sol3;
    std::cout << "Test Case 3 (Expected: -3): " << sol3.maxPathSum(root3) << std::endl;

    delete root3;

    return 0;
}