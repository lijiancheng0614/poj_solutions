#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
const int oo = 1 << 30;
typedef vector<int> vi;
class Solution
{
public:
    void solve(const vi & cost, const vi & state, const vi & sales, int cost_min, int cost_max)
    {
        int n = cost.size();
        int m = sales.size();
        int nn = 1 << n;
        double index_max = 0;
        int profit_max = -oo;
        int n_features_min = n;
        int n_customers_max = 0;
        int state_best = 0;
        int sales_total_best;
        int cost_total_best;
        for (int i = 1; i < nn; ++i)
        {
            int n_features = 0;
            int cost_total = 0;
            for (int j = 0; j < n; ++j)
                if ((i >> j) & 1)
                {
                    ++n_features;
                    cost_total += cost[j];
                }
            if (cost_total < cost_min || cost_total > cost_max)
                continue;
            int n_customers = 0;
            int sales_total = 0;
            for (int j = 0; j < m; ++j)
                if ((i & state[j]) == state[j])
                {
                    ++n_customers;
                    sales_total += sales[j];
                }
            double index = double(sales_total) / cost_total;
            int profit = sales_total - cost_total;
            if (index > index_max || (index == index_max && profit > profit_max) ||
                    (index == index_max && profit == profit_max && n_features < n_features_min) ||
                    (index == index_max && profit == profit_max && n_features == n_features_min && n_customers > n_customers_max))
            {
                state_best = i;
                index_max = index;
                profit_max = profit;
                n_features_min = n_features;
                n_customers_max = n_customers;
                sales_total_best = sales_total;
                cost_total_best = cost_total;
            }
        }
        cout << fixed << setprecision(3) << index_max << endl;
        cout << sales_total_best << endl;
        cout << cost_total_best << endl;
        for (int j = 0; j < n; ++j)
            if ((state_best >> j) & 1)
                cout << j + 1 << " ";
        cout << endl;
        for (int j = 0; j < m; ++j)
            if ((state_best & state[j]) == state[j])
                cout << j + 1 << " ";
        cout << endl;
    }
};

int main()
{
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; ++tt)
    {
        cout << "Feature Set " << tt << endl;
        int cost_min, cost_max, n, m;
        cin >> cost_min >> cost_max >> n >> m;
        vi cost(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> cost[i];
        vi state(m, 0), sales(m, 0);
        for (int i = 0; i < m; ++i)
        {
            int k;
            cin >> k;
            while (k--)
            {
                int x;
                cin >> x;
                state[i] += 1 << (x - 1);
            }
            cin >> sales[i];
        }
        Solution().solve(cost, state, sales, cost_min, cost_max);
    }
    return 0;
}
