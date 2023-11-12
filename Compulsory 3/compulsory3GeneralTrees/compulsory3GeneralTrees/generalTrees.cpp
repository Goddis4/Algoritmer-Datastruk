#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

// Node structure for a General Tree
template <typename T>
struct TreeNode {
    T data;  // Node information
    std::vector<TreeNode*> children;  // List of children
    TreeNode* parent; // Pointer to the parent node

    // Constructor
    TreeNode(const T& value) : data(value) {}
};

// General Tree class
template <typename T>
class GeneralTree {
private:
    TreeNode<T>* root;  // Root of the tree

    // Helper function to perform a random walk and get a random node
    TreeNode<T>* getRandomNodeHelper(TreeNode<T>* startNode) const {
        while (startNode != nullptr && rand() % 2 == 0 && !startNode->children.empty()) {
            const auto& children = startNode->children;
            startNode = children[rand() % children.size()];

            // Update parent pointer of the selected node's children
            for (auto& child : startNode->children) {
                child->parent = startNode;
            }
        }

        return startNode;
    }

public:
    // Constructor
    GeneralTree(const T& rootValue) {
        root = new TreeNode<T>(rootValue);
    }

    // Access functions

    // Get the root of the tree
    TreeNode<T>* getRoot() const {
        return root;
    }

    // Get the parent of a node (Assumes a parent pointer is maintained)
    TreeNode<T>* getParent(TreeNode<T>* node) const {
        // Placeholder implementation, adjust as needed based on your requirements
        return nullptr;
    }

    // Function to get a random node from the tree
    TreeNode<T>* getRandomNode() const {
        // Seed the random number generator with the current time
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        // Start the random walk from the root
        return getRandomNodeHelper(root);
    }

    // Get the children of a node
    std::vector<TreeNode<T>*> getChildren(TreeNode<T>* node) const {
        return node->children;
    }

    // Query functions

    // Check if the tree is empty
    bool isEmpty() const {
        return root == nullptr;
    }

    // Check if a node is the root of the tree
    bool isRoot(TreeNode<T>* node) const {
        return node == root;
    }

    // Check if a node is a leaf node
    bool isLeaf(TreeNode<T>* node) const {
        return node->children.empty();
    }

    // Get the size of the tree
    int size(TreeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        int count = 1;  // Count the current node
        for (const auto& child : node->children) {
            count += size(child);  // Recursively count the children
        }

        return count;
    }

    // Get the depth of a node in the tree
    int depth(TreeNode<T>* node) const {
        if (node == nullptr) {
            return 0;
        }

        int maxDepth = 0;
        for (const auto& child : node->children) {
            maxDepth = std::max(maxDepth, depth(child));  // Find the maximum depth among children
        }

        return 1 + maxDepth;
    }

    // Insertion functions

    // Insert a new node as a child of a specific parent node
    void insert(TreeNode<T>* parentNode, const T& value) {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        parentNode->children.push_back(newNode);
    }

    // Insert a new node at a random location in the tree
    void insertAtRandom(const T& value) {
        // For simplicity, we are choosing a random node to insert the new value
        // You might need a more sophisticated logic based on your requirements
        TreeNode<T>* randomNode = getRandomNode();  // Implement getRandomNode() as needed
        insert(randomNode, value);
    }

    // Deletion function

    // Delete a node from the tree
    void deleteNode(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        TreeNode<T>* parent = getParent(node);
        if (parent != nullptr) {
            // Find the node in the parent's list of children and remove it
            auto& children = parent->children;
            auto it = std::find(children.begin(), children.end(), node);

            if (it != children.end()) {
                children.erase(it);  // Erase the node from the vector
            }
        }
        else if (isRoot(node)) {
            // If the node is the root, delete the entire tree
            root = nullptr;
        }

        // Update parent pointers of the remaining children
        for (auto& child : node->children) {
            child->parent = parent;
        }

        // Set parent pointer to null before deleting the node
        node->parent = nullptr;

        // Recursively delete the subtree
        std::cout << "Deleting node with data: " << node->data << std::endl;
        deleteSubtree(node);
    }

