#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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


/// @brief 层序遍历二叉树
/// @tparam T 
/// @param root 
/// @return 
template<typename T>
vector<T> levelOrderTraversal(TreeNode<T>* root){
    vector<T> result;
    if(root == nullptr){return result;}
    //使用队列进行层序遍历
    queue<TreeNode<T>*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode<T>* node = q.front();
        q.pop();
        result.push_back(node->val);
        if(node->left != nullptr){q.push(node->left);}
        if(node->right != nullptr){q.push(node->right);}
    }
    return result;
}

/// @brief 前序遍历二叉树 根->左->右
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

/// @brief 中序遍历二叉树 左->根->右
/// @tparam T 
/// @param root 
/// @return 
template<typename T>
vector<T> inorderTraversal(TreeNode<T>* root){
    vector<T> result;
    if(root == nullptr){return result;}
    in_order(root, result);
    return result;
};

/// @brief 后序遍历二叉树 左->右->根
/// @tparam T 
/// @param root 
/// @return 
template<typename T>
vector<T> postorderTraversal(TreeNode<T>* root){
    vector<T> result;
    if(root == nullptr){return result;}
    post_order(root, result);
    return result;
};

/// @brief 前序遍历二叉树，递归实现
/// @tparam T 
/// @param node 
/// @param result 
template<typename T>
void pre_order(TreeNode<T>* node, vector<T>& result){
    if(node == nullptr){return;}
    result.push_back(node->val); //访问根节点
    pre_order(node->left, result); //访问左子树
    pre_order(node->right, result); //访问右子树
};

/// @brief 中序遍历二叉树 递归实现
/// @tparam T 
/// @param node 
/// @param result 
template<typename T>
void in_order(TreeNode<T>* node, vector<T>& result){
    if(node == nullptr){return;}
    in_order(node->left, result); //访问左子树
    result.push_back(node->val); //访问根节点
    in_order(node->right, result); //访问右子树
};

/// @brief 后序遍历二叉树 递归实现
/// @tparam T 
/// @param node 
/// @param result 
template<typename T>
void post_order(TreeNode<T>* node, vector<T>& result){
    if(node == nullptr){return;}
    post_order(node->left, result); //访问左子树
    post_order(node->right, result); //访问右子树
    result.push_back(node->val); //访问根节点
};

//使用迭代法实现二叉树先序遍历
template<typename T>
vector<T> PreOrderTranvesalByStack(TreeNode<T>* root){
    vector<T> result;
    if(root == nullptr){return result;}
    stack<TreeNode<T>*> st;
    st.push(root);
    while (!st.empty())
    {
        TreeNode<T>* node = st.top();
        st.pop();
        result.push_back(node->val); //访问根节点
        if(node->right != nullptr){st.push(node->right);}  //右子树先入栈
        if(node->left != nullptr){st.push(node->left);}  //左子树入栈
    }
    return result;
}



};//namespace BT

int main(int argc, char * argv[])
{
    cout << "Hello, world!" << endl;

    // 创建二叉树
    BT::TreeNode<int>* root = new BT::TreeNode<int>(1);
    root->left = new BT::TreeNode<int>(2);
    root->right = new BT::TreeNode<int>(3);
    root->left->left = new BT::TreeNode<int>(4);
    root->left->right = new BT::TreeNode<int>(5);
    root->right->left = new BT::TreeNode<int>(6);
    root->right->right = new BT::TreeNode<int>(7);

    // 前序遍历
    vector<int> preorder = BT::preorderTraversal(root);
    for(int i = 0; i < preorder.size(); i++){
        cout << preorder[i] << " ";
    }
    cout << endl;

    //先序遍历 迭代发
    vector<int> perorder2 = BT::PreOrderTranvesalByStack(root);
    for (int i = 0; i < perorder2.size(); i++)
    {
        cout << perorder2[i] << " ";
    }
    cout << endl;

    // 中序遍历
    vector<int> inorder = BT::inorderTraversal(root);
    for(int i = 0; i < inorder.size(); i++){
        cout << inorder[i] << " ";
    }
    cout << endl;   

    // 后序遍历
    vector<int> postorder = BT::postorderTraversal(root);
    for(int i = 0; i < postorder.size(); i++){
        cout << postorder[i] << " ";
    }
    cout << endl;

    // 层序遍历
    vector<int> levelorder = BT::levelOrderTraversal(root); 
    for(int i = 0; i < levelorder.size(); i++){
        cout << levelorder[i] << " ";
    }
    cout << endl;

    return 0;
}