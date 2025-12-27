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
class UnionFind {
public:
    vector<int> parents;

    UnionFind(int n) : parents(n) {
        iota(parents.begin(), parents.end(), 0);
    }

    int find(int node) {
        int parent = parents[node];
        if (parent == node) return parent;

        return parents[node] = find(parent);
    }
 
    void merge(int a, int b) {
        // a is a parent of b
        int a_root = find(a);
        int b_root = find(b);
        if (a_root != b_root) {
            parents[a_root] = b_root;
        }
    }
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        // possible scenarios:
        // 1. a node has two parents, no cycle
        // 2. a node has two parents, with cycle
        // 3. no node has two parents, with cycle

        int n = edges.size();
        vector<int> indegree(n + 1, -1);
        vector<int> edge1, edge2;

        for (auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (indegree[v] != -1) {
                edge1 = {indegree[v], v};
                edge2 = edge;

                // mark the second edge as invalid and skip it in union find
                edge[1] = -1; // mark as invalid
            } else {
                indegree[v] = u;
            }
        }

        UnionFind uf(n + 1);
        
        for (const auto& edge : edges) {
            if (edge[1] == -1) continue;

            int u = edge[0], v = edge[1];
            if (uf.find(u) == uf.find(v)) {
                // cycle detected
                if (edge1.empty()) {
                    // if no two parents, return the last edge causing the cycle
                    return edge;
                } else {
                    // if two parents, return the first edge causing two parents
                    // since the second edge is skipped, the cycle must be caused by the first edge
                    return edge1;
                }
            }
            uf.merge(u, v);
        }

        // if no cycle detected, return the second edge causing two parents
        return edge2;
    }
};
// @lc code=end

int main() {
    Solution sol;

    cout << "Test case 1" << endl;
    vector<vector<int>> edges1 = {{1,2}, {1,3}, {2,3}};
    vector<int> res1 = sol.findRedundantDirectedConnection(edges1);
    assert((res1 == vector<int>{2,3}));
    // Expected output: [2,3]

    cout << "Test case 2" << endl;
    vector<vector<int>> edges2 = {{1,2}, {2,3}, {3,4}, {4,1}, {1,5}};
    vector<int> res2 = sol.findRedundantDirectedConnection(edges2);
    assert((res2 == vector<int>{4,1}));
    // Expected output: [4,1]

    cout << "Test case 3" << endl;
    vector<vector<int>> edges3 = {{1,2}, {2,3}, {3,4}, {4,2}};
    vector<int> res3 = sol.findRedundantDirectedConnection(edges3);
    assert((res3 == vector<int>{4,2}));
    // Expected output: [4,2]

    cout << "Test case 4" << endl;
    vector<vector<int>> edges4 = {{1,2}, {3,4}, {4,2}, {2,3}};
    vector<int> res4 = sol.findRedundantDirectedConnection(edges4);
    assert((res4 == vector<int>{4,2}));

    cout << "Test case 5" << endl;
    vector<vector<int>> edges5 = {{3,4}, {4,1}, {1,2}, {2,3}, {5,1}};
    vector<int> res5 = sol.findRedundantDirectedConnection(edges5);
    assert((res5 == vector<int>{4,1}));
    // Expected output: [4,1]
    return 0;
}
