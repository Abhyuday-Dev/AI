#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

struct GraphNode {
    int val;
    vector<GraphNode*> neighbors;
    GraphNode(int x) {
        val = x;
    }
};

void treeDFS(TreeNode *root)
{
    if (!root)
        return;
    stack<TreeNode *> s;
    s.push(root);
    while (!s.empty())
    {
        TreeNode *node = s.top();
        s.pop();
        cout << node->val << " ";
        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);
    }
}
void graphDFS(GraphNode *start)
{
    if (!start)
        return;
    stack<GraphNode *> s;
    unordered_set<GraphNode *> visited;
    s.push(start);
    visited.insert(start);
    while (!s.empty())
    {
        GraphNode *node = s.top();
        s.pop();
        cout << node->val << " ";
        for (GraphNode *neighbor : node->neighbors)
        {
            if (visited.find(neighbor) == visited.end())
            {
                s.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
}
int main()
{
    // Tree example
    TreeNode *root = new TreeNode(2);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->left = new TreeNode(7);
    root->left->right = new TreeNode(9);
    cout << "Tree DFS traversal: ";
    treeDFS(root);
    cout << endl;
    // Graph example
    GraphNode *node1 = new GraphNode(5);
    GraphNode *node2 = new GraphNode(6);
    GraphNode *node3 = new GraphNode(7);
    node1->neighbors.push_back(node2);
    node1->neighbors.push_back(node3);
    node2->neighbors.push_back(node1);
    node2->neighbors.push_back(node3);
    node3->neighbors.push_back(node1);
    node3->neighbors.push_back(node2);
    cout << "Graph DFS traversal: ";
    graphDFS(node1);
    cout << endl;
    return 0;
}