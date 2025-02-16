#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

class Graph
{
    int V;
    vector<vector<int>> adj;
    vector<vector<int>> revAdj;
    vector<int> discovery, finish, parent;
    int time;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
        revAdj.resize(V);
        discovery.assign(V, -1);
        finish.assign(V, -1);
        parent.assign(V, -1);
        time = 0;
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        revAdj[v].push_back(u);
        cout << "Edge added successfully.\n";
    }

    void DFS(int u, vector<bool> &visited)
    {
        visited[u] = true;
        discovery[u] = ++time;

        for (int v : adj[u])
        {
            if (!visited[v])
            {
                parent[v] = u;
                DFS(v, visited);
            }
        }

        finish[u] = ++time;
    }

    void DFSTraversal()
    {
        vector<bool> visited(V, false);
        time = 0;

        cout << "\nNode  | Discovery Time | Finish Time\n";
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                DFS(i, visited);
            }
        }

        for (int i = 0; i < V; i++)
        {
            cout << " " << i << "    | " << discovery[i] << "              | " << finish[i] << endl;
        }
    }

    void classifyEdges()
    {
        cout << "\nEdge Classification:\n";
        vector<bool> visited(V, false);
        time = 0;

        for (int u = 0; u < V; u++)
        {
            if (!visited[u])
            {
                DFS(u, visited);
            }
        }

        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                if (parent[v] == u)
                {
                    cout << "(" << u << " -> " << v << ") Tree Edge\n";
                }
                else if (discovery[u] < discovery[v] && finish[u] > finish[v])
                {
                    cout << "(" << u << " -> " << v << ") Forward Edge\n";
                }
                else if (discovery[u] > discovery[v] && finish[u] < finish[v])
                {
                    cout << "(" << u << " -> " << v << ") Back Edge (Cycle detected!)\n";
                }
                else
                {
                    cout << "(" << u << " -> " << v << ") Cross Edge\n";
                }
            }
        }
    }

    bool detectCycleUtil(int u, vector<bool> &visited, vector<bool> &recStack)
    {
        visited[u] = true;
        recStack[u] = true;

        for (int v : adj[u])
        {
            if (!visited[v] && detectCycleUtil(v, visited, recStack))
            {
                return true;
            }
            else if (recStack[v])
            {
                return true;
            }
        }

        recStack[u] = false;
        return false;
    }

    void detectCycle()
    {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && detectCycleUtil(i, visited, recStack))
            {
                cout << "Cycle detected in the graph!\n";
                return;
            }
        }
        cout << "No cycle found in the graph.\n";
    }

    void topologicalSortDFS()
    {
        stack<int> s;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                topoDFS(i, visited, s);
            }
        }

        cout << "Topological Sort (DFS): ";
        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
        cout << endl;
    }

    void topoDFS(int u, vector<bool> &visited, stack<int> &s)
    {
        visited[u] = true;

        for (int v : adj[u])
        {
            if (!visited[v])
            {
                topoDFS(v, visited, s);
            }
        }

        s.push(u);
    }

    void findSCCs()
    {
        stack<int> s;
        vector<bool> visited(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                topoDFS(i, visited, s);
            }
        }

        fill(visited.begin(), visited.end(), false);
        int count = 0;

        while (!s.empty())
        {
            int u = s.top();
            s.pop();

            if (!visited[u])
            {
                count++;
                SCCDFS(u, visited);
                cout << endl;
            }
        }
        cout << "Total Strongly Connected Components: " << count << endl;
    }

    void SCCDFS(int u, vector<bool> &visited)
    {
        visited[u] = true;
        cout << u << " ";

        for (int v : revAdj[u])
        {
            if (!visited[v])
            {
                SCCDFS(v, visited);
            }
        }
    }

    void topoSortIndegree()
    {
        vector<int> indegree(V, 0);
        queue<int> q;

        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                indegree[v]++;
            }
        }

        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        cout << "Topological Sort (In-degree): ";
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u])
            {
                indegree[v]--;
                if (indegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
};

int main()
{
    int V, choice, u, v;
    cout << "Enter the number of vertices: ";
    cin >> V;

    Graph g(V);

    while (true)
    {
        cout << "\n--- Graph Operations Menu ---\n";
        cout << "1. DFS Traversal (Discovery & Finish Time)\n";
        cout << "2. Classify Edges\n";
        cout << "3. Detect Cycle in Directed Graph\n";
        cout << "4. Topological Sorting (DFS)\n";
        cout << "5. Find Strongly Connected Components (SCC)\n";
        cout << "6. Topological Sorting (In-degree)\n";
        cout << "7. Add Edge\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            g.DFSTraversal();
            break;
        case 2:
            g.classifyEdges();
            break;
        case 3:
            g.detectCycle();
            break;
        case 4:
            g.topologicalSortDFS();
            break;
        case 5:
            g.findSCCs();
            break;
        case 6:
            g.topoSortIndegree();
            break;
        case 7:
            cout << "Enter edge (u v): ";
            cin >> u >> v;
            g.addEdge(u, v);
            break;
        case 8:
            cout << "Exiting program.\n";
            return 0;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
