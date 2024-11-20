#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits.h>

using namespace std;

struct Node {
    int index;
    int g_value; 
    int h_value;  
    int f_value; 

    Node(int idx, int g, int h) : index(idx), g_value(g), h_value(h), f_value(g + h) {}
    
    bool operator>(const Node& other) const {
        return f_value > other.f_value;
    }
};

vector<vector<int>> graph = {
    {0, 6, 3, 1, 0, 0, 0, 0, 0, 0},
    {6, 0, 2, 0, 6, 4, 0, 0, 0, 0},
    {3, 2, 0, 3, 7, 0, 0, 0, 0, 0},
    {1, 0, 3, 0, 4, 7, 0, 0, 0, 0},
    {0, 6, 7, 4, 0, 3, 7, 0, 9, 9},
    {0, 4, 0, 7, 3, 0, 5, 8, 6, 9},
    {0, 0, 0, 0, 7, 5, 0, 9, 11, 12},
    {0, 0, 0, 0, 7, 8, 9, 0, 9, 14},
    {0, 0, 0, 0, 9, 6, 9, 12, 0, 14},
    {0, 0, 0, 0, 9, 9, 9, 0, 0, 15}
};

vector<int> heuristic = {15, 13, 13, 12, 10, 9, 7, 6, 5, 0};

void dfs(int start, vector<bool>& visited) {
    stack<int> s;
    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
        int node = s.top();
        s.pop();
        cout << "Visited: " << node << endl;
        for (int i = 0; i < graph[node].size(); i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                visited[i] = true;
                s.push(i);
            }
        }
    }
}

void bfs(int start) {
    queue<int> q;
    vector<bool> visited(graph.size(), false);
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << "Visited: " << node << endl;
        for (int i = 0; i < graph[node].size(); i++) {
            if (graph[node][i] != 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

void bestFirstSearch(int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<bool> visited(graph.size(), false);
    pq.push(Node(start, 0, heuristic[start]));
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited[current.index]) continue;
        visited[current.index] = true;
        cout << "Visited: " << current.index << endl;

        for (int i = 0; i < graph[current.index].size(); i++) {
            if (graph[current.index][i] != 0 && !visited[i]) {
                pq.push(Node(i, current.g_value + graph[current.index][i], heuristic[i]));
            }
        }
    }
}

void iterativeDeepening(int start) {
    for (int depth = 0; depth < graph.size(); depth++) {
        vector<bool> visited(graph.size(), false);
        dfs(start, visited);
    }
}

void beamSearch(int start, int width) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<bool> visited(graph.size(), false);
    pq.push(Node(start, 0, heuristic[start]));
    
    while (!pq.empty()) {
        vector<Node> levelNodes;
        int levelSize = pq.size();
        
        for (int i = 0; i < levelSize && i < width; i++) {
            Node current = pq.top();
            pq.pop();
            levelNodes.push_back(current);
        }

        for (auto& node : levelNodes) {
            if (!visited[node.index]) {
                visited[node.index] = true;
                cout << "Visited: " << node.index << endl;
                for (int i = 0; i < graph[node.index].size(); i++) {
                    if (graph[node.index][i] != 0 && !visited[i]) {
                        pq.push(Node(i, node.g_value + graph[node.index][i], heuristic[i]));
                    }
                }
            }
        }
    }
}

void aStar(int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<bool> visited(graph.size(), false);
    pq.push(Node(start, 0, heuristic[start]));
    
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (visited[current.index]) continue;
        visited[current.index] = true;
        cout << "Visited: " << current.index << endl;

        for (int i = 0; i < graph[current.index].size(); i++) {
            if (graph[current.index][i] != 0 && !visited[i]) {
                pq.push(Node(i, current.g_value + graph[current.index][i], heuristic[i]));
            }
        }
    }
}

int main() {
    int startNode, choice, width;
    vector<bool> visited(graph.size(), false);  // Initialize visited vector here

    cout << "Enter the starting node: ";
    cin >> startNode;

    cout << "\nSelect the search method:" << endl;
    cout << "1. DFS (Depth First Search)" << endl;
    cout << "2. BFS (Breadth First Search)" << endl;
    cout << "3. Best First Search" << endl;
    cout << "4. Iterative Deepening" << endl;
    cout << "5. Beam Search" << endl;
    cout << "6. A* Algorithm" << endl;
    cout << "Enter your choice (1-6): ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\nDFS:" << endl;
            dfs(startNode, visited);
            break;

        case 2:
            cout << "\nBFS:" << endl;
            bfs(startNode);
            break;

        case 3:
            cout << "\nBest First Search:" << endl;
            bestFirstSearch(startNode);
            break;

        case 4:
            cout << "\nIterative Deepening:" << endl;
            iterativeDeepening(startNode);
            break;

        case 5:
            cout << "\nEnter beam width: ";
            cin >> width;
            cout << "\nBeam Search (Width=" << width << "):" << endl;
            beamSearch(startNode, width);
            break;

        case 6:
            cout << "\nA* Algorithm:" << endl;
            aStar(startNode);
            break;

        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    return 0;
}
