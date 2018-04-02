#include <iostream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
typedef set<int> si;
typedef vector<string> vs;
class compare_insensitive
{
public:
    bool operator()(const string & s1, const string & s2) const
    {
        int l1 = s1.length(), l2 = s2.length();
        for (int i = 0; i < l1 && i < l2; ++i)
        {
            char c1 = tolower(s1[i]), c2 = tolower(s2[i]);
            if (c1 < c2)
                return true;
            if (c1 > c2)
                return false;
        }
        return l1 < l2;
    }
};
class Primary
{
public:
    si pages;
    map<string, si, compare_insensitive> secondaries;
};
class Document
{
public:
    vs get_markers(const vs & lines)
    {
        page = 1;
        for (int i = 0; i < lines.size(); ++i)
            for (int j = 0; j < lines[i].length(); ++j)
                update(lines[i][j]);
        return get_markers();
    }
private:
    int page;
    bool in_index;
    string index_string;
    map<string, Primary, compare_insensitive> primaries;
    inline string to_string(int n)
    {
        stringstream ss;
        ss << n;
        return ss.str();
    }
    inline string trim(const string & s)
    {
        int l = s.find_first_not_of(' ');
        if (l == string::npos)
            return "";
        return s.substr(l, s.find_last_not_of(' ') - l + 1);
    }
    void update(char c)
    {
        if (c == '&')
            ++page;
        else if (c == '{')
        {
            in_index = true;
            index_string = "";
        }
        else if (c == '}')
        {
            in_index = false;
            index_string = trim(index_string);
            int mid1 = index_string.find_first_of('%');
            int mid2 = index_string.find_first_of('$');
            if (mid2 != string::npos)
            {
                string primary_string;
                if (mid1 != string::npos)
                    primary_string = trim(index_string.substr(mid1 + 1, mid2 - mid1 - 1));
                else
                    primary_string = trim(index_string.substr(0, mid2));
                index_string = trim(index_string.substr(mid2 + 1));
                primaries[primary_string].secondaries[index_string].insert(page);
            }
            else
            {
                if (mid1 != string::npos)
                    index_string = trim(index_string.substr(mid1 + 1));
                primaries[index_string].pages.insert(page);
            }
        }
        else if (in_index)
            index_string += c;
    }
    vs get_markers()
    {
        vs markers;
        for (map<string, Primary>::iterator it = primaries.begin(); it != primaries.end(); ++it)
        {
            Primary & primary = it->second;
            string line = it->first;
            for (si::iterator i = primary.pages.begin(); i != primary.pages.end(); ++i)
                line += ", " + to_string(*i);
            markers.push_back(line);
            for (map<string, si>::iterator it2 = primary.secondaries.begin(); it2 != primary.secondaries.end(); ++it2)
            {
                si & secondary = it2->second;
                line = "+ " + it2->first;
                for (si::iterator i = secondary.begin(); i != secondary.end(); ++i)
                    line += ", " + to_string(*i);
                markers.push_back(line);
            }
        }
        return markers;
    }
};

int main()
{
    int t = 0;
    while (true)
    {
        string line;
        getline(cin, line);
        if (line == "**")
            break;
        cout << "DOCUMENT " << ++t << endl;
        vs lines;
        while (line != "*")
        {
            lines.push_back(line);
            getline(cin, line);
        }
        vs markers = Document().get_markers(lines);
        for (int i = 0; i < markers.size(); ++i)
            cout << markers[i] << endl;
    }
    return 0;
}
