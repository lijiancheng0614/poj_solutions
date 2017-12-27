#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
const double oo = 1e9;
const double eps = 1e-4;
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
    double solve(vector<Point> points_up, vector<Point> points_bottom)
    {
        double ans = -oo;
        int n = points_up.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                if (j == i)
                    continue;
                int k = 0;
                for (; k < n; ++k)
                    if (!is_cross(points_up[i], points_bottom[j], points_up[k], points_bottom[k]))
                        break;
                if (k >= n)
                    return -oo;
                if (k > max(i, j))
                    ans = max(ans,
                        max(intersection_x(points_up[i], points_bottom[j], points_up[k], points_up[k - 1]),
                        intersection_x(points_up[i], points_bottom[j], points_bottom[k], points_bottom[k - 1])));
            }
        return ans;
    }
private:
    bool is_cross(Point a, Point b, Point c, Point d)
    {
        return ((b - a) ^ (c - a)) * ((b - a) ^ (d - a)) <= 0;
    }
    double intersection_x(Point a, Point b, Point c, Point d)
    {
        double area1 = (b - a) ^ (c - a);
        double area2 = (b - a) ^ (d - a);
        if (area1 * area2 < 0)
            return (area2 * c.x - area1 * d.x) / (area2 - area1);
        if (area1 == 0)
            return c.x;
        if (area2 == 0)
            return d.x;
        return -oo;
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<Point> points_up, points_bottom;
        for (int i = 0; i < n; ++i)
        {
            double x, y;
            cin >> x >> y;
            points_up.push_back(Point(x, y));
            points_bottom.push_back(Point(x, y - 1));
        }
        double ans = Solution().solve(points_up, points_bottom);
        if (ans <= -oo)
            cout << "Through all the pipe." << endl;
        else
            cout << fixed << setprecision(2) << ans << endl;
    }
    return 0;
}
