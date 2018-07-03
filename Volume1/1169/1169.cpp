#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define h first
#define w second
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
class Solution
{
public:
    vi solve(const vpii & rects)
    {
        vi p(4, 0);
        area_least = 0;
        for (int i = 0; i < 4; ++i)
        {
            area_least += rects[i].h * rects[i].w;
            p[i] = i;
        }
        ans.assign(1, 0);
        vpii r = rects;
        do
        {
            for (int k = 0; k < 16; ++k)
            {
                for (int i = 0; i < 4; ++i)
                    if ((k >> i) & 1)
                        r[i] = pii(rects[p[i]].w, rects[p[i]].h);
                    else
                        r[i] = rects[p[i]];
                get_ans(r);
            }
        } while (next_permutation(p.begin(), p.end()));
        sort(ans.begin() + 1, ans.end());
        ans.resize(unique(ans.begin() + 1, ans.end()) - ans.begin());
        return ans;
    }
private:
    int area_least;
    vi ans;
    void update_ans(int h, int w)
    {
        int area = h * w;
        if (area < area_least)
            return;
        if (area < ans[0] || !ans[0])
            ans.assign(1, area);
        else if (area == ans[0])
            ans.push_back(min(h, w));
    }
    void get_ans(const vpii & rects)
    {
        int h = 0, w = 0;
        for (int i = 0; i < 3; ++i)
        {
            h += rects[i].h;
            w = max(w, rects[i].w);
        }
        // 1: all lined up next to each other
        update_ans(h + rects[3].h, max(w, rects[3].w));
        // 2: first three lined up, fourth on bottom
        update_ans(max(h, rects[3].h), w + rects[3].w);
        // 3: first two lined up, third under them, fourth to side
        update_ans(max(rects[0].h + rects[1].h, rects[2].h) + rects[3].h,
                   max(max(rects[0].w, rects[1].w) + rects[2].w, rects[3].w));
        // 4, 5: first two rectangles lined up, next two stacked
        update_ans(rects[0].h + rects[1].h + max(rects[2].h, rects[3].h),
                   max(max(rects[0].w, rects[1].w), rects[2].w + rects[3].w));
        // 6: first two pressed next to each other, next two on top
        w = max(rects[0].w + rects[2].w, rects[1].w + rects[3].w);
        h = rects[0].h + rects[1].h;
        if (rects[0].w < rects[1].w)
            h = max(h, rects[2].h + rects[1].h);
        if (rects[0].w + rects[2].w > rects[1].w)
            h = max(h, rects[2].h + rects[3].h);
        if (rects[1].w < rects[0].w)
            h = max(h, rects[0].h + rects[3].h);
        h = max(h, max(rects[2].h, rects[3].h));
        update_ans(h, w);
    }
};

int main()
{
    vpii rects;
    for (int i = 0; i < 4; ++i)
    {
        int h, w;
        cin >> h >> w;
        rects.push_back(pii(h, w));
    }
    vi ans = Solution().solve(rects);
    cout << ans[0] << endl;
    for (int i = 1; i < ans.size(); ++i)
        cout << ans[i] << " " << ans[0] / ans[i] << endl;
    return 0;
}
