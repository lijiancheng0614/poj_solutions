#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define N 20
#define M 16
typedef vector<int> vi;
typedef vector<vi> vvi;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const string OUTPUT = ".!X#";
class Solution
{
public:
    void solve(vector<string> & outputs, int day, const vi & d, vvi & a)
    {
        n = a.size();
        while (day--)
            a = update(a, d);
        outputs.assign(n, "");
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                outputs[i] += OUTPUT[a[i][j]];
    }
private:
    int n;
    int get_neighbor_sum(int i, int j, const vvi & a)
    {
        int s = a[i][j];
        for (int k = 0; k < 4; ++k)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < n && y >= 0 && y < n)
                s += a[x][y];
        }
        return s;
    }
    vvi update(const vvi & a, const vi & d)
    {
        vvi b(n, vi(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                b[i][j] = a[i][j] + d[get_neighbor_sum(i, j, a)];
                b[i][j] = min(b[i][j], 3);
                b[i][j] = max(b[i][j], 0);
            }
        return b;
    }
};

int main()
{
    int day;
    cin >> day;
    vi d(M, 0);
    for (int i = 0; i < M; ++i)
        cin >> d[i];
    vvi a(N, vi(N, 0));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> a[i][j];
    vector<string> outputs;
    Solution().solve(outputs, day, d, a);
    for (int i = 0; i < outputs.size(); ++i)
        cout << outputs[i] << endl;
    return 0;
}
