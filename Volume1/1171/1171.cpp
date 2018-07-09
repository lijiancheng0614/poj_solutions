#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int value[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
class Solution
{
public:
    int solve(char collected[], char dictionary[][8], int n)
    {
        bound.assign(26, 0);
        int n_collected = strlen(collected);
        for (int i = 0; i < n_collected; ++i)
            ++bound[collected[i] - 'a'];
        int ans = 0;
        vector<pii> a;
        for (int i = 0; i < n; ++i)
        {
            if (!check(dictionary[i]))
                continue;
            int v = tovalue(dictionary[i]);
            ans = max(ans, v);
            int n_i = strlen(dictionary[i]);
            if ((n_collected == 6 && n_i == 3) || (n_collected == 7 && n_i <= 4))
                a.push_back(pii(i, v));
        }
        if (n_collected >= 6)
        {
            for (int i = 1; i < a.size(); ++i)
                for (int j = 0; j < i; ++j)
                {
                    int n_i = strlen(dictionary[a[i].first]);
                    int n_j = strlen(dictionary[a[j].first]);
                    char s[n_i + n_j + 1];
                    strcpy(s, dictionary[a[i].first]);
                    strcpy(s + n_i, dictionary[a[j].first]);
                    if (!check(s))
                        continue;
                    ans = max(ans, a[i].second + a[j].second);
                }
        }
        return ans;
    }
private:
    vi bound;
    inline int tovalue(const char s[])
    {
        int v = 0;
        for (int i = 0; i < strlen(s); ++i)
            v += value[s[i] - 'a'];
        return v;
    }
    inline bool check(const char s[])
    {
        vi count(26, 0);
        for (int i = 0; i < strlen(s); ++i)
        {
            ++count[s[i] - 'a'];
            if (count[s[i] - 'a'] > bound[s[i] - 'a'])
                return false;
        }
        return true;
    }
};

int main()
{
    char collected[8];
    scanf("%s", collected);
    char dictionary[40000][8];
    int n = 0;
    while (scanf("%s", dictionary[n]) != EOF && dictionary[n][0] != '.')
        ++n;
    printf("%d\n", Solution().solve(collected, dictionary, n));
    return 0;
}
