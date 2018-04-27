#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
    void solve(vector<string> & outputs, int x, int y, const string & moves)
    {
        outputs.assign(32, string(32, '.'));
        for (int i = 0; moves[i] != '.'; ++i)
            if (moves[i] == 'W')
            {
                --y;
                outputs[x][y] = 'X';
            }
            else if (moves[i] == 'E')
            {
                ++y;
                outputs[x + 1][y - 1] = 'X';
            }
            else if (moves[i] == 'N')
            {
                --x;
                outputs[x + 1][y] = 'X';
            }
            else if (moves[i] == 'S')
            {
                ++x;
                outputs[x][y - 1] = 'X';
            }
    }
};

int main()
{
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        int x, y;
        cin >> y >> x;
        string moves;
        cin >> moves;
        cout << "Bitmap #" << tt << endl;
        vector<string> outputs;
        Solution().solve(outputs, 31 - x, y, moves);
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
        if (tt < t)
            cout << endl;
    }
    return 0;
}
