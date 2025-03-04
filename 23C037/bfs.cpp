#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

class Graph
{
    int V;                   // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u); // Since it's an undirected graph
    }

    // BFS Traversal with Parent and Distance
    void BFS(int src)
    {
        vector<int> parent(V, -1);
        vector<int> distance(V, INT_MAX);
        queue<int> q;

        distance[src] = 0;
        q.push(src);

        cout << "BFS Traversal:\n";
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            cout << "Node: " << node << ", Parent: " << parent[node] << ", Distance: " << distance[node] << endl;

            for (int neighbor : adj[node])
            {
                if (distance[neighbor] == INT_MAX)
                {
                    parent[neighbor] = node;
                    distance[neighbor] = distance[node] + 1;
                    q.push(neighbor);
                }
            }
        }
    }

    // Find Shortest Distance and Path using BFS
    void shortestPath(int src, int dest)
    {
        vector<int> parent(V, -1);
        vector<int> distance(V, INT_MAX);
        queue<int> q;

        distance[src] = 0;
        q.push(src);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int neighbor : adj[node])
            {
                if (distance[neighbor] == INT_MAX)
                {
                    parent[neighbor] = node;
                    distance[neighbor] = distance[node] + 1;
                    q.push(neighbor);
                }
            }
        }

        // Print shortest distance
        if (distance[dest] == INT_MAX)
        {
            cout << "No path from " << src << " to " << dest << endl;
            return;
        }
        cout << "Shortest Distance from " << src << " to " << dest << ": " << distance[dest] << endl;

        // Print shortest path
        vector<int> path;
        for (int at = dest; at != -1; at = parent[at])
        {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "Shortest Path: ";
        for (int node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }

    // Cycle Detection in Undirected Graph using BFS
    bool hasCycle()
    {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : adj[node])
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = true;
                            parent[neighbor] = node;
                            q.push(neighbor);
                        }
                        else if (neighbor != parent[node])
                        {
                            return true; // Cycle detected
                        }
                    }
                }
            }
        }
        return false;
    }

    // Find Number of Connected Components using BFS
    int countConnectedComponents()
    {
        vector<bool> visited(V, false);
        int count = 0;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                count++;
                queue<int> q;
                q.push(i);
                visited[i] = true;

                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    for (int neighbor : adj[node])
                    {
                        if (!visited[neighbor])
                        {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }

        return count;
    }
};

// Menu-driven program
int main()
{
    int V, choice, u, v, src, dest;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    while (true)
    {
        cout << "\n--- Graph Operations Menu ---\n";
        cout << "1. Add Edge\n";
        cout << "2. BFS Traversal (with Parent and Distance)\n";
        cout << "3. Find Shortest Path\n";
        cout << "4. Check for Cycle\n";
        cout << "5. Find Number of Connected Components\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
            break;
        case 2:
            cout << "Enter starting node for BFS: ";
            cin >> src;
            g.BFS(src);
            break;
        case 3:
            cout << "Enter source and destination: ";
            cin >> src >> dest;
            g.shortestPath(src, dest);
            break;
        case 4:
            if (g.hasCycle())
                cout << "Cycle detected in the graph.\n";
            else
                cout << "No cycle found in the graph.\n";
            break;
        case 5:
            cout << "Number of Connected Components: " << g.countConnectedComponents() << endl;
            break;
        case 6:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }
    }

    return 0;
}
