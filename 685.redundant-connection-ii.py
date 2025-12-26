#
# @lc app=leetcode id=685 lang=python3
#
# [685] Redundant Connection II
#

# @lc code=start
from typing import Dict, List, Tuple

class Solution:
    def findRedundantDirectedConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        graph = [[] for _ in range(n + 1)]
        parent = [-1] * (n + 1)
        edge_index = {}
        root_exist = False
        last_edge = []

        for i, (u, v) in enumerate(edges):
            edge_index[(u, v)] = i
            graph[u].append(v)
            if parent[v] == -1:
                parent[v] = u
            else:
                root_exist = True
                last_edge = [u, v]

        if root_exist:
            return self.findRedundantWhenRootExists(graph, parent, last_edge, n)
        else:
            return self.findRedundantWhenNoRoot(graph, edge_index, n)


    def dfs(self, node: int, cycle: List[int], visited: Dict[int, bool], graph: List[List[int]]) -> int:
        if node in visited:
            return node if visited[node] else 0
        visited[node] = True
        cycle.append(node)
        for adj_node in graph[node]:
            cycle_start = self.dfs(adj_node, cycle, visited, graph)
            if cycle_start:
                return cycle_start
        cycle.pop()
        visited[node] = False
        return 0


    def findRedundantWhenRootExists(self, graph: List[List[int]], parent: List[int], last_edge: List[int], n: int) -> List[int]:
        root = -1
        for node in range(1, n + 1):
            if parent[node] == -1:
                root = node
                break

        visited = {}
        cycle = []
        cycle_start = self.dfs(root, cycle, visited, graph)
        if cycle_start:
            cycle = cycle[cycle.index(cycle_start):]
            return [cycle[-1], cycle[0]]
        else:
            return last_edge


    def findRedundantWhenNoRoot(self, graph: List[List[int]], edge_index: Dict[Tuple[int, int], int], n: int) -> List[int]:
        # find cycle
        # and remove last edge of the cycle
        cycle = []
        visited = {}
        for start_node in range(1, n + 1):
            cycle_start = self.dfs(start_node, cycle, visited, graph)
            if cycle_start:
                cycle = cycle[cycle.index(cycle_start):]
                break

        cycle.append(cycle[0])
        last_index = 0
        last_edge = []
        for edge in zip(cycle, cycle[1:]):
            if edge_index[edge] > last_index:
                last_index = edge_index[edge]
                last_edge = edge
        return list(last_edge)
# @lc code=end

