#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
enum DIRECTION
{
    LEFT, UP, RIGHT, DOWN
};
class Node
{
public:
    int type;
    int left, right;
    Node() : type(-1), left(-1), right(-1) {}
    Node(int type, int left, int right) : type(type), left(left), right(right) {}
};
class Circuit
{
public:
    Circuit(vector<string> & inputs)
    {
        pii output = find(inputs);
        n = 0;
        tree.push_back(Node());
        construct_tree(inputs, 0, output.first, output.second, LEFT);
    }
    int get_output(string & input)
    {
        return get_output(input, 0);
    }
private:
    vector<Node> tree;
    int n;
    pii find(vector<string> & inputs, char c = '?')
    {
        for (int i = 0; i < inputs.size(); ++i)
            for (int j = 0; j < inputs[i].length(); ++j)
                if (inputs[i][j] == c)
                    return pii(i, j);
        return pii(-1, -1);
    }
    void construct_tree(vector<string> & inputs, int id, int x, int y, DIRECTION d)
    {
        if (inputs[x][y] == '?')
        {
            if (y && inputs[x][y - 1] == '-')
                construct_tree(inputs, id, x, y - 2, LEFT);
            else if (y + 1 < inputs[x].size() && inputs[x][y + 1] == '-')
                construct_tree(inputs, id, x, y + 2, RIGHT);
            else if (x && inputs[x - 1][y] == '|')
                construct_tree(inputs, id, x - 2, y, UP);
            else if (x + 1 < inputs.size() && inputs[x + 1][y] == '|')
                construct_tree(inputs, id, x + 2, y, DOWN);
            else if (y)
                construct_tree(inputs, id, x, y - 1, LEFT);
        }
        else if (inputs[x][y] == ')')
        {
            // and
            tree[id] = Node(-2, n + 1, n + 2);
            tree.push_back(Node());
            tree.push_back(Node());
            n += 2;
            construct_tree(inputs, tree[id].left, x - 1, y - 3, LEFT);
            construct_tree(inputs, tree[id].right, x + 1, y - 3, LEFT);
        }
        else if (inputs[x][y] == '>')
        {
            // or
            tree[id] = Node(-3, n + 1, n + 2);
            tree.push_back(Node());
            tree.push_back(Node());
            n += 2;
            construct_tree(inputs, tree[id].left, x - 1, y - 3, LEFT);
            construct_tree(inputs, tree[id].right, x + 1, y - 3, LEFT);
        }
        else if (inputs[x][y] == 'o')
        {
            // not
            tree[id] = Node(-4, n + 1, -1);
            tree.push_back(Node());
            ++n;
            if (inputs[x][y - 1] == ')' || inputs[x][y - 1] == '>')
                construct_tree(inputs, tree[id].left, x, y - 1, LEFT);
            else if (inputs[x][y - 1] == '-' && d != RIGHT)
                construct_tree(inputs, tree[id].left, x, y - 2, LEFT);
            else if (inputs[x][y + 1] == '-' && d != LEFT)
                construct_tree(inputs, tree[id].left, x, y - 2, RIGHT);
            else if (x && inputs[x - 1][y] == '|' && d != DOWN)
                construct_tree(inputs, tree[id].left, x - 2, y, UP);
            else if (x + 1 < inputs.size() && inputs[x + 1][y] == '|' && d != UP)
                construct_tree(inputs, tree[id].left, x + 2, y, DOWN);
        }
        else if (inputs[x][y] == '+')
        {
            if (d == UP || d == DOWN)
            {
                if (y && inputs[x][y - 1] == '-')
                    construct_tree(inputs, id, x, y - 2, LEFT);
                else
                    construct_tree(inputs, id, x, y + 2, RIGHT);
            }
            else
            {
                if (x && inputs[x - 1][y] == '|')
                    construct_tree(inputs, id, x - 2, y, UP);
                else
                    construct_tree(inputs, id, x + 2, y, DOWN);
            }
        }
        else if (inputs[x][y] == '-')
        {
            if (d == LEFT)
                construct_tree(inputs, id, x, y - 1, LEFT);
            else
                construct_tree(inputs, id, x, y + 1, RIGHT);
        }
        else if (inputs[x][y] == '|')
        {
            if (d == UP)
                construct_tree(inputs, id, x - 1, y, UP);
            else
                construct_tree(inputs, id, x + 1, y, DOWN);
        }
        else
        {
            tree[id] = Node(inputs[x][y] - 'A', -1, -1);
        }
    }
    int get_output(string & input, int id)
    {
        if (tree[id].type == -2)
            return get_output(input, tree[id].left) && get_output(input, tree[id].right);
        if (tree[id].type == -3)
            return get_output(input, tree[id].left) || get_output(input, tree[id].right);
        if (tree[id].type == -4)
            return !get_output(input, tree[id].left);
        return input[tree[id].type] - '0';
    }
};

int main()
{
    string line;
    getline(cin, line);
    while (line != "")
    {
        vector<string> inputs;
        while (line != "*")
        {
            inputs.push_back(line);
            getline(cin, line);
        }
        Circuit circuit(inputs);
        getline(cin, line);
        while (line != "*")
        {
            cout << circuit.get_output(line) << endl;
            getline(cin, line);
        }
        if (cin.eof())
            break;
        cout << endl;
        getline(cin, line);
    }
    return 0;
}
