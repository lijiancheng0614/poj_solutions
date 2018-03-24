#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
    string solve(const string & line)
    {
        for (int i = 0; i < line.length(); ++i)
            if (isdigit(line[i]))
            {
                if (a.size() > 1 && a.back() != -1)
                    a.push_back(-3);
                int x = 0;
                for (; isdigit(line[i]); ++i)
                    x = x * 10 + line[i] - '0';
                a.push_back(x);
                --i;
            }
            else if (line[i] == '(')
            {
                if (a.size() > 1 && a.back() != -1)
                    a.push_back(-3);
                a.push_back(-1);
            }
            else if (line[i] == ')')
                a.push_back(-2);
        if (!dfs(1))
            return "Impossible";
        stringstream ss;
        ss << a[0] << "=";
        for (int i = 1; i < a.size(); ++i)
            if (a[i] >= 0)
                ss << a[i];
            else if (a[i] == -1)
                ss << "(";
            else if (a[i] == -2)
                ss << ")";
            else if (a[i] == -4)
                ss << "+";
            else if (a[i] == -5)
                ss << "-";
            else if (a[i] == -6)
                ss << "*";
        return ss.str();
    }
private:
    vector<int> a;
    int num[13], ops[81];
    int n_num, n_ops;
    bool dfs(int k)
    {
        if (k >= a.size())
            return num[0] == a[0];
        if (a[k] == -3)
        {
            int t_num[13], t_ops[81];
            int t_n_num = n_num, t_n_ops = n_ops;
            for (int i = 0; i < n_num; ++i)
                t_num[i] = num[i];
            for (int i = 0; i < n_ops; ++i)
                t_ops[i] = ops[i];
            for (int op = -4; op >= -6; --op)
            {
                a[k] = op;
                ops[n_ops++] = op;
                if (dfs(k + 1))
                    return true;
                n_num = t_n_num, n_ops = t_n_ops;
                for (int i = 0; i < n_num; ++i)
                    num[i] = t_num[i];
                for (int i = 0; i < n_ops; ++i)
                    ops[i] = t_ops[i];
            }
            a[k] = -3;
        }
        else if (a[k] == -1)
        {
            ops[n_ops++] = -1;
            if (dfs(k + 1))
                return true;
        }
        else if (a[k] == -2)
        {
            --n_num;
            --n_ops;
            add_num(num[n_num]);
            if (dfs(k + 1))
                return true;
        }
        else
        {
            add_num(a[k]);
            if (dfs(k + 1))
                return true;
        }
        return false;
    }
    void add_num(int x)
    {
        if (n_ops == 0 || ops[n_ops - 1] == -1)
            num[n_num++] = x;
        else
        {
            int op = ops[n_ops - 1];
            int k = n_num - 1;
            if (op == -4)
                num[k] += x;
            else if (op == -5)
                num[k] -= x;
            else if (op == -6)
                num[k] *= x;
            --n_ops;
        }
    }
};

int main()
{
    int t = 0;
    while (!cin.eof())
    {
        string line;
        getline(cin, line);
        if (line[0] == '0')
            break;
        cout << "Equation #" << ++t << ":" << endl;
        cout << Solution().solve(line) << endl;
        cout << endl;
    }
    return 0;
}
