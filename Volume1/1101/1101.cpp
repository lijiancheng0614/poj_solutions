#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef vector<bool> vb;
typedef pair<int, int> pii;
typedef pair<pii, pii> piiii;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {-1, 0, 1, 0};
class Solution
{
public:
    Solution(int n, int m) : n(n), m(m) {}
    int solve(const vector<vb> & board, int x1, int y1, int x2, int y2)
    {
        queue<piiii> q;
        vector<vb> v(n, vb(m, false));
        q.push(piiii(pii(x1, y1), pii(-1, 0)));
        v[x1][y1] = true;
        while (!q.empty())
        {
            piiii head = q.front();
            q.pop();
            int x = head.first.first;
            int y = head.first.second;
            int d = head.second.first;
            int count = head.second.second;
            for (int k = 0; k < 4; ++k)
                for (int xx = x + dx[k], yy = y + dy[k];
                        xx >= 0 && xx < n && yy >= 0 && yy < m;
                        xx += dx[k], yy += dy[k])
                {
                    if (xx == x2 && yy == y2)
                        return count + (k != d);
                    if (board[xx][yy])
                        break;
                    if (!v[xx][yy])
                    {
                        q.push(piiii(pii(xx, yy), pii(k, count + (k != d))));
                        v[xx][yy] = true;
                    }
                }
        }
        return -1;
    }
private:
    int n, m;
};

int main()
{
    int t = 0;
    int n, m;
    while (cin >> m >> n && m)
    {
        string line;
        getline(cin, line);
        vector<vb> board(n + 2, vb(m + 2, false));
        for (int i = 0; i < n; ++i)
        {
            getline(cin, line);
            for (int j = 0; j < m; ++j)
                board[i + 1][j + 1] = line[j] == 'X';
        }
        Solution solution(n + 2, m + 2);
        cout << "Board #" << ++t << ":" << endl;
        int n_pair = 0;
        int x1, y1, x2, y2;
        while (cin >> y1 >> x1 >> y2 >> x2 && y1)
        {
            int ans = solution.solve(board, x1, y1, x2, y2);
            cout << "Pair " << ++n_pair << ": ";
            if (~ans)
                cout << ans << " segments." << endl;
            else
                cout << "impossible." << endl;
        }
        cout << endl;
    }
    return 0;
}
