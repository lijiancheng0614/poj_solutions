#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

class Graph
{
public:
    Graph(int n) : n(n)
    {
        g.assign(n, vpii());
        d.assign(n, 0);
        m = 0;
    }
    void add(int x, int y, int z)
    {
        g[x].push_back(pii(y, z));
        g[y].push_back(pii(x, z));
        ++d[x];
        ++d[y];
        m = max(m, z);
    }
    bool exist_eular_circuit()
    {
        for (int i = 0; i < n; ++i)
            if (d[i] & 1)
                return false;
        return true;
    }
    vector<int> get_eular_circuit(int start)
    {
        eular_circuit.clear();
        v.assign(m + 1, false);
        dfs(start);
        return eular_circuit;
    }
private:
    vector<vpii> g;
    vector<int> d;
    vector<bool> v;
    vector<int> eular_circuit;
    int n, m;
    void dfs(int k)
    {
        for (int i = 0; i < g[k].size(); ++i)
        {
            int id = g[k][i].second;
            if (v[id])
                continue;
            v[id] = true;
            dfs(g[k][i].first);
            eular_circuit.push_back(id);
        }
    }
};

int main()
{
    int x, y, z;
    while (cin >> x >> y && x + y)
    {
        cin >> z;
        --x, --y;
        int start = min(x, y);
        Graph graph(44);
        graph.add(x, y, z);
        while (cin >> x >> y && x + y)
        {
            cin >> z;
            --x, --y;
            start = min(start, min(x, y));
            graph.add(x, y, z);
        }
        if (!graph.exist_eular_circuit())
            cout << "Round trip does not exist." << endl;
        else
        {
            vector<int> edges = graph.get_eular_circuit(start);
            for (int i = edges.size() - 1; i; --i)
                cout << edges[i] << " ";
            cout << edges[0] << endl;
        }
    }
    return 0;
}
