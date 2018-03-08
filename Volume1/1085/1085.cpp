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
class Solution
{
public:
    bool solve(const vector<int> & edges)
    {
        bool flag = true;
        int state = 0;
        int score_a = 0, score_b = 0;
        for (int i = 0; i < edges.size(); ++i)
        {
            int score_a_old = score_a, score_b_old = score_b;
            state = get_next_state(state, 1 << edges[i], flag ? score_a : score_b);
            if (score_a == score_a_old && score_b == score_b_old)
                flag = !flag;
        }
        return alpha_beta(flag, state, false, true, score_a, score_b);
    }
private:
    int get_next_state(int state, int state_edge, int & score)
    {
        int state_next = state | state_edge;
        for (int i = 0; i < 9; ++i)
            if ((state & triangle[i]) != triangle[i] && (state_next & triangle[i]) == triangle[i])
                ++score;
        return state_next;
    }
    bool alpha_beta(bool flag, int state, bool alpha, bool beta, int score_a, int score_b)
    {
        if (score_a >= 5)
            return true;
        if (score_b >= 5)
            return false;
        if (state == state_end)
            return score_a > score_b;
        int state_left = ~state & state_end;
        while (state_left)
        {
            int score = flag ? score_a : score_b;
            int state_edge = state_left & (-state_left);
            int state_next = get_next_state(state, state_edge, score);
            if (flag)
                alpha = max(alpha, alpha_beta(score > score_a, state_next, alpha, beta, score, score_b));
            else
                beta = min(beta, alpha_beta(score <= score_b, state_next, alpha, beta, score_a, score));
            if (alpha >= beta)
                break;
            state_left -= state_edge;
        }
        return flag ? alpha : beta;
    }
};

int main()
{
    int t;
    cin >> t;
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
             (Solution().solve(edges) ? 'A' : 'B') << " wins." << endl;
    }
    return 0;
}
