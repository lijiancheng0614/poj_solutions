#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int n_types;
    int value_max;
    int n_cases_same_types;
    int n_cases_same_types_same_value_max;
    vector<int> combination;
    Solution() : n_cases_same_types(0), n_cases_same_types_same_value_max(0) {}
};

void solve(vector<int> values, int request)
{
    Solution f[5][request + 1];
    f[0][0].n_types = f[0][0].value_max = 0;
    f[0][0].n_cases_same_types = f[0][0].n_cases_same_types_same_value_max = 1;
    f[0][0].combination.clear();
    for (int i = 0; i < values.size(); ++i)
        for (int j = request; j >= values[i]; --j)
            for (int k = 1; k <= 4; ++k)
            {
                if (j < values[i] * k)
                    break;
                for (int n = k; n <= 4; ++n)
                {
                    Solution &s = f[n - k][j - values[i] * k];
                    if (s.n_cases_same_types == 0)
                        continue;
                    int n_types = s.n_types + 1;
                    int value_max = max(s.value_max, values[i]);
                    if (f[n][j].n_cases_same_types == 0 || n_types > f[n][j].n_types)
                    {
                        f[n][j].n_types = n_types;
                        f[n][j].value_max = value_max;
                        f[n][j].n_cases_same_types = s.n_cases_same_types;
                        f[n][j].n_cases_same_types_same_value_max = s.n_cases_same_types;
                        f[n][j].combination = s.combination;
                        for (int x = 0; x < k; ++x)
                            f[n][j].combination.push_back(values[i]);
                    }
                    else if (n_types == f[n][j].n_types && value_max > f[n][j].value_max)
                    {
                        f[n][j].value_max = value_max;
                        f[n][j].n_cases_same_types += s.n_cases_same_types;
                        f[n][j].n_cases_same_types_same_value_max = s.n_cases_same_types;
                        f[n][j].combination = s.combination;
                        for (int x = 0; x < k; ++x)
                            f[n][j].combination.push_back(values[i]);
                    }
                    else if (n_types == f[n][j].n_types && value_max == f[n][j].value_max)
                    {
                        f[n][j].n_cases_same_types += s.n_cases_same_types;
                        ++f[n][j].n_cases_same_types_same_value_max;
                    }
                }
            }
    int n = 0;
    for (int i = 1; i <= 4; ++i)
        if (f[i][request].n_cases_same_types_same_value_max && (f[n][request].n_cases_same_types_same_value_max == 0 ||
            f[i][request].n_types > f[n][request].n_types))
            n = i;
    if (f[n][request].n_cases_same_types_same_value_max == 1)
    {
        cout << request << " (" << f[n][request].n_types << "):";
        sort(f[n][request].combination.begin(), f[n][request].combination.end());
        for (int i = 0; i < f[n][request].combination.size(); ++i)
            cout << " " << f[n][request].combination[i];
        cout << endl;
    }
    else if (f[n][request].n_cases_same_types_same_value_max > 1)
        cout << request << " (" << f[n][request].n_types << "): tie" << endl;
    else
        cout << request << " ---- none" << endl;
}

int main()
{
    int value;
    while (cin >> value)
    {
        vector<int> values(1, value);
        while (cin >> value && value)
            values.push_back(value);
        int request;
        while (cin >> request && request)
            solve(values, request);
    }
    return 0;
}
