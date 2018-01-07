#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Solution
{
public:
    int solve(vector<vi> & a)
    {
        int ans = 0;
        int n = a.size();
        for (int i = 0; i < n; ++i)
        {
            vi b(n, 0);
            for (int j = i; j < n; ++j)
            {
                int s = 0;
                for (int k = 0; k < n; ++k)
                {
                    b[k] += a[j][k];
                    s = max(s, 0) + b[k];
                    ans = max(ans, s);
                }
            }
        }
        return ans;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<vi> a;
    for (int i = 0; i < n; ++i)
    {
        vi b;
        for (int j = 0; j < n; ++j)
        {
            int x;
            cin >> x;
            b.push_back(x);
        }
        a.push_back(b);
    }
    cout << Solution().solve(a) << endl;
    return 0;
}
