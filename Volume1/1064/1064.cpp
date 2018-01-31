#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
class Solution
{
public:
    double solve(vector<int> & a, int k)
    {
        int l = 0, r = 10000001;
        while (l + 1 < r)
        {
            int mid = (l + r) / 2;
            if (get(a, mid) >= k)
                l = mid;
            else
                r = mid;
        }
        return l / 100.0;
    }
private:
    int get(vector<int> & a, int x)
    {
        int s = 0;
        for (int i = 0; i < a.size(); ++i)
            s += a[i] / x;
        return s;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a;
    while (n--)
    {
        double x;
        cin >> x;
        a.push_back(x * 100);
    }
    cout << fixed << setprecision(2) << Solution().solve(a, k) << endl;
    return 0;
}
