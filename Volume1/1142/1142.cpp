#include <iostream>
#include <vector>
using namespace std;
#define N 10001
class Solution
{
public:
    Solution()
    {
        v.assign(N, false);
        v[1] = true;
        for (int i = 2; i < N; ++i)
        {
            if (!v[i])
                p.push_back(i);
            for (int j = 0; j < p.size() && i * p[j] < N; ++j)
            {
                v[i * p[j]] = true;
                if (i % p[j] == 0)
                    break;
            }
        }
    }
    int solve(int n)
    {
        while (++n)
            if (!prime(n) && factor(n) == sum(n))
                break;
        return n;
    }
private:
    vector<int> p;
    vector<bool> v;
    bool prime(int n)
    {
        if (n < N)
            return !v[n];
        for (int i = 0; i < p.size() && p[i] * p[i] <= n; ++i)
            if (n % p[i] == 0)
                return false;
        return true;
    }
    inline int sum(int n)
    {
        int s = 0;
        for (; n; n /= 10)
            s += n % 10;
        return s;
    }
    inline int factor(int n)
    {
        int s = 0;
        for (int i = 0; i < p.size() && p[i] * p[i] <= n; ++i)
            if (n % p[i] == 0)
            {
                int s1 = sum(p[i]);
                for (; n % p[i] == 0; n /= p[i])
                    s += s1;
                if (n == 1)
                    break;
                if (prime(n))
                {
                    s += sum(n);
                    break;
                }
            }
        return s;
    }
};

int main()
{
    Solution solution;
    int n;
    while (cin >> n && n)
        cout << solution.solve(n) << endl;
    return 0;
}
