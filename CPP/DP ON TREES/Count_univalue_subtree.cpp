//My Code

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val){
        this->val = val;
        left = right = NULL;
    }
};

tuple<int,int,bool> f(TreeNode* root){
    // 1. If null, return true for the flag. A missing node doesn't break a unival subtree.
    if(!root) return make_tuple(0, 0, true);

    // Leaf node: returns 1 count, its own value, and true
    if(!root->left && !root->right) return make_tuple(1, root->val, true);

    auto [cntleft, leftsameval, leftflag] = f(root->left);
    auto [cntright, rightsameval, rightflag] = f(root->right);

    // If either existing child is NOT a unival subtree, the current node can't be one either.
    if(!leftflag or !rightflag){
        return make_tuple(cntleft + cntright, root->val, false);
    }

    // 2. Assume it is a univalue tree, then prove it wrong.
    // We only check the value IF the child actually exists (!= NULL).
    bool is_unival = true;
    
    if(root->left != NULL && leftsameval != root->val){
        is_unival = false; // Left child exists but value doesn't match
    }
    if(root->right != NULL && rightsameval != root->val){
        is_unival = false; // Right child exists but value doesn't match
    }

    // 3. Return the calculated count and flag
    if(is_unival){
        return make_tuple(cntleft + cntright + 1, root->val, true);
    } else {
        return make_tuple(cntleft + cntright, root->val, false);
    }
}

int solve(TreeNode* root){
    // We just call the recursive function and extract the total count (the first item in tuple)
    auto [totalCount, val, flag] = f(root);
    return totalCount;
}

int32_t main(){
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    /* Let's build a test tree:
             5
            / \
           1   5
          / \   \
         5   5   5
         
       Expected Unival Subtrees:
       - The three leaf nodes (val 5) -> Count = 3
       - The node 1 is NOT unival (children are 5).
       - The right node 5 IS unival (its right child is 5, left is NULL). -> Count = 1
       - The root 5 is NOT unival (left subtree is not unival).
       Total expected answer = 4
    */

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(5);
    root->right = new TreeNode(5);
    
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(5);
    
    root->right->right = new TreeNode(5);

    int ans = solve(root);
    cout << "Total uni-value subtrees: " << ans << endl;

    return 0;
}
//Memory optimised code
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

class TreeNode{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val){
        this->val = val;
        left = right = NULL;
    }
};

// Now it just returns a boolean, and updates 'count' directly
bool f(TreeNode* root, int& count){
    // Base case: null nodes don't break the rules
    if(!root) return true;

    // Traverse left and right. 
    // Notice we compute BOTH before returning. We must not short-circuit, 
    // because we need to count subtrees hidden deep down!
    bool left_unival = f(root->left, count);
    bool right_unival = f(root->right, count);

    // If any child subtree is NOT uni-value, this one isn't either
    if(!left_unival || !right_unival) return false;

    // Check if children exist and if their values match the parent's value
    if(root->left != NULL && root->left->val != root->val) return false;
    if(root->right != NULL && root->right->val != root->val) return false;

    // If we passed all checks, this subtree is uni-value!
    count++;
    return true;
}

int solve(TreeNode* root){
    int totalCount = 0;
    f(root, totalCount); // totalCount is passed by reference
    return totalCount;
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(1);
    root->right = new TreeNode(5);
    
    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(5);
    
    root->right->right = new TreeNode(5);

    int ans = solve(root);
    cout << "Total uni-value subtrees: " << ans << endl;

    return 0;
}
