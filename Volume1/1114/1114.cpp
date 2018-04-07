#include <iostream>
#include <cctype>
#include <string>
#include <map>
using namespace std;
class Formula
{
public:
    map<string, int> count;
    Formula(const string & s)
    {
        parse(s);
    }
    bool operator==(Formula & f)
    {
        if (count.size() != f.count.size())
            return false;
        for (map<string, int>::iterator it = count.begin(); it != count.end(); ++it)
            if (it->second != f.count[it->first])
                return false;
        return true;
    }
private:
    inline int get_multiplier(const string & s, int & i)
    {
        int multiplier = 0;
        for (; i < s.length() && isdigit(s[i]); ++i)
            multiplier = multiplier * 10 + s[i] - '0';
        return multiplier == 0 ? 1 : multiplier;
    }
    void parse(const string & s)
    {
        for (int i = 0; i < s.length(); ++i)
        {
            int multiplier = get_multiplier(s, i);
            int j = i;
            while (i < s.length() && s[i] != '+')
                ++i;
            parse(s, j, i, multiplier);
        }
    }
    void parse(const string & s, int l, int r, int multiplier)
    {
        while (l < r)
            if (s[l] == '(')
            {
                int i = l + 1;
                int tot = 1;
                for (; i < r; ++i)
                {
                    if (s[i] == '(')
                        ++tot;
                    else if (s[i] == ')')
                        --tot;
                    if (!tot)
                        break;
                }
                int j = i + 1;
                int multiplier2 = get_multiplier(s, j);
                parse(s, l + 1, i, multiplier * multiplier2);
                l = j;
            }
            else if (s[l] >= 'A' && s[l] <= 'Z')
            {
                string element(1, s[l]);
                for (++l; l < r && s[l] >= 'a' && s[l] <= 'z'; ++l)
                    element += s[l];
                int multiplier2 = get_multiplier(s, l);
                count[element] += multiplier * multiplier2;
            }
            else
                ++l;
    }
};

int main()
{
    int n;
    string line_left;
    cin >> line_left;
    Formula left(line_left);
    cin >> n;
    while (n--)
    {
        string line_right;
        cin >> line_right;
        Formula right(line_right);
        if (left == right)
            cout << line_left << "==" << line_right << endl;
        else
            cout << line_left << "!=" << line_right << endl;
    }
    return 0;
}
