#include <iostream>
#include <vector>
#include <queue>

class TreeNode 
{
public:
    int data;
    TreeNode* parent;
    std::vector<TreeNode*> children;

    TreeNode(int value) : data(value), parent(nullptr) {}

    void addChild(TreeNode* child) 
    {
        children.push_back(child);
        child->parent = this;
    }

    TreeNode* getParent() const 
    {
        return parent;
    }

    const std::vector<TreeNode*>& getChildren() const 
    {
        return children;
    }
};

class GeneralTree 
{
public:
    TreeNode* root;

    GeneralTree(int rootValue) : root(new TreeNode(rootValue)) {}

    ~GeneralTree() 
    {
        deleteTree(root);
    }

    // Access Functions //

    // Access Functions for Return Root
    TreeNode* getRoot() const 
    {
        return root;
    }

    // Access Function for Parent of a Node
    TreeNode* getParent(TreeNode* node) const 
    {
        return (node) ? node->getParent() : nullptr;
    }

    // Access Function for children of a Node
    const std::vector<TreeNode*>& getChildren(TreeNode* node) const 
    {
        return node->getChildren();
    }

    // Query Functions //

    // Query Functions for Size
    int size(TreeNode* node) const 
    {
        if (node == nullptr) return 0;

        int count = 1;
        for (TreeNode* child : node->children) 
        {
            count += size(child);
        }
        return count;
    }

    // Query Functions for Depth
    int depth(TreeNode* node) const 
    {
        int depth = 0;
        while (node) 
        {
            node = node->parent;
            depth++;
        }
        return depth;
    }

    // Query Functions for isEmpty
    bool isEmpty() const 
    {
        return root == nullptr;
    }

    // Query Functions for isRoot
    bool isRoot(TreeNode* node) const 
    {
        return node == root;
    }

    // Query Functions for isLeaf
    bool isLeaf(TreeNode* node) const 
    {
        return node && node->children.empty();
    }

    // Insertion at Random Position
    bool insertNode(TreeNode* newNode) 
    {
        if (!newNode) return false;

        TreeNode* parent = getRandomNode(root);
        if (parent) 
        {
            parent->addChild(newNode);
            return true;
        }

        return false;
    }

    // Insertion as a child of a specific Node
    bool insertNode(TreeNode* parent, TreeNode* newNode) 
    {
        if (!parent || !newNode) return false;
        parent->addChild(newNode);
        return true;
    }

    // Breadth First Search Traversal
    void breadthTraversal() const 
    {
        if (root == nullptr) return;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) 
        {
            TreeNode* current = q.front();
            q.pop();
            std::cout << current->data << " ";

            for (TreeNode* child : current->children) 
            {
                q.push(child);
            }
        }
    }

private:
    // Deletion of Nodes
    void deleteTree(TreeNode* node) 
    {
        if (node) 
        {
            for (TreeNode* child : node->children) 
            {
                deleteTree(child);
            }
            delete node;
        }
    }

    TreeNode* getRandomNode(TreeNode* node) 
    {
        if (node == nullptr) return nullptr;
        if (node->children.empty() || rand() % 2 == 0) 
        {
            return node;
        }
        else 
        {
            int randomChildIndex = rand() % node->children.size();
            return getRandomNode(node->children[randomChildIndex]);
        }
    }
};

int main() 
{
    GeneralTree tree(1);

    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);

    tree.insertNode(tree.getRoot(), node2);
    tree.insertNode(tree.getRoot(), node3);
    tree.insertNode(node2, node4);
    tree.insertNode(node2, node5);
    tree.insertNode(node3, node6);

    std::cout << "Breadth Traversal: ";
    tree.breadthTraversal();
    std::cout << std::endl;

    std::cout << "Breadth Traversal after insertions: ";
    tree.breadthTraversal();
    std::cout << std::endl;

    return 0;
}
