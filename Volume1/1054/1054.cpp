#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    int solve(vector<pii> & points, int r, int c)
    {
        int n = points.size();
        sort(points.begin(), points.end());
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
            {
                int dx = points[j].first - points[i].first;
                int dy = points[j].second - points[i].second;
                if (points[i].first - dx >= 0 && points[i].first - dx < r &&
                    points[i].second - dy >= 0 && points[i].second - dy < c)
                    continue;
                int x = points[j].first + dx;
                int y = points[j].second + dy;
                int s = 0;
                while (x >= 0 && x < r && y >= 0 && y < c)
                {
                    if (binary_search(points.begin(), points.end(), pii(x, y)))
                        ++s;
                    else
                    {
                        s = 0;
                        break;
                    }
                    x += dx;
                    y += dy;
                }
                if (s)
                    ans = max(ans, s + 2);
            }
        return ans;
    }
};

int main()
{
    int r, c, n;
    cin >> r >> c >> n;
    vector<pii> points;
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        points.push_back(pii(x - 1, y - 1));
    }
    cout << Solution().solve(points, r, c) << endl;
    return 0;
}
