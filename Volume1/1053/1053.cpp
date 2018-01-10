#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef vector<string> vs;
const int n = 12;
class Solution
{
public:
    vector<vs> solve(vs & inputs)
    {
        vector<vs> ans;
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                for (int k = j + 1; k < n; ++k)
                    if (check(inputs[i], inputs[j], inputs[k]))
                    {
                        vs set;
                        set.push_back(inputs[i]);
                        set.push_back(inputs[j]);
                        set.push_back(inputs[k]);
                        ans.push_back(set);
                    }
        return ans;
    }
private:
    bool check(string & a, string & b, string & c)
    {
        for (int i = 0; i < a.length(); ++i)
        {
            if (a[i] == b[i] && b[i] == c[i])
                continue;
            if (a[i] != b[i] && b[i] != c[i] && c[i] != a[i])
                continue;
            return false;
        }
        return true;
    }
};

int main()
{
    string x;
    while (cin >> x && x != "")
    {
        vs inputs(1, x);
        for (int i = 1; i < n; ++i)
        {
            cin >> x;
            inputs.push_back(x);
        }
        vector<vs> ans = Solution().solve(inputs);
        cout << "CARDS: ";
        for (int i = 0; i < 12; ++i)
            cout << " " << inputs[i];
        cout << endl;
        if (ans.size() == 0)
            cout << "SETS:   *** None Found ***" << endl;
        else
        {
            cout << "SETS:   1. ";
            for (int i = 0; i < 3; ++i)
                cout << " " << ans[0][i];
            cout << endl;
            for (int i = 1; i < ans.size(); ++i)
            {
                cout << "        " << i + 1 << ". ";
                for (int j = 0; j < 3; ++j)
                    cout << " " << ans[i][j];
                cout << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
