#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;
typedef pair<int, string> pis;
typedef vector<int> vi;
typedef vector<vi> vvi;
const int oo = 1 << 30;
class Solution
{
public:
    Solution(const vector<piii> & edges, const vector<string> & names)
    {
        this->names = names;
        n = names.size();
        d.assign(n, vi(n, oo));
        vvi nearest(n, vi(n, 0));
        for (int i = 0; i < edges.size(); ++i)
        {
            int x = edges[i].first.first;
            int y = edges[i].first.second;
            int z = edges[i].second;
            d[x][y] = d[y][x] = z;
            nearest[x][y] = y;
            nearest[y][x] = x;
        }
        floyd();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (j != i)
                    for (int k = 0; k < n; ++k)
                        if (k != i && k != j && nearest[i][k] == k && d[i][j] == d[i][k] + d[k][j])
                        {
                            nearest[i][j] = k;
                            break;
                        }
        cities_to.assign(n, vvi(n, vi()));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (j != i && names[j] != "")
                    cities_to[i][nearest[i][j]].push_back(j);
    }
    vector<pis> get_sign_outputs(int x, int y, int z)
    {
        vector<pis> outputs;
        for (int i = 0; i < cities_to[x][y].size(); ++i)
        {
            int k = cities_to[x][y][i];
            outputs.push_back(pis((d[x][k] - z + 50) / 100, names[k]));
        }
        sort(outputs.begin(), outputs.end());
        return outputs;
    }
private:
    vector<vi> d;
    vector<string> names;
    vector<vvi> cities_to;
    int n;
    void floyd()
    {
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                if (k != i && d[i][k] < oo)
                    for (int j = 0; j < n; ++j)
                        if (k != j && d[k][j] < oo)
                            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    }
};

int main()
{
    int n, m, k, s;
    cin >> n >> m >> k;
    vector<piii> edges;
    while (m--)
    {
        int x, y;
        double z;
        cin >> x >> y >> z;
        edges.push_back(piii(pii(x, y), int(z * 100 + 0.5)));
    }
    vector<string> names(n, "");
    while (k--)
    {
        int x;
        cin >> x;
        cin >> names[x];
    }
    Solution solution(edges, names);
    cin >> s;
    vector<piii> signs;
    while (s--)
    {
        int x, y;
        double z;
        cin >> x >> y >> z;
        vector<pis> outputs = solution.get_sign_outputs(x, y, int(z * 100 + 0.5));
        for (int i = 0; i < outputs.size(); ++i)
            cout << setw(20) << setiosflags(ios_base::left) <<
                 outputs[i].second << outputs[i].first << endl;
        cout << endl;
    }
    return 0;
}
