#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
class Point
{
public:
    int x, y, z;
    Point() {}
    Point(int x, int y, int z = 0) : x(x), y(y), z(z) {}
    Point operator-(const Point & i) const
    {
        return Point(x - i.x, y - i.y);
    }
    int operator*(const Point & i) const
    {
        return x * i.x + y * i.y;
    }
    int operator^(const Point & i) const
    {
        return x * i.y - y * i.x;
    }
    bool operator<(const Point & p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
    bool operator!=(const Point & p) const
    {
        return x != p.x || y != p.y;
    }
};
typedef vector<Point> Points;
class Solution
{
public:
    int solve(Points & ans, Points & p1, Points & p2)
    {
        if (p2.size() > p1.size())
            return 0;
        if (p2.size() == 1)
        {
            ans.push_back(p1[0]);
            for (int i = 1; i < p1.size(); ++i)
                if (p1[i].z > ans[0].z)
                    ans[0] = p1[i];
            return p1.size();
        }
        s_max = 0;
        sort(p1.begin(), p1.end());
        sort(p2.begin(), p2.end());
        p2_mapped = p2;
        return mapping(ans, p1, p2, 1) / mapping(ans, p2, p2, 0);
    }
private:
    Points p2_mapped;
    int s_max, s;
    bool check(const Point & a, const Point & b, const Points & p1, const Points & p2)
    {
        Point seg1 = b - a;
        Point seg2 = p2[1] - p2[0];
        double len = seg2 * seg2;
        double cos = (seg1 * seg2) / len, sin = (seg2 ^ seg1) / len;
        s = 0;
        for (int i = 0; i < p2.size(); ++i)
        {
            Point p = p2[i] - p2[0];
            double x = a.x + p.x * cos - p.y * sin, y = a.y + p.x * sin + p.y * cos;
            p.x = round(x), p.y = round(y);
            if (fabs(x - p.x) >= eps || fabs(y - p.y) >= eps)
                return false;
            p2_mapped[i] = p1[lower_bound(p1.begin(), p1.end(), p) - p1.begin()];
            if (p2_mapped[i] != p)
                return false;
            s += p2_mapped[i].z;
        }
        return true;
    }
    int mapping(Points & ans, const Points & p1, const Points & p2, bool type)
    {
        int times = 0;
        for (int i = 0; i < p1.size(); ++i)
            for (int j = 0; j < p1.size(); ++j)
                if (j != i && check(p1[i], p1[j], p1, p2))
                {
                    ++times;
                    if (type && s > s_max)
                    {
                        s_max = s;
                        ans = p2_mapped;
                    }
                }
        return times;
    }
};

int main()
{
    int t = 0;
    int n;
    while (cin >> n && n)
    {
        cout << "Map #" << ++t << endl;
        Points p1;
        for (int i = 0; i < n; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            p1.push_back(Point(x, y, z));
        }
        int m;
        cin >> m;
        while (m--)
        {
            Points p2;
            string name;
            cin >> n >> name;
            for (int i = 0; i < n; ++i)
            {
                int x, y;
                cin >> x >> y;
                p2.push_back(Point(x, y));
            }
            Points ans;
            int times = Solution().solve(ans, p1, p2);
            cout << endl << name << " occurs " << times << " time(s) in the map." << endl;
            if (times)
            {
                sort(ans.begin(), ans.end());
                cout << "Brightest occurrence:";
                for (int i = 0; i < ans.size(); ++i)
                    cout << " (" << ans[i].x << "," << ans[i].y << ")";
                cout << endl;
            }
        }
        cout << "-----" << endl;
    }
    return 0;
}
