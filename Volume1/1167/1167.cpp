#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define N 60
typedef vector<int> vi;
class Route
{
public:
    int start, interval, times;
    Route(int start, int interval, int times) : start(start),
        interval(interval), times(times) {}
    bool operator< (const Route & route) const
    {
        return times > route.times;
    }
};
class Solution
{
public:
    int solve(vi & a, int n)
    {
        for (int i = 0; i < 30; ++i)
            for (int j = i + 1; i + j < N; ++j)
                if (check(i, j, a))
                    routes.push_back(Route(i, j, (N - 1 - i) / j + 1));
        sort(routes.begin(), routes.end());
        ans = 17;
        dfs(0, n, 0, a);
        return ans;
    }
private:
    vector<Route> routes;
    int ans;
    inline bool check(int start, int interval, const vi & a)
    {
        for (; start < N; start += interval)
            if (!a[start])
                return false;
        return true;
    }
    void dfs(int k, int n, int s, vi & a)
    {
        if (!n)
        {
            ans = min(ans, s);
            return;
        }
        for (int i = k; i < routes.size(); ++i)
        {
            if (s + n / routes[i].times >= ans)
                return;
            if (!check(routes[i].start, routes[i].interval, a))
                continue;
            for (int j = routes[i].start; j < N; j += routes[i].interval)
                --a[j];
            dfs(i, n - routes[i].times, s + 1, a);
            for (int j = routes[i].start; j < N; j += routes[i].interval)
                ++a[j];
        }
    }
};

int main()
{
    int n;
    cin >> n;
    vi a(N, 0);
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        ++a[x];
    }
    cout << Solution().solve(a, n) << endl;
    return 0;
}
