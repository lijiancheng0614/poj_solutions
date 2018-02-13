#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
const double pi = acos(-1);
const double eps = 1e-8;
typedef pair<double, double> pdd;
typedef pair<int, int> pii;
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
    double operator*(const Point & i) const
    {
        return x * i.x + y * i.y;
    }
    double operator^(const Point & i) const
    {
        return x * i.y - y * i.x;
    }
    double distance(const Point & i) const
    {
        return sqrt((x - i.x) * (x - i.x) + (y - i.y) * (y - i.y));
    }
    double length()
    {
        return sqrt(*this * *this);
    }
    Point rotate(const Point & i, double angle)
    {
        double dx = i.x - x, dy = i.y - y;
        return Point(x + dx * cos(angle) - dy * sin(angle),
            y + dy * cos(angle) + dx * sin(angle));
    }
};
typedef pair<Point, Point> Segment;
class Solution
{
public:
    void solve(Point & gravity, vector<Point> & polygon,
        const vector<pdd> & hill, const Point & hill_peak)
    {
        vector<Segment> hill_segments;
        Point point = hill_peak;
        for (int i = 0; i < hill.size(); ++i)
        {
            double length = hill[i].first;
            double slope = hill[i].second;
            double x = length / sqrt(1 + slope * slope);
            hill_segments.push_back(Segment(Point(point.x - x,
                point.y - slope * x), point));
            point = hill_segments[i].first;
        }
        vector<pii> start_point;
        for (int i = 0; i < polygon.size(); ++i)
            for (int j = 0; j < hill_segments.size(); ++j)
                if (on_segment(polygon[i], hill_segments[j]))
                    start_point.push_back(pii(polygon[i].x, i));
        sort(start_point.begin(), start_point.end());
        if (start_point[0].first + eps > gravity.x)
        {
            int id = start_point[0].second;
            while (polygon[id].x + eps > gravity.x)
                go(-1, id, gravity, polygon, hill_segments);
        }
        else if (start_point[start_point.size() - 1].first + eps < gravity.x)
        {
            int id = start_point[start_point.size() - 1].second;
            while (polygon[id].x + eps < gravity.x)
                go(1, id, gravity, polygon, hill_segments);
        }
    }
private:
    bool on_segment(const Point & point, const Segment & segment)
    {
        Point a = segment.first, b = segment.second;
        return point.x + eps > a.x && point.x < b.x + eps &&
            fabs((point - a) ^ (point - b)) < eps;
    }
    double distance(const Point & point, const Segment & segment)
    {
        Point d1 = segment.second - segment.first;
        Point d2 = point - segment.first;
        return (d1 ^ d2) / d1.length();
    }
    Point get_intersection(int direction, const Point & point, double r,
        const Segment & segment, double h)
    {
        double angle1 = atan2(segment.second.y - segment.first.y,
            segment.second.x - segment.first.x);
        double angle2 = asin(h / r);
        double angle = direction == 1 ? angle1 - angle2 : angle1 + angle2 + pi;
        return Point(point.x + r * cos(angle), point.y + r * sin(angle));
    }
    void go(int direction, int & start_point, Point & gravity, vector<Point> & polygon,
        const vector<Segment> & hill_segments)
    {
        double angle = 2 * pi;
        for (int i = 0; i < polygon.size(); ++i)
            if (i != start_point)
            {
                double r = polygon[i].distance(polygon[start_point]);
                for (int j = 0; j < hill_segments.size(); ++j)
                {
                    double h = distance(polygon[start_point], hill_segments[j]);
                    if (h > r + eps)
                        continue;
                    Point intersection = get_intersection(direction,
                        polygon[start_point], r, hill_segments[j], h);
                    if (on_segment(intersection, hill_segments[j]))
                    {
                        double angle_new = 2 * asin(polygon[i].distance(intersection) / (2 * r));
                        if (angle_new + eps < angle && angle_new > eps)
                            angle = angle_new;
                    }
                }
            }
        if (direction == 1)
            angle = 2 * pi - angle;
        for (int i = 0; i < polygon.size(); ++i)
            if (i != start_point)
                polygon[i] = polygon[start_point].rotate(polygon[i], angle);
        gravity = polygon[start_point].rotate(gravity, angle);
        for (int i = polygon.size() - 1; i >= 0; --i)
            if (i != start_point)
                for (int j = 0; j < hill_segments.size(); ++j)
                    if (on_segment(polygon[i], hill_segments[j]))
                    {
                        start_point = i;
                        return;
                    }
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
        vector<Point> polygon;
        double x, y;
        for (int i = 0; i < n; ++i)
        {
            cin >> x >> y;
            polygon.push_back(Point(x, y));
        }
        cin >> x >> y;
        Point gravity(x, y);
        vector<pdd> hill;
        while (true)
        {
            double length, slope;
            cin >> length >> slope;
            hill.push_back(pdd(length, slope));
            if (fabs(slope) < eps)
                break;
        }
        cin >> x >> y;
        Point hill_peak(x, y);
        Solution().solve(gravity, polygon, hill, hill_peak);
        cout << fixed << setprecision(3) << gravity.x << " " << gravity.y + eps << endl;
    }
    return 0;
}
