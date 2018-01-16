#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
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
    bool solve(vector<string> & lines)
    {
        vector<string> files;
        Node * node = build_tree(lines);
        output_tree(node, 0);
        return true;
    }
private:
    Node * build_tree(vector<string> & lines)
    {
        stack<Node *> s;
        Node * node = new Node("ROOT");
        s.push(node);
        for (int i = 0; i < lines.size(); ++i)
        {
            if (lines[i][0] == 'f')
                node->files.push_back(lines[i]);
            else if (lines[i][0] == 'd')
            {
                Node * node_new = new Node(lines[i]);
                node->dirs.push_back(node_new);
                s.push(node_new);
                node = node_new;
            }
            else
            {
                s.pop();
                node = s.top();
            }
        }
        return node;
    }
    void output_tree(Node * node, int depth)
    {
        for (int i = 0; i < depth; ++i)
            cout << "|     ";
        cout << node->name << endl;
        for (int i = 0; i < node->dirs.size(); ++i)
            output_tree(node->dirs[i], depth + 1);
        if (node->files.size() == 0)
            return;
        sort(node->files.begin(), node->files.end());
        for (int i = 0; i < node->files.size(); ++i)
        {
            for (int j = 0; j < depth; ++j)
                cout << "|     ";
            cout << node->files[i] << endl;
        }
    }
};


int main()
{
    int t = 0;
    string line;
    while (cin >> line && line != "#")
    {
        vector<string> lines;
        while (line != "*")
        {
            lines.push_back(line);
            cin >> line;
        }
        cout << "DATA SET " << ++t << ":" << endl;
        Solution().solve(lines);
        cout << endl;
    }
    return 0;
}
