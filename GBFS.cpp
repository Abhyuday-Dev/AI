#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;
struct GraphNode
{
    int val;
    vector<pair<GraphNode *, int>> neighbors;
    GraphNode(int x) : val(x) {}
};
struct Path
{
    GraphNode *node;
    int heuristic; // heuristic value for the node
    Path(GraphNode *n, int h) : node(n), heuristic(h) {}
};
struct ComparePath
{
    bool operator()(const Path &a, const Path &b) const
    {
        return a.heuristic > b.heuristic; // prioritize lower heuristic
    }
};
void GBFS(GraphNode *start, GraphNode *goal)
{
    priority_queue<Path, vector<Path>, ComparePath> pq;
    unordered_set<GraphNode *> visited;
    unordered_map<GraphNode *, GraphNode *> parents;
    pq.push(Path(start, 0));
    while (!pq.empty())
    {
        GraphNode *current = pq.top().node;
        pq.pop();
        if (current == goal)
        {
            cout << "Goal found" << endl;
            cout << "Path: ";
            while (current)
            {
                cout << current->val << " ";
                current = parents[current];
            }
            cout << endl;
            return;
        }

        visited.insert(current);

        for (auto &neighbor : current->neighbors)
        {
            GraphNode *next = neighbor.first;
            if (visited.find(next) == visited.end())
            {
                pq.push(Path(next, next->val));
                parents[next] = current;
            }
        }
    }

    cout << "Goal not found" << endl;
}

int main()
{
    GraphNode *node1 = new GraphNode(5);
    GraphNode *node2 = new GraphNode(6);
    GraphNode *node3 = new GraphNode(7);
    GraphNode *node4 = new GraphNode(8);
    node1->neighbors.push_back({node2, 3});
    node1->neighbors.push_back({node3, 6});
    node2->neighbors.push_back({node3, 2});
    node2->neighbors.push_back({node4, 8});
    node3->neighbors.push_back({node4, 4});
    GBFS(node1, node4); // Find the path from node1 to node4
    return 0;
}