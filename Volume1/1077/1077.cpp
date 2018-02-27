#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
const string direction = "ulrd";
const int moves[][4] = {
    { -1, -1, 1, 3}, { -1, 0, 2, 4}, { -1, 1, -1, 5},
    { 0, -1, 4, 6}, { 1, 3, 5, 7}, { 2, 4, -1, 8},
    { 3, -1, 7, -1}, { 4, 6, 8, -1}, { 5, 7, -1, -1}
};
class Solution
{
public:
    Solution(int n = 3, int target_state = 1090176648) : n(n)
    {
        n2 = n * n;
        a.assign(n2, 0);
        factorial.push_back(1);
        for (int i = 1; i <= n2; ++i)
            factorial.push_back(factorial[i - 1] * i);
        move_next.assign(factorial[n2], 0);
        target_c = cantor(target_state);
        bfs(target_state, target_c);
    }
    string solve(vi & a)
    {
        int state = encode(a);
        int c = cantor(state);
        if (!move_next[c])
            return "unsolvable";
        string output = "";
        while (c != target_c)
        {
            output += direction[3 - (move_next[c] & 15)];
            c = move_next[c] >> 4;
        }
        return output;
    }
private:
    vi a;
    vi factorial;
    vi move_next;
    int target_c;
    int n, n2;
    void bfs(int state, int c)
    {
        queue<pii> q;
        move_next[c] = encode_cantor_and_move(c, 4);
        q.push(pii(state, c));
        while (!q.empty())
        {
            pii head = q.front();
            q.pop();
            int i = get_x(head.first);
            int d = move_next[head.second] & 15;
            for (int k = 0; k < 4; ++k)
            {
                int j = moves[i][k];
                if (~j && d + k != 3)
                {
                    state = head.first + update_state(get_state(head.first, j), i, j);
                    c = cantor(state);
                    if (!move_next[c])
                    {
                        move_next[c] = encode_cantor_and_move(head.second, k);
                        q.push(pii(state, c));
                    }
                }
            }
        }
    }
    inline int cantor(int s)
    {
        decode(s);
        int c = 0;
        for (int i = 1; i < n2; ++i)
        {
            int inv = 0;
            for (int j = 0; j < i; ++j)
                inv += a[j] < a[i];
            c += inv * factorial[i];
        }
        return c;
    }
    inline int encode(vi & a)
    {
        int s = 0;
        for (int i = 0; i < n2; ++i)
            s |= a[i] ? ((a[i] - 1) << (i * 3)) : (i << 27);
        return s;
    }
    inline void decode(int s)
    {
        for (int i = 0; i < n2; ++i)
            a[i] = get_state(s, i) + 1;
        a[get_x(s)] = 0;
    }
    inline int get_state(int s, int i)
    {
        return (s >> (i * 3)) & 7;
    }
    inline int get_x(int s)
    {
        return s >> 27;
    }
    inline int update_state(int s, int i, int j)
    {
        return (s << (i * 3)) - (s << (j * 3)) + (j << 27) - (i << 27);
    }
    inline int encode_cantor_and_move(int c, int d)
    {
        return (c << 4) | d;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    Solution solution;
    string line;
    while (!cin.eof())
    {
        getline(cin, line);
        if (line == "")
            break;
        stringstream ss(line);
        vi a;
        for (int i = 0; i < 9; ++i)
        {
            string s;
            ss >> s;
            a.push_back(s[0] == 'x' ? 0 : s[0] - '0');
        }
        cout << solution.solve(a) << endl;
    }
    return 0;
}
