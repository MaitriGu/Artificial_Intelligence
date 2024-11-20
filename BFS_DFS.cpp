/*Implement in Following Way:
1. In main Function, Take Graph of 8-10 nodes as an input. You can number the nodes starting from 0.
2. Ask User the Starting node.
3. Ask Option for BFS/DFS
4. Create Separate Functions for BFS and DFS with Input Arguments as (Graph, Starting Node). These functions will return the list containing the order in which these nodes are being visited.
5. Based on Option entered by user, Execute BFS or DFS.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

void addEdge(vector<vector<int>> &graph, int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void bfs(const vector<vector<int>> &graph, int start)
{
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty())
    {
        int current = q.front();
        q.pop();
        cout << current << " ";

        vector<int> Neighbours = graph[current];

        for (int neighbour : Neighbours)
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }
    cout << endl;
}

void dfs(const vector<vector<int>> &graph, int start)
{
    vector<bool> visited(graph.size(), false);
    stack<int> s;
    s.push(start);

    while (!s.empty())
    {
        int vertex = s.top();
        s.pop();

        if (!visited[vertex])
        {
            visited[vertex] = true;
            cout << vertex << " ";

            vector<int> sortedNeighbours = graph[vertex];
            sort(sortedNeighbours.rbegin(), sortedNeighbours.rend());

            for (int neighbour:sortedNeighbours)
            {
                if (!visited[neighbour])
                {
                    s.push(neighbour);
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    int numVertices, numEdges;
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<vector<int>> graph(numVertices);

    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < numEdges; i++)
    {
        int u, v;
        cin >> u >> v;
        addEdge(graph, u, v);
    }

    int choice;
    do
    {
        cout << "\nChoose an option:\n";
        cout << "1. BFS\n";
        cout << "2. DFS\n";
        cout << "3. Exit\n";
        cin >> choice;

        int startVertex;

        switch (choice)
        {
        case 1:
            cout << "Enter the starting vertex for BFS: ";
            cin >> startVertex;
            cout << "BFS: ";
            bfs(graph, startVertex);
            break;
        case 2:
            cout << "Enter the starting vertex for DFS: ";
            cin >> startVertex;
            cout << "DFS: ";
            dfs(graph, startVertex);
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option. Please try again.\n";
            break;
        }
    } while (choice != 3);

    return 0;
}
