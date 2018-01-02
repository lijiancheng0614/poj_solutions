#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Solution
{
public:
    Solution(double vs, double r, double c) : vs(vs), r(r), c(c) {}
    double solve(double w)
    {
        return r * c * w * vs * sqrt(1 / (sqr(r) * sqr(c) * sqr(w) + 1));
    }
private:
    double vs, r, c;
    inline double sqr(double x)
    {
        return x * x;
    }
};

int main()
{
    double vs, r, c;
    int n;
    cin >> vs >> r >> c >> n;
    Solution solution(vs, r, c);
    while (n--)
    {
        double w;
        cin >> w;
        cout << fixed << setprecision(3) << solution.solve(w) << endl;
    }
    return 0;
}
