struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// BST is assumed sorted and properly ordered.
class Solution {
public:
  TreeNode *searchBST(TreeNode *root, int val) {
    TreeNode *current{root};

    while (current->val != val) {
      if (current->val > val) {
        current = current->left;
        if (current == nullptr) {
          return nullptr;
        }
      } else {
        current = current->right;
        if (current == nullptr) {
          return nullptr;
        }
      }
    }

    return current;
  }
};
