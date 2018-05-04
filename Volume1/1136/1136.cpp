#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const double eps = 1e-8;
const double pi = acos(-1);
class Point
{
public:
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    Point operator-(const Point & i) const
    {
        return Point(x - i.x, y - i.y);
    }
    double operator*(const Point & i) const
    {
        return x * i.x + y * i.y;
    }
    double length()
    {
        return sqrt(*this * *this);
    }
};
class Solution
{
public:
    double solve(const vector<Point> & points, double r)
    {
        ans = 0;
        swing(points, 0, r, 0);
        return ans * 2;
    }
private:
    double ans;
    void swing(const vector<Point> & points, int k, double r, double angle)
    {
        double a_min = 2 * pi;
        double d_max = 0;
        int next = -1;
        double a_max = points[k].y < r ? pi + asin(points[k].y / r) - angle : 2 * pi;
        for (int i = 1; i < points.size(); ++i)
            if (i != k)
            {
                double d = (points[i] - points[k]).length();
                if (d >= r)
                    continue;
                double a = atan2(points[i].y - points[k].y, points[i].x - points[k].x) - angle;
                if (a < 0)
                    a += 2 * pi;
                if (a >= a_max)
                    continue;
                if (a < a_min || (fabs(a - a_min) < eps && d > d_max))
                {
                    a_min = a;
                    d_max = d;
                    next = i;
                }
            }
        if (~next)
        {
            ans += a_min * r;
            angle += a_min;
            if (angle >= 2 * pi)
                angle -= 2 * pi;
            swing(points, next, r - d_max, angle);
        }
        else if (points[k].y < r)
            ans += a_max * r;
        else
            ans = pi * r;
    }
};

int main()
{
    int t = 0;
    int n;
    double r;
    while (cin >> n >> r && n)
    {
        vector<Point> points(1, Point(0, 0));
        while (n--)
        {
            int x, y;
            cin >> x >> y;
            points.push_back(Point(-x, -y));
        }
        cout << "Pendulum #" << ++t << endl;
        cout << "Length of periodic orbit = " << fixed << setprecision(2) <<
             Solution().solve(points, r) << endl << endl;
    }
    return 0;
}
