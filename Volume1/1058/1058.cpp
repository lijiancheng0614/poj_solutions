#include <iostream>
#include <vector>
using namespace std;
typedef vector<string> vs;
typedef vector<bool> vb;
class Node
{
public:
    Node(string name) : name(name){}
    vector<string> files;
    vector<Node *> dirs;
    string name;
};
class Solution
{
public:
    Solution(int n = 16) : n(n) {}
    bool solve(vector<vs> & lines, vector<vs> & ans)
    {
        ans.assign(2, vs(4, "AAAA"));
        graph.assign(n, vb(n, false));
        for (int i = 0; i < lines.size(); ++i)
            for (int j = 0; j < 4; ++j)
                add_block(lines[i][j]);
        for (int i = 1; i < n; ++i)
            if (!graph[0][i])
            {
                vector<int> points = get_disconnected_points(0, i);
                if (points.size() != 2)
                    return false;
                ans[0][0][1] = i + 'A';
                ans[0][0][2] = points[0] + 'A';
                ans[0][0][3] = points[1] + 'A';
                add_block(ans[0][0]);
                for (int j = 0; j < 4; ++j)
                {
                    points = get_disconnected_points(ans[0][0][j] - 'A');
                    if (points.size() != 3)
                        return false;
                    ans[1][j][0] = ans[0][0][j];
                    for (int k = 0; k < 3; ++k)
                        ans[1][j][1 + k] = points[k] + 'A';
                    add_block(ans[1][j]);
                }
                break;
            }
            for (int j = 1; j < 4; ++j)
            {
                vector<int> points = get_disconnected_points(ans[1][0][j] - 'A');
                if (points.size() != 3)
                    return false;
                ans[0][j][0] = ans[1][0][j];
                for (int k = 0; k < 3; ++k)
                    ans[0][j][1 + k] = points[k] + 'A';
                add_block(ans[1][j]);
            }
        return true;
    }
private:
    vector<vb> graph;
    int n;
    void add_block(string & block)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
            {
                int x = block[i] - 'A';
                int y = block[j] - 'A';
                graph[x][y] = graph[y][x] = true;
            }
    }
    vector<int> get_disconnected_points(int i, int j)
    {
        vector<int> ans;
        for (int k = 0; k < n; ++k)
            if (!graph[i][k] && !graph[j][k])
                ans.push_back(k);
        return ans;
    }
    vector<int> get_disconnected_points(int i)
    {
        vector<int> ans;
        for (int k = 0; k < n; ++k)
            if (!graph[i][k])
                ans.push_back(k);
        return ans;
    }
};


int main()
{
    string block;
    while (cin >> block)
    {
        vs line(1, block);
        for (int i = 0; i < 3; ++i)
        {
            cin >> block;
            line.push_back(block);
        }
        vector<vs> lines(1, line);
        for (int i = 0; i < 2; ++i)
        {
            vs line;
            for (int j = 0; j < 4; ++j)
            {
                cin >> block;
                line.push_back(block);
            }
            lines.push_back(line);
        }
        vector<vs> ans;
        bool flag = Solution().solve(lines, ans);
        if (!flag)
            cout << "It is not possible to complete this schedule." << endl;
        else
        {
            for (int i = 0; i < lines.size(); ++i)
            {
                for (int j = 0; j < lines[i].size(); ++j)
                    cout << lines[i][j] << " ";
                cout << endl;
            }
            for (int i = 0; i < ans.size(); ++i)
            {
                for (int j = 0; j < ans[i].size(); ++j)
                    cout << ans[i][j] << " ";
                cout << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
