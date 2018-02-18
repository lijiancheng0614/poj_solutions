#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#define L 20
#define C 26
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<bool> vb;
class Trie
{
public:
    Trie()
    {
        g.push_back(vi(C, 0));
        f.push_back(false);
    }
    void add(const string & s)
    {
        int p = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            int k = s[i] - 'A';
            if (!g[p][k])
            {
                g[p][k] = g.size();
                g.push_back(vi(C, 0));
                f.push_back(false);
            }
            p = g[p][k];
        }
        f[p] = true;
    }
    bool dfs(int p, int i, const string & s,
             vb & v, vi & decryption_table)
    {
        if (i == s.length())
            return f[p];
        int j = s[i] - 'A';
        if (decryption_table[j] >= 0)
        {
            int k = decryption_table[j];
            return g[p][k] && dfs(g[p][k], i + 1, s, v, decryption_table);
        }
        for (int k = 0; k < C; ++k)
            if (!v[k] && g[p][k])
            {
                v[k] = true;
                decryption_table[j] = k;
                bool flag = dfs(g[p][k], i + 1, s, v, decryption_table);
                v[k] = false;
                decryption_table[j] = -1;
                if (flag)
                    return true;
            }
        return false;
    }
private:
    vector<vi> g;
    vb f;
};
class Solution
{
public:
    Solution(const vector<string> & words)
    {
        word_length.assign(L + 1, false);
        for (int i = 0; i < words.size(); ++i)
        {
            trie.add(words[i]);
            word_length[words[i].length()] = true;
        }
    }
    string solve(const vector<string> & codes)
    {
        encryption_table = "#No solution#";
        this->codes = codes;
        vi letter_count(C, 0);
        for (int i = 0; i < codes.size(); ++i)
        {
            int l = codes[i].length();
            if (l > L || !word_length[l])
                return encryption_table;
            for (int j = 0; j < l; ++j)
                ++letter_count[codes[i][j] - 'A'];
        }
        letters.clear();
        for (int i = 0; i < C; ++i)
            if (letter_count[i])
                letters.push_back(pii(-letter_count[i], i));
        sort(letters.begin(), letters.end());
        ans_count = 0;
        decryption_table.assign(C, -1);
        v.assign(C, false);
        dfs(0);
        if (ans_count > 1)
            return "#More than one solution#";
        return encryption_table;
    }
private:
    Trie trie;
    vb word_length;
    vector<string> codes;
    vector<pii> letters;
    vi decryption_table;
    vb v;
    string encryption_table;
    int ans_count;
    bool check()
    {
        for (int i = 0; i < codes.size(); ++i)
            if (!trie.dfs(0, 0, codes[i], v, decryption_table))
                return false;
        return true;
    }
    void dfs(int k)
    {
        if (k >= letters.size())
        {
            ++ans_count;
            if (ans_count > 1)
                return;
            encryption_table.assign(C, '*');
            for (int i = 0; i < C; ++i)
                if (decryption_table[i] >= 0)
                    encryption_table[decryption_table[i]] = i + 'A';
            return;
        }
        for (int i = 0; i < C; ++i)
            if (!v[i])
            {
                v[i] = true;
                decryption_table[letters[k].second] = i;
                if (check())
                {
                    dfs(k + 1);
                    if (ans_count > 1)
                        return;
                }
                v[i] = false;
            }
        decryption_table[letters[k].second] = -1;
    }
};


int main()
{
    int t;
    cin >> t;
    vector<string> words;
    while (t--)
    {
        string x;
        cin >> x;
        words.push_back(x);
    }
    Solution solution(words);
    cin >> t;
    string line;
    getline(cin, line);
    getline(cin, line);
    while (t--)
    {
        vector<string> codes;
        getline(cin, line);
        while (line != "")
        {
            stringstream ss(line);
            string x;
            while (ss >> x)
                codes.push_back(x);
            if (cin.eof())
                break;
            getline(cin, line);
        }
        cout << solution.solve(codes) << endl;
    }
    return 0;
}
