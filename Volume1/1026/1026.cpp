#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    Solution(vector<int> a)
    {
        this->a = a;
        n = a.size();
        for (int i = 0; i < n; ++i)
        {
            len.push_back(1);
            for (int j = a[i]; j != i; j = a[j])
                ++len[i];
        }
    }
    string solve(int k, string s)
    {
        string ans = s;
        for (int i = 0; i < n; ++i)
        {
            int l = k % len[i];
            int j = i;
            while (l--)
                j = a[j];
            ans[j] = s[i];
        }
        return ans;
    }
private:
    vector<int> a;
    vector<int> len;
    int n;
};

int main()
{
    int n;
    while (cin >> n && n)
    {
        vector<int> a;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            a.push_back(x - 1);
        }
        Solution solution(a);
        int k;
        string s;
        while (cin >> k && k)
        {
            cin.get();
            getline(cin, s);
            s += string(n - s.length(), ' ');
            cout << solution.solve(k, s) << endl;
        }
        cout << endl;
    }
    return 0;
}
