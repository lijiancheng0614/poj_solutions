#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;
typedef pair<double, double> pdd;
const double pi = acos(-1);

class Solution
{
public:
    double solve(double k, double h, vector<pdd> points)
    {
        int n = points.size();
        double angle_min = 0, angle_max = 0, angle_sum = 0;
        for (int i = 0; i < n; ++i)
        {
            double angle = get_angle(points[i], points[(i + 1) % n]);
            angle_sum += angle;
            angle_min = min(angle_min, angle_sum);
            angle_max = max(angle_max, angle_sum);
            if (angle_max - angle_min >= 2 * pi)
            {
                angle_max = angle_min + 2 * pi;
                break;
            }
        }
        return k * h * (angle_max - angle_min);
    }
private:
    double get_angle(pdd a, pdd b)
    {
        double alpha = atan2(a.second, a.first);
        double beta = atan2(b.second, b.first);
        alpha -= beta;
        if (alpha < -pi)
            alpha += 2 * pi;
        if (alpha > pi)
            alpha -= 2 * pi;
        return alpha;
    }
};

int main()
{
    double k, h;
    int n;
    cin >> k >> h >> n;
    vector<pdd> points;
    for (int i = 0; i < n; ++i)
    {
        double x, y;
        cin >> x >> y;
        points.push_back(pdd(x, y));
    }
    cout << setiosflags(ios::fixed) << setprecision(2) << Solution().solve(k, h, points) << endl;
    return 0;
}
