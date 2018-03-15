#include <iostream>
#include <vector>
using namespace std;
const double oo = 1e9;
typedef vector<bool> vb;
class Point
{
public:
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator-(const Point & i) const
    {
        return Point(x - i.x, y - i.y);
    }
    double operator^(const Point & i) const
    {
        return x * i.y - y * i.x;
    }
};
class Solution
{
public:
    int solve(int m, const vector<Point> & points, const vector<vb> & g)
    {
        n = points.size();
        this->m = m;
        this->points = points;
        this->g = g;
        ans = 0;
        path.assign(m, 0);
        v.assign(n, false);
        for (start_id = 0; start_id < n; ++start_id)
            dfs(start_id, 1);
        return ans;
    }
private:
    vector<Point> points;
    vector<vb> g;
    vector<int> path;
    vb v;
    int n, m, start_id, ans;
    double area()
    {
        double s = 0;
        for (int i = 0; i < m; ++i)
            s += points[path[i]] ^ points[path[(i + 1) % m]];
        return s;
    }
    bool is_cross(const Point & a, const Point & b, const Point & c, const Point & d)
    {
        return max(a.x, b.x) >= min(c.x, d.x)  &&
               max(c.x, d.x) >= min(a.x, b.x)  &&
               max(a.y, b.y) >= min(c.y, d.y)  &&
               max(c.y, d.y) >= min(a.y, b.y)  &&
               ((b - a) ^ (c - a)) * ((b - a) ^ (d - a)) <= 0 &&
               ((d - c) ^ (a - c)) * ((d - c) ^ (b - c)) <= 0;
    }
    bool is_inside(const Point & p1)
    {
        bool flag = false;
        Point p0(oo, 1000);
        for (int i = 0; i < m; ++i)
            if (is_cross(p0, p1, points[path[i]], points[path[(i + 1) % m]]))
                flag = !flag;
        return flag;
    }
    bool is_polygon()
    {
        if (area() < 0)
            return false;
        for (int i = 0; i < n; ++i)
            if (!v[i] && is_inside(points[i]))
                return false;
        if (m <= 3)
            return true;
        for (int i = 0; i < m - 2; ++i)
        {
            int k = i ? m : m - 1;
            for (int j = i + 2; j < k; ++j)
                if (g[path[i]][path[j]])
                    return false;
        }
        return true;
    }
    void dfs(int k, int s)
    {
        v[k] = true;
        path[m - s] = k;
        if (s == m)
        {
            if (g[k][start_id] && is_polygon())
                ++ans;
            v[k] = false;
            return;
        }
        for (int i = start_id; i < n; ++i)
            if (!v[i] && g[k][i])
                dfs(i, s + 1);
        v[k] = false;
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
        vector<Point> points(n, Point());
        vector<vb> g(n, vb(n, false));
        while (n--)
        {
            int i, j, k;
            double x, y;
            cin >> i;
            --i;
            cin >> points[i].x >> points[i].y >> k;
            while (k--)
            {
                cin >> j;
                --j;
                g[i][j] = g[j][i] = true;
            }
        }
        cin >> n;
        cout << Solution().solve(n, points, g) << endl;
    }
    return 0;
}
