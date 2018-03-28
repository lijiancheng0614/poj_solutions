#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef vector<string> vs;
typedef pair<int, int> pii;
class Solution
{
public:
    vs solve(vvvb & v)
    {
        t = v.size(), w = v[0].size(), h = v[0][0].size();
        for (int k = 1; k < t; ++k)
            for (int i = 0; i < w; ++i)
                for (int j = 0; j < h; ++j)
                    if (!v[k][i][j] && check(v, k - 1, i, j))
                        v[k][i][j] = true;
        vector<int> count(t, 0);
        vector<pii> pos(t, pii(0, 0));
        for (int k = t - 1; k >= 0; --k)
        {
            for (int i = 0; i < w; ++i)
                for (int j = 0; j < h; ++j)
                {
                    if (k < t - 1 && !v[k][i][j] && check(v, k + 1, i, j))
                        v[k][i][j] = true;
                    if (!v[k][i][j])
                    {
                        ++count[k];
                        if (count[k] == 1)
                            pos[k] = pii(i, j);
                    }
                }
            if (count[k] == 0)
                return vs(1, "The robber has escaped.");
        }
        vs outputs;
        for (int k = 0; k < t; ++k)
            if (count[k] == 1)
                outputs.push_back("Time step " + to_string(k + 1) + ": The robber has been at " +
                                  to_string(pos[k].first + 1) + "," + to_string(pos[k].second + 1) + ".");
        if (outputs.size() == 0)
            return vs(1, "Nothing known.");
        return outputs;
    }
private:
    int t, w, h;
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    bool check(const vector<vvb> & v, int t, int i, int j)
    {
        if (!v[t][i][j])
            return false;
        for (int k = 0; k < 4; ++k)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x >= 0 && x < w && y >= 0 && y < h && !v[t][x][y])
                return false;
        }
        return true;
    }
};

int main()
{
    int n_cases = 0, w, h, t;
    while (cin >> w >> h >> t && w)
    {
        int n;
        cin >> n;
        vvvb v(t, vvb(w, vb(h, false)));
        while (n--)
        {
            int k, x1, y1, x2, y2;
            cin >> k >> x1 >> y1 >> x2 >> y2;
            --k, --x1, --y1;
            for (int i = x1; i < x2; ++i)
                for (int j = y1; j < y2; ++j)
                    v[k][i][j] = true;
        }
        cout << "Robbery #" << ++n_cases << ":" << endl;
        vs outputs = Solution().solve(v);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        cout << endl;
    }
    return 0;
}
