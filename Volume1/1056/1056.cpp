#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
class Trie
{
public:
    Trie(int c) : c(c)
    {
        g.push_back(vi(c, 0));
        f.push_back(false);
    }
    bool add(string & s)
    {
        int p = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            int k = s[i] - '0';
            if (!g[p][k])
            {
                g[p][k] = g.size();
                g.push_back(vi(c, 0));
                f.push_back(false);
            }
            p = g[p][k];
            if (f[p])
                return false;
        }
        f[p] = true;
        return true;
    }
private:
    vector<vi> g;
    vector<bool> f;
    int c;
};
class Solution
{
public:
    bool solve(vector<string> & codes)
    {
        Trie trie(2);
        for (int i = 0; i < codes.size(); ++i)
            if (!trie.add(codes[i]))
                return false;
        return true;
    }
};


int main()
{
    int t = 0;
    string code;
    while (cin >> code)
    {
        vector<string> codes;
        while (code != "9")
        {
            codes.push_back(code);
            cin >> code;
        }
        cout << "Set " << ++t << " is " <<
            (Solution().solve(codes) ? "" : "not ") << "immediately decodable" << endl;
    }
    return 0;
}
