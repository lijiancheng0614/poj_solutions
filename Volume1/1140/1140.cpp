#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
typedef vector<string> vs;
class Solution
{
public:
    void solve(vs & outputs, int a, int b)
    {
        outputs.assign(1, ".");
        vector<int> v(1001, 0);
        v[a] = 1;
        a *= 10;
        int n = 2;
        while (true)
        {
            outputs.back() += a / b + '0';
            a %= b;
            if (v[a])
            {
                outputs.push_back("The last " + to_string(n - v[a]) + " digits repeat forever.");
                return;
            }
            if (a == 0)
            {
                outputs.push_back("This expansion terminates.");
                return;
            }
            if (outputs.back().length() == 50)
                outputs.push_back("");
            v[a] = n++;
            a *= 10;
        }
    }
private:
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
};

int main()
{
    int a, b;
    while (cin >> a >> b && b)
    {
        vs outputs;
        Solution().solve(outputs, a, b);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
    }
    return 0;
}
