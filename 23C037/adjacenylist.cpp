#include <iostream>
#include <vector>
using namespace std;
void addedge(vector<vector<int>> &graph, int s, int d)
{
    graph[s - 1].push_back(d - 1);
    graph[d - 1].push_back(s - 1);
}
void printgraph(vector<vector<int>> &graph, int v)
{
    cout << endl;
    for (int i = 0; i < v; i++)
    {

        cout << i + 1 << " : ";
        for (int j : graph[i])
        {
            cout << j + 1 << "->";
        }
        cout << endl;
    }
}

int main()
{

    cout << "Enter the number of vertices:";
    int v, x, s, d;
    cin >> v;
    vector<vector<int>> graph(v);
    while (true)
    {
        cout << "Enter the choices\n1) Add edge\n2)print graph\n3)exit\nEnter:";
        cin >> x;
        if (x == 3)
        {
            break;
        }
        switch (x)
        {
        case 1:
            cout << "Enter the source and destination vertex";
            cin >> s >> d;
            addedge(graph, s, d);
            printgraph(graph, v);
            break;
        case 2:
            printgraph(graph, v);
            break;
        default:
            cout << "Enter the correct choice!!!";
            break;
        }
    }
}