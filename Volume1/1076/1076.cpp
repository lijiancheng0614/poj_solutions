#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
    vector<string> solve(string & line)
    {
        vector<string> output(2, "");
        stringstream ss(line);
        string name;
        ss >> name;
        vector<int> a;
        int x;
        while (ss >> x && x != -1)
            a.push_back(x);
        output[0] = name + string(12 - name.length(), ' ');
        output[1] = string(12, ' ');
        int k = 0;
        int score_total = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            ++k;
            if (k < 11)
                output[0] += " ";
            if (a[i])
            {
                output[0] += a[i] == 10 ? "-" : to_string(10 - a[i]);
                if (i + 1 < a.size())
                {
                    if (a[i + 1] == 0)
                    {
                        output[0] += "/";
                        if (i + 2 < a.size())
                        {
                            score_total += 20 - a[i + 2];
                            output[1] += to_string(score_total, 4);
                        }
                    }
                    else if (a[i + 1] == a[i])
                    {
                        output[0] += "-";
                        score_total += 10 - a[i];
                        output[1] += to_string(score_total, 4);
                    }
                    else
                    {
                        output[0] += to_string(a[i] - a[i + 1]);
                        score_total += 10 - a[i + 1];
                        output[1] += to_string(score_total, 4);
                    }
                }
                if (i + 2 < a.size() && k < 10)
                    output[0] += " ";
                ++i;
            }
            else
            {
                output[0] += i + 1 < a.size() && k < 10 ? "X  " : "X";
                if (i + 2 < a.size())
                {
                    score_total += (a[i + 1] ? 20 : 30) - a[i + 2];
                    output[1] += to_string(score_total, 4);
                }
            }
        }
        return output;
    }
private:
    inline string to_string(int n, int width = 0)
    {
        stringstream ss;
        ss << setw(width) << n;
        return ss.str();
    }
};

int main()
{
    string line;
    getline(cin, line);
    while (line != "")
    {
        vector<string> output = Solution().solve(line);
        for (int i = 0; i < output.size(); ++i)
            cout << output[i] << endl;
        if (cin.eof())
            break;
        cout << endl;
        getline(cin, line);
    }
    return 0;
}
