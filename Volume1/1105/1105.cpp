#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    char solve(const vi & order, const string & terminal, const string & values)
    {
        int node = 0;
        for (int i = 0; i < order.size(); ++i)
            node = node * 2 + (values[order[i]] == '1');
        return terminal[node];
    }
};

int main()
{
    int t = 0, n;
    while (cin >> n && n)
    {
        vi order;
        while (n--)
        {
            string x;
            cin >> x;
            order.push_back(x[1] - '1');
        }
        string terminal;
        cin >> terminal;
        string ans = "";
        cin >> n;
        while (n--)
        {
            string values;
            cin >> values;
            ans += Solution().solve(order, terminal, values);
        }
        cout << "S-Tree #" << ++t << ":" << endl;
        cout << ans << endl;
        cout << endl;
    }
    return 0;
}
