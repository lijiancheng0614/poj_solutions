#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    vector<pii> solve(int a, int b)
    {
        vector<pii> ratios;
        double exact = (double)a / b;
        double c = int(exact + 0.5);
        ratios.push_back(pii(c, 1));
        for (int q = 2; q <= b; ++q)
        {
            int p = exact * q + 0.5;
            double d = (double)p / q;
            if (fabs(d - exact) < fabs(c - exact))
            {
                ratios.push_back(pii(p, q));
                if (d == exact)
                    break;
                c = d;
            }
        }
        return ratios;
    }
};

int main()
{
    int a, b;
    while (cin >> a >> b)
    {
        vector<pii> ratios = Solution().solve(a, b);
        for (int i = 0; i < ratios.size(); ++i)
            cout << ratios[i].first << "/" << ratios[i].second << endl;
        cout << endl;
    }
    return 0;
}
