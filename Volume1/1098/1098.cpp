#include <iostream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    Solution(int n = 31, int m = 31) : n(n), m(m) {}
    vector<string> solve(vector<pii> & robots, vector<pii> & teleports,
                         pii player = pii(14, 14))
    {
        outputs.clear();
        int n_robots = robots.size();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                board[i][j] = -1;
        for (int i = 0; i < n_robots; ++i)
            board[robots[i].first][robots[i].second] = i;
        int n_steps = 0;
        while (true)
        {
            ++n_steps;
            bool need_teleport = true;
            int n_robots_best = robots.size();
            int d_min_best = -1;
            vector<pii> robots_best;
            pii player_best;
            for (int dx = -1; dx <= 1; ++dx)
                for (int dy = -1; dy <= 1; ++dy)
                {
                    int x = player.first + dx, y = player.second + dy;
                    int xx = x + dx, yy = y + dy;
                    bool has_debris = in_range(xx, yy) && board[x][y] == -2 && board[xx][yy] != -2;
                    if (!((dx == 0 && dy == 0) || (in_range(x, y) && (board[x][y] == -1 || has_debris))))
                        continue;
                    int n_robots_next = n_robots;
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < m; ++j)
                            board_next[i][j] = board[i][j];
                    vector<pii> robots_next = robots;
                    if (has_debris)
                    {
                        if (board[xx][yy] >= 0)
                        {
                            --n_robots_next;
                            robots_next[board[xx][yy]].first = -1;
                        }
                        board_next[xx][yy] = -2;
                        board_next[x][y] = -1;
                    }
                    if (is_robot_nearby(board_next, x, y))
                        continue;
                    need_teleport = false;
                    robots_move(x, y, n_robots_next, board_next, robots_next);
                    int d_min = get_min_distance(robots_next, x, y);
                    if (n_robots_next < n_robots_best || (n_robots_next == n_robots_best && d_min > d_min_best))
                    {
                        n_robots_best = n_robots_next;
                        d_min_best = d_min;
                        for (int i = 0; i < n; ++i)
                            for (int j = 0; j < m; ++j)
                                board_best[i][j] = board_next[i][j];
                        robots_best = robots_next;
                        player_best = pii(x, y);
                    }
                }
            if (!need_teleport)
            {
                n_robots = n_robots_best;
                for (int i = 0; i < n; ++i)
                    for (int j = 0; j < m; ++j)
                        board[i][j] = board_best[i][j];
                robots = robots_best;
                player = player_best;
                if (n_robots == 0)
                {
                    output(true, n_steps, get_debris_count(board), n_robots, player);
                    return outputs;
                }
                continue;
            }
            int i = get_teleport_id(board, teleports);
            if (i >= 0)
            {
                player = teleports[i];
                teleports[i].first = -1;
                outputs.push_back("Move " + to_string(n_steps) + ": teleport to (" +
                                  to_string(player.first + 1) + "," +
                                  to_string(player.second + 1) + ")");
                robots_move(player.first, player.second, n_robots, board, robots);
                if (n_robots == 0)
                {
                    output(true, n_steps, get_debris_count(board), n_robots, player);
                    return outputs;
                }
            }
            else
            {
                robots_move(player.first, player.second, n_robots, board, robots);
                output(false, n_steps, get_debris_count(board), n_robots, player);
                return outputs;
            }
        }
    }
private:
    int board[31][31], board_best[31][31], board_next[31][31];
    vector<string> outputs;
    int n, m;
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    bool in_range(int x, int y)
    {
        return x >= 0 && x < n && y >= 0 && y < m;
    }
    bool is_robot_nearby(const int board[31][31], int x, int y)
    {
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                if (in_range(x + dx, y + dy) && board[x + dx][y + dy] >= 0)
                    return true;
        return false;
    }
    void robots_move(int x, int y, int & n_robots, int board[31][31], vector<pii> & robots)
    {
        for (int i = 0; i < robots.size(); ++i)
        {
            if (robots[i].first < 0)
                continue;
            board[robots[i].first][robots[i].second] = -1;
            if (robots[i].first < x)
                ++robots[i].first;
            else if (robots[i].first > x)
                --robots[i].first;
            if (robots[i].second < y)
                ++robots[i].second;
            else if (robots[i].second > y)
                --robots[i].second;
        }
        for (int i = 0; i < robots.size(); ++i)
        {
            if (robots[i].first < 0)
                continue;
            if (board[robots[i].first][robots[i].second] == -1)
                board[robots[i].first][robots[i].second] = i;
            else if (board[robots[i].first][robots[i].second] == -2)
            {
                robots[i].first = -1;
                --n_robots;
            }
            else
            {
                robots[board[robots[i].first][robots[i].second]].first = -1;
                board[robots[i].first][robots[i].second] = -2;
                robots[i].first = -1;
                n_robots -= 2;
            }
        }
    }
    int get_min_distance(const vector<pii> & robots, int x, int y)
    {
        int d_min = n * m;
        for (int i = 0; i < robots.size(); ++i)
        {
            if (robots[i].first < 0)
                continue;
            int d = abs(x - robots[i].first) + abs(y - robots[i].second);
            d_min = min(d_min, d);
        }
        return d_min;
    }
    int get_debris_count(const int board[31][31])
    {
        int n_debris = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (board[i][j] == -2)
                    ++n_debris;
        return n_debris;
    }
    void output(bool win, int n_steps, int n_debris, int n_robots, const pii & player)
    {
        if (win)
            outputs.push_back("Won game after making " + to_string(n_steps) + " moves.");
        else
            outputs.push_back("Lost game after making " + to_string(n_steps) + " moves.");
        outputs.push_back("Final position: (" +
                          to_string(player.first + 1) + "," +
                          to_string(player.second + 1) + ")");
        outputs.push_back("Number of cells with debris: " + to_string(n_debris));
        if (!win)
            outputs.push_back("Number of robots remaining: " + to_string(n_robots));
    }
    int get_teleport_id(const int board[31][31], const vector<pii> & teleports)
    {
        for (int i = 0; i < teleports.size(); ++i)
        {
            if (teleports[i].first < 0)
                continue;
            int x = teleports[i].first, y = teleports[i].second;
            if (board[x][y] != -1 || is_robot_nearby(board, x, y))
                continue;
            return i;
        }
        return -1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    int n_cases = 0, r, t;
    while (cin >> r >> t && r)
    {
        vector<pii> robots;
        while (r--)
        {
            int x, y;
            cin >> x >> y;
            robots.push_back(pii(x - 1, y - 1));
        }
        vector<pii> teleports;
        while (t--)
        {
            int x, y;
            cin >> x >> y;
            teleports.push_back(pii(x - 1, y - 1));
        }
        cout << "Case " << ++n_cases << ":" << endl;
        vector<string> outputs = Solution().solve(robots, teleports);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        cout << endl;
    }
    return 0;
}