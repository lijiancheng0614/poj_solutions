#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef vector<string> vs;
class Node
{
public:
    char c;
    int l, r, h, w;
};
class Solution
{
public:
    vs solve(const string & preorder)
    {
        nodes.assign(1, Node());
        build_tree(preorder, 0, 0);
        outputs.assign(nodes[0].h + 1, string(nodes[0].w + 1, ' '));
        get_outputs(0, 0, 0, nodes[0].h, nodes[0].w);
        return outputs;
    }
private:
    vs outputs;
    vector<Node> nodes;
    int build_tree(const string & preorder, int k, int i)
    {
        nodes[k].c = preorder[i];
        if (preorder[i] >= 'A' && preorder[i] <= 'Z')
        {
            nodes[k].h = nodes[k].w = 2;
            return i + 1;
        }
        nodes[k].l = nodes.size();
        nodes.push_back(Node());
        nodes[k].r = nodes.size();
        nodes.push_back(Node());
        ++i;
        i = build_tree(preorder, nodes[k].l, i);
        i = build_tree(preorder, nodes[k].r, i);
        if (nodes[k].c == '-')
        {
            nodes[k].w = max(nodes[nodes[k].l].w, nodes[nodes[k].r].w);
            nodes[k].h = nodes[nodes[k].l].h + nodes[nodes[k].r].h;
        }
        else if (nodes[k].c == '|')
        {
            nodes[k].h = max(nodes[nodes[k].l].h, nodes[nodes[k].r].h);
            nodes[k].w = nodes[nodes[k].l].w + nodes[nodes[k].r].w;
        }
        return i;
    }
    void get_outputs(int k, int x, int y, int h, int w)
    {
        if (nodes[k].c >= 'A' && nodes[k].c <= 'Z')
        {
            outputs[x][y] = nodes[k].c;
            outputs[x + h][y] = '*';
            outputs[x][y + w] = '*';
            outputs[x + h][y + w] = '*';
            for (int i = x + 1; i < x + h; ++i)
            {
                if (outputs[i][y] == ' ')
                    outputs[i][y] = '|';
                if (outputs[i][y + w] == ' ')
                    outputs[i][y + w] = '|';
            }
            for (int i = y + 1; i < y + w; ++i)
            {
                if (outputs[x][i] == ' ')
                    outputs[x][i] = '-';
                if (outputs[x + h][i] == ' ')
                    outputs[x + h][i] = '-';
            }
            return;
        }
        int l = nodes[k].l, r = nodes[k].r;
        if (nodes[k].c == '-')
        {
            int hh = h * nodes[l].h / (nodes[l].h + nodes[r].h) + (h * nodes[l].h % (nodes[l].h + nodes[r].h) != 0);
            get_outputs(l, x, y, hh, w);
            get_outputs(r, x + hh, y, h - hh, w);
        }
        else if (nodes[k].c == '|')
        {
            int ww = w * nodes[l].w / (nodes[l].w + nodes[r].w) + (w * nodes[l].w % (nodes[l].w + nodes[r].w) != 0);
            get_outputs(l, x, y, h, ww);
            get_outputs(r, x, y + ww, h, w - ww);
        }
    }
};

int main()
{
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        string preorder;
        cin >> preorder;
        vs outputs = Solution().solve(preorder);
        cout << tt << endl;
        for (int i = 0; i < outputs.size(); ++i)
            cout << outputs[i] << endl;
    }
    return 0;
}
