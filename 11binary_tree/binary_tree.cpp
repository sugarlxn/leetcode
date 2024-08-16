#include <iostream>
#include <vector>
using namespace std;

namespace BT{
/// @brief 二叉树节点
/// @tparam T
template<typename T>
struct TreeNode{
    T val;
    TreeNode* left;
    TreeNode* right;
    TreeNode():val(0),left(nullptr),right(nullptr){};
    TreeNode(T x):val(x),left(nullptr),right(nullptr){};
    TreeNode(T x, TreeNode<T>* left, TreeNode<T>* right): val(x), left(left), right(right){};
};//struct TreeNode


/// @brief 前序遍历二叉树
/// @tparam T 
/// @param root 
/// @return 
template<typename T>
vector<T> preorderTraversal(TreeNode<T>* root){
    vector<T> result;
    if(root == nullptr){return result;}
    pre_order(root, result);
    return result;
};

/// @brief 前序遍历二叉树，递归实现
/// @tparam T 
/// @param node 
/// @param result 
template<typename T>
void pre_order(TreeNode<T>* node, vector<T>& result){
    if(node == nullptr){return;}
    result.push_back(node->val);
    pre_order(node->left, result);
    pre_order(node->right, result);
};

};//namespace BT

int main(int argc, char * argv[])
{
    cout << "Hello, world!" << endl;
    return 0;
}