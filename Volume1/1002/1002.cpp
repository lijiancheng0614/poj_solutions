#include <iostream>
#include <string>
#include <map>
using namespace std;

int convert_to_tel(string s)
{
    int t = 0;
    for (int i = 0; i < s.length(); ++i)
        if (s[i] >= '0'&& s[i] <= '9')
            t = t * 10 + s[i] - '0';
        else if (s[i] >= 'A' && s[i] < 'Z')
            t = t * 10 + (s[i] - 'A' - (s[i] > 'Q')) / 3 + 2;
    return t;
}

void solve()
{
    int n;
    cin >> n;
    map<int, int> h;
    for (int i = 0; i < n; ++i)
    {
        string s;
        cin >> s;
        ++h[convert_to_tel(s)];
    }
    cout.fill('0');
    bool flag = true;
    for (map<int, int>::iterator it = h.begin(); it != h.end(); ++it)
        if (it->second > 1)
        {
            cout.width(3);
            cout << it->first / 10000;
            cout << "-";
            cout.width(4);
            cout << it->first % 10000;
            cout << " " << it->second << endl;
            flag = false;
        }
    if (flag)
        cout << "No duplicates." << endl;
}

int main()
{
    solve();
    return 0;
}
