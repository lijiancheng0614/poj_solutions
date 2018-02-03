#include <iostream>
#include <cmath>
using namespace std;
class Solution
{
public:
    bool win(int a, int b)
    {
        if (a > b)
            swap(a, b);
        b = floor((b - a) * (1 + sqrt(5)) / 2);
        return a != b;
    }
};

int main()
{
    int a, b;
    while (cin >> a >> b)
        cout << Solution().win(a, b) << endl;
    return 0;
}
