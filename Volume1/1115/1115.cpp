#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
using namespace std;
typedef pair<char, string> Answer;
class Question
{
public:
    string code;
    string name;
    vector<Answer> answers;
    map<char, int> answers_id;
};
class Survey
{
public:
    void print_table(int q1, int q2, vector<Question> & questions,
                     const vector<string> & answers)
    {
        int n1 = questions[q1].answers.size();
        int n2 = questions[q2].answers.size();
        int a[n1 + 1][n2 + 1];
        memset(a, 0, sizeof(a));
        for (int i = 0; i < answers.size(); ++i)
        {
            int x = questions[q1].answers_id[answers[i][q1]];
            int y = questions[q2].answers_id[answers[i][q2]];
            ++a[x][y];
        }
        for (int i = 0; i < n1; ++i)
            for (int j = 0; j < n2; ++j)
            {
                a[i][n2] += a[i][j];
                a[n1][j] += a[i][j];
            }
        a[n1][n2] = answers.size();
        int row_percent[n1 + 1][n2 + 1], col_percent[n1 + 1][n2 + 1];
        for (int i = 0; i <= n1; ++i)
            if (a[i][n2] == 0)
                for (int j = 0; j <= n2; ++j)
                    row_percent[i][j] = -1;
            else
            {
                row_percent[i][n2] = 100;
                bool has_fraction[n2];
                memset(has_fraction, 0, sizeof(has_fraction));
                int left = 100;
                for (int j = 0; j < n2; ++j)
                {
                    row_percent[i][j] = a[i][j] * 100 / a[i][n2];
                    has_fraction[j] = a[i][j] * 100 % a[i][n2] != 0;
                    left -= row_percent[i][j];
                }
                for (int j = 0; j < n2 && left; ++j)
                    if (has_fraction[j])
                    {
                        ++row_percent[i][j];
                        --left;
                    }
            }
        for (int j = 0; j <= n2; ++j)
            if (a[n1][j] == 0)
                for (int i = 0; i <= n1; ++i)
                    col_percent[i][j] = -1;
            else
            {
                col_percent[n1][j] = 100;
                bool has_fraction[n1];
                memset(has_fraction, 0, sizeof(has_fraction));
                int left = 100;
                for (int i = 0; i < n1; ++i)
                {
                    col_percent[i][j] = a[i][j] * 100 / a[n1][j];
                    has_fraction[i] = a[i][j] * 100 % a[n1][j] != 0;
                    left -= col_percent[i][j];
                }
                for (int i = 0; i < n1 && left; ++i)
                    if (has_fraction[i])
                    {
                        ++col_percent[i][j];
                        --left;
                    }
            }
        string code1 = questions[q1].code;
        string code2 = questions[q2].code;
        cout << "      ";
        for (int j = 0; j < n2; ++j)
            cout << " " << code2 << ":" << questions[q2].answers[j].first;
        cout << " TOTAL" << endl;
        for (int i = 0; i <= n1; ++i)
        {
            if (i >= n1)
                cout << " TOTAL";
            else
                cout << " " << code1 << ":" << questions[q1].answers[i].first;
            for (int j = 0; j <= n2; ++j)
                cout << setw(6) << setfill(' ') << a[i][j];
            cout << endl;
            cout << "      ";
            for (int j = 0; j <= n2; ++j)
                if (row_percent[i][j] == -1)
                    cout << "     -";
                else
                    cout << setw(5) << setfill(' ') << row_percent[i][j] << "%";
            cout << endl;
            cout << "      ";
            for (int j = 0; j <= n2; ++j)
                if (col_percent[i][j] == -1)
                    cout << "     -";
                else
                    cout << setw(5) << setfill(' ') << col_percent[i][j] << "%";
            cout << endl;
        }
    }
};

ostream & operator<<(ostream & out, const Question & q)
{
    out << q.code << " " << q.name << endl;
    for (int i = 0; i < q.answers.size(); ++i)
        out << " " << q.answers[i].first << " " << q.answers[i].second << endl;
    return out;
}

int main()
{
    ios::sync_with_stdio(false);
    string survey_name;
    getline(cin, survey_name);
    string line;
    vector<Question> questions;
    map<string, int> questions_id;
    vector<string> answers;
    for (getline(cin, line); line != "#"; getline(cin, line))
    {
        if (line[0] == ' ')
        {
            char code = line[1];
            questions.back().answers_id[code] = questions.back().answers.size();
            questions.back().answers.push_back(Answer(code, line.substr(3)));
        }
        else
        {
            Question question;
            question.code = line.substr(0, 3);
            question.name = line.substr(4);
            questions_id[question.code] = questions.size();
            questions.push_back(question);
        }
    }
    for (getline(cin, line); line != "#"; getline(cin, line))
        answers.push_back(line);
    for (getline(cin, line); line != "#"; getline(cin, line))
    {
        int q1 = questions_id[line.substr(0, 3)];
        int q2 = questions_id[line.substr(4, 3)];
        string query_name = line.substr(8);
        cout << survey_name << " - " << query_name << endl;
        cout << questions[q1] << questions[q2] << endl;
        Survey().print_table(q1, q2, questions, answers);
        cout << endl;
    }
    return 0;
}
