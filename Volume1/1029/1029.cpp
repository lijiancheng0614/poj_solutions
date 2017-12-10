#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    Solution(int n) : n(n)
    {
        same.assign(n, false);
        small.assign(n, false);
        large.assign(n, false);
    }
    void update(vector<int> l, vector<int> r, char op)
    {
        int m = l.size();
        if (op == '=')
        {
            for (int i = 0; i < m; ++i)
                same[l[i]] = true;
            for (int i = 0; i < m; ++i)
                same[r[i]] = true;
        }
        else if (op == '<')
        {
            vector<bool> visited(n, false);
            for (int i = 0; i < m; ++i)
            {
                small[l[i]] = true;
                visited[l[i]] = true;
            }
            for (int i = 0; i < m; ++i)
            {
                large[r[i]] = true;
                visited[r[i]] =  true;
            }
            for (int i = 0; i < n; ++i)
                if (!visited[i])
                    same[i] = true;
        }
        else if (op == '>')
        {
            vector<bool> visited(n, false);
            for (int i = 0; i < m; ++i)
            {
                small[r[i]] = true;
                visited[r[i]] = true;
            }
            for (int i = 0; i < m; ++i)
            {
                large[l[i]] = true;
                visited[l[i]] =  true;
            }
            for (int i = 0; i < n; ++i)
                if (!visited[i])
                    same[i] = true;
        }
    }
    int solve()
    {
        bool flag = false;
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (same[i] || (small[i] && large[i]))
                continue;
            if (flag)
                return 0;
            ans = i;
            flag = true;
        }
        return ans + 1;
    }
private:
    vector<bool> same, small, large;
    int n;
};

int main()
{
    int n, k;
    cin >> n >> k;
    Solution solution(n);
    while (k--)
    {
        int p;
        cin >> p;
        vector<int> a[2];
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < p; ++j)
            {
                int x;
                cin >> x;
                a[i].push_back(x - 1);
            }
        char op;
        cin >> op;
        solution.update(a[0], a[1], op);
    }
    cout << solution.solve() << endl;
    return 0;
}
