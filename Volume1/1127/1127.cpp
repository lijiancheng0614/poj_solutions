#include <iostream>
#include <vector>
using namespace std;
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
    int operator^(const Point & i) const
    {
        return x * i.y - y * i.x;
    }
};
typedef pair<Point, Point> Segment;
class Solution
{
public:
    Solution(const vector<Segment> & segments)
    {
        int n = segments.size();
        f.assign(n, 0);
        for (int i = 0; i < n; ++i)
            f[i] = i;
        for (int i = 1; i < n; ++i)
            for (int j = 0; j < i; ++j)
                if (is_cross(segments[i], segments[j]))
                    union_set(i, j);
    }
    int is_connected(int i, int j)
    {
        return find(i) == find(j);
    }
private:
    vector<int> f;
    bool is_cross(const Point & a, const Point & b, const Point & c, const Point & d)
    {
        return max(a.x, b.x) >= min(c.x, d.x) &&
               max(c.x, d.x) >= min(a.x, b.x) &&
               max(a.y, b.y) >= min(c.y, d.y) &&
               max(c.y, d.y) >= min(a.y, b.y) &&
               ((b - a) ^ (c - a)) * ((b - a) ^ (d - a)) <= 0 &&
               ((d - c) ^ (a - c)) * ((d - c) ^ (b - c)) <= 0;
    }
    bool is_cross(const Segment & a, const Segment & b)
    {
        return is_cross(a.first, a.second, b.first, b.second);
    }
    int find(int k)
    {
        return f[k] == k ? k : f[k] = find(f[k]);
    }
    void union_set(int i, int j)
    {
        i = find(i);
        j = find(j);
        f[i] = j;
    }
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<Segment> segments;
        while (n--)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments.push_back(Segment(Point(x1, y1), Point(x2, y2)));
        }
        Solution solution(segments);
        int i, j;
        while (cin >> i >> j && i)
            cout << (solution.is_connected(i - 1, j - 1) ? "CONNECTED" : "NOT CONNECTED") << endl;
    }
    return 0;
}
