#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
class Decoder
{
public:
    Decoder()
    {
        dictionary['A'] = ".-";
        dictionary['B'] = "-...";
        dictionary['C'] = "-.-.";
        dictionary['D'] = "-..";
        dictionary['E'] = ".";
        dictionary['F'] = "..-.";
        dictionary['G'] = "--.";
        dictionary['H'] = "....";
        dictionary['I'] = "..";
        dictionary['J'] = ".---";
        dictionary['K'] = "-.-";
        dictionary['L'] = ".-..";
        dictionary['M'] = "--";
        dictionary['N'] = "-.";
        dictionary['O'] = "---";
        dictionary['P'] = ".--.";
        dictionary['Q'] = "--.-";
        dictionary['R'] = ".-.";
        dictionary['S'] = "...";
        dictionary['T'] = "-";
        dictionary['U'] = "..-";
        dictionary['V'] = "...-";
        dictionary['W'] = ".--";
        dictionary['X'] = "-..-";
        dictionary['Y'] = "-.--";
        dictionary['Z'] = "--..";
        dictionary['_'] = "..--";
        dictionary['.'] = "---.";
        dictionary[','] = ".-.-";
        dictionary['?'] = "----";
    }
    string decode(string & message)
    {
        int n = message.length();
        string codes;
        vector<int> len;
        for (int i = 0; i < n; ++i)
        {
            string code = dictionary[message[i]];
            codes += code;
            len.push_back(code.length());
        }
        string ans;
        int k = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (map<char, string>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
                if (it->second == codes.substr(k, len[i]))
                {
                    ans += it->first;
                    break;
                }
            k += len[i];
        }
        return ans;
    }
private:
    map<char, string> dictionary;
};

int main()
{
    int n;
    cin >> n;
    Decoder decoder;
    for (int i = 0; i < n; ++i)
    {
        string message;
        cin >> message;
        cout << i + 1 << ": " << decoder.decode(message) << endl;
    }
    return 0;
}
