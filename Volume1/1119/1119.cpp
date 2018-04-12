#include <iostream>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <string>
#include <map>
using namespace std;
class Solution
{
public:
    double get_score(const map<string, int> & terms, map<string, int> & terms_doc)
    {
        double score = 0;
        for (map<string, int>::const_iterator it = terms.begin(); it != terms.end(); ++it)
            score += sqrt(it->second * terms_doc[it->first]);
        return score;
    }
};

inline string parse(const string & s)
{
    string t = "";
    for (int i = 0; i < s.length(); ++i)
        if (isalnum(s[i]))
            t += toupper(s[i]);
    return t;
}

int main()
{
    const string TERMINATES(10, '-');
    string s;
    map<string, int> terms;
    while (cin >> s && s != TERMINATES)
    {
        string term = parse(s);
        if (term != "")
            ++terms[term];
    }
    while (cin >> s && s != TERMINATES)
    {
        map<string, int> terms_doc;
        while (s != TERMINATES)
        {
            string term = parse(s);
            if (term != "")
                ++terms_doc[term];
            cin >> s;
        }
        cout << fixed << setprecision(2) << Solution().get_score(terms, terms_doc) << endl;
    }
    return 0;
}
