#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
class Image : vector<pii>
{
    friend istream& operator>>(istream &is, Image &image);
    friend ostream& operator<<(ostream &os, Image &image);
public:
    Image(int width = 0) : width(width), total(0) {}
    void setTotal(int _total)
    {
        total = _total;
    }
    Image detect_edge()
    {
        Image image_output(width);
        image_output.setTotal(total);
        for (int i = 0; i < size(); ++i)
        {
            int pos = (*this)[i].first;
            int row = pos / width;
            int col = pos % width;
            for (int y = max(row - 1, 0); y < row + 2; ++y)
                for (int x = max(col - 1, 0); x < col + 2; ++x)
                {
                    int pos2 = y * width + x;
                    if (pos2 >= total)
                        continue;
                    int value = calc_edge(pos2);
                    image_output.push_back(pii(pos2, value));
                }
        }
        int pos2 = total - width;
        int value = calc_edge(pos2);
        image_output.push_back(pii(pos2, value));
        sort(image_output.begin(), image_output.end());
        return image_output;
    }
private:
    int width, total;
    inline int get_value(int pos)
    {
        return (*this)[lower_bound(begin(), end(), pii(pos, 256)) - begin() - 1].second;
    }
    int calc_edge(int pos)
    {
        int value_max = 0;
        int row = pos / width;
        int col = pos % width;
        int value = get_value(pos);
        for (int y = max(row - 1, 0); y < row + 2; ++y)
            for (int x = max(col - 1, 0); x < min(col + 2, width); ++x)
            {
                int pos2 = y * width + x;
                if (pos2 >= total || pos2 == pos)
                    continue;
                int value2 = get_value(pos2);
                value_max = max(value_max, abs(value - value2));
            }
        return value_max;
    }
};

istream& operator>>(istream &is, Image &image)
{
    int value, length;
    int total = 0;
    while (is >> value >> length && length)
    {
        image.push_back(pii(total, value));
        total += length;
    }
    image.setTotal(total);
    return is;
}

ostream& operator<<(ostream &os, Image &image)
{
    os << image.width << endl;
    pii start = image[0];
    for (int i = 1; i < image.size(); ++i)
    {
        if (image[i].second == start.second)
            continue;
        os << start.second << " " << image[i].first - start.first << endl;
        start = image[i];
    }
    os << start.second << " " << image.total - start.first << endl;
    os << "0 0" << endl;
    return os;
}

int main()
{
    int width;
    while (cin >> width && width)
    {
        Image image(width);
        cin >> image;
        image = image.detect_edge();
        cout << image;
    }
    cout << "0" << endl;
    return 0;
}
