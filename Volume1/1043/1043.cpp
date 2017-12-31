#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<char, string> pcs;
typedef pair<string, string> pss;
typedef vector<int> vi;
typedef vector<bool> vb;

class Graph
{
public:
    Graph(int n, int m) : n(n), m(m)
    {
        g.assign(n, vb(m, true));
    }
    void remove(int i, int j)
    {
        g[i][j] = false;
    }
    vi get_match()
    {
        vi match_id(n, -1);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (g[i][j])
                {
                    g[i][j] = false;
                    if (max_match() != n)
                    {
                        g[i][j] = true;
                        match_id[i] = j;
                        break;
                    }
                    g[i][j] = true;
                }
        return match_id;
    }
private:
    vector<vb> g;
    vi l;
    vb T;
    int n, m;
    int max_match()
    {
        l.assign(m, -1);
        int s = 0;
        for (int i = 0; i < n; ++i)
        {
            T.assign(m, false);
            s += find(i);
        }
        return s;
    }
    bool find(int k)
    {
        for (int j = 0; j < m; ++j)
            if (g[k][j] && !T[j])
            {
                T[j] = true;
                if (l[j] < 0 || find(l[j]))
                {
                    l[j] = k;
                    return true;
                }
            }
        return false;
    }
};

class Solution
{
public:
    vector<pss> solve(vector<string> & a, vector<pcs> & logs)
    {
        map<string, int> h;
        int n = a.size();
        for (int i = 0; i < n; ++i)
            h[a[i]] = i;
        Graph g(n, n);
        vb v(n, false);
        b.clear();
        for (int i = 0; i < logs.size(); ++i)
            if (logs[i].first == 'E')
                v[get_name(logs[i].second)] = true;
            else if (logs[i].first == 'L')
                v[get_name(logs[i].second)] = false;
            else if (logs[i].first == 'M')
            {
                int id = h[logs[i].second];
                for (int j = 0; j < n; ++j)
                    if (!v[j])
                        g.remove(j, id);
            }
        vi match_id = g.get_match();
        vector<pss> ans;
        for (int i = 0; i < n; ++i)
            ans.push_back(pss(b[i], match_id[i] == -1 ? "???" : a[match_id[i]]));
        sort(ans.begin(), ans.end());
        return ans;
    }
private:
    vector<string> b;
    int get_name(string s)
    {
        for (int i = 0; i < b.size(); ++i)
            if (b[i] == s)
                return i;
        b.push_back(s);
        return b.size() - 1;
    }
};

int main()
{
    vector<string> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        a.push_back(s);
    }
    vector<pcs> logs;
    char log_type;
    while (cin >> log_type && log_type != 'Q')
    {
        string log_arg;
        cin >> log_arg;
        logs.push_back(pcs(log_type, log_arg));
    }
    vector<pss> ans = Solution().solve(a, logs);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i].first << ":" << ans[i].second << endl;
    return 0;
}