    // Helper function to delete the entire subtree rooted at a given node
    void deleteSubtree(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }

        // Display deleted node's data (for debugging purposes)
        std::cout << "Deleting node with data: " << node->data << std::endl;

        // Set parent pointer to null before removal from the parent
        if (node->parent != nullptr) {
            auto& parentChildren = node->parent->children;
            auto it = std::find(parentChildren.begin(), parentChildren.end(), node);
            if (it != parentChildren.end()) {
                parentChildren.erase(it);
            }
        }

        // Recursively delete the children
        for (auto& child : node->children) {
            deleteSubtree(child);
        }

        // Clear children vector
        node->children.clear();

        // Delete the node itself
        delete node;
    }

    // Traversal function

    // Depth-first preorder traversal
    void depthFirstPreorderTraversal(TreeNode<T>* node) const {
        if (node != nullptr) {
            if (node->parent != nullptr) {
                std::cout << node->data << " ";  // Process the current node
            }
            else {
                std::cout << "Deleted node with data: " << node->data << " ";
            }

            for (const auto& child : node->children) {
                depthFirstPreorderTraversal(child);  // Recursively traverse the children
            }
        }
    }

    // Breadth-first traversal
    void breadthFirstTraversal() const {
        if (root == nullptr) {
            return;
        }

        std::queue<TreeNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode<T>* current = q.front();
            q.pop();

            std::cout << current->data << " ";  // Process the current node

            for (const auto& child : current->children) {
                q.push(child);  // Enqueue the children for later processing
            }
        }
    }
};

// Example usage:
int main() {
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Create a GeneralTree with an integer root value
    GeneralTree<int> myTree(1);

    // Access the root node
    TreeNode<int>* rootNode = myTree.getRoot();

    // Insert two children to the root
    myTree.insert(rootNode, 2);
    myTree.insert(rootNode, 3);

    // Access the first child (node with value 2)
    TreeNode<int>* node2 = myTree.getChildren(rootNode)[0];

    // Insert two children to the first child (node with value 2)
    myTree.insert(node2, 4);
    myTree.insert(node2, 5);

    // Access the second child (node with value 3)
    TreeNode<int>* node3 = myTree.getChildren(rootNode)[1];

    // Insert a child to the second child (node with value 3)
    myTree.insert(node3, 6);

    // Perform depth-first preorder traversal
    std::cout << "Depth-First Preorder Traversal: ";
    myTree.depthFirstPreorderTraversal(rootNode);
    std::cout << std::endl;

    // Perform breadth-first traversal
    std::cout << "Breadth-First Traversal: ";
    myTree.breadthFirstTraversal();
    std::cout << std::endl;

    // Display the size of the tree
    std::cout << "Size of the tree: " << myTree.size(rootNode) << std::endl;

    // Display the depth of the tree
    std::cout << "Depth of the tree: " << myTree.depth(rootNode) << std::endl;

    // Insert a new node at a random location in the tree
    int minValue = 1;  // Adjust as needed for your minimum value
    int maxValue = 100;  // Adjust as needed for your maximum value
    int randomValue = rand() % (maxValue - minValue + 1) + minValue;
    myTree.insertAtRandom(randomValue);

    // Insert a new node at a specific location in the tree
    int valueToInsert = 7;
    myTree.insert(node3, valueToInsert);

    // Perform depth-first preorder traversal after insertion
    std::cout << "Depth-First Preorder Traversal after insertion: ";
    myTree.depthFirstPreorderTraversal(rootNode);
    std::cout << std::endl;

    // Delete a node from the tree
    myTree.deleteNode(node2);

    // Perform depth-first preorder traversal after deletion
    std::cout << "Depth-First Preorder Traversal after deletion: ";
    myTree.depthFirstPreorderTraversal(rootNode);
    std::cout << std::endl;

    return 0;
}
