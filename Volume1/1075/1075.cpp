#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class Student
{
public:
    int region;
    int score;
    vector<int> universities;
};
class University
{
public:
    int region;
    int capacity;
    int get_rule_score(const Student & student)
    {
        return student.score * (student.region == region ? 10 : 7);
    }
};
class Rule
{
public:
    Rule(int sid, int score) : sid(sid), score(score) {}
    int sid;
    int score;
    bool operator<(const Rule & b) const
    {
        return score > b.score;
    }
};
class Solution
{
public:
    vector<int> solve(vector<Student> & students, vector<University> & universities)
    {
        int n = students.size();
        int m = universities.size();
        vector<int> accepted_universities(n, -1);
        vector<int> applied_universities(n, 0);
        vector< priority_queue<Rule> > q_universities(m, priority_queue<Rule>());
        queue<int> q;
        for (int i = 0; i < n; ++i)
            if (students[i].universities.size() > 0)
                q.push(i);
        while (!q.empty())
        {
            int sid = q.front();
            q.pop();
            int uid = students[sid].universities[applied_universities[sid]];
            ++applied_universities[sid];
            q_universities[uid].push(Rule(sid, universities[uid].get_rule_score(students[sid])));
            accepted_universities[sid] = uid;
            if (q_universities[uid].size() > universities[uid].capacity)
            {
                Rule r = q_universities[uid].top();
                q_universities[uid].pop();
                accepted_universities[r.sid] = -1;
                if (applied_universities[r.sid] < students[r.sid].universities.size())
                    q.push(r.sid);
            }
        }
        return accepted_universities;
    }
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<Student> students;
        while (n--)
        {
            Student student;
            int k;
            cin >> student.region >> student.score >> k;
            while (k--)
            {
                int uid;
                cin >> uid;
                student.universities.push_back(uid - 1);
            }
            students.push_back(student);
        }
        vector<University> universities;
        while (m--)
        {
            University university;
            cin >> university.region >> university.capacity;
            universities.push_back(university);
        }
        vector<int> accepted_universities = Solution().solve(students, universities);
        for (int i = 0; i < accepted_universities.size(); ++i)
            if (accepted_universities[i] < 0)
                cout << "not accepted" << endl;
            else
                cout << accepted_universities[i] + 1 << endl;
        cout << endl;
    }
    return 0;
}
