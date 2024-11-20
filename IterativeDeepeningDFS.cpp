/* Take Input graph of 21 nodes as discussed in Class.
Modify the existing Depth First Search program to iteratively call it for different depths.
i.e. for Depth=1 to 3 { Call DFS(Graph, starting node, Depth)}
if you are using recursion, on each recursive call reduce the Depth by 1.
Exit criteria of recursion is Depth=0
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }
    void addEdge(int v, int w) {
        adj[v].push_back(w); 
    }
};
struct NodeDepth {
    int node;
    int depth;
};

void iterativeDFS(Graph &g, int start, int maxDepth) {
    vector<bool> visited(g.V, false);
    stack<NodeDepth> stack;
    stack.push({start, maxDepth});
    while (!stack.empty()) {
        NodeDepth current = stack.top();
        stack.pop();
        if (!visited[current.node]) {
            cout << current.node << " ";
            visited[current.node] = true;
        }
        if (current.depth > 1) {
    for (int neighbor : g.adj[current.node]) {
        if (!visited[neighbor]) {
            stack.push({neighbor, current.depth - 1});
        }
    }
}

        }
    }

int main() {
    Graph g(21); 
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(3, 8);
    g.addEdge(4, 9);
    g.addEdge(4, 10);
    g.addEdge(5, 11);
    g.addEdge(5, 12);
    g.addEdge(6, 13);
    g.addEdge(6, 14);
    g.addEdge(7, 15);
    g.addEdge(8, 16);
    g.addEdge(9, 17);
    g.addEdge(10, 18);
    g.addEdge(11, 19);
    g.addEdge(12, 20);
    for (int depth = 1; depth <= 7; depth++) {
        cout << "DFS with max depth = " << depth << ":\n";
        iterativeDFS(g, 0, depth);
        cout << "\n\n";
    }

    return 0;
}

