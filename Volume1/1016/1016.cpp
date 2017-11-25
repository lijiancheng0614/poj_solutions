#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string solve(string n)
    {
        string ans = n + " ";
        vector<string> inventory;
        for (int i = 0; i < 15; ++i)
        {
            inventory.push_back(n);
            n = get_inventory(n);
            for (int j = 0; j <= i; ++j)
                if (n == inventory[j])
                {
                    if (i == j && j == 0)
                        return ans + "is self-inventorying";
                    else if (i == j && j > 0)
                        return ans + "is self-inventorying after " + to_string(j) + " steps";
                    else
                        return ans + "enters an inventory loop of length " + to_string(i - j + 1);
                }
        }
        return ans + "can not be classified after 15 iterations";
    }
private:
    string get_inventory(string n)
    {
        stringstream ss;
        int c[10] = {0};
        for (int i = 0; i < n.length(); ++i)
        {
            int d = n[i] - '0';
            ++c[d];
        }
        for (int d = 0; d < 10; ++d)
            if (c[d] > 0)
                ss << 10 * c[d] + d;
        return ss.str();
    }
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
};

int main()
{
    string n;
    while (cin >> n && n != "-1")
        cout << Solution().solve(n) << endl;
    return 0;
}
