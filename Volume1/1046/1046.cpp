#include <iostream>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

class Solution
{
public:
    Solution(vector<piii> clusters) : clusters(clusters) {}
    piii nearest_neighbor(piii & a)
    {
        int dis_min = get_distance(clusters[0], a);
        int k = 0;
        for (int i = 1; i < clusters.size(); ++i)
        {
            int dis = get_distance(clusters[i], a);
            if (dis < dis_min)
            {
                dis_min = dis;
                k = i;
            }
        }
        return clusters[k];
    }
private:
    vector<piii> clusters;
    int get_distance(piii & a, piii & b)
    {
        return sqr(a.first - b.first) +
            sqr(a.second.first - b.second.first) +
            sqr(a.second.second - b.second.second);
    }
    inline int sqr(int x)
    {
        return x * x;
    }
};

int main()
{
    vector<piii> clusters;
    for (int i = 0; i < 16; ++i)
    {
        int r, g, b;
        cin >> r >> g >> b;
        clusters.push_back(piii(r, pii(g, b)));
    }
    Solution solution(clusters);
    int r, g, b;
    while (cin >> r >> g >> b && r + g + b >= 0)
    {
        piii a = piii(r, pii(g, b));
        piii c = solution.nearest_neighbor(a);
        cout << "(" << r << "," << g << "," << b << ") maps to (" <<
            c.first << "," << c.second.first << "," << c.second.second << ")" << endl;
    }
    return 0;
}
