#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

class Solution
{
public:
    void solve(vector<string> board)
    {
        this->board = board;
        h = board.size();
        w = board[0].size();
        component_id.assign(h, vi(w, 0));
        int step = 0;
        int score_final = 0;
        int num_balls = h * w;
        while (true)
        {
            int y_max, x_max;
            int count = get_max_component(y_max, x_max);
            if (count < 2)
                break;
            char c = this->board[y_max][x_max];
            remove_component(component_id[y_max][x_max]);
            update_board();
            int score = sqr(count - 2);
            score_final += score;
            num_balls -= count;
            cout << "Move " << ++step << " at (" << h - y_max << "," << x_max + 1 << "): removed " <<
                count << " balls of color " << c << ", got " << score << " points." << endl;
        }
        if (num_balls == 0)
            score_final += 1000;
        cout << "Final score: " << score_final << ", with " << num_balls << " balls remaining." << endl;
    }
private:
    int h, w;
    vector<string> board;
    vector<vi> component_id;
    int dfs(int y, int x, int id)
    {
        component_id[y][x] = id;
        int s = 1;
        for (int k = 0; k < 4; ++k)
        {
            int yy = y + dy[k];
            int xx = x + dx[k];
            if (yy >= 0 && yy < h && xx >= 0 && xx < w && !component_id[yy][xx] && board[yy][xx] == board[y][x])
                s += dfs(yy, xx, id);
        }
        return s;
    }
    int get_max_component(int & y_max, int & x_max)
    {
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x)
                component_id[y][x] = 0;
        int id_tot = 0;
        int count_max = 0;
        for (int x = 0; x < w; ++x)
            for (int y = h - 1; y >= 0; --y)
                if (!component_id[y][x] && board[y][x] != ' ')
                {
                    int count = dfs(y, x, ++id_tot);
                    if (count > count_max)
                    {
                        count_max = count;
                        y_max = y;
                        x_max = x;
                    }
                }
        return count_max;
    }
    void remove_component(int id)
    {
        for (int x = 0; x < w; ++x)
            for (int y = 0; y < h; ++y)
                if (component_id[y][x] == id)
                    board[y][x] = ' ';
    }
    void update_board()
    {
        for (int x = 0; x < w; ++x)
        {
            int yy = h - 1;
            for (int y = h - 1; y >= 0; --y)
                if (board[y][x] != ' ')
                    board[yy--][x] = board[y][x];
            for (; yy >= 0; --yy)
                board[yy][x] = ' ';
        }
        int xx = 0;
        for (int x = 0; x < w; ++x)
            if (board[h - 1][x] != ' ')
            {
                for (int y = 0; y < h; ++y)
                    board[y][xx] = board[y][x];
                ++xx;
            }
        w = xx;
    }
    inline int sqr(int x)
    {
        return x * x;
    }
};

int main()
{
    int t;
    cin >> t;
    Solution solution;
    for (int tt = 1; tt <= t; ++tt)
    {
        vector<string> board;
        for (int i = 0; i < 10; ++i)
        {
            string s;
            cin >> s;
            board.push_back(s);
        }
        cout << "Game " << tt << ":" << endl << endl;
        solution.solve(board);
        if (tt < t)
            cout << endl;
    }
    return 0;
}
