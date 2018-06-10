#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define N 7
class Point
{
public:
    int x, y, z;
    Point(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator!=(const Point & p) const
    {
        return x != p.x || y != p.y || z != p.z;
    }
    bool operator<(const Point & p) const
    {
        return x < p.x || (x == p.x && y < p.y) ||
               (x == p.x && y == p.y && z < p.z);
    }
    Point & operator-=(const Point & i)
    {
        x -= i.x, y -= i.y, z -= i.z;
        return *this;
    }
};
class Block : vector<Point>
{
public:
    using vector::size;
    using vector::operator[];
    using vector::push_back;
    bool operator<(const Block & b) const
    {
        return size() > b.size();
    }
    bool operator==(const Block & b) const
    {
        if (size() != b.size())
            return false;
        for (int i = 0; i < size(); ++i)
            if ((*this)[i] != b[i])
                return false;
        return true;
    }
    void normalize()
    {
        Point p_min(N, N, N);
        for (int i = 0; i < size(); ++i)
        {
            p_min.x = min(p_min.x, (*this)[i].x);
            p_min.y = min(p_min.y, (*this)[i].y);
            p_min.z = min(p_min.z, (*this)[i].z);
        }
        for (int i = 0; i < size(); ++i)
            (*this)[i] -= p_min;
        sort(begin(), end());
    }
    Block rotate(int axis, int n) const
    {
        if (n == 0)
            return *this;
        Block ans = *this;
        for (int i = 0; i < size(); ++i)
            if (axis == 0)
            {
                ans[i].y = rotate((*this)[i].y, -(*this)[i].z, n);
                ans[i].z = rotate((*this)[i].z, (*this)[i].y, n);
            }
            else if (axis == 1)
            {
                ans[i].x = rotate((*this)[i].x, -(*this)[i].z, n);
                ans[i].z = rotate((*this)[i].z, (*this)[i].x, n);
            }
            else
            {
                ans[i].x = rotate((*this)[i].x, -(*this)[i].y, n);
                ans[i].y = rotate((*this)[i].y, (*this)[i].x, n);
            }
        return ans;
    }
private:
    inline int rotate(int x, int y, int n) const
    {
        return y * (n - 2) - x * (n == 2);
    }
};
class Solution
{
public:
    int solve(const vector<Block> & blocks, const Block & obj)
    {
        n = blocks.size();
        x_max = y_max = z_max = 0;
        for (int i = 0; i < obj.size(); ++i)
        {
            a[obj[i].x][obj[i].y][obj[i].z] = true;
            x_max = max(x_max, obj[i].x);
            y_max = max(y_max, obj[i].y);
            z_max = max(z_max, obj[i].z);
        }
        m = obj.size() / 4;
        while (!dfs(0, 0, obj.size(), blocks))
            ++m;
        return m;
    }
private:
    bool a[N][N][N];
    int n, m, x_max, y_max, z_max;
    bool check_block(const Block & b, int x, int y, int z)
    {
        for (int i = 0; i < b.size(); ++i)
            if (!a[x + b[i].x][y + b[i].y][z + b[i].z])
                return false;
        return true;
    }
    void put_block(const Block & b, int x, int y, int z)
    {
        for (int i = 0; i < b.size(); ++i)
            a[x + b[i].x][y + b[i].y][z + b[i].z] = false;
    }
    void pop_block(const Block & b, int x, int y, int z)
    {
        for (int i = 0; i < b.size(); ++i)
            a[x + b[i].x][y + b[i].y][z + b[i].z] = true;
    }
    bool dfs(int k, int pre, int left, const vector<Block> & blocks)
    {
        if (k == m)
            return left == 0;
        if (left > blocks[pre].size() * (m - k))
            return 0;
        while (pre < n && blocks[pre].size() > left)
            ++pre;
        for (int i = pre; i < n; ++i)
            for (int x = 0; x <= x_max; ++x)
                for (int y = 0; y <= y_max; ++y)
                    for (int z = 0; z <= z_max; ++z)
                        if (check_block(blocks[i], x, y, z))
                        {
                            put_block(blocks[i], x, y, z);
                            if (dfs(k + 1, i, left - blocks[i].size(), blocks))
                                return true;
                            pop_block(blocks[i], x, y, z);
                        }
        return false;
    }
};

bool check(const Block & b, const vector<Block> & blocks)
{
    for (int i = 0; i < blocks.size(); ++i)
        if (b == blocks[i])
            return true;
    return false;
}

void add_rotate(const Block & b, vector<Block> & blocks)
{
    for (int x = 0; x < 4; ++x)
    {
        Block tx = b.rotate(0, x);
        for (int y = 0; y < 4; ++y)
        {
            Block ty = tx.rotate(1, y);
            for (int z = 0; z < 4; ++z)
            {
                Block tz = ty.rotate(2, z);
                tz.normalize();
                if (!check(tz, blocks))
                    blocks.push_back(tz);
            }
        }
    }
}

vector<Block> get_blocks()
{
    vector<Block> blocks;
    int blocks_info[][13] =
    {
        {1, 0, 0, 0},
        {2, 0, 0, 0, 0, 1, 0},
        {3, 0, 0, 0, 0, 1, 0, 0, 2, 0},
        {3, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {4, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0},
        {4, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {4, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2},
        {4, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 1},
        {4, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 1},
        {4, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {4, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1},
        {4, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1}
    };
    for (int i = 0; i < 12; ++i)
    {
        Block b;
        int v = blocks_info[i][0];
        for (int j = 0; j < v; ++j)
            b.push_back(Point(blocks_info[i][j * 3 + 1],
                              blocks_info[i][j * 3 + 2],
                              blocks_info[i][j * 3 + 3]));
        b.normalize();
        blocks.push_back(b);
        add_rotate(b, blocks);
    }
    sort(blocks.begin(), blocks.end());
    return blocks;
}

int main()
{
    ios::sync_with_stdio(false);
    vector<Block> blocks = get_blocks();
    Block obj;
    int v;
    cin >> v;
    for (int i = 0; i < v; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        obj.push_back(Point(x, y, z));
    }
    obj.normalize();
    cout << Solution().solve(blocks, obj) << endl;
    return 0;
}
