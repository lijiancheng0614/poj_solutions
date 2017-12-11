#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;

class Team
{
public:
    Team(int id) : id(id)
    {
        place = place_offset = place_sum = 0;
        places[0] = places[1] = 0;
    }
    int id, place, place_offset, place_sum;
    int places[2];
    static bool cmp_places2(const Team * const a, const Team * const b)
    {
        if (a->place_sum != b->place_sum)
            return a->place_sum < b->place_sum;
        return a->id < b->id;
    }
    static bool cmp_place(const Team * const a, const Team * const b)
    {
        if (a->place != b->place)
            return a->place < b->place;
        if (a->place_offset != b->place_offset)
            return a->place_offset < b->place_offset;
        return a->id < b->id;
    }
};

class Solution
{
public:
    vector<vi> solve(vector<vi> result_tables[2], int n = 100)
    {
        vector<Team> teams;
        vector<Team *> final_result;
        for (int i = 0; i < n; ++i)
            teams.push_back(Team(i + 1));
        for (int k = 0; k < 2; ++k)
        {
            int place = 1;
            for (int i = 0; i < result_tables[k].size(); ++i)
            {
                for (int j = 0; j < result_tables[k][i].size(); ++j)
                {
                    int idx = result_tables[k][i][j] - 1;
                    teams[idx].places[k] = place;
                    teams[idx].place_sum += place;
                    if (teams[idx].places[0] > 0 && teams[idx].places[1] > 0)
                        final_result.push_back(&teams[idx]);
                }
                place += result_tables[k][i].size();
            }
        }
        int m = final_result.size();
        // two places
        if (m > 0)
        {
            sort(final_result.begin(), final_result.end(), Team::cmp_places2);
            int place = 1;
            final_result[0]->place = 1;
            for (int i = 1; i < final_result.size(); ++i)
            {
                if (final_result[i]->place_sum != final_result[i - 1]->place_sum)
                    place = i + 1;
                final_result[i]->place = place;
            }
        }
        // only one place
        for (int i = 0; i < n; ++i)
            if (teams[i].place_sum > 0 && (teams[i].places[0] == 0 || teams[i].places[1] == 0))
            {
                bool flag = true;
                int k = teams[i].places[1] == 0 ? 0 : 1;
                int place_front = 0, place_behind = n;
                for (int j = 0; j < m; ++j)
                    if (final_result[j]->places[k] < teams[i].places[k])
                        place_front = max(place_front, final_result[j]->place);
                    else if (final_result[j]->places[k] > teams[i].places[k])
                        place_behind = min(place_behind, final_result[j]->place);
                    else
                    {
                        if (teams[i].place == 0)
                            teams[i].place = final_result[j]->place;
                        else if (teams[i].place != final_result[j]->place)
                        {
                            flag = false;
                            break;
                        }
                    }
                if (teams[i].place > 0)
                {
                    if (flag)
                        final_result.push_back(&teams[i]);
                }
                else if (place_front < place_behind)
                {
                    teams[i].place = place_front;
                    teams[i].place_offset = teams[i].places[k];
                    final_result.push_back(&teams[i]);
                }
            }
        sort(final_result.begin(), final_result.end(), Team::cmp_place);
        // assign result table
        vector<vi> final_result_table;
        vi result(1, final_result[0]->id);
        for (int i = 1; i < final_result.size(); ++i)
        {
            if (final_result[i]->place != final_result[i - 1]->place ||
                final_result[i]->place_offset != final_result[i - 1]->place_offset)
            {
                final_result_table.push_back(result);
                result.clear();
            }
            result.push_back(final_result[i]->id);
        }
        final_result_table.push_back(result);
        return final_result_table;
    }
};

int main()
{
    vector<vi> result_tables[2];
    for (int k = 0; k < 2; ++k)
    {
        int n;
        cin >> n;
        string line;
        getline(cin, line);
        for (int i = 0; i < n; ++i)
        {
            getline(cin, line);
            stringstream ss(line);
            vi result;
            int x;
            while (ss >> x)
                result.push_back(x);
            result_tables[k].push_back(result);
        }
    }
    vector<vi> final_result_table = Solution().solve(result_tables);
    for (int i = 0; i < final_result_table.size(); ++i)
    {
        cout << final_result_table[i][0];
        for (int j = 1; j < final_result_table[i].size(); ++j)
            cout << " " << final_result_table[i][j];
        cout << endl;
    }
    return 0;
}
