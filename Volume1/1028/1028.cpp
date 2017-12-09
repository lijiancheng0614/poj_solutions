#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    void solve(vector<string> commands)
    {
        vector<string> urls(1, "http://www.acm.org/");
        int n = 0;
        int cur = 0;
        for (int i = 0; i < commands.size(); ++i)
            if (commands[i] == "VISIT")
            {
                ++cur;
                n = cur;
                ++i;
                if (cur < urls.size())
                    urls[cur] = commands[i];
                else
                    urls.push_back(commands[i]);
                cout << commands[i] << endl;
            }
            else if (commands[i] == "BACK")
            {
                if (cur <= 0)
                    cout << "Ignored" << endl;
                else
                    cout << urls[--cur] << endl;
            }
            else if (commands[i] == "FORWARD")
            {
                if (cur + 1 > n)
                    cout << "Ignored" << endl;
                else
                    cout << urls[++cur] << endl;
            }
    }
};

int main()
{
    vector<string> commands;
    string s;
    while (cin >> s && s != "QUIT")
        commands.push_back(s);
    Solution().solve(commands);
    return 0;
}
