class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty()) { // 空节点
            return nullptr;
        }

        //ranges::find 返回迭代器，减去inorder.begin()得到左子树大小
        int left_size = ranges::find(inorder, preorder[0]) - inorder.begin(); // 左子树的大小

        vector<int> pre1(preorder.begin() + 1, preorder.begin() + 1 + left_size);//左子树的前序遍历 （左开右闭区间）
        vector<int> pre2(preorder.begin() + 1 + left_size, preorder.end());//右子树的前序遍历
        vector<int> in1(inorder.begin(), inorder.begin() + left_size);//左子树中序遍历
        vector<int> in2(inorder.begin() + 1 + left_size, inorder.end());//右子树中序遍历

        TreeNode* left = buildTree(pre1, in1);
        TreeNode* right = buildTree(pre2, in2);
        
        return new TreeNode(preorder[0], left, right);
    }
};

// 作者：灵茶山艾府
// 链接：https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/solutions/2646359/tu-jie-cong-on2-dao-onpythonjavacgojsrus-aob8/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

/*
上述代码ranges::find时间复杂度O(n)、复制 vector 开销也很大
用一个哈希表查找元素优化查找时间复杂度、用传入 index 代替复制 vector
*/
class Solution {
private:
    unordered_map<int, int> v_index_map;

public:
    /*
    preLeft: 当前处理节点的前序序列 区间左 index（闭区间）
    preRight： 前序序列区间右 index
    inLeft: 中序序列区间左 index
    inRight：中序序列区间右 index
    传 index 是为了减少 vector 复制开销

    例子preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
    */
    TreeNode* myBuildTree(vector<int>& preorder, vector<int>& inorder, int preLeft, int preRight, int inLeft, int inRight)
    {
        //结束条件
        if(preLeft > preRight)
        {
            return nullptr;
        }

        int preorder_root = preLeft; //当前节点的前序 index 3 的 index 0
        int inorder_root = v_index_map[preorder[preorder_root]]; //当前节点的中序index 3 的 index 1
        int NodeNumOfLeft_subTree = inorder_root - inLeft;//左子树节点数，1-0 = 1 个node

        //递归左树，左树的 inorder 节点是现在的下一个
        /*
        左子树 preorder [9]，[preLeft+1, preLeft + NodeNumOfLeft_subTree] 
        右子树 preorder [20,15,7], [reLeft+ NodeNumOfLeft_subTree + 1, preRight]
        左子树 inorder [9], [ inLeft , inorder_root -1]
        右子树 inorder[15,20,7] [inorder_root + 1 , inRight]
        */
        auto leftTreeNode = myBuildTree(preorder, inorder,  preLeft+1,  preLeft + NodeNumOfLeft_subTree , inLeft , inorder_root -1);
        auto rightTreeNdoe = myBuildTree(preorder, inorder, preLeft+ NodeNumOfLeft_subTree + 1, preRight, inorder_root + 1 , inRight);
        TreeNode* root = new TreeNode(preorder[preorder_root], leftTreeNode, rightTreeNdoe);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int NodeNum = inorder.size();

        //装填哈希表 value - index
        for(int i = 0; i<NodeNum; i++)
        {
            v_index_map[inorder[i]] = i;
        }

        return myBuildTree(preorder,inorder,0,NodeNum-1,0,NodeNum-1);
    }
};