#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
#define N 1025
class SegmentTree
{
public:
    void add(double x1, double y1, double x2, double y2)
    {
        edges.push_back(Edge(x1, y1, y2, 1));
        edges.push_back(Edge(x2, y1, y2, -1));
        y.push_back(y1);
        y.push_back(y2);
    }
    double solve()
    {
        sort(edges.begin(), edges.end());
        sort(y.begin(), y.end());
        int m = unique(y.begin(), y.end()) - y.begin();
        a.assign(N, Segment());
        double s = 0;
        for (int i = 0; i < edges.size(); ++i)
        {
            if (i)
                s += (edges[i].x - edges[i - 1].x) * a[1].y;
            update(1, 0, m - 1, edges[i].y1, edges[i].y2, edges[i].left);
        }
        return s;
    }
private:
    class Edge
    {
    public:
        double x, y1, y2;
        int left;
        Edge(double x, double y1, double y2, int left) : x(x), y1(y1), y2(y2), left(left) {}
        bool operator<(const Edge & e) const
        {
            return (x < e.x) || (x == e.x && left < e.left);
        }
    };
    class Segment
    {
    public:
        double y;
        int left;
        Segment() : y(0), left(0) {}
    };
    vector<Edge> edges;
    vector<double> y;
    vector<Segment> a;
    void update(int p, int l, int r, double y1, double y2, int left)
    {
        if (y1 <= y[l] && y[r] <= y2)
            a[p].left += left;
        else if (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            if (y1 < y[mid])
                update(p * 2, l, mid, y1, y2, left);
            if (y2 > y[mid])
                update(p * 2 + 1, mid, r, y1, y2, left);
        }
        else
            return;
        a[p].y = a[p].left > 0 ? y[r] - y[l] : a[p * 2].y + a[p * 2 + 1].y;
    }
};

int main()
{
    int t = 0;
    int n;
    while (cin >> n && n)
    {
        SegmentTree st;
        while (n--)
        {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            st.add(x1, y1, x2, y2);
        }
        cout << "Test case #" << ++t << endl;
        cout << "Total explored area: " << fixed << setprecision(2) << st.solve() << endl;
        cout << endl;
    }
    return 0;
}
