#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
typedef vector<int> vi;

class Cube4D
{
public:
    Cube4D(int id, vi neighbors) : id(id), neighbors(neighbors) {}
    int id;
    vi neighbors;
};

class Solution
{
public:
    int get_enclosing_cube(vector<Cube4D> cubes)
    {
        int n = cubes.size();
        for (int i = 0; i < n; ++i)
            map_id[cubes[i].id] = i;
        if (!is_connected(cubes))
            return -1;
        int shape[8] = {0};
        for (int k = 0; k < 8; ++k)
            for (int i = 0; i < n; ++i)
                shape[k] = max(shape[k], distance[i][k]);
        int size = 1;
        for (int k = 0; k < 8; k += 2)
            size *= shape[k] + shape[k + 1] + 1;
        return size;
    }
private:
    map<int, int> map_id;
    vector<vi> distance;
    bool is_connected(vector<Cube4D> cubes)
    {
        int n = cubes.size();
        vector<bool> v(n, false);
        distance.assign(n, vi());
        queue<int> q;
        int m = 1;
        v[0] = true;
        distance[0] = vi(8, 0);
        q.push(0);
        while (!q.empty())
        {
            int head = q.front();
            q.pop();
            for (int k = 0; k < 8; ++k)
            {
                int next = cubes[head].neighbors[k];
                if (next == 0)
                    continue;
                next = map_id[next];
                if (v[next])
                    continue;
                int next_neighbor = cubes[next].neighbors[k ^ 1];
                if (next_neighbor == 0)
                    continue;
                next_neighbor = map_id[next_neighbor];
                if (head == next_neighbor)
                {
                    ++m;
                    v[next] = true;
                    distance[next] = distance[head];
                    distance[next][k] = distance[head][k] + 1;
                    q.push(next);
                }
            }
        }
        return m == n;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<Cube4D> cubes;
        for (int i = 0; i < n; ++i)
        {
            int id;
            vi neighbors;
            cin >> id;
            for (int j = 0; j < 8; ++j)
            {
                int x;
                cin >> x;
                neighbors.push_back(x);
            }
            cubes.push_back(Cube4D(id, neighbors));
        }
        int ans = Solution().get_enclosing_cube(cubes);
        if (ans < 0)
            cout << "Inconsistent" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}
