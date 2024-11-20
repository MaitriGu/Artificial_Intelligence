/*Use following two test Graphs for testing your program with different types of Width

1. Constant Width at Level, Wl=2
2. Constant Width for Node, Wn=2

Test for different types of Width: width values, w=1,2,3 at  both Node and Level.

# TESTCASES:

## Sample 10 Node Graph
# graph =[[0, 1, 1, 0, 0, 1, 0, 0, 0, 0], 
#         [1, 0, 1, 1, 0, 0, 0, 0, 0, 0], 
#         [1, 1, 0, 0, 1, 0, 0, 1, 0, 0], 
#         [0, 1, 0, 0, 1, 0, 1, 0, 1, 0], 
#         [0, 0, 1, 1, 0, 1, 1, 0, 0, 0], 
#         [1, 0, 0, 0, 1, 0, 0, 0, 0, 1], 
#         [0, 0, 0, 1, 1, 0, 0, 1, 0, 0], 
#         [0, 0, 1, 0, 0, 0, 1, 0, 0, 0], 
#         [0, 0, 0, 1, 0, 0, 0, 0, 0, 1], 
#         [0, 0, 0, 0, 0, 1, 0, 0, 1, 0]]

## Sample 12 Node Graph 
# graph =[[0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0], 
#         [1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0], 
#         [0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0], 
#         [0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0], 
#         [0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0], 
#         [0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0], 
#         [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 
#         [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0], 
#         [1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1], 
#         [0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0], 
#         [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1], 
#         [0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0]]
*/
#include <bits/stdc++.h>
using namespace std;
vector<int> BFS_level_constant(const vector<vector<int>>& graph, int width, int start_pt) {
int n = graph.size();
queue<int> q;
vector<int> bfs_traverse;
vector<int> visited(n, 0);
if (start_pt >= n) {
cout << "INVALID START \n";
return {};
}
q.push(start_pt);

visited[start_pt] = 1;
while (!q.empty()) {
int level_size = q.size();
vector<int> current_level;
for (int i = 0; i < level_size; ++i) {
int vertex = q.front();
q.pop();
bfs_traverse.push_back(vertex);
current_level.push_back(vertex);
for (int j = 0; j < n && current_level.size() < width; ++j) {
if (!visited[j] && graph[vertex][j] == 1) {
q.push(j);
visited[j] = 1;
}
}
}
}
return bfs_traverse;
}
vector<int> BFS_node_constant(const vector<vector<int>>& graph, int width, int start_pt) {
int n = graph.size();
queue<int> q;
vector<int> bfs_traverse;
vector<int> visited(n, 0);
if (start_pt >= n) {
cout << "INVALID START\n";
return {};
}
q.push(start_pt);
visited[start_pt] = 1;
while (!q.empty()) {
int vertex = q.front();
q.pop();
bfs_traverse.push_back(vertex);
int cnt = 0;
for (int i = 0; i < n && cnt < width; ++i) {
if (!visited[i] && graph[vertex][i] == 1) {
q.push(i);
visited[i] = 1;
cnt++;
}
}
}
return bfs_traverse;
}
void test_graph(const vector<vector<int>>& graph, int start_pt) {

cout << "Testing with graph:" << endl;
cout << "Sample Graph" << endl;
for (int width = 1; width <= 3; ++width) {
cout << "\nConstant Width at Level (Wl=" << width << "):" << endl;
vector<int> bfs_level = BFS_level_constant(graph, width, start_pt);
for (int node : bfs_level) {
cout << node << " ";
}
cout << endl;
cout << "Constant Width at Node (Wn=" << width << "):" << endl;
vector<int> bfs_node = BFS_node_constant(graph, width, start_pt);
for (int node : bfs_node) {
cout << node << " ";
}
cout << endl;
}
}
int main() {
vector<vector<int>> graph1 = {
{0, 1, 1, 0, 0, 1, 0, 0, 0, 0},
{1, 0, 1, 1, 0, 0, 0, 0, 0, 0},
{1, 1, 0, 0, 1, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
{0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
{0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
{0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 1, 0, 0, 1, 0}
};
vector<vector<int>> graph2 = {
{0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
{0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
{0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0}
};
int start_pt;
cout << "Enter the start point (0 to n-1): ";
cin >> start_pt;
cout << "\nTesting on Sample 10 Node Graph:" << endl;
test_graph(graph1, start_pt);

cout << "\nTesting on Sample 12 Node Graph:" << endl;
test_graph(graph2, start_pt);
return 0;
}