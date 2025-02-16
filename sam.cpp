#include <iostream>
#include <vector>
using namespace std;
int i, j;
void initgraph(vector<vector<int>> &graph, int v)
{

    graph.resize(v, vector<int>(v, 0));
}
void addedge(vector<vector<int>> &graph, int s, int d)
{
    graph[s - 1][d - 1] = 1;
    graph[d - 1][s - 1] = 1;
}
void removeedge(vector<vector<int>> &graph, int s, int d)
{
    graph[s - 1][d - 1] = 0;
    graph[d - 1][s - 1] = 0;
}
void printgraph(vector<vector<int>> &graph, int v)
{
    cout << endl
         << "  ";
    for (j = 0; j < v; j++)
    {
        cout << j + 1 << " ";
    }
    cout << endl;
    for (i = 0; i < v; i++)
    {
        cout << i + 1 << " ";
        for (j = 0; j < v; j++)
        {

            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
{
    cout << "Enter the number of vertices:";
    int v, s, d, n = 1;
    cin >> v;
    vector<vector<int>> graph;
    initgraph(graph, v);
    printgraph(graph, v);
    while (n == 1)
    {
        int x;
        cout << "Enter one of the following:\n1) Add edge\n2) Remove edge\n3) display graph\n4) Exit\nEnter:";
        cin >> x;
        switch (x)
        {
        case 1:
            cout << "Add the source and the destination:";
            cin >> s >> d;
            addedge(graph, s, d);
            printgraph(graph, v);
            break;
        case 2:
            cout << "Add the source and the destination:";
            cin >> s >> d;
            removeedge(graph, s, d);
            printgraph(graph, v);

            break;
        case 3:
            printgraph(graph, v);
            break;
        case 4:
            cout << "Exiting...";
            n = 0;
            break;
        }
    }
}