#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int N = 1 << 18;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int d[4] = {-3, 1, 1, 1};
const int moves[][6] =
{
    {0, 1, 3, 4, -1},
    {0, 1, 2, -1},
    {1, 2, 4, 5, -1},
    {0, 3, 6, -1},
    {1, 3, 4, 5, 7, -1},
    {2, 5, 8, -1},
    {3, 4, 6, 7, -1},
    {6, 7, 8, -1},
    {4, 5, 7, 8, -1}
};
int pow4[10];
class Solution
{
public:
    vi solve(int state)
    {
        next.assign(N, pii(0, 0));
        bfs(state);
        vi ans;
        for (; state; state = next[state].first)
            ans.push_back(next[state].second);
        reverse(ans.begin(), ans.end());
        return ans;
    }
private:
    vector<pii> next;
    void get_state(int state, int a[])
    {
        for (int i = 0; state; state /= 4)
            a[i++] = state % 4;
    }
    void bfs(int state)
    {
        queue<int> q;
        vector<bool> v(N, false);
        v[0] = true;
        q.push(0);
        while (!q.empty())
        {
            int head = q.front();
            q.pop();
            int a[9] = {};
            get_state(head, a);
            for (int i = 0; i < 9; ++i)
            {
                int tail = head;
                for (int j = 0; ~moves[i][j]; ++j)
                    tail -= pow4[moves[i][j]] * d[a[moves[i][j]]];
                if (!v[tail])
                {
                    v[tail] = true;
                    q.push(tail);
                    next[tail] = pii(head, i + 1);
                    if (tail == state)
                        return;
                }
            }
        }
    }
};

int main()
{
    pow4[0] = 1;
    for (int i = 1; i < 10; ++i)
        pow4[i] = pow4[i - 1] * 4;
    int state = 0;
    for (int i = 0; i < 9; ++i)
    {
        int x;
        cin >> x;
        state |= x * pow4[i];
    }
    vi ans = Solution().solve(state);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    return 0;
}
