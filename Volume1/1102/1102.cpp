#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<string> vs;
const char code[5][31] = {
    " -     -  -     -  -  -  -  - ",
    "| |  |  |  || ||  |    || || |",
    "       -  -  -  -  -     -  - ",
    "| |  ||    |  |  || |  || |  |",
    " -     -  -     -  -     -  - ",
};
class Solution
{
public:
    vs solve(int s, const string & n)
    {
        vs outputs;
        for (int i = 0; i < 5; ++i)
        {
            string output = get_line(i, s, n);
            outputs.push_back(output);
            if (i == 1 || i == 3)
                for (int j = 1; j < s; ++j)
                    outputs.push_back(output);
        }
        return outputs;
    }
private:
    inline string get_line(int t, int s, const string & n)
    {
        string output = "";
        for (int i = 0; i < n.size(); ++i)
        {
            int k = n[i] - '0';
            if (i)
                output += " ";
            output += code[t][k * 3];
            for (int j = 0; j < s; ++j)
                output += code[t][k * 3 + 1];
            output += code[t][k * 3 + 2];
        }
        return output;
    }
};

int main()
{
    int s;
    string n;
    while (cin >> s >> n && s)
    {
        vs outputs = Solution().solve(s, n);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        cout << endl;
    }
    return 0;
}
