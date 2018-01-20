#include <iostream>
#include <vector>
using namespace std;
const int BOARD_SIZE = 100;
class Solution
{
public:
    Solution(vector<int> & moves) : moves(moves){}
    int solve(int n, vector<int> & board)
    {
        vector<int> pos(n, 0);
        int player_id = 0;
        int move_id = 0;
        while (true)
        {
            if (pos[player_id] < 0)
                pos[player_id] = -pos[player_id];
            else
            {
                int target = pos[player_id] + moves[move_id++];
                if (target == BOARD_SIZE)
                    return player_id + 1;
                if (target < BOARD_SIZE)
                {
                    pos[player_id] = target;
                    if (board[target] > BOARD_SIZE)
                        continue;
                    else if (board[target] < 0)
                        pos[player_id] = -pos[player_id];
                    else if (board[target])
                        pos[player_id] = board[target];
                }
            }
            player_id = (player_id + 1) % n;
        }
        return 1;
    }
private:
    vector<int> moves;
};


int main()
{
    vector<int> moves;
    int x;
    while (cin >> x && x)
        moves.push_back(x);
    Solution solution(moves);
    int n;
    while (cin >> n && n)
    {
        vector<int> board(BOARD_SIZE + 1, 0);
        int x, y;
        while (cin >> x >> y && x)
            board[x] = y;
        while (cin >> x && x)
            if (x > 0)
                board[x] = BOARD_SIZE + 1;
            else
                board[-x] = -1;
        cout << solution.solve(n, board) << endl;
    }
    return 0;
}
