#include <iostream>
#include <unordered_map>
#include <functional>
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
    int pathSum(TreeNode* root, int targetSum) {
        int ans = 0;
        unordered_map<long long, int> cnt{{0, 1}};
        function<void(TreeNode*, long long)> dfs = [&](TreeNode* node, long long s) {
            // 例子：以测试用例3的树结构为例（targetSum = 8）：
            //        10
            //       /  \
            //      5   -3
            //     / \    \
            //    3   2   11
            //   / \   \
            //  3  -2   1
            // 
            // 我们将跟踪根节点到各个节点的递归过程
            
            if (node == nullptr) {
                return;
            }

            // 当前前缀和 s 更新为从根到当前节点的和
            s += node->val;
            
            // 示例：假设当前处理节点值为5，s = 15（10+5）
            // 查找是否存在前缀和为 s-targetSum = 15-8 = 7 的路径
            // 如果存在，从该路径的下一个节点到当前节点的路径和就是targetSum
            ans += cnt[s - targetSum]; 

            // 将当前前缀和及其出现次数存入哈希表
            // 示例：处理节点10时，s=10，执行后cnt变为{{0,1}, {10,1}}
            //      处理节点5时，s=15，执行后cnt变为{{0,1}, {10,1}, {15,1}}
            cnt[s]++;
            
            // 递归处理左子树
            // 示例：从节点5递归到节点3，s=18（10+5+3）
            // 在节点3处，s-targetSum=10，查找cnt[10]=1
            // 这意味着从节点10到节点3的路径和为8，ans增加1
            if(node->left) dfs(node->left, s);
            
            // 递归处理右子树
            // 示例：从节点5递归到节点2，s=17（10+5+2）
            // 在节点2处，s-targetSum=9，cnt中不存在9
            // 但在它的子节点1处，s=18，s-targetSum=10，cnt[10]=1
            // ans再增加1
            if(node->right) dfs(node->right, s);
            
            // 回溯：恢复哈希表状态
            // 确保当前路径的修改不影响其他分支的递归
            // 示例：处理完节点5的所有子树后，cnt[15]--，回到{{0,1}, {10,1}}
            cnt[s]--;
        };
        dfs(root, 0);
        return ans;
    }
};

int main() {
    Solution s;
    
    // 测试用例1：空树
    cout << "\n=== 测试用例1 ===\n"
         << "空树测试...\n"
         << "实际输出: " << s.pathSum(nullptr, 0) << "\n预期结果: 0\n\n";
    
    // 测试用例2：单节点树
    TreeNode* root2 = new TreeNode(10);
    cout << "=== 测试用例2 ===\n"
         << "单节点树测试...\n"
         << "实际输出: " << s.pathSum(root2, 10) << "\n预期结果: 1\n\n";
    
    // 测试用例3：LeetCode 示例
    /*
          10
         /  \
        5   -3
       / \    \
      3   2   11
     / \   \
    3  -2   1
    */
    TreeNode* root3 = new TreeNode(10,
        new TreeNode(5,
            new TreeNode(3, new TreeNode(3), new TreeNode(-2)),
            new TreeNode(2, nullptr, new TreeNode(1))),
        new TreeNode(-3, nullptr, new TreeNode(11)));
    cout << "=== 测试用例3 ===\n"
         << "LeetCode标准测试案例...\n"
         << "实际输出: " << s.pathSum(root3, 8) << "\n预期结果: 3\n\n";
    
    return 0;
}

