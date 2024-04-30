#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct GraphNode {
    int val;
    vector<pair<GraphNode*, int>> neighbors; // pair<neighbor, edge_weight>
    GraphNode(int x) {
        val = x;
    }
};

struct Path {
    GraphNode* node;
    int cost;
    Path(GraphNode* n, int c) {
        node = n;
        cost = c;
    }
};

struct ComparePath {
    bool operator()(const Path& a, const Path& b) const {
        return a.cost > b.cost; // prioritize lower cost
    }
};


void UCS(GraphNode *start, GraphNode *goal)
{
    priority_queue<Path, vector<Path>, ComparePath> pq;
    unordered_map<GraphNode *, int> costs;
    unordered_map<GraphNode *, GraphNode *> parents;

    pq.push(Path(start, 0));
    costs[start] = 0;

    while (!pq.empty())
    {
        GraphNode *current = pq.top().node;
        int current_cost = pq.top().cost;
        pq.pop();

        if (current == goal)
        {
            cout << "Uniform Cost Search found the goal with cost: " << current_cost << endl;
            // Reconstruct and print the path
            cout << "Path: ";
            while (current)
            {
                cout << current->val << " ";
                current = parents[current];
            }
            cout << endl;
            return;
        }
        for (auto &neighbor : current->neighbors)
        {
            GraphNode *next = neighbor.first;
            int edge_cost = neighbor.second;
            int new_cost = current_cost + edge_cost;
            if (costs.find(next) == costs.end() || new_cost < costs[next])
            {
                costs[next] = new_cost;
                pq.push(Path(next, new_cost));
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
    GraphNode *node4 = new GraphNode(9);
    node1->neighbors.push_back({node2, 3});
    node1->neighbors.push_back({node3, 6});
    node2->neighbors.push_back({node3, 2});
    node2->neighbors.push_back({node4, 8});
    node3->neighbors.push_back({node4, 4});
    UCS(node1, node3); // Find the path from node1 to node4
    return 0;
}