#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

class Agent
{
public:
    int time_start;
    int num_visited;
    vector<int> room_num;
    vector<int> duration;
};

class Solution
{
    static const int time_period;
    static const int time_enter;
    static const int time_floor_transfer;
    static const int time_room_transfer;
    static map<int, int> time_room_available;
    static vector<int> time_agent;
public:
    Solution(vector<Agent> agents)
    {
        this->agents = agents;
        time_agent.clear();
        for (int i = 0; i < agents.size(); ++i)
            time_agent.push_back(agents[i].time_start);
        records.assign(agents.size(), vpii());
    }
    void solve()
    {
        priority_queue<pii, vpii, pii_Compare> queue;
        for (int i = 0; i < agents.size(); ++i)
        {
            if (agents[i].room_num.size() == 0)
                continue;
            if (agents[i].room_num[0] / 100 == 1)
                records[i].push_back(pii(agents[i].room_num[0], time_enter));
            else
                records[i].push_back(pii(100, time_enter));
            time_agent[i] += time_enter;
            queue.push(pii(i, records[i].back().first));
        }
        map<int, bool> updated;
        while (!queue.empty())
        {
            pii state = queue.top();
            queue.pop();
            int room_num = state.second;
            if (updated[room_num])
            {
                queue.push(state);
                updated[room_num] = false;
                continue;
            }
            int i = state.first;
            int time = time_agent[i];
            int floor_num = room_num / 100;
            int room_num_to;
            if (room_num % 100 == 0)
            {
                // wait for elevator
                int time_wait = 0;
                if (time <= time_room_available[room_num])
                    time_wait = time_room_available[room_num] - time;
                else if (time % time_period)
                    time_wait = time_period - time % time_period;
                if (time_wait)
                    records[i].push_back(pii(room_num, time_wait));
                time_agent[i] += time_wait;
                time_room_available[room_num] = time_agent[i] + time_period;
                updated[room_num] = true;
                room_num_to = agents[i].room_num[agents[i].num_visited];
                if (room_num_to == 0)
                {
                    // Exit
                    records[i].push_back(pii(100, time_floor_transfer * (floor_num - 1)));
                    records[i].push_back(pii(room_num_to, time_enter));
                    continue;
                }
                // transfer to floor
                int floor_num_to = room_num_to / 100;
                int time_transfer = time_floor_transfer * (max(floor_num_to, floor_num) - min(floor_num_to, floor_num));
                records[i].push_back(pii(floor_num_to * 100, time_transfer));
                time_agent[i] += time_transfer;
            }
            else
            {
                // wait for room
                int time_wait = max(time_room_available[room_num] - time, 0);
                if (time_wait)
                    records[i].push_back(pii(room_num, time_wait));
                time_agent[i] += time_wait;
                int time_stay = agents[i].duration[agents[i].num_visited];
                records[i].push_back(pii(-room_num, time_stay));
                time_agent[i] += time_stay;
                time_room_available[room_num] = time_agent[i];
                updated[room_num] = true;
                ++agents[i].num_visited;
                room_num_to = agents[i].room_num[agents[i].num_visited];
                if (room_num_to == 0 && floor_num == 1)
                {
                     // Exit
                    records[i].push_back(pii(room_num_to, time_enter));
                    continue;
                }
                // transfer to elevator
                if (room_num_to / 100 != floor_num)
                    room_num_to = floor_num * 100;
            }
            records[i].push_back(pii(room_num_to, time_room_transfer));
            time_agent[i] += time_room_transfer;
            queue.push(pii(i, room_num_to));
        }
    }
    void output()
    {
        for (int i = 0; i < agents.size(); ++i)
        {
            if (records[i].size() == 0)
                continue;
            int time = agents[i].time_start;
            int pos_pre = 0;
            cout << char('A' + i) << endl;
            for (int j = 0; j < records[i].size(); ++j)
            {
                cout << convert_time(time) << " ";
                time += records[i][j].second;
                cout << convert_time(time) << " ";
                int pos_cur = records[i][j].first;
                cout << get_description(pos_pre, pos_cur) << endl;
                pos_pre = pos_cur;
            }
            cout << endl;
        }
    }
private:
    vector<Agent> agents;
    vector<vpii> records;
    struct pii_Compare
    {
        bool operator()(const pii &a, const pii &b)
        {
            int time_a = time_agent[a.first];
            int time_b = time_agent[b.first];
            if (a.second != b.second)
                return time_a > time_b;
            if (time_a == time_b)
                return a.first > b.first;
            int room_num = a.second;
            if (room_num % 100 == 0)
            {
                if (time_a % time_period)
                    time_a = (time_a / time_period + 1) * time_period;
                if (time_b % time_period)
                    time_b = (time_b / time_period + 1) * time_period;
                if ((time_a <= time_room_available[room_num] && time_b <= time_room_available[room_num]) || time_a == time_b)
                    return a.first > b.first;
                return time_a > time_b;
            }
            if (time_a <= time_room_available[room_num] && time_b <= time_room_available[room_num])
                return a.first > b.first;
            return time_a > time_b;
        }
    };
    inline string to_string(int n, int width = 4)
    {
        stringstream ss;
        ss << setw(width) << setfill('0') << n;
        return ss.str();
    }
    inline string convert_time(int time)
    {
        int hours = time / 3600;
        int minutes = (time % 3600) / 60;
        int seconds = time % 3600 % 60;
        stringstream ss;
        ss.fill('0');
        ss << setw(2) << hours << ":" << setw(2) << minutes << ":" << setw(2) << seconds;
        return ss.str();
    }
    string get_description(int pre, int cur)
    {
        if (pre == 0)
            return "Entry";
        if (cur == 0)
            return "Exit";
        if (cur < 0)
            return "Stay in room " + to_string(-cur);
        if (pre == cur)
        {
            if (cur % 100 == 0)
                return "Waiting in elevator queue";
            return "Waiting in front of room " + to_string(cur);
        }
        if (pre % 100 == 0 && cur % 100 == 0)
            return "Stay in elevator";
        if (pre < 0)
        {
            if (cur % 100 == 0)
                return "Transfer from room " + to_string(-pre) + " to elevator";
            return "Transfer from room " + to_string(-pre) + " to room " + to_string(cur);
        }
        return "Transfer from elevator to room " + to_string(cur);
    }
};
const int Solution::time_period = 5;
const int Solution::time_enter = 30;
const int Solution::time_floor_transfer = 30;
const int Solution::time_room_transfer = 10;
map<int, int> Solution::time_room_available;
vector<int> Solution::time_agent;

int main()
{
    char c;
    vector<Agent> agents(26, Agent());
    while (cin >> c && c != '.')
    {
        int i = c - 'A';
        string s;
        cin >> s;
        int hours = (s[0] - '0') * 10 + s[1] - '0';
        int minutes = (s[3] - '0') * 10 + s[4] - '0';
        int seconds = (s[6] - '0') * 10 + s[7] - '0';
        agents[i].time_start = hours * 3600 + minutes * 60 + seconds;
        int room_num;
        while (cin >> room_num && room_num)
        {
            int duration;
            cin >> duration;
            agents[i].room_num.push_back(room_num);
            agents[i].duration.push_back(duration);
        }
        agents[i].room_num.push_back(0);
        agents[i].duration.push_back(0);
    }
    Solution solution(agents);
    solution.solve();
    solution.output();
    return 0;
}
