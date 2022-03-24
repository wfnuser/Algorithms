#include<vector>

using namespace std;

class BIT {
    int n;
    vector<int> tr;

public:
    BIT(int n) {
        this->n = n;
        tr = vector<int>(n+1, 0);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int v) {
        for (int i = x; i <= n; i += lowbit(i)) {
            tr[i] += v;
        }
    } 

    int query(int x) {
        int res = 0;
        for (int i = x; i != 0; i -= lowbit(i)) {
            res += tr[i];
        }
        return res;
    }
};