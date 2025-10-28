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
迭代先序遍历 + 保存
*/

class Solution {
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        vector<TreeNode* > nodeLst;
        stack<TreeNode* > stk;
        
        stk.push(root);
        while(!stk.empty())
        {
            TreeNode* node = stk.top();
            stk.pop();

            nodeLst.emplace_back(node);

            if(node->right) //先压栈的后遍历到，这里先压右树节点
                stk.push(node->right);
            if(node->left)
                stk.push(node->left);
            
        }
        int i;
        // auto dummyHead = new TreeNode(0, nullptr, root);
        for(int i=0; i < nodeLst.size() - 1 ; i++){
            nodeLst[i]->left = nullptr;
            nodeLst[i]->right = nodeLst[i+1];
        }
    }
    
};


/*
原地算法
*/

class Solution {
public:
    void flatten(TreeNode* root) {
        while(root)
        {
            //左树
            auto move = root->left;
            
            //找左树的最右节点
            while(move && move->right)
            {
                move = move->right;
            }        

            //右树接到左树最右节点后
            // move = root->left; 赋值的时候，有可能 move 已经是 nullptr，不存在，所以上面的 while 和这里都要判断一下
            if(move) 
            {
                move -> right = root -> right;
                root -> right = root->left; //左树变右树
                root -> left  = nullptr; //清空原来左边的链接
            }

            root = root -> right;
        }
    }
};
