#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, string> pis;
typedef vector<pis> vpis;

class Solution
{
public:
    Solution(vector<vpis> & dict)
    {
        this->dict = dict;
    }
    string solve(string & s)
    {
        int len = s.length();
        vpis replacements;
        for (int i = 0; i < dict[len].size(); ++i)
        {
            int dis = get_distance(dict[len][i].second, s);
            if (dis == 0)
                return s + " is correct";
            if (dis == 1)
                replacements.push_back(dict[len][i]);
        }
        for (int k = len - 1; k < len + 2; k += 2)
            for (int i = 0; i < dict[k].size(); ++i)
                if (get_distance(dict[k][i].second, s) == 1)
                    replacements.push_back(dict[k][i]);
        string ans = s + ":";
        sort(replacements.begin(), replacements.end());
        for (int i = 0; i < replacements.size(); ++i)
            ans += " " + replacements[i].second;
        return ans;
    }
private:
    vector<vpis> dict;
    int get_distance(string & a, string & b)
    {
        int s = 0;
        int n = a.length();
        int m = b.length();
        if (n == m)
        {
            for (int i = 0; i < n; ++i)
                if (a[i] != b[i])
                    ++s;
        }
        else if (n < m)
        {
            int i = 0, j = 0;
            while (i < n && j < m)
            {
                if (a[i] != b[j])
                    ++s;
                else
                    ++i;
                ++j;
            }
            s += n - i + m - j;
        }
        else
            s = get_distance(b, a);
        return s;
    }
};

int main()
{
    string s;
    vector<vpis> dict(16, vpis());
    int order = 0;
    while (cin >> s && s != "#")
    {
        int len = s.length();
        dict[len].push_back(pis(order++, s));
    }
    Solution solution(dict);
    while (cin >> s && s != "#")
        cout << solution.solve(s) << endl;
    return 0;
}
