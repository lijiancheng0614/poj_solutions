#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
const double pi = acos(-1);
using namespace std;
class Point
{
public:
    int x, y;
    Point() {}
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
    bool operator<(const Point & i) const
    {
        return x < i.x || (x == i.x && y < i.y);
    }
};
class Solution
{
public:
    int solve(vector<Point> & points, int l)
    {
        points = convex(points);
        double ans = points[0].distance(points[points.size() - 1]);
        for (int i = 1; i < points.size(); ++i)
            ans += points[i].distance(points[i - 1]);
        return ans + 2 * pi * l + 0.5;
    }
private:
    vector<Point> convex(vector<Point> & p)
    {
        sort(p.begin(), p.end());
        int n = p.size();
        vector<Point> f(n + 1);
        int m = 0;
        for (int i = 0; i < n; ++i)
        {
            while (m > 1 && ((f[m - 1] - f[m - 2]) ^ (p[i] - f[m - 2])) <= 0)
                --m;
            f[m++] = p[i];
        }
        int k = m;
        for (int i = n - 2; i >= 0; --i)
        {
            while (m > k && ((f[m - 1] - f[m - 2]) ^ (p[i] - f[m - 2])) <= 0)
                --m;
            f[m++] = p[i];
        }
        if (n > 1)
            --m;
        f.resize(m);
        return f;
    }

};

int main()
{
    int n, l;
    cin >> n >> l;
    vector<Point> points;
    while (n--)
    {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    cout << Solution().solve(points, l) << endl;
    return 0;
}
