#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<bool> vb;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const bool reflect_factors[][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};

class Board
{
public:
    Board(int w, int h) : w(w), h(h)
    {
        board.assign(w, vb(h, false));
    }
    void put(vector<pii> points)
    {
        for (int i = 0; i < points.size(); ++i)
            board[points[i].first][points[i].second] = true;
    }
    vector<vpii> get_pieces()
    {
        vector<vpii> pieces;
        for (int x = 0; x < w; ++x)
            for (int y = 0; y < h; ++y)
                if (board[x][y])
                    pieces.push_back(bfs(x, y));
        return pieces;
    }
private:
    int w, h;
    vector<vb> board;
    vpii bfs(int x, int y)
    {
        vpii piece;
        board[x][y] = false;
        piece.push_back(pii(x, y));
        int head = 0;
        while (head < piece.size())
        {
            int x = piece[head].first;
            int y = piece[head].second;
            ++head;
            for (int k = 0; k < 4; ++k)
            {
                int xx = x + dx[k];
                int yy = y + dy[k];
                if (xx >= 0 && xx < w && yy >= 0 && yy < h && board[xx][yy])
                {
                    board[xx][yy] = false;
                    piece.push_back(pii(xx, yy));
                }
            }
        }
        return piece;
    }
};

class Solution
{
public:
    bool solve(int w, int h, vpii points_a, vpii points_b)
    {
        Board a(w, h), b(w, h);
        a.put(points_a);
        b.put(points_b);
        vector<vpii> pieces_a = a.get_pieces();
        vector<vpii> pieces_b = b.get_pieces();
        int n = pieces_a.size();
        if (pieces_b.size() != n)
            return false;
        for (int i = 0; i < n; ++i)
        {
            process(pieces_a[i]);
            process(pieces_b[i]);
        }
        sort(pieces_a.begin(), pieces_a.end());
        sort(pieces_b.begin(), pieces_b.end());
        for (int i = 0; i < n; ++i)
            if (pieces_a[i] != pieces_b[i])
                return false;
        return true;
    }
private:
    void process(vpii & piece)
    {
        int n = piece.size();
        // move
        int xmin = piece[0].first, ymin = piece[0].second;
        for (int i = 0; i < n; ++i)
        {
            xmin = min(xmin, piece[i].first);
            ymin = min(ymin, piece[i].second);
        }
        int xmax = 0, ymax = 0;
        for (int i = 0; i < n; ++i)
        {
            piece[i].first -= xmin;
            piece[i].second -= ymin;
            xmax = max(xmax, piece[i].first);
            ymax = max(ymax, piece[i].second);
        }
        // reflect
        vector<vpii> pieces_reflected(4, piece);
        for (int k = 0; k < 4; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                if (reflect_factors[k][0])
                    pieces_reflected[k][i].first = xmax - pieces_reflected[k][i].first;
                if (reflect_factors[k][1])
                    pieces_reflected[k][i].second = ymax - pieces_reflected[k][i].second;
            }
            sort(pieces_reflected[k].begin(), pieces_reflected[k].end());
        }
        sort(pieces_reflected.begin(), pieces_reflected.end());
        piece = pieces_reflected[0];
        // transpose
        vpii piece_transposed = piece;
        for (int i = 0; i < n; ++i)
            swap(piece_transposed[i].first, piece_transposed[i].second);
        sort(piece_transposed.begin(), piece_transposed.end());
        if (piece_transposed < piece)
            piece = piece_transposed;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int w, h, n;
        cin >> w >> h >> n;
        vpii points[2];
        for (int k = 0; k < 2; ++k)
            for (int i = 0; i < n; ++i)
            {
                int x, y;
                cin >> x >> y;
                points[k].push_back(pii(x, y));
            }
        cout << (Solution().solve(w, h, points[0], points[1]) ? "YES" : "NO") << endl;
    }
    return 0;
}
