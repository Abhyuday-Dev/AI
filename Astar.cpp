#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>
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
    int g_cost; // Actual cost from start node
    int f_cost; // Estimated total cost (g_cost + heuristic)
    Path(GraphNode *n, int g, int f) : node(n), g_cost(g), f_cost(f) {}
};
struct ComparePath
{
    bool operator()(const Path &a, const Path &b) const
    {
        return a.f_cost > b.f_cost; // prioritize lower f_cost
    }
};
void AStar(GraphNode *start, GraphNode *goal)
{
    priority_queue<Path, vector<Path>, ComparePath> pq;
    unordered_map<GraphNode *, int> g_costs;
    unordered_map<GraphNode *, GraphNode *> parents;

    pq.push(Path(start, 0, INT_MAX)); // Initial f_cost is set to infinity
    g_costs[start] = 0;

    while (!pq.empty())
    {
        GraphNode *current = pq.top().node;
        int current_g_cost = pq.top().g_cost;
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

        for (auto &neighbor : current->neighbors)
        {
            GraphNode *next = neighbor.first;
            int edge_cost = neighbor.second;
            int new_g_cost = current_g_cost + edge_cost;
            int f_cost = new_g_cost + next->val;

            if (g_costs.find(next) == g_costs.end() || new_g_cost < g_costs[next])
            {
                g_costs[next] = new_g_cost;
                pq.push(Path(next, new_g_cost, f_cost));
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
    AStar(node1, node4); // Find the path from node1 to node4
    return 0;
}