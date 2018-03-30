#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Point
{
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    Point operator-(const Point & p) const
    {
        return Point(x - p.x, y - p.y);
    }
    double operator*(const Point & p) const
    {
        return x * p.x + y * p.y;
    }
    double operator^(const Point & p) const
    {
        return x * p.y - y * p.x;
    }
    double length() const
    {
        return sqrt(*this * *this);
    }
    double distance(const Point & p) const
    {
        return (*this - p).length();
    }
};
class Solution
{
public:
    int solve(const vector<Point> & points, const Point & p0, double r)
    {
        int n = points.size();
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            int s = 0;
            for (int j = 0; j < n; ++j)
                if (((points[i] - p0) ^ (points[j] - p0)) >= 0)
                    ++s;
            ans = max(ans, s);
        }
        return ans;
    }
};

int main()
{
    int x, y;
    double r;
    while (cin >> x >> y >> r && r >= 0)
    {
        Point p0(x, y);
        vector<Point> points;
        int n;
        cin >> n;
        while (n--)
        {
            cin >> x >> y;
            Point p(x, y);
            if (p0.distance(p) <= r)
                points.push_back(p);
        }
        cout << Solution().solve(points, p0, r) << endl;
    }
    return 0;
}
