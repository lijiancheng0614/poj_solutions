#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
class Solution
{
public:
    vector<string> solve(const vector<string> & words, int w)
    {
        vector<int> lengths;
        for (int i = 0; i < words.size(); ++i)
            lengths.push_back(words[i].length());
        dp(lengths, w);
        return output(words);
    }
private:
    vector<pii> g;
    inline int sqr(int x)
    {
        return x * x;
    }
    void dp(const vector<int> & lengths, int w)
    {
        int n = lengths.size();
        vector<int> f(n + 1, 0);
        g.assign(n, pii(0, 0));
        for (int i = n - 1; i >= 0; --i)
        {
            f[i] = f[i + 1] + 500;
            int len = lengths[i];
            for (int j = 1; j < n - i; ++j)
            {
                len += lengths[i + j] + 1;
                if (len > w)
                    break;
                int spaces_left = w - len;
                int badness = sqr(spaces_left / j) * j + (2 * (spaces_left / j) + 1) * (spaces_left % j);
                if (f[i + j + 1] + badness <= f[i])
                {
                    f[i] = f[i + j + 1] + badness;
                    g[i] = pii(j, spaces_left);
                }
            }
        }
    }
    vector<string> output(const vector<string> & words)
    {
        vector<string> lines;
        for (int k = 0; k < words.size(); k += g[k].first + 1)
        {
            int n_spaces = g[k].first;
            int spaces_left = g[k].second;
            if (n_spaces == 0)
                lines.push_back(words[k]);
            else
            {
                string line = "";
                string spaces(spaces_left / n_spaces + 1, ' ');
                int split = n_spaces - spaces_left % n_spaces;
                for (int i = 0; i < n_spaces; ++i)
                    line += words[k + i] + spaces + (i >= split ? " " : "");
                line += words[k + n_spaces];
                lines.push_back(line);
            }
        }
        return lines;
    }
};

int main()
{
    int w;
    while (cin >> w && w)
    {
        string line;
        getline(cin, line);
        getline(cin, line);
        vector<string> words;
        while (line != "")
        {
            stringstream ss(line);
            string word;
            while (ss >> word)
                words.push_back(word);
            getline(cin, line);
        }
        vector<string> lines = Solution().solve(words, w);
        for (int i = 0; i < lines.size(); ++i)
            cout << lines[i] << endl;
        cout << endl;
    }
    return 0;
}
