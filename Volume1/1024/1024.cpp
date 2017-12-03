#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

class Point
{
public:
    bool wall_right, wall_up, on_path;
    int dis[2];
};

class Solution
{
public:
    bool check(int w, int h, string path, vector<vi> walls)
    {
        int len = path.length();
        maze.assign(w, vector<Point>(h, Point()));
        maze[0][0].on_path = true;
        int x = 0, y = 0;
        for (int i = 0; i < len; ++i)
        {
            if (path[i] == 'L')
                --x;
            else if (path[i] == 'R')
                ++x;
            else if (path[i] == 'U')
                ++y;
            else if (path[i] == 'D')
                --y;
            maze[x][y].on_path = true;
        }
        for (int i = 0; i < walls.size(); ++i)
        {
            int x1 = walls[i][0];
            int y1 = walls[i][1];
            int x2 = walls[i][2];
            int y2 = walls[i][3];
            if (x1 == x2 && y1 + 1 == y2)
                maze[x1][y1].wall_up = true;
            else if (x1 == x2 && y1 - 1 == y2)
                maze[x2][y2].wall_up = true;
            else if (y1 == y2 && x1 + 1 == x2)
                maze[x1][y1].wall_right = true;
            else if (y1 == y2 && x1 - 1 == x2)
                maze[x2][y2].wall_right = true;
        }
        bfs(0, 0, w, h, 0);
        bfs(x, y, w, h, 1);
        for (x = 0; x < w; ++x)
            for (y = 0; y < h; ++y)
            {
                if (!maze[x][y].on_path &&
                    maze[x][y].dis[0] + maze[x][y].dis[1] - 2 <= len)
                    return false;
                if (maze[x][y].wall_right && x + 1 < w &&
                    maze[x][y].dis[0] + maze[x + 1][y].dis[1] - 1 > len &&
                    maze[x][y].dis[1] + maze[x + 1][y].dis[0] - 1 > len)
                    return false;
                if (maze[x][y].wall_up && y + 1 < h &&
                    maze[x][y].dis[0] + maze[x][y + 1].dis[1] - 1 > len &&
                    maze[x][y].dis[1] + maze[x][y + 1].dis[0] - 1 > len)
                    return false;
            }
        return true;
    }
private:
    vector< vector<Point> > maze;
    void bfs(int x, int y, int w, int h, int flag)
    {
        queue<pii> q;
        q.push(pii(x, y));
        maze[x][y].dis[flag] = 1;
        while (!q.empty())
        {
            pii head = q.front();
            q.pop();
            x = head.first;
            y = head.second;
            bool can_go[] = {x > 0 && !maze[x - 1][y].wall_right,
                y > 0 && !maze[x][y - 1].wall_up,
                x + 1 < w && !maze[x][y].wall_right,
                y + 1 < h && !maze[x][y].wall_up};
            for (int k = 0; k < 4; ++k)
            {
                int xx = x + dx[k];
                int yy = y + dy[k];
                if (can_go[k] && maze[xx][yy].dis[flag] == 0)
                {
                    maze[xx][yy].dis[flag] = maze[x][y].dis[flag] + 1;
                    q.push(pii(xx, yy));
                }
            }
        }
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int w, h;
        cin >> w >> h;
        string path;
        cin >> path;
        int m;
        cin >> m;
        vector<vi> walls(m, vi());
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < 4; ++j)
            {
                int x;
                cin >> x;
                walls[i].push_back(x);
            }
        cout << (Solution().check(w, h, path, walls) ? "CORRECT" : "INCORRECT") << endl;
    }
    return 0;
}
