#include <iostream>
#include <vector>
using namespace std;
const int edge_id[11][11] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 3, 5, 0, 0, 0, 0, 0},
    {0, 2, 1, 0, 0, 6, 8, 0, 0, 0, 0},
    {0, 0, 3, 0, 0, 4, 0, 9, 11, 0, 0},
    {0, 0, 5, 6, 4, 0, 7, 0, 12, 14, 0},
    {0, 0, 0, 8, 0, 7, 0, 0, 0, 15, 17},
    {0, 0, 0, 0, 9, 0, 0, 0, 10, 0, 0},
    {0, 0, 0, 0, 11, 12, 0, 10, 0, 13, 0},
    {0, 0, 0, 0, 0, 14, 15, 0, 13, 0, 16},
    {0, 0, 0, 0, 0, 0, 17, 0, 0, 16, 0}
};
const int triangle[9] = {7, 56, 98, 448, 3584, 6160, 28672, 49280, 229376};
const int state_end = (1 << 18) - 1;
const int MIN = -10;
class Solution
{
public:
    Solution()
    {
        f.assign(state_end + 1, MIN);
        f[state_end] = 0;
    }
    bool solve(const vector<int> & edges)
    {
        bool flag = true;
        int state = 0;
        int score = 0;
        for (int i = 0; i < edges.size(); ++i)
        {
            int score_new = 0;
            state = get_next_state(state, 1 << edges[i], score_new);
            if (score_new)
                score += (flag ? 1 : -1) * score_new;
            else
                flag = !flag;
        }
        return score + (flag ? 1 : -1) * dp(state) > 0;
    }
private:
    vector<int> f;
    int get_next_state(int state, int state_edge, int & score)
    {
        int state_next = state | state_edge;
        for (int i = 0; i < 9; ++i)
            if ((state & triangle[i]) != triangle[i] && (state_next & triangle[i]) == triangle[i])
                ++score;
        return state_next;
    }
    int dp(int state)
    {
        if (f[state] > MIN)
            return f[state];
        int state_left = ~state & state_end;
        while (state_left)
        {
            int state_edge = state_left & (-state_left);
            int score = 0;
            int state_next = get_next_state(state, state_edge, score);
            f[state] = max(f[state], (score ? 1 : -1) * dp(state_next) + score);
            state_left -= state_edge;
        }
        return f[state];
    }
};

int main()
{
    int t;
    cin >> t;
    Solution solution;
    for (int tt = 1; tt <= t; ++tt)
    {
        int n;
        cin >> n;
        vector<int> edges;
        while (n--)
        {
            int i, j;
            cin >> i >> j;
            edges.push_back(edge_id[i][j]);
        }
        cout << "Game " << tt << ": " <<
             (solution.solve(edges) ? 'A' : 'B') << " wins." << endl;
    }
    return 0;
}
