#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
const int oo = 1 << 30;
const string direction = "dlru";
const int dx[4] = {1, 0, 0, -1};
const int dy[4] = {0, -1, 1, 0};
class Solution
{
public:
    Solution(int n, vi target) : n(n), target(target)
    {
        n2 = n * n;
    }
    string id_astar(vi & a)
    {
        this->a = a;
        if (check())
            return "unsolvable";
        int x = 0;
        while (x < n2 && a[x])
            ++x;
        steps = get_h();
        path = string(steps, ' ');
        steps_new = oo;
        while (!dfs(0, x, 4))
        {
            steps = steps_new;
            path = string(steps, ' ');
            steps_new = oo;
        }
        return path;
    }
private:
    vi a;
    vi target;
    string path;
    int n, n2;
    int steps, steps_new;
    bool dfs(int s, int pos, int d)
    {
        if (s > steps)
            return false;
        int h = get_h();
        if (h + s > steps)
        {
            steps_new = min(steps_new, h + s);
            return false;
        }
        if (!h)
            return true;
        for (int k = 0; k < 4; ++k)
        {
            if (k + d == 3)
                continue;
            int x = pos / 3 + dx[k];
            int y = pos % 3 + dy[k];
            if (x >= 0 && x < 3 && y >= 0 && y < 3)
            {
                int pos_new = x * 3 + y;
                swap(a[pos], a[pos_new]);
                path[s] = direction[k];
                if (dfs(s + 1, pos_new, k))
                    return true;
                swap(a[pos], a[pos_new]);
            }
        }
        return false;
    }
    int get_h()
    {
        int s = 0;
        for (int i = 0; i < n2; ++i)
        {
            int x = i / 3;
            int y = i % 3;
            if (a[i])
                s += abs(x - target[a[i]] / 3) + abs(y - target[a[i]] % 3);
        }
        return s;
    }
    bool check()
    {
        int s = 0;
        for (int i = 1; i < n2; ++i)
            if (a[i])
            for (int j = 0; j < i; ++j)
                if (a[j] && a[j] < a[i])
                    ++s;
        return s & 1;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    vi target;
    for (int i = 0; i < 9; ++i)
        target.push_back(i - 1);
    target[0] = 8;
    Solution solution(3, target);
    string line;
    while (!cin.eof())
    {
        getline(cin, line);
        if (line == "")
            break;
        stringstream ss(line);
        vi a;
        for (int i = 0; i < 9; ++i)
        {
            string s;
            ss >> s;
            a.push_back(s[0] == 'x' ? 0 : s[0] - '0');
        }
        cout << solution.id_astar(a) << endl;
    }
    return 0;
}
