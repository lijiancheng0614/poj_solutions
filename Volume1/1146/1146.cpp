#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool get_successor(string & s)
    {
        return next_permutation(s.begin(), s.end());
    }
};

int main()
{
    string s;
    while (cin >> s && s != "#")
    {
        if (Solution().get_successor(s))
            cout << s << endl;
        else
            cout << "No Successor" << endl;
    }
    return 0;
}
