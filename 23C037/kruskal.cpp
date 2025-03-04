#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Function to perform BFS for finding augmenting path in Ford-Fulkerson
bool bfs(vector<vector<int>> &residualGraph, int source, int sink, vector<int> &parent)
{
    int n = residualGraph.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v = 0; v < n; v++)
        {
            if (!visited[v] && residualGraph[u][v] > 0)
            { // Positive residual capacity
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if (v == sink)
                    return true; // Augmenting path found
            }
        }
    }
    return false;
}

// Ford-Fulkerson Algorithm to find maximum flow
int fordFulkerson(vector<vector<int>> &graph, int source, int sink)
{
    int n = graph.size();
    vector<vector<int>> residualGraph = graph;
    vector<int> parent(n);
    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent))
    { // While an augmenting path exists
        int pathFlow = INT_MAX;
        int v = sink;

        // Find minimum residual capacity in the path
        while (v != source)
        {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
            v = parent[v];
        }

        // Update residual capacities
        v = sink;
        while (v != source)
        {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
            v = parent[v];
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

// Convert bipartite graph to a flow network
vector<vector<int>> createFlowNetwork(int U, int V, vector<pair<int, int>> edges)
{
    int totalNodes = U + V + 2;
    int source = 0, sink = U + V + 1;
    vector<vector<int>> graph(totalNodes, vector<int>(totalNodes, 0));

    // Connect source to U partition
    for (int u = 1; u <= U; u++)
    {
        graph[source][u] = 1;
    }

    // Connect V partition to sink
    for (int v = U + 1; v <= U + V; v++)
    {
        graph[v][sink] = 1;
    }

    // Connect U nodes to V nodes based on bipartite edges
    for (auto &edge : edges)
    {
        int u = edge.first, v = edge.second;
        graph[u][v] = 1; // Capacity of 1 for matching
    }

    return graph;
}

// Menu function to choose between Maximum Flow and Maximum Bipartite Matching
void menu()
{
    while (true)
    {
        cout << "\n=========== MENU ===========\n";
        cout << "1. Find Maximum Flow (Ford-Fulkerson)\n";
        cout << "2. Find Maximum Bipartite Matching (Ford-Fulkerson)\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            // User Input for Flow Network
            int nodes, edges, u, v, capacity;
            cout << "Enter the number of nodes: ";
            cin >> nodes;

            vector<vector<int>> graph(nodes, vector<int>(nodes, 0));
            cout << "Enter number of edges: ";
            cin >> edges;

            cout << "Enter edges with capacities (format: u v capacity): \n";
            for (int i = 0; i < edges; i++)
            {
                cin >> u >> v >> capacity;
                graph[u][v] = capacity;
            }

            int source, sink;
            cout << "Enter source node: ";
            cin >> source;
            cout << "Enter sink node: ";
            cin >> sink;

            cout << "Maximum Flow: " << fordFulkerson(graph, source, sink) << endl;
        }
        else if (choice == 2)
        {
            // User Input for Bipartite Graph
            int U, V, edges;
            cout << "Enter number of nodes in Left Partition (U): ";
            cin >> U;
            cout << "Enter number of nodes in Right Partition (V): ";
            cin >> V;

            cout << "Enter number of edges: ";
            cin >> edges;
            vector<pair<int, int>> edgeList;

            cout << "Enter edges between U and V (format: U V): \n";
            for (int i = 0; i < edges; i++)
            {
                int u, v;
                cin >> u >> v;
                edgeList.push_back({u, v});
            }

            vector<vector<int>> graph = createFlowNetwork(U, V, edgeList);
            int maxMatching = fordFulkerson(graph, 0, U + V + 1);
            cout << "Maximum Bipartite Matching: " << maxMatching << endl;
        }
        else if (choice == 3)
        {
            cout << "Exiting the program.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
}

// Main function
int main()
{
    menu();
    return 0;
}
