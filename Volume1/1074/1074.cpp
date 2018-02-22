#include <iostream>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<bool> vb;
typedef vector<string> vs;
class State
{
public:
    vd variables;
    double p;
    State(int n_variables, int n_programs=2, int n_registers=2)
    {
        variables.assign(n_variables, 0);
        registers.assign(n_programs, vd(n_registers, 0));
        p = 1;
    }
    void run(int id, int program_id, int a, int b, int c, bool op)
    {
        switch (id % 4)
        {
            case 0:
                variables[-a - 1] = registers[program_id][0];
                break;
            case 1:
                registers[program_id][0] = b < 0 ? variables[-b - 1] : b;
                break;
            case 2:
                registers[program_id][1] = c < 0 ? variables[-c - 1] : c;
                break;
            case 3:
                if (op)
                    registers[program_id][0] += registers[program_id][1];
                else
                    registers[program_id][0] -= registers[program_id][1];
                break;
        }
    }
    void update(const State & s1, double p1, const State & s2, double p2)
    {
        p = p1 + p2;
        for (int i = 0; i < variables.size(); ++i)
            variables[i] = (s1.variables[i] * p1 + s2.variables[i] * p2) / p;
        for (int i = 0; i < registers.size(); ++i)
            for (int j = 0; j < registers[i].size(); ++j)
                registers[i][j] = (s1.registers[i][j] * p1 + s2.registers[i][j] * p2) / p;
    }
private:
    vector<vd> registers;
};
class Solution
{
public:
    vd solve(const vector<vs> & programs)
    {
        n_variables = 0;
        vector<vi> a(2, vi()), b(2, vi()), c(2, vi());
        vector<vb> op(2, vb());
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < programs[i].size(); ++j)
            {
                string x = "";
                for (int k = 0; k < programs[i][j].size(); ++k)
                    if (programs[i][j][k] == ':')
                    {
                        a[i].push_back(-get_variable_id(x));
                        x = "";
                        ++k;
                    }
                    else if (programs[i][j][k] == '+' || programs[i][j][k] == '-')
                    {
                        if (isdigit(x[0]))
                            b[i].push_back(to_int(x));
                        else
                            b[i].push_back(-get_variable_id(x));
                        op[i].push_back(programs[i][j][k] == '+');
                        x = "";
                    }
                    else if (programs[i][j][k] != ' ')
                        x += tolower(programs[i][j][k]);
                if (isdigit(x[0]))
                    c[i].push_back(to_int(x));
                else
                    c[i].push_back(-get_variable_id(x));
            }
        // dp
        int n0 = programs[0].size() * 4;
        int n1 = programs[1].size() * 4;
        vector< vector<State> > f(n0 + 1, vector<State>(n1 + 1, State(n_variables)));
        State state_init(n_variables);
        for (int i = 0; i <= n0; ++i)
            for (int j = 0; j <= n1; ++j)
            {
                if (i == 0 && j == 0)
                    continue;
                State f0(n_variables), f1(n_variables);
                double p0 = 0, p1 = 0;
                if (i == 0)
                {
                    int id = (j - 1) / 4;
                    f1 = f[i][j - 1];
                    p1 = f1.p * 0.5;
                    f1.run(j, 1, a[1][id], b[1][id], c[1][id], op[1][id]);
                }
                else if (j == 0)
                {
                    int id = (i - 1) / 4;
                    f0 = f[i - 1][j];
                    p0 = f0.p * 0.5;
                    f0.run(i, 0, a[0][id], b[0][id], c[0][id], op[0][id]);
                }
                else
                {
                    int id = (i - 1) / 4;
                    f0 = f[i - 1][j];
                    p0 = f0.p * (j == n1 ? 1 : 0.5);
                    f0.run(i, 0, a[0][id], b[0][id], c[0][id], op[0][id]);
                    id = (j - 1) / 4;
                    f1 = f[i][j - 1];
                    p1 = f1.p * (i == n0 ? 1 : 0.5);
                    f1.run(j, 1, a[1][id], b[1][id], c[1][id], op[1][id]);
                }
                f[i][j].update(f0, p0, f1, p1);
            }
        vd ans;
        for (map<string, int>::iterator it = variables.begin();
            it != variables.end(); ++it)
            ans.push_back(f[n0][n1].variables[it->second - 1]);
        return ans;
    }
private:
    map<string, int> variables;
    int n_variables;
    int get_variable_id(string & x)
    {
        if (!variables[x])
            variables[x] = ++n_variables;
        return variables[x];
    }
    inline int to_int(string & x)
    {
        int n;
        stringstream(x) >> n;
        return n;
    }
};

vs read_program()
{
    vs program;
    string line;
    getline(cin, line);
    while (line != "END")
    {
        if (line != "")
            program.push_back(line);
        getline(cin, line);
    }
    return program;
}

int main()
{
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--)
    {
        vector<vs> programs;
        for (int i = 0; i < 2; ++i)
            programs.push_back(read_program());
        vd variables = Solution().solve(programs);
        for (int i = 0; i < variables.size(); ++i)
            cout << fixed << setprecision(4) << variables[i] << endl;
        cout << endl;
    }
    return 0;
}
