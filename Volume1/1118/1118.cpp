#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const double oo = 1e30;
class Point
{
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    double get_slope(const Point & p) const
    {
        return p.x == x ? oo : double(p.y - y) / (p.x - x);
    }
};
class Solution
{
public:
    int solve(const vector<Point> & points)
    {
        int n = points.size();
        int ans = 1;
        for (int i = 0; i < n - ans; ++i)
        {
            vector<double> slopes;
            for (int j = i + 1; j < n; ++j)
                slopes.push_back(points[i].get_slope(points[j]));
            sort(slopes.begin(), slopes.end());
            int s = 1;
            for (int j = 1; j < slopes.size(); ++j)
                if (slopes[j] == slopes[j - 1])
                    ++s;
                else
                {
                    ans = max(ans, s);
                    s = 1;
                }
            ans = max(ans, s);
        }
        return ans + 1;
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<Point> points;
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(x, y));
        }
        cout << Solution().solve(points) << endl;
    }
    return 0;
}
