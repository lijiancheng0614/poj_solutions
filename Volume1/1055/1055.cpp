#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<int, vector<int> > pivi;
class Solution
{
public:
    void solve(vector<string> & codes)
    {
        int n = codes.size();
        int letters_total = 0;
        int bundles_total = 0;
        vector<string> codes_invalid;
        map<int, int> count_zip;
        for (int i = 0; i < n; ++i)
            if (check(codes[i]))
            {
                int code = to_int(codes[i]);
                ++count_zip[code];
                ++letters_total;
            }
            else
            {
                bool flag = true;
                for (int j = 0; j < codes_invalid.size(); ++j)
                    if (codes_invalid[j] == codes[i])
                    {
                        flag = false;
                        break;
                    }
                if (flag)
                    codes_invalid.push_back(codes[i]);
            }
        output_5digit_bundles(count_zip, bundles_total);
        output_3digit_bundles(count_zip, bundles_total);
        output_first_class(count_zip);
        cout << "TOTALS" << setw(11) << letters_total << setw(12) << bundles_total << endl << endl;
        output_invalid_codes(codes_invalid);
    }
private:
    void output_5digit_bundles(map<int, int> & count_zip, int & bundles_total)
    {
        vector<piii> ans;
        for (map<int, int>::iterator it = count_zip.begin(); it != count_zip.end(); ++it)
            if (it->second >= 10)
            {
                int bundles = it->second / 15;
                int letters = bundles * 15;
                if (it->second - letters >= 10)
                {
                    letters = it->second;
                    ++bundles;
                }
                it->second -= letters;
                ans.push_back(piii(it->first, pii(letters, bundles)));
                bundles_total += bundles;
            }
        cout << "ZIP         LETTERS     BUNDLES" << endl << endl;
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i].first << setw(12) << ans[i].second.first << setw(12) << ans[i].second.second << endl;
        cout << endl;
    }
    void output_3digit_bundles(map<int, int> & count_zip, int & bundles_total)
    {
        vector<piii> ans;
        map<int, pivi> count_3digit;
        for (map<int, int>::iterator it = count_zip.begin(); it != count_zip.end(); ++it)
            if (it->second > 0)
            {
                int idx = it->first / 100;
                count_3digit[idx].first += it->second;
                count_3digit[idx].second.push_back(it->first);
            }
        for (map<int, pivi>::iterator it = count_3digit.begin(); it != count_3digit.end(); ++it)
            if (it->second.first >= 10)
            {
                int bundles = it->second.first / 15;
                int letters = bundles * 15;
                if (it->second.first - letters >= 10)
                {
                    letters = it->second.first;
                    ++bundles;
                }
                bundles_total += bundles;
                ans.push_back(piii(it->first, pii(letters, bundles)));
                for (int i = 0; i < it->second.second.size(); ++i)
                    if (count_zip[it->second.second[i]] < letters)
                    {
                        letters -= count_zip[it->second.second[i]];
                        count_zip[it->second.second[i]] = 0;
                    }
                    else
                    {
                        count_zip[it->second.second[i]] -= letters;
                        break;
                    }
            }
        for (int i = 0; i < ans.size(); ++i)
            cout << ans[i].first << "xx" << setw(12) << ans[i].second.first << setw(12) << ans[i].second.second << endl;
        cout << endl;
    }
    void output_first_class(map<int, int> & count_zip)
    {
        for (map<int, int>::iterator it = count_zip.begin(); it != count_zip.end(); ++it)
            if (it->second > 0)
                cout << it->first << setw(12) << it->second << setw(12) << 0 << endl;
        cout << endl;
    }
    void output_invalid_codes(vector<string> & codes_invalid)
    {
        cout << "INVALID ZIP CODES" << endl << endl;
        for (int i = 0; i < codes_invalid.size(); ++i)
            cout << codes_invalid[i] << endl;
    }
    bool check(string & code)
    {
        if (code.length() != 5)
            return false;
        bool flag = false;
        for (int i = 0; i < 5; ++i)
        {
            if (code[i] < '0' || code[i] > '9')
                return false;
            if (code[i] != '0')
                flag = true;
        }
        return flag;
    }
    inline int to_int(string & x)
    {
        int n;
        stringstream(x) >> n;
        return n;
    }
};

int main()
{
    vector<string> codes;
    string code;
    while (cin >> code)
        codes.push_back(code);
    Solution().solve(codes);
    return 0;
}
