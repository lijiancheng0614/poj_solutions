#include <iostream>
#include <sstream>
#include <string>
using namespace std;
class Microprocessor
{
public:
    string execute(string memory)
    {
        char a = '0';
        char b = '0';
        for (int i = 0; i < memory.size(); ++i)
            if (memory[i] == '0')
            {
                a = memory[hex2dec(memory.substr(i + 1, 2))];
                i += 2;
            }
            else if (memory[i] == '1')
            {
                memory[hex2dec(memory.substr(i + 1, 2))] = a;
                i += 2;
            }
            else if (memory[i] == '2')
                swap(a, b);
            else if (memory[i] == '3')
            {
                int x = hex2dec(a);
                int y = hex2dec(b);
                a = dec2hex((x + y) % 16);
                b = dec2hex((x + y) / 16);
            }
            else if (memory[i] == '4')
            {
                if (a == 'F')
                    a = '0';
                else if (a == '9')
                    a = 'A';
                else
                    ++a;
            }
            else if (memory[i] == '5')
            {
                if (a == '0')
                    a = 'F';
                else if (a == 'A')
                    a = '9';
                else
                    --a;
            }
            else if (memory[i] == '6')
            {
                if (a == '0')
                    i = hex2dec(memory.substr(i + 1, 2)) - 1;
                else
                    i += 2;
            }
            else if (memory[i] == '7')
                i = hex2dec(memory.substr(i + 1, 2)) - 1;
            else if (memory[i] == '8')
                break;
        return memory;
    }
private:
    int hex2dec(string x)
    {
        int n;
        stringstream(x) >> hex >> n;
        return n;
    }
    int hex2dec(char x)
    {
        return x >= '0' && x <= '9' ? x - '0' : x - 'A' + 10;
    }
    char dec2hex(int x)
    {
        return x >= 10 ? x - 10 + 'A' : x + '0';
    }
};

int main()
{
    string memory;
    Microprocessor microprocessor;
    while (cin >> memory && memory[0] != '8')
        cout << microprocessor.execute(memory) << endl;
    return 0;
}
