#include <iostream>
#include <vector>
using namespace std;
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
typedef pair<Point, Point> Segment;
class Solution
{
public:
    int solve(vector<Segment> & segments, Point p)
    {
        int n = segments.size();
        if (n == 0)
            return 1;
        int ans = n;
        for (int i = 0; i < n; ++i)
        {
            ans = min(ans, get_cross_count(segments, Segment(segments[i].first, p)));
            ans = min(ans, get_cross_count(segments, Segment(segments[i].second, p)));
        }
        return ans + 1;
    }
private:
    int get_cross_count(vector<Segment> & segments, Segment segment)
    {
        int s = 0;
        for (int i = 0; i < segments.size(); ++i)
            if (is_cross(segments[i], segment))
                ++s;
        return s;
    }
    bool is_cross(Segment & a, Segment & b)
    {
        return is_cross(a.first, a.second, b.first, b.second);
    }
    bool is_cross(Point & a, Point & b, Point & c, Point & d)
    {
        return max(a.x, b.x) >= min(c.x, d.x) &&
            max(c.x, d.x) >= min(a.x, b.x) &&
            max(a.y, b.y) >= min(c.y, d.y) &&
            max(c.y, d.y) >= min(a.y, b.y) &&
            ((b - a) ^ (c - a)) * ((b - a) ^ (d - a)) < 0 &&
            ((d - c) ^ (a - c)) * ((d - c) ^ (b - c)) < 0;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<Segment> segments;
    for (int i = 0; i < n; ++i)
    {
        double x, y, xx, yy;
        cin >> x >> y >> xx >> yy;
        segments.push_back(Segment(Point(x, y), Point(xx, yy)));
    }
    double x, y;
    cin >> x >> y;
    cout << "Number of doors = " << Solution().solve(segments, Point(x, y)) << endl;
    return 0;
}
