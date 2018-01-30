#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
class Solution
{
public:
    bool solve(vector<int> & a)
    {
        vector<int> v(2, 0);
        int n = a.size();
        for (int i = 0; i < n; ++i)
            v[i % 2] += a[i];
        return n % 2 || abs(v[0] - v[1]) < 2;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            a.push_back(x);
        }
        cout << (Solution().solve(a) ? "YES" : "NO") << endl;
    }
    return 0;
}
