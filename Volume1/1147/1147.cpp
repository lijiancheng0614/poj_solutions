#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;

class Solution
{
public:
    vi bwt_decode(const vi & a)
    {
        int n = a.size();
        vi p;
        for (int i = 0; i < n; ++i)
            if (!a[i])
                p.push_back(i);
        int n0 = p.size();
        for (int i = 0; i < n; ++i)
            if (a[i])
                p.push_back(i);
        vi b;
        for (int i = 0; n--; i = p[i])
            b.push_back(i >= n0);
        return b;
    }
};

int main()
{
    int n;
    cin >> n;
    vi a(n, 0);
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    a = Solution().bwt_decode(a);
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}
