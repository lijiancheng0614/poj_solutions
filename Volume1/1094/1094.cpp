#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
class Solution
{
public:
    string solve(int n, const vector<pii> & a)
    {
        this->n = n;
        d.assign(n, 0);
        g.assign(n, vi());
        for (int i = 0; i < a.size(); ++i)
        {
            int x = a[i].first;
            int y = a[i].second;
            ++d[y];
            g[x].push_back(y);
            int flag = topsort();
            if (flag == 0)
                return "Inconsistency found after " + to_string(i + 1) +
                       " relations.";
            if (flag == 2)
                return "Sorted sequence determined after " + to_string(i + 1) +
                       " relations: " + to_string(sequence) + ".";
        }
        return "Sorted sequence cannot be determined.";
    }
private:
    vector<vi> g;
    vi d;
    vi sequence;
    int n;
    int topsort()
    {
        vi d = this->d;
        sequence.clear();
        int flag = 2;
        for (int k = 0; k < n; ++k)
        {
            int tot = 0;
            int x;
            for (int i = 0; i < n; ++i)
                if (d[i] == 0)
                {
                    ++tot;
                    x = i;
                }
            if (tot == 0)
                return 0;
            if (tot > 1)
                flag = 1;
            sequence.push_back(x);
            d[x] = -1;
            for (int i = 0; i < g[x].size(); ++i)
                --d[g[x][i]];
        }
        return flag;
    }
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    inline string to_string(const vi & sequence)
    {
        string s = "";
        for (int i = 0; i < sequence.size(); ++i)
            s += 'A' + sequence[i];
        return s;
    }
};

int main()
{
    int n, m;
    while (cin >> n >> m && n)
    {
        vector<pii> a;
        while (m--)
        {
            string line;
            cin >> line;
            a.push_back(pii(line[0] - 'A', line[2] - 'A'));
        }
        cout << Solution().solve(n, a) << endl;
    }
    return 0;
}
