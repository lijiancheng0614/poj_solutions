#include <iostream>
#include <cctype>
using namespace std;

class Solution
{
public:
    bool solve(const string & tree, int m)
    {
        this->m = m;
        n = 0;
        p = 0;
        flag = false;
        dfs(0, tree);
        return flag;
    }
private:
    int n, m, p;
    bool flag;
    int dfs(int s, const string & tree)
    {
        ++p;
        if (tree[p] == ')')
        {
            ++p;
            return -1;
        }
        bool neg = false;
        int x = 0;
        if (tree[p] == '-')
        {
            neg = true;
            ++p;
        }
        for (; isdigit(tree[p]); ++p)
            x = x * 10 + tree[p] - '0';
        if (neg)
            x = -x;
        ++n;
        int l = dfs(s + x, tree);
        int r = dfs(s + x, tree);
        if (l == -1 && r == -1 && s + x == m)
            flag = true;
        ++p;
        return n;
    }
};

bool check(const string & tree)
{
    int s = 0;
    for (int i = 0; i < tree.length(); ++i)
        if (tree[i] == '(')
            ++s;
        else if (tree[i] == ')')
            --s;
    return s || tree.length() == 0;
}

int main()
{
    int m;
    while (cin >> m)
    {
        string tree;
        cin >> tree;
        while (check(tree))
        {
            string line;
            cin >> line;
            tree += line;
        }
        cout << (Solution().solve(tree, m) ? "yes" : "no") << endl;
    }
    return 0;
}
