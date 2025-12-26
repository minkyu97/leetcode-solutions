/*
 * @lc app=leetcode id=685 lang=cpp
 *
 * [685] Redundant Connection II
 */
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

using namespace std;

// @lc code=start
class pair_hash {
public:
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Solution {
public:
    vector<int> findCycle(int node, vector<vector<int>>& graph, unordered_map<int, bool>& visited, vector<int>& path) {
        if (visited.find(node) != visited.end()) {
            if (visited[node]) {
                return {};
            } else {
                // cycle detected
                auto it  = find(path.begin(), path.end(), node);
                return vector<int>(it, path.end());
            }
        }

        visited[node] = false;
        path.push_back(node);
        for (const int neighbor: graph[node]) {
            vector<int> cycle = findCycle(neighbor, graph, visited, path);
            if (!cycle.empty()) {
                return cycle;
            }
        }
        path.pop_back();
        visited[node] = true;
        return {};
    }

    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        const int n = edges.size();
        vector<vector<int>> graph(n + 1, vector<int>());
        vector<int> parents(n + 1, -1);
        unordered_map<pair<int, int>, int, pair_hash> edge_index;

        // possible scenarios:
        // 1. a node has two parents, no cycle
        // 2. a node has two parents, with cycle
        // 3. no node has two parents, with cycle

        bool two_parents = false;
        int last_two_parents_edge = -1;

        for (const auto& edge: edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            int curr_index = &edge - &edges[0];
            edge_index[{u, v}] = curr_index;
            
            if (parents[v] != -1) {
                two_parents = true;
                last_two_parents_edge = curr_index;
            } else {
                parents[v] = u;
            }
        }

        if (two_parents) {
            // find root
            int root = -1;
            for (root = 1; root <= n; ++root) {
                if (parents[root] == -1) {
                    break;
                }
            }
            // find cycle
            vector<int> path;
            unordered_map<int, bool> visited;
            vector<int> cycle = findCycle(root, graph, visited, path);
            if (cycle.empty()) {
                // scenario 1
                return edges[last_two_parents_edge];
            } else {
                // scenario 2
                return {cycle.back(), cycle.front()};
            }
        } else {
            // scenario 3
            unordered_map<int, bool> visited;
            for (int node = 1; node <= n; ++node) {
                vector<int> path;
                vector<int> cycle = findCycle(node, graph, visited, path);
                if (cycle.empty()) continue;

                size_t last_index = 0;
                vector<int> last_edge;
                for (size_t i = 0; i < cycle.size(); ++i) {
                    int u = cycle[i];
                    int v = cycle[(i + 1) % cycle.size()];
                    int index = edge_index[{u, v}];
                    if (index > last_index) {
                        last_index = index;
                        last_edge = {u, v};
                    }
                }
                return last_edge;
            }
        }

        return {};
    }
};
// @lc code=end

int main() {
    Solution sol;
    vector<vector<int>> edges1 = {{1,2}, {1,3}, {2,3}};
    vector<int> res1 = sol.findRedundantDirectedConnection(edges1);
    assert((res1 == vector<int>{2,3}));
    // Expected output: [2,3]

    vector<vector<int>> edges2 = {{1,2}, {2,3}, {3,4}, {4,1}, {1,5}};
    vector<int> res2 = sol.findRedundantDirectedConnection(edges2);
    assert((res2 == vector<int>{4,1}));
    // Expected output: [4,1]

    return 0;
}
