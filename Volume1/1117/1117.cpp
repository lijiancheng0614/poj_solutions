#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, string> pis;
class Solution
{
public:
    void solve(vector<pis> & outputs, int n)
    {
        for (int i = 0, ii = 1; ii <= n; ii *= 10, ++i)
        {
            if (n % ii % 2)
                continue;
            int a = n / ii / 11;
            int b = n / ii % 11;
            int c = n % ii / 2;
            if (b < 10 && (a || b))
            {
                int x = (10 * a + b) * ii + c;
                int y = a * ii + c;
                outputs.push_back(pis(x, to_string(y, i)));
            }
            --b;
            c = (n % ii + ii) / 2;
            if (b >= 0 && c && (a || b))
            {
                int x = (10 * a + b) * ii + c;
                int y = a * ii + c;
                outputs.push_back(pis(x, to_string(y, i)));
            }
        }
        sort(outputs.begin(), outputs.end());
        outputs.resize(unique(outputs.begin(), outputs.end()) - outputs.begin());
    }
private:
    inline string to_string(int n, int width = 0)
    {
        stringstream ss;
        ss << setw(width) << setfill('0') << n;
        return ss.str();
    }
};

int main()
{
    int n;
    cin >> n;
    vector<pis> outputs;
    Solution().solve(outputs, n);
    cout << outputs.size() << endl;
    for (int i = 0; i < outputs.size(); ++i)
        cout << outputs[i].first << " + " << outputs[i].second << " = " << n << endl;
    return 0;
}
